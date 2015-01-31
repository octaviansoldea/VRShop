#ifndef OSGQT_WIDGET_H
#define OSGQT_WIDGET_H

#include <QWidget>
#include <osgViewer/Viewer>


namespace VR	{
	class OSGQT_Widget : public QWidget {
	public:
		OSGQT_Widget(QWidget * apQWidget = 0, Qt::WindowFlags f = false);

		virtual void paintEvent(QPaintEvent* event);
		virtual void timerEvent(QTimerEvent* event);

		void setSceneData(osg::Node* apNode);
		osg::Node * getSceneData();

		void setCameraManipulator(osgGA::CameraManipulator* manipulator, bool resetPosition = true);
		osgGA::CameraManipulator * getCameraManipulator();
		void addEventHandler(osgGA::GUIEventHandler *eventHandler);

	private:
		osgViewer::Viewer m_viewer;
	};
}
#endif //OSGQT_WIDGET_H