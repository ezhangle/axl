// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2013. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#define _AXL_LOG_REPRESENT_H

#include "axl_log_MergeCriteria.h"
#include "axl_log_Line.h"
#include "axl_obj_Root.h"
#include "axl_rtl_Array.h"

namespace axl {
namespace log {

//.............................................................................

enum EPart
{
	EPart_PlainText = 0,
	EPart_HyperText,
	EPart_Bin,
}; 

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

inline
ELine 
GetLineKindFromPartKind (
	EPart PartKind,
	EBinView BinViewKind
	)
{
	return 
		PartKind != EPart_Bin ? ELine_Text : 
		BinViewKind == EBinView_Text ? ELine_BinText : ELine_BinHex;
}

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

inline
ELine 
GetLineKindFromPartKind (
	EPart PartKind,
	const TBinDataConfig& BinDataConfig
	)
{
	return GetLineKindFromPartKind (PartKind, (EBinView) BinDataConfig.m_BinViewKind);
}

//.............................................................................

struct IRepresentorTarget: public obj::IRoot
{
	// {B33CEBA8-20EB-4EE5-ACE6-7AEA28C4EE0E}
	AXL_OBJ_INTERFACE (
		IRepresentorTarget,
		0xb33ceba8, 0x20eb, 0x4ee5, 0xac, 0xe6, 0x7a, 0xea, 0x28, 0xc4, 0xee, 0x0e
		)

protected:
	uint_t m_PacketCode;
	uint64_t m_Timestamp;

public:
	TBinDataConfig m_BinDataConfig;
	TLineAttr m_LineAttr;
	
public:
	IRepresentorTarget ()
	{
		m_PacketCode = 0;
		m_Timestamp = 0;
	}

	virtual 
	void 
	AddPart (
		EPart PartKind,
		uint_t PartCode,
		uint_t MergeFlags,
		const void* p,
		size_t Size
		) = 0;

	virtual 
	void 
	Break () = 0;

	void
	AddPlainText0 (
		const char* pText,
		size_t Length = -1
		)
	{
		AddText0 (
			EPart_PlainText, 
			m_PacketCode, 
			GetMergeFlagsFromPacketCode (m_PacketCode), 
			pText, 
			Length
			);
	}

	void
	AddPlainText0 (
		uint_t MergeFlags,
		const char* pText,
		size_t Length = -1
		)
	{
		AddText0 (
			EPart_PlainText, 
			m_PacketCode, 
			MergeFlags, 
			pText, 
			Length
			);
	}

	void
	AddPlainText0 (
		uint_t PartCode,
		uint_t MergeFlags,
		const char* pText,
		size_t Length = -1
		)
	{
		AddText0 (
			EPart_PlainText, 
			PartCode, 
			MergeFlags, 
			pText, 
			Length
			);
	}

	void
	AddPlainText (
		const char* pFormat,
		...
		)
	{
		AXL_VA_DECL (va, pFormat);

		AddText_va (
			EPart_PlainText, 
			m_PacketCode, 
			GetMergeFlagsFromPacketCode (m_PacketCode), 
			pFormat, 
			va
			);
	}

	void
	AddPlainText (
		uint_t MergeFlags,
		const char* pFormat,
		...
		)
	{
		AXL_VA_DECL (va, pFormat);

		AddText_va (
			EPart_PlainText, 
			m_PacketCode, 
			MergeFlags, 
			pFormat, 
			va
			);
	}

	void
	AddPlainText (
		uint_t PartCode,
		uint_t MergeFlags,
		const char* pFormat,
		...
		)
	{
		AXL_VA_DECL (va, pFormat);

		AddText_va (
			EPart_PlainText, 
			PartCode, 
			MergeFlags, 
			pFormat, 
			va
			);
	}

	void
	AddPlainText_va (
		const char* pFormat,
		axl_va_list va
		)
	{
		AddText_va (
			EPart_PlainText, 
			m_PacketCode, 
			GetMergeFlagsFromPacketCode (m_PacketCode), 
			pFormat, 
			va
			);
	}

	void
	AddPlainText_va (
		uint_t MergeFlags,
		const char* pFormat,
		axl_va_list va
		)
	{
		AddText_va (
			EPart_PlainText, 
			m_PacketCode, 
			MergeFlags, 
			pFormat, 
			va
			);
	}

	void
	AddPlainText_va (
		uint_t PartCode,
		uint_t MergeFlags,
		const char* pFormat,
		axl_va_list va
		)
	{
		AddText_va (
			EPart_PlainText, 
			PartCode, 
			MergeFlags, 
			pFormat, 
			va
			);
	}

	void
	AddHyperText0 (
		const char* pText,
		size_t Length = -1
		)
	{
		AddText0 (
			EPart_HyperText, 
			m_PacketCode, 
			GetMergeFlagsFromPacketCode (m_PacketCode), 
			pText, 
			Length
			);
	}

	void
	AddHyperText0 (
		uint_t MergeFlags,
		const char* pText,
		size_t Length = -1
		)
	{
		AddText0 (
			EPart_HyperText, 
			m_PacketCode, 
			MergeFlags, 
			pText, 
			Length
			);
	}

	void
	AddHyperText0 (
		uint_t PartCode,
		uint_t MergeFlags,
		const char* pText,
		size_t Length = -1
		)
	{
		AddText0 (
			EPart_HyperText, 
			PartCode, 
			MergeFlags, 
			pText, 
			Length
			);
	}

	void
	AddHyperText (
		const char* pFormat,
		...
		)
	{
		AXL_VA_DECL (va, pFormat);

		AddText_va (
			EPart_HyperText, 
			m_PacketCode, 
			GetMergeFlagsFromPacketCode (m_PacketCode), 
			pFormat, 
			va
			);
	}

	void
	AddHyperText (
		uint_t MergeFlags,
		const char* pFormat,
		...
		)
	{
		AXL_VA_DECL (va, pFormat);

		AddText_va (
			EPart_HyperText, 
			m_PacketCode, 
			MergeFlags, 
			pFormat, 
			va
			);
	}

	void
	AddHyperText (
		uint_t PartCode,
		uint_t MergeFlags,
		const char* pFormat,
		...
		)
	{
		AXL_VA_DECL (va, pFormat);

		AddText_va (
			EPart_HyperText, 
			PartCode, 
			MergeFlags, 
			pFormat, 
			va
			);
	}

	void
	AddHyperText_va (
		const char* pFormat,
		axl_va_list va
		)
	{
		AddText_va (
			EPart_HyperText, 
			m_PacketCode, 
			GetMergeFlagsFromPacketCode (m_PacketCode), 
			pFormat, 
			va
			);
	}

	void
	AddHyperText_va (
		uint_t MergeFlags,
		const char* pFormat,
		axl_va_list va
		)
	{
		AddText_va (
			EPart_HyperText, 
			m_PacketCode, 
			MergeFlags, 
			pFormat, 
			va
			);
	}

	void
	AddHyperText_va (
		uint_t PartCode,
		uint_t MergeFlags,
		const char* pFormat,
		axl_va_list va
		)
	{
		AddText_va (
			EPart_HyperText, 
			PartCode, 
			MergeFlags, 
			pFormat, 
			va
			);
	}

	void
	AddBin (
		const void* p,
		size_t Size
		)
	{
		AddPart (
			EPart_Bin, 
			m_PacketCode, 
			GetMergeFlagsFromPacketCode (m_PacketCode), 
			p, 
			Size
			);
	}

	void
	AddBin (
		uint_t MergeFlags,
		const void* p,
		size_t Size
		)
	{
		AddPart (
			EPart_Bin, 
			m_PacketCode, 
			MergeFlags, 
			p, 
			Size
			);
	}

	void
	AddBin (
		uint_t PartCode,
		uint_t MergeFlags,
		const void* p,
		size_t Size
		)
	{
		AddPart (
			EPart_Bin, 
			PartCode, 
			MergeFlags, 
			p, 
			Size
			);
	}

protected:
	void
	AddText0 (
		EPart PartKind,
		uint_t PartCode,
		uint_t MergeFlags,
		const char* pText,
		size_t Length
		);

	void
	AddText_va (
		EPart PartKind,
		uint_t PartCode,
		uint_t MergeFlags,
		const char* pFormat,
		axl_va_list va
		);
};

//.............................................................................

struct IRepresentor: public obj::IRoot
{
	// {037B9FE2-66CA-4628-B15F-AA867BBF62AE}
	AXL_OBJ_INTERFACE (
		IRepresentor,
		0x037b9fe2, 0x66ca, 0x4628, 0xb1, 0x5f, 0xaa, 0x86, 0x7b, 0xbf, 0x62, 0xae
		)

	virtual 
	bool 
	Represent (
		IRepresentorTarget* pTarget, 
		uint_t PacketCode, 
		const void* p, 
		size_t Size, 
		uint_t VolatileFlags
		) = 0;
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

class CRepresentorStack: 
	public IRepresentor,
	public rtl::CArrayT <IRepresentor*>
{
public:
	virtual 
	bool 
	Represent (
		IRepresentorTarget* pTarget, 
		uint_t PacketCode, 
		const void* p, 
		size_t Size, 
		uint_t VolatileFlags
		);
};

//.............................................................................

} // namespace log 
} // namespace axl