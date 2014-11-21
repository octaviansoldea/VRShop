#include <QWidget>
#include <QPaintEvent>
#include <QTimerEvent>
#include <QGridLayout>

#include <osgQt/GraphicsWindowQt>
#include <osgGA/CameraManipulator>

#include "VROSGQT_Widget.h"

using namespace osg;
using namespace VR;

//--------------------------------------------------------------------

OSGQT_Widget::OSGQT_Widget(QWidget * apQWidget, Qt::WindowFlags f) : QWidget(apQWidget, f | Qt::MSWindowsOwnDC) {
	osg::ref_ptr<osg::GraphicsContext::Traits> pTraits = new osg::GraphicsContext::Traits(osg::DisplaySettings::instance().get());
	pTraits->width = width();
	pTraits->height = height();
	pTraits->doubleBuffer = true;

	osg::ref_ptr<osgQt::GraphicsWindowQt> pGraphicsWindow = new osgQt::GraphicsWindowQt(pTraits.get());

	QVBoxLayout* pLayout = new QVBoxLayout;
	pLayout->addWidget(pGraphicsWindow->getGLWidget());
	pLayout->setMargin(0);
	setLayout(pLayout);

	m_viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);

	osg::Camera* pCamera = m_viewer.getCamera();
	pCamera->setClearColor(osg::Vec4(0.53725,0.53725,0.53725,1));
	pCamera->setGraphicsContext(pGraphicsWindow);
	pCamera->setViewMatrix(osg::Matrix::identity());
	pCamera->setViewport(new osg::Viewport(0, 0, pTraits->width, pTraits->height));
	pCamera->setProjectionMatrixAsPerspective( 30.0, 
		(float)pCamera->getViewport()->width() / (float)pCamera->getViewport()->height(),
		1.0, 10000.0 );

	startTimer(40);
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

Node * OSGQT_Widget::getSceneData()	{
	return m_viewer.getSceneData();
}

//--------------------------------------------------------------------

void OSGQT_Widget::setCameraManipulator(osgGA::CameraManipulator* manipulator, bool resetPosition)	{
	m_viewer.setCameraManipulator(manipulator, resetPosition);
}

//--------------------------------------------------------------------

osgGA::CameraManipulator* OSGQT_Widget::getCameraManipulator()	{
	return(m_viewer.getCameraManipulator());
}

//--------------------------------------------------------------------

void OSGQT_Widget::addEventHandler(osgGA::GUIEventHandler *eventHandler)	{
	m_viewer.addEventHandler(eventHandler);
}

//--------------------------------------------------------------------
