#include "stdafx.h"
#include "axl_pg_Node.h"
#include "axl_pg_ClassMgr.h"

namespace axl {
namespace pg {

//.............................................................................

CNode::CNode ()
{
	m_Kind = ENode_Undefined;
	m_Index = -1;
	m_MasterIndex = -1;
	m_Flags = 0;
}

void
CNode::Trace ()
{
	printf ("%s\n", m_Name);
}

bool
CNode::MarkReachable ()
{
	if (m_Flags & ENodeFlag_IsReachable)
		return false;

	m_Flags |= ENodeFlag_IsReachable;
	return true;
}

//.............................................................................

void
CGrammarNode::Trace ()
{
	printf (
		"%s\n"
		"\t  FIRST:  %s%s\n"
		"\t  FOLLOW: %s%s\n", 
		m_Name,
		NodeArrayToString (&m_FirstArray), IsNullable () ? " <eps>" : "",
		NodeArrayToString (&m_FollowArray), IsFinal () ? " $" : ""
		);
}

bool
CGrammarNode::MarkNullable ()
{
	if (IsNullable ())
		return false;

	m_Flags |= EGrammarNodeFlag_IsNullable;
	return true;
}

bool
CGrammarNode::MarkFinal ()
{
	if (IsFinal ())
		return false;

	m_Flags |= EGrammarNodeFlag_IsFinal;
	return true;
}

void
CGrammarNode::ExportSrcPos (
	lua::CLuaState* pLuaState,
	const lex::CLineCol& LineCol
	)
{
	pLuaState->SetMemberString ("FilePath", m_SrcPos.m_FilePath);
	pLuaState->SetMemberInteger ("Line", LineCol.m_Line);
	pLuaState->SetMemberInteger ("Col", LineCol.m_Col);
}

//.............................................................................

CSymbolNode::CSymbolNode ()
{
	m_Kind = ENode_Symbol;
	m_CharToken = 0;
	m_pClass = NULL;
	m_pResolver = NULL;
	m_ResolverPriority = 0;
}

rtl::CString
CSymbolNode::GetArgName (size_t Index)
{
	ASSERT (Index < m_ArgNameList.GetCount ());

	rtl::CBoxIteratorT <rtl::CString> It = m_ArgNameList.GetHead ();
	for (size_t i = 0; i < Index; i++)
		It++;

	return *It;
}

void
CSymbolNode::AddProduction (CGrammarNode* pNode)
{
	if (pNode->m_Kind == ENode_Symbol && 
		!(pNode->m_Flags & ESymbolNodeFlag_IsNamed) && 
		!((CSymbolNode*) pNode)->m_pResolver)
		m_ProductionArray.Append (((CSymbolNode*) pNode)->m_ProductionArray); // merge temp symbol productions
	else
		m_ProductionArray.Append (pNode);
}

bool
CSymbolNode::MarkReachable ()
{
	if (!CNode::MarkReachable ())
		return false;

	if (m_pResolver)
		m_pResolver->MarkReachable ();

	if (m_pClass)
		m_pClass->m_Flags |= EClassFlag_IsReachable;

	size_t Count = m_ProductionArray.GetCount ();
	for (size_t i = 0; i < Count; i++) 
	{
		CNode* pChild = m_ProductionArray [i];
		pChild->MarkReachable ();
	}

	return true;
}

void
CSymbolNode::Trace ()
{
	CGrammarNode::Trace ();

	if (m_Kind == ENode_Token)
		return;

	if (m_pResolver)
		printf ("\t  RSLVR:  %s\n", m_pResolver->m_Name);

	if (m_pClass)
		printf ("\t  CLASS:  %s\n", m_pClass->m_Name);		

	size_t ChildrenCount = m_ProductionArray.GetCount ();

	for (size_t i = 0; i < ChildrenCount; i++)
	{
		CNode* pChild = m_ProductionArray [i];		
		printf ("\t  -> %s\n", pChild->GetProductionString ());
	}
}

void
CSymbolNode::Export (lua::CLuaState* pLuaState)
{
	if (m_Kind == ENode_Token)
	{
		pLuaState->CreateTable (1);

		if (m_Flags & ESymbolNodeFlag_IsEofToken)
			pLuaState->SetMemberBoolean ("IsEofToken", true);
		else if (m_Flags & ESymbolNodeFlag_IsAnyToken)
			pLuaState->SetMemberBoolean ("IsAnyToken", true);
		else if (m_Flags & ESymbolNodeFlag_IsNamed)
			pLuaState->SetMemberString ("Name", m_Name);
		else 
			pLuaState->SetMemberInteger ("Token", m_CharToken);

		return;
	}

	pLuaState->CreateTable (0, 5);
	pLuaState->SetMemberString ("Name", m_Name);
	pLuaState->SetMemberBoolean ("IsCustom", !m_Arg.IsEmpty () || !m_Local.IsEmpty ());

	pLuaState->CreateTable (0, 3);
	ExportSrcPos (pLuaState, m_SrcPos);
	pLuaState->SetMember ("SrcPos");

	if (m_Flags & ESymbolNodeFlag_IsNoAst)
		pLuaState->SetMemberBoolean ("IsNoAst", true);
	else if (m_pClass)
		pLuaState->SetMemberString ("Class", m_pClass->m_Name);

	if (!m_Arg.IsEmpty ())
	{
		pLuaState->SetMemberString ("Arg", m_Arg);
		pLuaState->SetMemberInteger ("ArgLine", m_ArgLineCol.m_Line);
	}

	if (!m_Local.IsEmpty ())
	{
		pLuaState->SetMemberString ("Local", m_Local);
		pLuaState->SetMemberInteger ("LocalLine", m_LocalLineCol.m_Line);
	}

	if (!m_Enter.IsEmpty ())
	{
		pLuaState->SetMemberString ("Enter", m_Enter);
		pLuaState->SetMemberInteger ("EnterLine", m_EnterLineCol.m_Line);
	}

	if (!m_Leave.IsEmpty ())
	{
		pLuaState->SetMemberString ("Leave", m_Leave);
		pLuaState->SetMemberInteger ("LeaveLine", m_LeaveLineCol.m_Line);
	}

	pLuaState->CreateTable (m_ArgNameList.GetCount ());

	rtl::CBoxIteratorT <rtl::CString> It = m_ArgNameList.GetHead ();
	for (size_t i = 1; It; It++, i++)
		pLuaState->SetArrayElementString (i, *It);

	pLuaState->SetMember ("ArgNameTable");

	size_t ChildrenCount = m_ProductionArray.GetCount ();
	pLuaState->CreateTable (ChildrenCount);

	for (size_t i = 0; i < ChildrenCount; i++)
	{
		CNode* pChild = m_ProductionArray [i];
		pLuaState->SetArrayElementInteger (i + 1, pChild->m_MasterIndex);
	}

	pLuaState->SetMember ("ProductionTable");
}

//.............................................................................

CSequenceNode::CSequenceNode ()
{
	m_Kind = ENode_Sequence;
}

void
CSequenceNode::Append (CGrammarNode* pNode)
{
	if (pNode->m_Kind == ENode_Sequence) 
		m_Sequence.Append (((CSequenceNode*) pNode)->m_Sequence); // merge sequences
	else
		m_Sequence.Append (pNode);
}

bool
CSequenceNode::MarkReachable ()
{
	if (!CNode::MarkReachable ())
		return false;

	size_t Count = m_Sequence.GetCount ();
	for (size_t i = 0; i < Count; i++) 
	{
		CNode* pChild = m_Sequence [i];
		pChild->MarkReachable ();
	}

	return true;
}

void
CSequenceNode::Trace ()
{
	CGrammarNode::Trace ();
	printf ("\t  %s\n", NodeArrayToString (&m_Sequence));
}

void
CSequenceNode::Export (lua::CLuaState* pLuaState)
{
	pLuaState->CreateTable (0, 2);
	pLuaState->SetMemberString ("Name", m_Name);

	size_t Count = m_Sequence.GetCount ();
	pLuaState->CreateTable (Count);

	for (size_t j = 0; j < Count; j++)
	{
		CNode* pChild = m_Sequence [j];
		pLuaState->SetArrayElementInteger (j + 1, pChild->m_MasterIndex);
	}

	pLuaState->SetMember ("Sequence");
}

rtl::CString 
CSequenceNode::GetProductionString ()
{
	return rtl::CString::Format_s (_T("%s: %s"), m_Name, NodeArrayToString (&m_Sequence));
}

//.............................................................................

CUserNode::CUserNode ()
{
	m_Flags = EGrammarNodeFlag_IsNullable;
	m_pProductionSymbol = NULL;
	m_pDispatcher = NULL;
	m_pResolver = NULL;
}

//.............................................................................

CActionNode::CActionNode ()
{
	m_Kind = ENode_Action;
}

void
CActionNode::Trace ()
{
	printf (
		"%s\n"
		"\t  SYMBOL:     %s\n"
		"\t  DISPATCHER: %s\n"
		"\t  { %s }\n", 
		m_Name,
		m_pProductionSymbol->m_Name,
		m_pDispatcher ? m_pDispatcher->m_Name : "NONE",
		m_UserCode
		);
}

void
CActionNode::Export (lua::CLuaState* pLuaState)
{
	pLuaState->CreateTable (0, 2);

	if (m_pDispatcher)
	{
		pLuaState->GetGlobalArrayElement ("DispatcherTable", m_pDispatcher->m_Index + 1);
		pLuaState->SetMember ("Dispatcher");
	}

	pLuaState->GetGlobalArrayElement ("SymbolTable", m_pProductionSymbol->m_Index + 1);
	pLuaState->SetMember ("ProductionSymbol");

	pLuaState->SetMemberString ("UserCode", m_UserCode);

	pLuaState->CreateTable (0, 3);
	ExportSrcPos (pLuaState, m_SrcPos);
	pLuaState->SetMember ("SrcPos");
}

//.............................................................................

CArgumentNode::CArgumentNode ()
{
	m_Kind = ENode_Argument;
	m_pTargetSymbol = NULL;
}

void
CArgumentNode::Trace ()
{
	printf (
		"%s\n"
		"\t  SYMBOL: %s\n"
		"\t  DISPATCHER: %s\n"
		"\t  TARGET SYMBOL: %s\n"
		"\t  <",
		m_Name,
		m_pProductionSymbol->m_Name,
		m_pDispatcher ? m_pDispatcher->m_Name : "NONE",
		m_pTargetSymbol->m_Name
		);

	rtl::CBoxIteratorT <rtl::CString> It = m_ArgValueList.GetHead ();
	ASSERT (It); // empty argument should have been eliminated

	printf ("%s", *It);

	for (It++; It; It++)
		printf (", %s", *It);

	printf (">\n");
}

void
CArgumentNode::Export (lua::CLuaState* pLuaState)
{
	pLuaState->CreateTable (0, 3);

	if (m_pDispatcher)
	{
		pLuaState->GetGlobalArrayElement ("DispatcherTable", m_pDispatcher->m_Index + 1);
		pLuaState->SetMember ("Dispatcher");
	}

	pLuaState->GetGlobalArrayElement ("SymbolTable", m_pProductionSymbol->m_Index + 1);
	pLuaState->SetMember ("ProductionSymbol");
	pLuaState->GetGlobalArrayElement ("SymbolTable", m_pTargetSymbol->m_Index + 1);
	pLuaState->SetMember ("TargetSymbol");

	pLuaState->CreateTable (m_ArgValueList.GetCount ());

	rtl::CBoxIteratorT <rtl::CString> It = m_ArgValueList.GetHead ();
	ASSERT (It); // empty argument should have been eliminated

	for (size_t i = 1; It; It++, i++)
		pLuaState->SetArrayElementString (i, *It);

	pLuaState->SetMember ("ValueTable");

	pLuaState->CreateTable (0, 3);
	ExportSrcPos (pLuaState, m_SrcPos);
	pLuaState->SetMember ("SrcPos");
}

//.............................................................................

CBeaconNode::CBeaconNode ()
{
	m_Kind = ENode_Beacon;
	m_SlotIndex = -1;
	m_pTarget = NULL;
	m_pArgument = NULL;
	m_pResolver = NULL;
}

bool
CBeaconNode::MarkReachable ()
{
	if (!CNode::MarkReachable ())
		return false;

	m_pTarget->MarkReachable ();
	return true;
}

void
CBeaconNode::Trace ()
{
	ASSERT (m_pTarget);

	CGrammarNode::Trace ();

	printf (
		"\t  $%d => %s\n", 
		m_SlotIndex, 
		m_pTarget->m_Name
		);
}

void
CBeaconNode::Export (lua::CLuaState* pLuaState)
{
	pLuaState->CreateTable (0, 2);
	pLuaState->SetMemberInteger ("Slot", m_SlotIndex);
	pLuaState->SetMemberInteger ("Target", m_pTarget->m_MasterIndex);
}

//.............................................................................

void
CDispatcherNode::Trace ()
{
	ASSERT (m_pSymbol);

	printf (
		"%s\n"
		"\t  @ %s\n"
		"\t  %s\n",
		m_Name, 
		m_pSymbol->m_Name,
		NodeArrayToString (&m_BeaconArray)
		);		
}

void
CDispatcherNode::Export (lua::CLuaState* pLuaState)
{
	pLuaState->CreateTable (0, 3);

	pLuaState->GetGlobalArrayElement ("SymbolTable", m_pSymbol->m_Index + 1);
	pLuaState->SetMember ("Symbol");

	size_t BeaconCount = m_BeaconArray.GetCount ();
	pLuaState->CreateTable (BeaconCount);

	for (size_t j = 0; j < BeaconCount; j++)
	{
		CBeaconNode* pBeacon = m_BeaconArray [j];
		ASSERT (pBeacon->m_SlotIndex == j);

		pLuaState->CreateTable (1);
		if (pBeacon->m_pTarget->m_Kind == ENode_Symbol)
		{
			pLuaState->GetGlobalArrayElement ("SymbolTable", pBeacon->m_pTarget->m_Index + 1);
			pLuaState->SetMember ("Symbol");
		}

		pLuaState->SetArrayElement (j + 1);
	}

	pLuaState->SetMember ("BeaconTable");
}

//.............................................................................

CConflictNode::CConflictNode ()
{
	m_Kind = ENode_Conflict;
	m_pSymbol = NULL;
	m_pToken = NULL;
	m_pResultNode = NULL;
}

void
CConflictNode::Trace ()
{
	ASSERT (m_pSymbol);
	ASSERT (m_pToken);

	printf (
		"%s\n"
		"\t  on %s in %s\n"
		"\t  DFA:      %s\n"
		"\t  POSSIBLE:\n",
		m_Name,
		m_pToken->m_Name,
		m_pSymbol->m_Name, 
		m_pResultNode ? m_pResultNode->m_Name : "<none>"
		);

	size_t Count = m_ProductionArray.GetCount ();
	for (size_t i = 0; i < Count; i++)
	{
		CNode* pNode = m_ProductionArray [i];
		printf ("\t  \t-> %s\n", pNode->GetProductionString ());
	}
}

//.............................................................................

CLaDfaNode::CLaDfaNode ()
{
	m_Kind = ENode_LaDfa;
	m_pToken = NULL;
	m_pResolver = NULL;
	m_pResolverElse = NULL;
	m_pResolverUplink = NULL;
	m_pProduction = NULL;
}

void
CLaDfaNode::Trace ()
{
	printf (
		"%s%s\n", 
		m_Name, 
		(m_Flags & ELaDfaNodeFlag_IsLeaf) ? "*" : 
		(m_Flags & ELaDfaNodeFlag_IsResolved) ? "~" : ""
		);

	if (m_pResolver)
	{
		printf (
			"\t  if resolver (%s) %s\n"
			"\t  else %s\n",
			m_pResolver->m_Name,
			m_pProduction->GetProductionString (),
			m_pResolverElse->GetProductionString ()
			);
	}
	else
	{
		size_t Count = m_TransitionArray.GetCount ();
		for (size_t i = 0; i < Count; i++)
		{
			CLaDfaNode* pChild = m_TransitionArray [i];
			printf ("\t  %s -> %s\n", pChild->m_pToken->m_Name, pChild->GetProductionString ());
		}

		if (m_pProduction)
		{
			printf ("\t  . -> %s\n", m_pProduction->GetProductionString ());
		}
	}

	printf ("\n");
}

size_t
GetTransitionIndex (CNode* pNode)
{
	if (pNode->m_Kind != ENode_LaDfa || !(pNode->m_Flags & ELaDfaNodeFlag_IsLeaf))
		return pNode->m_MasterIndex;
	
	CLaDfaNode* pLaDfaNode = (CLaDfaNode*) pNode;
	ASSERT (pLaDfaNode->m_pProduction && pLaDfaNode->m_pProduction->m_Kind != ENode_LaDfa);
	return pLaDfaNode->m_pProduction->m_MasterIndex;
}

void
CLaDfaNode::ExportResolverMembers (lua::CLuaState* pLuaState)
{
	pLuaState->SetMemberString ("Name", m_Name);
	pLuaState->SetMemberInteger ("Resolver", m_pResolver->m_MasterIndex);
	pLuaState->SetMemberInteger ("Production", m_pProduction->m_MasterIndex);
	pLuaState->SetMemberInteger ("ResolverElse", GetTransitionIndex (m_pResolverElse));
	pLuaState->SetMemberBoolean ("HasChainedResolver", ((CLaDfaNode*) m_pResolverElse)->m_pResolver != NULL);
}

void
CLaDfaNode::Export (lua::CLuaState* pLuaState)
{
	ASSERT (!(m_Flags & ELaDfaNodeFlag_IsLeaf));

	if (m_pResolver)
	{
		pLuaState->CreateTable (0, 3);
		ExportResolverMembers (pLuaState);
		return;
	}

	size_t ChildrenCount = m_TransitionArray.GetCount ();
	ASSERT (ChildrenCount);

	pLuaState->CreateTable (0, 2);

	pLuaState->CreateTable (ChildrenCount);
			
	for (size_t i = 0; i < ChildrenCount; i++)
	{
		CLaDfaNode* pChild = m_TransitionArray [i];

		pLuaState->CreateTable (0, 4);

		pLuaState->GetGlobalArrayElement ("TokenTable", pChild->m_pToken->m_Index + 1);
		pLuaState->SetMember ("Token");

		if (pChild->m_pResolver)
			pChild->ExportResolverMembers (pLuaState);
		else
			pLuaState->SetMemberInteger ("Production", GetTransitionIndex (pChild));

		pLuaState->SetArrayElement (i + 1);
	}

	pLuaState->SetMember ("TransitionTable");

	if (m_pProduction)
		pLuaState->SetMemberInteger ("DefaultProduction", GetTransitionIndex (m_pProduction));
}

//.............................................................................

} // namespace pg {
} // namespace axl {
