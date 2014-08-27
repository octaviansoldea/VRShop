/**********************************************************\

  Auto-generated VRShop.cpp

  This file contains the auto-generated main plugin object
  implementation for the VRShop project

\**********************************************************/

#include "win_common.h"
#include <Win/PluginWindowWin.h>

#include "VRShopAPI.h"

#include "SceneEditorDlg.h"
#include <QApplication>

#include <QWindow>

#include <QWidget>
#include <QString>

#include "VRShop.h"

///////////////////////////////////////////////////////////////////////////////
/// @fn VRShop::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginInitialize()
///
/// @see FB::FactoryBase::globalPluginInitialize
///////////////////////////////////////////////////////////////////////////////
void VRShop::StaticInitialize()
{
    // Place one-time initialization stuff here; As of FireBreath 1.4 this should only
    // be called once per process
}

///////////////////////////////////////////////////////////////////////////////
/// @fn VRShop::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginDeinitialize()
///
/// @see FB::FactoryBase::globalPluginDeinitialize
///////////////////////////////////////////////////////////////////////////////
void VRShop::StaticDeinitialize()
{
    // Place one-time deinitialization stuff here. As of FireBreath 1.4 this should
    // always be called just before the plugin library is unloaded
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  VRShop constructor.  Note that your API is not available
///         at this point, nor the window.  For best results wait to use
///         the JSAPI object until the onPluginReady method is called
///////////////////////////////////////////////////////////////////////////////
VRShop::VRShop()
{
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  VRShop destructor.
///////////////////////////////////////////////////////////////////////////////
VRShop::~VRShop()
{
    // This is optional, but if you reset m_api (the shared_ptr to your JSAPI
    // root object) and tell the host to free the retained JSAPI objects then
    // unless you are holding another shared_ptr reference to your JSAPI object
    // they will be released here.
    releaseRootJSAPI();
    m_host->freeRetainedObjects();
}

void VRShop::onPluginReady()
{
    // When this is called, the BrowserHost is attached, the JSAPI object is
    // created, and we are ready to interact with the page and such.  The
    // PluginWindow may or may not have already fire the AttachedEvent at
    // this point.
}

void VRShop::shutdown()
{
    // This will be called when it is time for the plugin to shut down;
    // any threads or anything else that may hold a shared_ptr to this
    // object should be released here so that this object can be safely
    // destroyed. This is the last point that shared_from_this and weak_ptr
    // references to this object will be valid
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  Creates an instance of the JSAPI object that provides your main
///         Javascript interface.
///
/// Note that m_host is your BrowserHost and shared_ptr returns a
/// FB::PluginCorePtr, which can be used to provide a
/// boost::weak_ptr<VRShop> for your JSAPI class.
///
/// Be very careful where you hold a shared_ptr to your plugin class from,
/// as it could prevent your plugin class from getting destroyed properly.
///////////////////////////////////////////////////////////////////////////////
FB::JSAPIPtr VRShop::createJSAPI()
{
    // m_host is the BrowserHost
    return boost::make_shared<VRShopAPI>(FB::ptr_cast<VRShop>(shared_from_this()), m_host);
}

bool VRShop::onMouseDown(FB::MouseDownEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse down at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

bool VRShop::onMouseUp(FB::MouseUpEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse up at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

bool VRShop::onMouseMove(FB::MouseMoveEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse move at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}
bool VRShop::onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindow * win)
{	

	FB::PluginWindowWin* window = reinterpret_cast<FB::PluginWindowWin*>(win);
	if ( window )	{
		int argc = 0;
		char ** argv = 0;
		QApplication app(argc, argv);

		SceneEditorDlg sceneEditorDlg;
		sceneEditorDlg.setAttribute(Qt::WA_NativeWindow);
		SetParent((HWND)sceneEditorDlg.winId(), window->getHWND());
 
		sceneEditorDlg.show();
		return app.exec();
	}

	// The window is attached; act appropriately
    return false;
}

bool VRShop::onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindow *)
{
    // The window is about to be detached; act appropriately
    return false;
}

