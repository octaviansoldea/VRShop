/**********************************************************\

  Auto-generated OSGQtBrowser.cpp

  This file contains the auto-generated main plugin object
  implementation for the OSGQtBrowser project

\**********************************************************/

#include <iostream>
#include <fstream>

#include "OSGQtBrowserAPI.h"

#include <Win/PluginWindowWin.h>

#include <QProcess>
#include <QString>

#include "OSGQtBrowser.h"

///////////////////////////////////////////////////////////////////////////////
/// @fn OSGQtBrowser::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginInitialize()
///
/// @see FB::FactoryBase::globalPluginInitialize
///////////////////////////////////////////////////////////////////////////////
void OSGQtBrowser::StaticInitialize()
{
    // Place one-time initialization stuff here; As of FireBreath 1.4 this should only
    // be called once per process
}

///////////////////////////////////////////////////////////////////////////////
/// @fn OSGQtBrowser::StaticInitialize()
///
/// @brief  Called from PluginFactory::globalPluginDeinitialize()
///
/// @see FB::FactoryBase::globalPluginDeinitialize
///////////////////////////////////////////////////////////////////////////////
void OSGQtBrowser::StaticDeinitialize()
{
    // Place one-time deinitialization stuff here. As of FireBreath 1.4 this should
    // always be called just before the plugin library is unloaded
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  OSGQtBrowser constructor.  Note that your API is not available
///         at this point, nor the window.  For best results wait to use
///         the JSAPI object until the onPluginReady method is called
///////////////////////////////////////////////////////////////////////////////
OSGQtBrowser::OSGQtBrowser()
{

}

///////////////////////////////////////////////////////////////////////////////
/// @brief  OSGQtBrowser destructor.
///////////////////////////////////////////////////////////////////////////////
OSGQtBrowser::~OSGQtBrowser()
{
    // This is optional, but if you reset m_api (the shared_ptr to your JSAPI
    // root object) and tell the host to free the retained JSAPI objects then
    // unless you are holding another shared_ptr reference to your JSAPI object
    // they will be released here.

	int nState = m_pProcess->state();
	if (nState == QProcess::Running)	{
		m_pProcess->close();
	}

	if (m_pProcess != 0)	{
		delete m_pProcess;
		m_pProcess = 0;
	}

	releaseRootJSAPI();
    m_host->freeRetainedObjects();
}

void OSGQtBrowser::onPluginReady()
{

//	m_host->evaluateJavaScript("document.getElementById('pluginCont').style.border = '1px solid black';");

    // When this is called, the BrowserHost is attached, the JSAPI object is
    // created, and we are ready to interact with the page and such.  The
    // PluginWindow may or may not have already fire the AttachedEvent at
    // this point.
}

void OSGQtBrowser::shutdown()
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
/// boost::weak_ptr<OSGQtBrowser> for your JSAPI class.
///
/// Be very careful where you hold a shared_ptr to your plugin class from,
/// as it could prevent your plugin class from getting destroyed properly.
///////////////////////////////////////////////////////////////////////////////
FB::JSAPIPtr OSGQtBrowser::createJSAPI()
{
	// m_host is the BrowserHost
    return boost::make_shared<OSGQtBrowserAPI>(FB::ptr_cast<OSGQtBrowser>(shared_from_this()), m_host);
}

bool OSGQtBrowser::onMouseDown(FB::MouseDownEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse down at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

bool OSGQtBrowser::onMouseUp(FB::MouseUpEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse up at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

bool OSGQtBrowser::onMouseMove(FB::MouseMoveEvent *evt, FB::PluginWindow *)
{
    //printf("Mouse move at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

bool OSGQtBrowser::onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindow * win)
{
	//This process should wait until 
	FB::PluginWindowWin* window = reinterpret_cast<FB::PluginWindowWin*>(win);
	if ( window )	{

		HWND hWnd=  window->getHWND();

		QString strArguments = QString::number((unsigned long)hWnd);

		m_pProcess = new QProcess(0);
		
		QString strFPExeEditor = "C:/Projekti/VRShop/Dev/CorePlatform/Build/ShopScene/Test_libShopEditor/Debug/Test_libShopEditor.exe";
		QString strFPExeClient = "C:/Projekti/VRShop/Dev/CorePlatform/Build/ShopScene/Test_libShoppingPlace/Debug/Test_libShoppingPlace.exe";
		QString strFPExeWebsite = "C:/Projekti/VRShop/Dev/CorePlatform/Build/EmbeddedWidget/Test_libEmbeddedWidget/Debug/Test_libEmbeddedWidget.exe";

		m_pProcess->start(strFPExeWebsite, QStringList() << strArguments);

		return true;
	}

    // The window is attached; act appropriately
    return false;
}

bool OSGQtBrowser::onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindow *)
{
	int nState = m_pProcess->state();
	if (nState == QProcess::Running)	{
		m_pProcess->close();
	}

	delete m_pProcess;
	m_pProcess = 0;

	// The window is about to be detached; act appropriately
	return false;
}

