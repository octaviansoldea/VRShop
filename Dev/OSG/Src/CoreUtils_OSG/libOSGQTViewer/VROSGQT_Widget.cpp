//#include <cassert>
//#include <stdexcept>
//#include <vector>
#include <iostream>

#include <osg/Camera>
#include <osg/Geode>
#include <osg/Shape>
#include <osg/ShapeDrawable>
#include <osgGA/EventQueue>
#include <osgGA/TrackballManipulator>
#include <osgViewer/View>
#include <osgViewer/ViewerEventHandlers>

#include <QDebug>
#include <QKeyEvent>
#include <QWheelEvent>

#include "VROSGQT_Widget.h"

using namespace std;
using namespace VR;

OSGQT_Widget::OSGQT_Widget( QWidget* parent,
                      const QGLWidget* shareWidget,
                      Qt::WindowFlags f )
  : QGLWidget( parent,
               shareWidget,
               f ),
    graphicsWindow_( new osgViewer::GraphicsWindowEmbedded( this->x(), this->y(),
                                                            this->width(), this->height() ) )
{
  float aspectRatio = static_cast<float>( this->width() / 2 ) / static_cast<float>( this->height() );

  osg::Camera* pCamera = new osg::Camera;
  pCamera->setViewport( 0, 0, this->width() / 2, this->height() );
  pCamera->setClearColor( osg::Vec4(0.53725,0.53725,0.53725,1) );
  pCamera->setGraphicsContext( graphicsWindow_ );
  pCamera->setViewMatrix(osg::Matrix::identity());
  pCamera->setProjectionMatrixAsPerspective( 30.f, aspectRatio, 1.f, 1000.f );

  m_viewer.setCamera(pCamera);
  //m_viewer.addEventHandler( new osgViewer::StatsHandler );
  m_viewer.setCameraManipulator( new osgGA::TrackballManipulator );

  m_viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);
		//AutomaticSelection);

  // This ensures that the widget will receive keyboard events. This focus
  // policy is not set by default. The default, Qt::NoFocus, will result in
  // keyboard events that are ignored.
  this->setFocusPolicy( Qt::StrongFocus );
  this->setMinimumSize( 100, 100 );

  // Ensures that the widget receives mouse move events even though no
  // mouse button has been pressed. We require this in order to let the
  // graphics window switch viewports properly.
  this->setMouseTracking( true );

  //startTimer(40);
}

//--------------------------------------------------------------------

OSGQT_Widget::~OSGQT_Widget()
{
}

//--------------------------------------------------------------------

 osgGA::GUIEventAdapter::KeySymbol OSGQT_Widget::qtKeyToOsg(QKeyEvent * e)const {
   int qtKey = e->key();
   switch(qtKey)
   {
      case Qt::Key_Up:
      {
         return(osgGA::GUIEventAdapter::KEY_Up);
      }
      case Qt::Key_Down:
      {
         return (osgGA::GUIEventAdapter::KEY_Down);
      }
      case Qt::Key_Left:
      {
         return (osgGA::GUIEventAdapter::KEY_Left);
      }
      case Qt::Key_Right:
      {
         return (osgGA::GUIEventAdapter::KEY_Right);
      }
      case Qt::Key_Return:
      {
         return (osgGA::GUIEventAdapter::KEY_Return);
      }
      default:
      {
         if((qtKey >= Qt::Key_A)&&(qtKey <= Qt::Key_Z))
         {
            QString s = e->text();
            std::string stdString = s.toStdString();
            char c = *stdString.begin();
            return (osgGA::GUIEventAdapter::KeySymbol)(c); 
         }
      }
   }
	      return (osgGA::GUIEventAdapter::KeySymbol)(qtKey);
}


//--------------------------------------------------------------------

 void OSGQT_Widget::addModifiers(osg::ref_ptr<osgGA::EventQueue> eventQueue, Qt::KeyboardModifiers modifier)
 {
	 if(!eventQueue.valid()) return;
	 unsigned int modKeyMask = 0;
	 osgGA::GUIEventAdapter* adapter = eventQueue->getCurrentEventState();
	 if(!adapter) return;
	 if(modifier & Qt::ShiftModifier)
	 {
		 modKeyMask|=osgGA::GUIEventAdapter::MODKEY_SHIFT;
	 }
	 if(modifier & Qt::ControlModifier)
	 {
		 modKeyMask|=osgGA::GUIEventAdapter::MODKEY_CTRL;
	 }
	 if(modifier & Qt::AltModifier)
	 {
		 modKeyMask|=osgGA::GUIEventAdapter::MODKEY_ALT;
	 }
	 if(modifier & Qt::MetaModifier)
	 {
		 modKeyMask|=osgGA::GUIEventAdapter::MODKEY_META;
	 }
	 adapter->setModKeyMask(modKeyMask);
 }

 //--------------------------------------------------------------------

void OSGQT_Widget::paintGL()
{
  m_viewer.frame();
}

//--------------------------------------------------------------------

void OSGQT_Widget::resizeGL( int width, int height )
{
  this->getEventQueue()->windowResize( this->x(), this->y(), width, height );
  graphicsWindow_->resized( this->x(), this->y(), width, height );

  this->onResize( width, height );
}

//--------------------------------------------------------------------

void OSGQT_Widget::initializeGL()
{
	osg::Camera * pCamera = m_viewer.getCamera();
	if(pCamera != 0) {
		pCamera->setClearColor(osg::Vec4(0.0f,0.0f,0.4f,1.0f)); 
		pCamera->setClearMask(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); 
	}
}

//--------------------------------------------------------------------

void OSGQT_Widget::keyPressEvent( QKeyEvent* event )
{
  QString keyString   = event->text();
  const char* keyData = keyString.toStdString().c_str();

  osgGA::GUIEventAdapter::KeySymbol keyOSG = qtKeyToOsg(event);

  addModifiers(graphicsWindow_->getEventQueue(), event->modifiers());

  this->getEventQueue()->keyPress( osgGA::GUIEventAdapter::KeySymbol( keyOSG ));

  //Tavi
  //int nQtKey = event->key();
  //int nOSGKey;
  //if(nQtKey == Qt::Key::Key_Left) 
	 // nOSGKey = osgGA::GUIEventAdapter::KEY_Left;
  //else
	 // nOSGKey = osgGA::GUIEventAdapter::KEY_Right;

  //this->getEventQueue()->keyPress( osgGA::GUIEventAdapter::KeySymbol( nOSGKey//*keyData
	 // ));

  if( event->key() == Qt::Key_H )
    this->onHome();
}

//--------------------------------------------------------------------

void OSGQT_Widget::keyReleaseEvent( QKeyEvent* event )
{
  QString keyString   = event->text();
  const char* keyData = keyString.toStdString().c_str();

  osgGA::GUIEventAdapter::KeySymbol keyOSG = qtKeyToOsg(event);

  addModifiers(graphicsWindow_->getEventQueue(), event->modifiers());

  this->getEventQueue()->keyPress( osgGA::GUIEventAdapter::KeySymbol( keyOSG ));

  this->getEventQueue()->keyRelease( osgGA::GUIEventAdapter::KeySymbol( *keyData ) );
}

//--------------------------------------------------------------------

void OSGQT_Widget::mouseMoveEvent( QMouseEvent* event )
{
  this->getEventQueue()->mouseMotion( static_cast<float>( event->x() ),
                                      static_cast<float>( event->y() ) );
}

//--------------------------------------------------------------------

void OSGQT_Widget::mousePressEvent( QMouseEvent* event )
{
  // 1 = left mouse button
  // 2 = middle mouse button
  // 3 = right mouse button

  unsigned int button = 0;

  switch( event->button() )
  {
  case Qt::LeftButton:
    button = 1;
    break;

  case Qt::MiddleButton:
    button = 2;
    break;

  case Qt::RightButton:
    button = 3;
    break;

  default:
    break;
  }

  this->getEventQueue()->mouseButtonPress( static_cast<float>( event->x() ),
                                           static_cast<float>( event->y() ),
                                           button );
}

//--------------------------------------------------------------------

void OSGQT_Widget::mouseReleaseEvent(QMouseEvent* event)
{
  // 1 = left mouse button
  // 2 = middle mouse button
  // 3 = right mouse button

  unsigned int button = 0;

  switch( event->button() )
  {
  case Qt::LeftButton:
    button = 1;
    break;

  case Qt::MiddleButton:
    button = 2;
    break;

  case Qt::RightButton:
    button = 3;
    break;

  default:
    break;
  }

  this->getEventQueue()->mouseButtonRelease( static_cast<float>( event->x() ),
                                             static_cast<float>( event->y() ),
                                             button );
}

//--------------------------------------------------------------------

void OSGQT_Widget::wheelEvent( QWheelEvent* event )
{
  event->accept();
  int delta = event->delta();

  osgGA::GUIEventAdapter::ScrollingMotion motion = delta > 0 ?   osgGA::GUIEventAdapter::SCROLL_UP
                                                               : osgGA::GUIEventAdapter::SCROLL_DOWN;

  this->getEventQueue()->mouseScroll( motion );
}

//--------------------------------------------------------------------

bool OSGQT_Widget::event( QEvent* event )
{
  bool handled = QGLWidget::event( event );

  // This ensures that the OSG widget is always going to be repainted after the
  // user performed some interaction. Doing this in the event handler ensures
  // that we don't forget about some event and prevents duplicate code.
  switch( event->type() )
  {
  case QEvent::KeyPress:
	  {
		  int indy = 1;
	  }
  case QEvent::KeyRelease:
	  {
		  int indy = 1;
	  }
  case QEvent::MouseButtonDblClick:
	  {
		  int indy = 1;
	  }
  case QEvent::MouseButtonPress:
	  {
		  int indy = 1;
	  }
  case QEvent::MouseButtonRelease:
	  {
		  int indy = 1;
	  }
  case QEvent::MouseMove:
	  {
		  int indy = 1;
	  }
  case QEvent::Wheel:
	  {
		  int indy = 1;
	  }
    this->update();
    break;

  default:
    break;
  }

  return( handled );
}
//--------------------------------------------------------------------

  //old functions - begin
void OSGQT_Widget::paintEvent(QPaintEvent* event)	{
	m_viewer.frame();
	QGLWidget::paintEvent(event);
}

//--------------------------------------------------------------------

void OSGQT_Widget::timerEvent(QTimerEvent* event)	{
	m_viewer.frame();
//	QWidget::timerEvent(event);
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

osgGA::CameraManipulator* OSGQT_Widget::getCameraManipulator()	{
	return(m_viewer.getCameraManipulator());
}

//--------------------------------------------------------------------

void OSGQT_Widget::addEventHandler(osgGA::GUIEventHandler *eventHandler)	{
	m_viewer.addEventHandler(eventHandler);
}

//old functions - end

//--------------------------------------------------------------------

void OSGQT_Widget::onHome()
{
  osgViewer::ViewerBase::Views views;
  m_viewer.getViews( views );

  for( std::size_t i = 0; i < views.size(); i++ )
  {
    osgViewer::View* view = views.at(i);
    view->home();
  }
}

//--------------------------------------------------------------------

void OSGQT_Widget::onResize( int width, int height )
{
  std::vector<osg::Camera*> cameras;
  m_viewer.getCameras( cameras );

  //assert( cameras.size() == 2 );

  cameras[0]->setViewport( 0, 0, this->width(), this->height() );
}

//--------------------------------------------------------------------

osgGA::EventQueue* OSGQT_Widget::getEventQueue() const
{
  osgGA::EventQueue* eventQueue = graphicsWindow_->getEventQueue();

  if( eventQueue )
    return( eventQueue );
  else
    throw( std::runtime_error( "Unable to obtain valid event queue") );
}

//--------------------------------------------------------------------