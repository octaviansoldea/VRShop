#include "VRQOSGWidget.h"

#include <osgQt/GraphicsWindowQt>
#include <osgGA/CameraManipulator>

#include <QGridLayout>

using namespace VR;

//--------------------------------------------------------------------

QOSGWidget::QOSGWidget(QWidget * apQWidget, Qt::WindowFlags f) : QWidget(apQWidget, f | Qt::MSWindowsOwnDC) {
	osg::ref_ptr<osg::GraphicsContext::Traits> m_pTraits = new osg::GraphicsContext::Traits(osg::DisplaySettings::instance().get());
	m_pTraits->width = width();
	m_pTraits->height = height();
	m_pTraits->doubleBuffer = true;
	osgQt::GraphicsWindowQt* m_pGraphicsWindow = new osgQt::GraphicsWindowQt(m_pTraits.get());

	QGridLayout* m_pGrid = new QGridLayout;
	m_pGrid->setMargin(0);
	m_pGrid->addWidget(m_pGraphicsWindow->getGraphWidget(), 0, 0);
	setLayout(m_pGrid);
	
	m_viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);
	
	osg::Camera* m_pCamera = m_viewer.getCamera();
	m_pCamera->setGraphicsContext(m_pGraphicsWindow);
	//m_pCamera->setProjectionResizePolicy(osg::Camera::FIXED); //To preserve the shape of elements
	m_pCamera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
	m_pCamera->setViewMatrix(osg::Matrix::identity());
	m_pCamera->setViewport(new osg::Viewport(0, 0, width(), height()));
	
	startTimer(10);
}

//--------------------------------------------------------------------

void QOSGWidget::paintEvent(QPaintEvent* event)	{
	m_viewer.frame();
}

//--------------------------------------------------------------------

void QOSGWidget::timerEvent(QTimerEvent* event)	{
	m_viewer.frame();
}

//--------------------------------------------------------------------

void QOSGWidget::setSceneData(osg::Node* apNode)	{
	m_viewer.setSceneData(apNode);
}

//--------------------------------------------------------------------

void QOSGWidget::setCameraManipulator(osgGA::CameraManipulator* manipulator, bool resetPosition)	{
	m_viewer.setCameraManipulator(manipulator, resetPosition);
}