#include "pch.h"
#include "axl_jnc_PropertyPtrType.h"
#include "axl_jnc_Module.h"

namespace axl {
namespace jnc {

//.............................................................................

const char*
GetPropertyPtrTypeKindString (EPropertyPtrType PtrTypeKind)
{
	static const char* StringTable [EPropertyPtrType__Count] = 
	{
		"closure",  // EPropertyPtrType_Normal = 0,
		"weak",     // EPropertyPtrType_Weak,
		"thin",     // EPropertyPtrType_Thin,
	};

	return (size_t) PtrTypeKind < EPropertyPtrType__Count ? 
		StringTable [PtrTypeKind] : 
		"undefined-property-ptr-kind";
}

//.............................................................................

CPropertyPtrType::CPropertyPtrType ()
{
	m_TypeKind = EType_PropertyPtr;
	m_PtrTypeKind = EPropertyPtrType_Normal;
	m_Size = sizeof (TPropertyPtr);
	m_pTargetType = NULL;
}

CStructType* 
CPropertyPtrType::GetPropertyPtrStructType ()
{
	return m_pModule->m_TypeMgr.GetPropertyPtrStructType (m_pTargetType);
}

rtl::CString
CPropertyPtrType::CreateSignature (
	CPropertyType* pPropertyType,
	EType TypeKind,
	EPropertyPtrType PtrTypeKind,
	uint_t Flags
	)
{
	rtl::CString Signature = TypeKind == EType_PropertyRef ? "RX" : "PX";

	switch (PtrTypeKind)
	{
	case EPropertyPtrType_Thin:
		Signature += 't';
		break;

	case EPropertyPtrType_Weak:
		Signature += 'w';
		break;
	}

	Signature += GetPtrTypeFlagSignature (Flags);
	Signature += pPropertyType->GetSignature ();
	return Signature;
}

void
CPropertyPtrType::PrepareTypeString ()
{
	m_TypeString = m_pTargetType->GetReturnType ()->GetTypeString ();
	m_TypeString += ' ';
	m_TypeString += m_pTargetType->GetTypeModifierString ();

	if (m_Flags & EPtrTypeFlag__AllMask)
	{
		m_TypeString += ' ';
		m_TypeString += GetPtrTypeFlagString (m_Flags);
	}

	if (m_PtrTypeKind != EPropertyPtrType_Normal)
	{
		m_TypeString += GetPropertyPtrTypeKindString (m_PtrTypeKind);
		m_TypeString += ' ';
	}

	m_TypeString += m_TypeKind == EType_PropertyRef ? "property&" : "property*";

	if (m_pTargetType->IsIndexed ())
	{
		m_TypeString += ' ';
		m_TypeString += m_pTargetType->GetGetterType ()->GetArgString ();
	}
}

void
CPropertyPtrType::PrepareLlvmType ()
{
	m_pLlvmType = 
		m_PtrTypeKind != EPropertyPtrType_Thin ? GetPropertyPtrStructType ()->GetLlvmType () : 
		m_pTargetType->GetVTableStructType ()->GetDataPtrType (EDataPtrType_Thin, EPtrTypeFlag_Unsafe)->GetLlvmType ();
}

//.............................................................................

} // namespace jnc {
} // namespace axl {