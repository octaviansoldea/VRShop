#include "OSGQT_Widget.h"

#include <osgQt/GraphicsWindowQt>
#include <osgGA/CameraManipulator>

#include <QGridLayout>
#include <QFrame>

//--------------------------------------------------------------------

OSGQT_Widget::OSGQT_Widget(QWidget * apQWidget, Qt::WindowFlags f) : QWidget(apQWidget, f | Qt::MSWindowsOwnDC) {
 	osg::ref_ptr<osg::GraphicsContext::Traits> pTraits = new osg::GraphicsContext::Traits(osg::DisplaySettings::instance().get());
	pTraits->width = width();
	pTraits->height = height();
	pTraits->doubleBuffer = true;
	
	osgQt::GraphicsWindowQt* pGraphicsWindow = new osgQt::GraphicsWindowQt(pTraits.get());

	QGridLayout* pGrid = new QGridLayout;
	pGrid->setMargin(0);
	pGrid->addWidget(pGraphicsWindow->getGraphWidget(), 0, 0);
	setLayout(pGrid);
	
	m_viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);
	m_viewer.getCamera()->setClearColor(osg::Vec4(0.53725,0.53725,0.53725,1));

	osg::Camera* pCamera = m_viewer.getCamera();
	
	pCamera->setGraphicsContext(pGraphicsWindow);
	pCamera->setProjectionResizePolicy(osg::Camera::FIXED); //To preserve the shape of elements
	pCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	pCamera->setViewMatrix(osg::Matrix::identity());
	pCamera->setViewport(new osg::Viewport(0, 0, width(), height()));
	
	startTimer(10);
}

//--------------------------------------------------------------------

void OSGQT_Widget::paintEvent(QPaintEvent* event)	{
	m_viewer.frame();
}

//--------------------------------------------------------------------

void OSGQT_Widget::timerEvent(QTimerEvent* event)	{
	m_viewer.frame();
}

//--------------------------------------------------------------------

void OSGQT_Widget::setSceneData(osg::Node* apNode)	{
	m_viewer.setSceneData(apNode);
}

//--------------------------------------------------------------------

void OSGQT_Widget::setCameraManipulator(osgGA::CameraManipulator* manipulator, bool resetPosition)	{
	m_viewer.setCameraManipulator(manipulator, resetPosition);
}

//--------------------------------------------------------------------

void OSGQT_Widget::addEventHandler(osgGA::GUIEventHandler *eventHandler)	{
	m_viewer.addEventHandler(eventHandler);
}