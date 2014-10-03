// This file is part of AXL (R) Library
// Tibbo Technology Inc (C) 2004-2014. All rights reserved
// Author: Vladimir Gladkov

#pragma once

#define _AXL_GUI_QTWIDGET_H

#include "axl_gui_Engine.h"
#include "axl_gui_Widget.h"
#include "axl_gui_QtCanvas.h"
#include "axl_gui_QtCursor.h"
#include "axl_err_Error.h"

namespace axl {
namespace gui {

class QtEngine;
class QtWidgetBase;

QtEngine*
getQtEngineSingleton ();

//.............................................................................

class QtNotifyEvent: public QEvent
{
public:
	enum
	{
		QtEventType = QEvent::User + 0x200, // reserve 512 codes just in case
	};

public:
	QtNotifyEvent (
		uint_t code,
		const void* params
		): QEvent ((QEvent::Type) QtEventType)
	{
		m_code = code;
		m_params = params;
	}

	uint_t code ()
	{
		return m_code;
	}

	const void* params ()
	{
		return m_params;
	}

private:
	uint_t m_code;
	const void* m_params;
};

//.............................................................................

class QtWidgetEventHandler: public Widget
{
public:
	// this class is needed to get access to protected members in CWidget
	// also to put part of implementation into .cpp instead of having one huge CQtWidgetT <>

	static
	MouseButton
	getMouseButtonFromQtButton (Qt::MouseButton qtButton)
	{
		return (MouseButton) (qtButton & 0x7);
	}

	static
	uint_t
	getMouseButtonsFromQtButtons (int qtButtons)
	{
		return qtButtons & 0x7;
	}

	static
	uint_t
	getModifierKeysFromQtModifiers (int qtModifiers)
	{
		return (qtModifiers >> 25) & 0x7;
	}

	void
	onEvent (
		QEvent* event,
		WidgetMsgCode msgCode
		);

	void
	onMouseEvent (
		QMouseEvent* event,
		WidgetMsgCode msgCode
		);

	void
	onMouseWheelEvent (QWheelEvent* event);

	void
	onKeyEvent (
		QKeyEvent* event,
		WidgetMsgCode msgCode
		);

	void
	onPaintEvent (
		QPaintEvent* event,
		QPainter* qtPainter
		);

	void
	onResizeEvent (QResizeEvent* event);

	void
	onScroll (
		QScrollBar* verticalScrollBar,
		QScrollBar* horizontalScrollBar
		);
};

//.............................................................................

// use QT naming conventions in this portion

class QtWidgetBase: public QAbstractScrollArea
{
	Q_OBJECT

protected:
	QtWidgetEventHandler* m_qtWidget;
	bool m_mouseMoveEventFlag;

public:
	QtWidgetBase (
		QtWidgetEventHandler* qtWidget,
		QWidget* parent
		):
		QAbstractScrollArea (parent)
	{
		m_qtWidget = qtWidget;
		m_mouseMoveEventFlag = false;

		connect(
			this, &QtWidgetBase::threadMsgSignal,
			this, &QtWidgetBase::threadMsgSlot,
			Qt::QueuedConnection
			);
	}

	void
	postThreadMsg (
		uint_t code,
		const ref::Ptr <void>& params
		)
	{
		WidgetThreadMsg* msg = AXL_MEM_NEW (WidgetThreadMsg);
		msg->m_msgCode = WidgetMsgCode_ThreadMsg;
		msg->m_code = code;
		msg->m_params = params;

		emit threadMsgSignal (msg);
	}

private slots:
	void threadMsgSlot (WidgetThreadMsg* msg)
	{
		bool isHandled = true;
		m_qtWidget->processWidgetMsg (msg, &isHandled);
		AXL_MEM_DELETE (msg);
	}

signals:
	void threadMsgSignal (WidgetThreadMsg* msg);

public:
	virtual
	bool
	event (QEvent* e)
	{
		if (e->type () != (QEvent::Type) QtNotifyEvent::QtEventType)
			return QAbstractScrollArea::event (e);

		notifyEvent ((QtNotifyEvent*) e);
		return e->isAccepted ();
	}

protected:
	virtual
	void
	notifyEvent (QtNotifyEvent* e)
	{
	}

	virtual
	void
	mousePressEvent (QMouseEvent* e)
	{
		m_qtWidget->onMouseEvent (e, WidgetMsgCode_MouseButtonDown);
	}

	virtual
	void
	mouseReleaseEvent (QMouseEvent* e)
	{
		m_qtWidget->onMouseEvent (e, WidgetMsgCode_MouseButtonUp);
	}

	virtual
	void
	mouseDoubleClickEvent (QMouseEvent* e)
	{
		m_qtWidget->onMouseEvent (e, WidgetMsgCode_MouseButtonDoubleClick);
	}

	virtual
	void
	mouseMoveEvent (QMouseEvent* e);

	virtual
	void
	wheelEvent (QWheelEvent* e)
	{
		m_qtWidget->onMouseWheelEvent (e);
	}

	virtual
	void
	keyPressEvent (QKeyEvent* e)
	{
		m_qtWidget->onKeyEvent (e, WidgetMsgCode_KeyDown);
	}

	virtual
	void
	keyReleaseEvent (QKeyEvent* e)
	{
		m_qtWidget->onKeyEvent (e, WidgetMsgCode_KeyUp);
	}

	virtual
	void
	focusInEvent (QFocusEvent* e)
	{
		m_qtWidget->onEvent (e, WidgetMsgCode_SetFocus);
	}

	virtual
	void
	focusOutEvent (QFocusEvent* e)
	{
		m_qtWidget->onEvent (e, WidgetMsgCode_KillFocus);
	}

	virtual
	void
	leaveEvent (QEvent* e)
	{
		m_qtWidget->onEvent (e, WidgetMsgCode_MouseLeave);
	}

	virtual
	void
	paintEvent (QPaintEvent* e)
	{
		QPainter painter (viewport ());
		m_qtWidget->onPaintEvent (e, &painter);
	}

	virtual
	void
	resizeEvent (QResizeEvent* e)
	{
		m_qtWidget->onResizeEvent (e);
	}

	virtual
	void
	closeEvent (QCloseEvent* e)
	{
		m_qtWidget->onEvent (e, WidgetMsgCode_Close);
	}

	virtual
	void
	scrollContentsBy (
		int dx,
		int dy
		)
	{
		m_qtWidget->onScroll (
			dy ? verticalScrollBar () : NULL,
			dx ? horizontalScrollBar () : NULL
			);
	}
};

//.............................................................................

template <typename T>
class QtWidgetImpl: public T
{
	friend class QtEngine;

public:
	QtWidgetBase* m_qtScrollArea;
	QWidget* m_qtWidget;
	bool m_mouseMoveFlag;

public:
	QtWidgetImpl (): T (getQtEngineSingleton ())
	{
		m_qtScrollArea = NULL;
		m_qtWidget = NULL;
		m_mouseMoveFlag = false;
	}

	virtual
	ref::Ptr <Canvas>
	getCanvas ()
	{
		ref::Ptr <QtCanvas> canvas = AXL_REF_NEW (ref::Box <QtCanvas>);
		canvas->attach (new QPainter (m_qtScrollArea->viewport ()));
		return canvas;
	}

	virtual
	bool
	redraw (
		int left,
		int top,
		int right,
		int bottom
		)
	{
		if (left == right || top == bottom)
			m_qtWidget->update ();
		else
			m_qtWidget->update (left, top, right - left, bottom - top);

		return true;
	}

	virtual
	bool
	isFocused ()
	{
		return m_qtWidget->hasFocus ();
	}

	virtual
	bool
	setFocus ()
	{
		m_qtWidget->setFocus ();
		return true;
	}

	virtual
	bool
	setCursor (Cursor* cursor)
	{
		ASSERT (cursor->getEngine ()->getEngineKind () == EngineKind_Qt);
		m_qtWidget->setCursor (((QtCursor*) cursor)->m_qtCursor);
		this->m_cursor = cursor;
		return true;
	}

	virtual
	bool
	setMouseCapture ()
	{
		m_qtWidget->grabMouse ();
		return true;
	}

	virtual
	bool
	releaseMouseCapture ()
	{
		m_qtWidget->releaseMouse ();
		return true;
	}

	virtual
	bool
	updateScrollBar (WidgetOrientation orientation)
	{
		ASSERT (orientation < WidgetOrientation__Count);

		const WidgetScrollBar* scrollBar = &this->m_scrollBarArray [orientation];

		QScrollBar* qtScrollBar = orientation == WidgetOrientation_Horizontal ?
			m_qtScrollArea->horizontalScrollBar () :
			m_qtScrollArea->verticalScrollBar ();

		size_t maximum = scrollBar->m_page < scrollBar->m_end ?
			scrollBar->m_end - scrollBar->m_page :
			0;

		qtScrollBar->setPageStep (scrollBar->m_page);
		qtScrollBar->setMaximum (maximum);
		qtScrollBar->setValue (scrollBar->m_pos);
		return true;
	}

	virtual
	intptr_t
	notifyParent (
		intptr_t notifyCode,
		void* param = NULL
		)
	{
		QtNotifyEvent e (notifyCode, param);
		return m_qtScrollArea->event (&e);
	}

	virtual
	void
	postThreadMsg (
		uint_t code,
		const ref::Ptr <void>& params
		)
	{
		m_qtScrollArea->postThreadMsg (code, params);
	}
};

//. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

template <typename T>
class QtWidget: public QtWidgetBase
{
protected:
	QtWidgetImpl <T> m_widget;

public:
	QtWidget (QWidget* parent = 0):
		QtWidgetBase ((QtWidgetEventHandler*) (Widget*) &m_widget, parent)
	{
		m_widget.m_qtScrollArea = this;
		m_widget.m_qtWidget = viewport ();
		m_widget.m_qtWidget->setMouseTracking (true);
	}

	T*
	operator -> ()
	{
		return &m_widget;
	}

	T*
	w ()
	{
		return &m_widget;
	}
};

//.............................................................................

} // namespace gui
} // namespace axl
