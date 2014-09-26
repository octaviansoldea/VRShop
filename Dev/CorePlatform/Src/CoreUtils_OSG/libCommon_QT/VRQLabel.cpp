#include <QMouseEvent>
#include <QHoverEvent>

#include <QEvent>

#include "VRQLabel.h"

using namespace VR;

VRQLabel::VRQLabel(QWidget * parent, Qt::WindowFlags f)	: QLabel(parent,f)	{
	setMouseTracking(true);
}

//----------------------------------------------------------------------

VRQLabel::VRQLabel(const QString & text, QWidget * parent, Qt::WindowFlags f) : QLabel(text,parent,f)	{
	setMouseTracking(true);
}

//----------------------------------------------------------------------

VRQLabel::~VRQLabel()	{
}

//======================================================================

void VRQLabel::mousePressEvent(QMouseEvent * event)	{
	emit clicked();
}

//----------------------------------------------------------------------

void VRQLabel::mouseMoveEvent(QMouseEvent *event)	{
	QLabel::mouseMoveEvent(event);

	int nEvent = event->type();

	if (nEvent == QEvent::MouseMove)	{
		emit hovered(true);
	}
}

//---------------------------------------------------------------------

void VRQLabel::leaveEvent(QEvent * event)	{
	QLabel::leaveEvent(event);

	emit hovered(false);
}