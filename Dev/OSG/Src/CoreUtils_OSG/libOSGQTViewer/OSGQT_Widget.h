#ifndef OSGQT_WIDGET_H
#define OSGQT_WIDGET_H

#include <QWidget>
#include <QTimer>
#include <osgViewer/Viewer>


namespace VR	{
	class OSGQT_Widget : public QWidget {
		Q_OBJECT

	public:
		OSGQT_Widget(QWidget * apQWidget = 0, Qt::WindowFlags f = false);

		virtual void paintEvent(QPaintEvent* event);
		virtual void timerEvent(QTimerEvent* event);

		void setSceneData(osg::Node* apNode);
		void setCameraManipulator(osgGA::CameraManipulator* manipulator, bool resetPosition = true);
		osgGA::CameraManipulator * getCameraManipulator();
		void addEventHandler(osgGA::GUIEventHandler *eventHandler);

	private:
		osgViewer::Viewer m_viewer;
		//QTimer            m_timer;
	};
}
#endif //OSGQT_WIDGET_H