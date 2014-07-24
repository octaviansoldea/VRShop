#include <iostream>

#include <QMouseEvent>
#include <QHoverEvent>

#include <QEvent>

#include "VRQFrame.h"

using namespace VR;

VRQFrame::VRQFrame(QWidget * parent) :
QFrame(parent)	{
	setMouseTracking(true);
}

//=====================================================================

void VRQFrame::mouseMoveEvent(QMouseEvent *event)	{
	QFrame::mouseMoveEvent(event);

	int nEvent = event->type();

	if (nEvent == QEvent::MouseMove)	{
		emit hovered(true);
	}
}

//---------------------------------------------------------------------

void VRQFrame::leaveEvent (QEvent * event)	{
	QFrame::leaveEvent(event);

	emit hovered(false);
}