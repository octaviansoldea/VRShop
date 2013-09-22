#ifndef OSGQT_WIDGET_H
#define OSGQT_WIDGET_H

#include <QWidget>

#include <osgViewer/Viewer>

class OSGQT_Widget : public QWidget {
	Q_OBJECT

public:
	OSGQT_Widget(QWidget * apQWidget = 0, Qt::WindowFlags f = false);

	virtual void paintEvent(QPaintEvent* event);
	virtual void timerEvent(QTimerEvent* event);

	// Set the scene graph that the View will use.
	void setSceneData(osg::Node* apNode);

	// Set the CameraManipulator that moves the View's master Camera position in response to events.
	// The parameter resetPosition determines whether manipulator is set to its home position.
	void setCameraManipulator(osgGA::CameraManipulator* manipulator, bool resetPosition = true);

private:
	osgViewer::Viewer m_viewer;
};
#endif //OSGQT_WIDGET_H