#include "OSGWidget.h"

#include <osg/Camera>

#include <osg/Geode>
#include <osg/Shape>
#include <osg/ShapeDrawable>

#include <osgGA/EventQueue>
#include <osgGA/TrackballManipulator>

#include <osgViewer/View>
#include <osgViewer/ViewerEventHandlers>

#include <cassert>

#include <stdexcept>
#include <vector>

#include <QDebug>

#include <QKeyEvent>
#include <QWheelEvent>

OSGWidget::OSGWidget( QWidget* parent,
                      const QGLWidget* shareWidget,
                      Qt::WindowFlags f )
  : QGLWidget( parent,
               shareWidget,
               f ),
    graphicsWindow_( new osgViewer::GraphicsWindowEmbedded( this->x(), this->y(),
                                                            this->width(), this->height() ) ),
    viewer_( new osgViewer::CompositeViewer )
{
  osg::Sphere* sphere    = new osg::Sphere( osg::Vec3( 0.f, 0.f, 0.f ), 0.25f );
  osg::ShapeDrawable* sd = new osg::ShapeDrawable( sphere );
  sd->setColor( osg::Vec4( 1.f, 0.f, 0.f, 1.f ) );

  osg::Geode* geode = new osg::Geode;
  geode->addDrawable( sd );

  float aspectRatio = static_cast<float>( this->width() / 2 ) / static_cast<float>( this->height() );

  osg::Camera* camera = new osg::Camera;
  camera->setViewport( 0, 0, this->width() / 2, this->height() );
  camera->setClearColor( osg::Vec4( 0.f, 0.f, 1.f, 1.f ) );
  camera->setProjectionMatrixAsPerspective( 30.f, aspectRatio, 1.f, 1000.f );
  camera->setGraphicsContext( graphicsWindow_ );

  osgViewer::View* view = new osgViewer::View;
  view->setCamera( camera );
  view->setSceneData( geode );
  view->addEventHandler( new osgViewer::StatsHandler );
  view->setCameraManipulator( new osgGA::TrackballManipulator );

  osg::Camera* sideCamera = new osg::Camera;
  sideCamera->setViewport( this->width() /2, 0,
                           this->width() /2, this->height() );

  sideCamera->setClearColor( osg::Vec4( 0.f, 0.f, 1.f, 1.f ) );
  sideCamera->setProjectionMatrixAsPerspective( 30.f, aspectRatio, 1.f, 1000.f );
  sideCamera->setGraphicsContext( graphicsWindow_ );

  osgViewer::View* sideView = new osgViewer::View;
  sideView->setCamera( sideCamera );
  sideView->setSceneData( geode );
  sideView->addEventHandler( new osgViewer::StatsHandler );
  sideView->setCameraManipulator( new osgGA::TrackballManipulator );

  viewer_->addView( view );
  viewer_->addView( sideView );
  viewer_->setThreadingModel( osgViewer::CompositeViewer::SingleThreaded );

  // This ensures that the widget will receive keyboard events. This focus
  // policy is not set by default. The default, Qt::NoFocus, will result in
  // keyboard events that are ignored.
  this->setFocusPolicy( Qt::StrongFocus );
  this->setMinimumSize( 100, 100 );

  // Ensures that the widget receives mouse move events even though no
  // mouse button has been pressed. We require this in order to let the
  // graphics window switch viewports properly.
  this->setMouseTracking( true );
}

OSGWidget::~OSGWidget()
{
}

void OSGWidget::paintGL()
{
  viewer_->frame();
}

void OSGWidget::resizeGL( int width, int height )
{
  this->getEventQueue()->windowResize( this->x(), this->y(), width, height );
  graphicsWindow_->resized( this->x(), this->y(), width, height );

  this->onResize( width, height );
}

void OSGWidget::keyPressEvent( QKeyEvent* event )
{
  QString keyString   = event->text();
  const char* keyData = keyString.toAscii().data();

  this->getEventQueue()->keyPress( osgGA::GUIEventAdapter::KeySymbol( *keyData ) );

  if( event->key() == Qt::Key_H )
    this->onHome();
}

void OSGWidget::keyReleaseEvent( QKeyEvent* event )
{
  QString keyString   = event->text();
  const char* keyData = keyString.toAscii().data();

  this->getEventQueue()->keyRelease( osgGA::GUIEventAdapter::KeySymbol( *keyData ) );
}

void OSGWidget::mouseMoveEvent( QMouseEvent* event )
{
  this->getEventQueue()->mouseMotion( static_cast<float>( event->x() ),
                                      static_cast<float>( event->y() ) );
}

void OSGWidget::mousePressEvent( QMouseEvent* event )
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

void OSGWidget::mouseReleaseEvent(QMouseEvent* event)
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

void OSGWidget::wheelEvent( QWheelEvent* event )
{
  event->accept();
  int delta = event->delta();

  osgGA::GUIEventAdapter::ScrollingMotion motion = delta > 0 ?   osgGA::GUIEventAdapter::SCROLL_UP
                                                               : osgGA::GUIEventAdapter::SCROLL_DOWN;

  this->getEventQueue()->mouseScroll( motion );
}

bool OSGWidget::event( QEvent* event )
{
  bool handled = QGLWidget::event( event );

  // This ensures that the OSG widget is always going to be repainted after the
  // user performed some interaction. Doing this in the event handler ensures
  // that we don't forget about some event and prevents duplicate code.
  switch( event->type() )
  {
  case QEvent::KeyPress:
  case QEvent::KeyRelease:
  case QEvent::MouseButtonDblClick:
  case QEvent::MouseButtonPress:
  case QEvent::MouseButtonRelease:
  case QEvent::MouseMove:
  case QEvent::Wheel:
    this->update();
    break;

  default:
    break;
  }

  return( handled );
}

void OSGWidget::onHome()
{
  osgViewer::ViewerBase::Views views;
  viewer_->getViews( views );

  for( std::size_t i = 0; i < views.size(); i++ )
  {
    osgViewer::View* view = views.at(i);
    view->home();
  }
}

void OSGWidget::onResize( int width, int height )
{
  std::vector<osg::Camera*> cameras;
  viewer_->getCameras( cameras );

  assert( cameras.size() == 2 );

  cameras[0]->setViewport( 0, 0, this->width() / 2, this->height() );
  cameras[1]->setViewport( this->width() / 2, 0, this->width() / 2, this->height() );
}

osgGA::EventQueue* OSGWidget::getEventQueue() const
{
  osgGA::EventQueue* eventQueue = graphicsWindow_->getEventQueue();

  if( eventQueue )
    return( eventQueue );
  else
    throw( std::runtime_error( "Unable to obtain valid event queue") );
}
