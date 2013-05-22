#ifndef _LLVMIR_H
#define _LLVMIR_H

#include "editor.h"
#include "../../axl_jnc/axl_jnc_Parser.llk.h"

class LlvmIrHighlighter;

#define LlvmIrBase Editor

class LlvmIr : public LlvmIrBase
{
	Q_OBJECT

public:
	LlvmIr(QWidget *parent);
	
	QSize sizeHint() const { return QSize(300, 50); }	
	bool build(jnc::CModule *module);

private:
	void setupHighlighter();

	LlvmIrHighlighter *highlighter;
};

#endif