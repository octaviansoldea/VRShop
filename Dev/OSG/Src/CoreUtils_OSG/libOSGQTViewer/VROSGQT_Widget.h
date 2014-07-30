#ifndef VR_OSGQT_WIDGET_H
#define VR_OSGQT_WIDGET_H

#include <osg/ref_ptr>
#include <osgViewer/Viewer>
#include <osgViewer/GraphicsWindow>

#include <QtOpenGL>
#include <QWidget>
#include <QTimer>

 

namespace VR	{
	class OSGQT_Widget : public QGLWidget	{
		Q_OBJECT

	public:
		OSGQT_Widget(
			QWidget* parent = 0,
			const QGLWidget* shareWidget = 0,
			Qt::WindowFlags f = 0
		);

		OSGQT_Widget(const QGLFormat & format, QWidget * parent, const QGLWidget * shareWidget, Qt::WindowFlags f);

		virtual ~OSGQT_Widget();
		
		osgViewer::GraphicsWindow* getGraphicsWindow() { return graphicsWindow_.get(); }
		const osgViewer::GraphicsWindow* getGraphicsWindow() const { return graphicsWindow_.get(); }


	protected:
		osgGA::GUIEventAdapter::KeySymbol qtKeyToOsg(QKeyEvent * e)const;
		void addModifiers(osg::ref_ptr<osgGA::EventQueue> eventQueue, Qt::KeyboardModifiers modifier);

		virtual void paintGL();
		virtual void resizeGL(int width, int height);
		virtual void initializeGL();

		virtual void keyPressEvent(QKeyEvent* event);
		virtual void keyReleaseEvent(QKeyEvent* event);

		virtual void mouseMoveEvent(QMouseEvent* event);
		virtual void mousePressEvent(QMouseEvent* event);
		virtual void mouseReleaseEvent(QMouseEvent* event);
		virtual void wheelEvent(QWheelEvent* event);

		virtual bool event(QEvent* event);

	public:
		//old functions - begin
		virtual void paintEvent(QPaintEvent* event);
		virtual void timerEvent(QTimerEvent* event);
		void setSceneData(osg::Node* apNode);
		void setCameraManipulator(osgGA::CameraManipulator* manipulator, bool resetPosition = true);
		osgGA::CameraManipulator * getCameraManipulator();
		void addEventHandler(osgGA::GUIEventHandler *eventHandler);
		//old functions - end

	private:

		virtual void onHome();
		virtual void onResize( int width, int height );

		osgGA::EventQueue* getEventQueue() const;

		osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> graphicsWindow_;
		//osg::ref_ptr<osgViewer::CompositeViewer> viewer_;
		osgViewer::Viewer m_viewer;

	};
}
#endif //VR_OSGQT_WIDGET_H
