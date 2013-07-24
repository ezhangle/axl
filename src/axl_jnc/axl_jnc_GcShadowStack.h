#pragma once

#include "axl_jnc_Value.h"

namespace axl {
namespace jnc {

//.............................................................................

class CGcShadowStack : public llvm::GCStrategy
{
protected:
	struct TRoot
	{
		llvm::CallInst* m_pLlvmGcRoot;
		llvm::AllocaInst* m_pLlvmAlloca;
		llvm::Constant* m_pLlvmType;
	};

protected:
	CModule* m_pModule;

public:
	CGcShadowStack();

	virtual
	bool 
	initializeCustomLowering (llvm::Module& LlvmModule);
	
	virtual
	bool 
	performCustomLowering (llvm::Function& LlvmFunction);

private:
	size_t
	CollectRoots (
		CFunction* pFunction,
		rtl::CArrayT <TRoot>* pRootArray
		);

	bool
	GetFrameMap (
		CFunction* pFunction,
		TRoot* pRootArray,
		size_t RootCount,
		CValue* pResultValue
		);
};

//.............................................................................

void
RegisterGcShadowStack (int);

//.............................................................................

} // namespace axl 
} // namespace jnc 