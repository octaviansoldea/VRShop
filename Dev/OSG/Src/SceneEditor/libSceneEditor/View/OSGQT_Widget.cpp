#include "OSGQT_Widget.h"

#include <osgQt/GraphicsWindowQt>
#include <osgGA/CameraManipulator>


#include <QGridLayout>
#include <QFrame>

using namespace osg;

//--------------------------------------------------------------------

OSGQT_Widget::OSGQT_Widget(QWidget * apQWidget, Qt::WindowFlags f) : QWidget(apQWidget, f | Qt::MSWindowsOwnDC) {
 	osg::ref_ptr<osg::GraphicsContext::Traits> pTraits = new osg::GraphicsContext::Traits(osg::DisplaySettings::instance().get());
	pTraits->width = width();
	pTraits->height = height();
	pTraits->doubleBuffer = true;

	osgQt::GraphicsWindowQt* pGraphicsWindow = new osgQt::GraphicsWindowQt(pTraits.get());

	QGridLayout* pLayout = new QGridLayout;
	pLayout->setMargin(0);
	pLayout->addWidget(pGraphicsWindow->getGraphWidget(), 0, 0);
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

//--------------------------------------------------------------------
