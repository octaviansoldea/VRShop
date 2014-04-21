#include "VRQFrame.h"

using namespace VR;

VRQFrame::VRQFrame(QWidget * parent) :
QFrame(parent)	{
	setMouseTracking(true);
}

//=====================================================================

void VRQFrame::mouseMoveEvent(QMouseEvent *event)	{
	QFrame::mouseMoveEvent(event);
	emit hovered();
}