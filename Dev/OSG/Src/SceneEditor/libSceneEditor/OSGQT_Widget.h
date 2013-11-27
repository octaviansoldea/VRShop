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

	void setSceneData(osg::Node* apNode);
	void setCameraManipulator(osgGA::CameraManipulator* manipulator, bool resetPosition = true);
	void addEventHandler(osgGA::GUIEventHandler *eventHandler);

	//int heightForWidth(int w) const;

private:
	osgViewer::Viewer m_viewer;
};
#endif //OSGQT_WIDGET_H