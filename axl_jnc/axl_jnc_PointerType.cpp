#include "stdafx.h"
#include "axl_jnc_PointerType.h"
#include "axl_jnc_Module.h"

namespace axl {
namespace jnc {

//.............................................................................

llvm::Type* 
CPointerType::GetLlvmType ()
{
	if (m_pLlvmType)
		return m_pLlvmType;

	if (m_TypeKind == EType_Pointer_u || m_TypeKind == EType_Reference_u)
	{
		m_pLlvmType = llvm::PointerType::get (m_pBaseType->GetLlvmType (), 0);
		return m_pLlvmType;
	}

	llvm::Type* LlvmTypeArray [] =
	{
		llvm::PointerType::get (m_pBaseType->GetLlvmType (), 0),
		m_pModule->m_TypeMgr.GetStdType (EStdType_SafePtrValidator)->GetLlvmType (),
	};

	m_pLlvmType = llvm::StructType::get (
		llvm::getGlobalContext (), 
		llvm::ArrayRef <llvm::Type*> (LlvmTypeArray, countof (LlvmTypeArray)),
		true
		);

	return m_pLlvmType;
}

CStructType* 
CPointerType::GetPointerStructType ()
{
	if (m_pPointerStructType)
		return m_pPointerStructType;

	m_pPointerStructType = m_pModule->m_TypeMgr.CreateUnnamedStructType ();
	m_pPointerStructType->m_Tag.Format (_T("ptr %s"), GetTypeString ());
	m_pPointerStructType->CreateMember (m_pBaseType->GetPointerType (EType_Pointer_u));
	m_pPointerStructType->CreateMember (m_pModule->m_TypeMgr.GetStdType (EStdType_SafePtrValidator));
	m_pPointerStructType->CalcLayout ();

	return m_pPointerStructType;
}

//.............................................................................

} // namespace axl {
} // namespace jnc {
