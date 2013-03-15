#include "stdafx.h"
#include "axl_jnc_UnionType.h"
#include "axl_jnc_Module.h"

namespace axl {
namespace jnc {

//.............................................................................

CStructField*
CUnionType::CreateField (
	const rtl::CString& Name,
	CType* pType,
	size_t BitCount,
	int PtrTypeFlags
	)
{
	if (!(pType->GetFlags () & ETypeFlag_Pod))
	{
		err::SetFormatStringError (_T("non-POD '%s' cannot be union member"), pType->GetTypeString ());
		return NULL;
	}

	CStructField* pMember = AXL_MEM_NEW (CStructField);
	pMember->m_Name = Name;
	pMember->m_pParentType = this;
	pMember->m_pType = pType;
	pMember->m_PtrTypeFlags = PtrTypeFlags;
	pMember->m_pBitFieldBaseType = BitCount ? pType : NULL;
	pMember->m_BitCount = BitCount;
	m_FieldList.InsertTail (pMember);

	bool Result = AddItem (pMember);
	if (!Result)
		return NULL;

	return pMember;
}

bool
CUnionType::CalcLayout ()
{
	if (m_Flags & ETypeFlag_LayoutReady)
		return true;

	bool Result = PreCalcLayout ();
	if (!Result)
		return false;

	CType* pLargestMemberType = NULL;

	rtl::CIteratorT <CStructField> Member = m_FieldList.GetHead ();
	for (; Member; Member++)
	{
		CStructField* pMember = *Member;

		Result = pMember->m_pType->CalcLayout ();
		if (!Result)
			return false;

		if (pMember->m_BitCount)
		{
			pMember->m_pType = m_pModule->m_TypeMgr.GetBitFieldType (pMember->m_pBitFieldBaseType, 0, pMember->m_BitCount);
			if (!pMember->m_pType)
				return false;
		}

		if (!pLargestMemberType || pMember->m_pType->GetSize () > pLargestMemberType->GetSize ())
			pLargestMemberType = pMember->m_pType;
	}

	ASSERT (pLargestMemberType);

	m_pStructType = m_pModule->m_TypeMgr.CreateUnnamedStructType ();
	m_pStructType->m_Tag.Format (_T("%s.struct"), m_Tag);
	m_pStructType->CreateField (pLargestMemberType);
	Result = m_pStructType->CalcLayout ();
	if (!Result)
		return false;

	PostCalcLayout ();
	return true;
}

//.............................................................................

} // namespace jnc {
} // namespace axl {

