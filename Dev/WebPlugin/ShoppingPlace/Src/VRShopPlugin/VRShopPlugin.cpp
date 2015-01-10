/**********************************************************\

  Auto-generated VRShopPlugin.cpp

  This file contains the auto-generated main plugin object
  implementation for the VRShopPlugin project

\**********************************************************/

#include "BasicStringDefinitions.h"
#include "VRDownloadFile.h"
#include "VRAppData.h"

#include "DOM/Window.h"
#include "DOM/Document.h"

#include "VRShopPluginAPI.h"
#include <fstream>

#include "VRShopPlugin.h"

using namespace std;
using namespace VR;

void VRShopPlugin::StaticInitialize()	{
    // Place one-time initialization stuff here; As of FireBreath 1.4 this should only
    // be called once per process

	ofstream out;
	string strLog = AppData::getFPathLog() + "errors.txt";
	out.open(strLog,ios::app);
	out << "StaticInitialize: " << endl;
	out.close();
}

//--------------------------------------------------------------------------------------

void VRShopPlugin::StaticDeinitialize()	{
    // Place one-time deinitialization stuff here. As of FireBreath 1.4 this should
    // always be called just before the plugin library is unloaded

	ofstream out;
	string strLog = AppData::getFPathLog() + "errors.txt";
	out.open(strLog,ios::app);
	out << "StaticDEInitialize: " << endl;
	out.close();
}

//--------------------------------------------------------------------------------------

VRShopPlugin::VRShopPlugin()	{
	ofstream out;
	string strLog = AppData::getFPathLog() + "errors.txt";
	out.open(strLog,ios::app);
	out << "VRShop plugin constructor: " << endl;
	out.close();

}

//--------------------------------------------------------------------------------------

VRShopPlugin::~VRShopPlugin()	{
    // This is optional, but if you reset m_api (the shared_ptr to your JSAPI
    // root object) and tell the host to free the retained JSAPI objects then
    // unless you are holding another shared_ptr reference to your JSAPI object
    // they will be released here.
	releaseRootJSAPI();
    m_host->freeRetainedObjects();

	ofstream out;
	string strLog = AppData::getFPathLog() + "errors.txt";
	out.open(strLog,ios::app);
	out << "VRShop plugin destructor: " << endl;
	out.close();
}

//--------------------------------------------------------------------------------------

void VRShopPlugin::onPluginReady()	{
    // When this is called, the BrowserHost is attached, the JSAPI object is
    // created, and we are ready to interact with the page and such.  The
    // PluginWindow may or may not have already fire the AttachedEvent at
    // this point.

	ofstream out;
	string strLog = AppData::getFPathLog() + "errors.txt";
	out.open(strLog,ios::app);
	out << "On plugin ready: " << endl;
	out.close();
}

//--------------------------------------------------------------------------------------

void VRShopPlugin::shutdown()	{
    // This will be called when it is time for the plugin to shut down;
    // any threads or anything else that may hold a shared_ptr to this
    // object should be released here so that this object can be safely
    // destroyed. This is the last point that shared_from_this and weak_ptr
    // references to this object will be valid

	ofstream out;
	string strLog = AppData::getFPathLog() + "errors.txt";
	out.open(strLog,ios::app);
	out << "Plugin shutdown: " << endl;
	out.close();
}

///////////////////////////////////////////////////////////////////////////////
/// @brief  Creates an instance of the JSAPI object that provides your main
///         Javascript interface.
///
/// Note that m_host is your BrowserHost and shared_ptr returns a
/// FB::PluginCorePtr, which can be used to provide a
/// boost::weak_ptr<VRShopPlugin> for your JSAPI class.
///
/// Be very careful where you hold a shared_ptr to your plugin class from,
/// as it could prevent your plugin class from getting destroyed properly.
///////////////////////////////////////////////////////////////////////////////
FB::JSAPIPtr VRShopPlugin::createJSAPI()	{
    // m_host is the BrowserHost
    return boost::make_shared<VRShopPluginAPI>(FB::ptr_cast<VRShopPlugin>(shared_from_this()), m_host);
}

//--------------------------------------------------------------------------------------

bool VRShopPlugin::onMouseDown(FB::MouseDownEvent *evt, FB::PluginWindow *)	{
    //printf("Mouse down at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

//--------------------------------------------------------------------------------------

bool VRShopPlugin::onMouseUp(FB::MouseUpEvent *evt, FB::PluginWindow *)	{
    //printf("Mouse up at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

//--------------------------------------------------------------------------------------

bool VRShopPlugin::onMouseMove(FB::MouseMoveEvent *evt, FB::PluginWindow *)	{
    //printf("Mouse move at: %d, %d\n", evt->m_x, evt->m_y);
    return false;
}

//--------------------------------------------------------------------------------------

bool VRShopPlugin::onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindow * win)	{
	// The window is attached; act appropriately

	boost::thread t(boost::bind(&VRShopPlugin::runApplicationThread, this));

	return false;
}

//--------------------------------------------------------------------------------------

bool VRShopPlugin::onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindow *)	{
    // The window is about to be detached; act appropriately

	return false;
}

//--------------------------------------------------------------------------------------

void VRShopPlugin::newProcess(string & astrApplicationName, string & astrArguments)	{
	PROCESS_INFORMATION pi;
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;
	
	//IMPORTANT: RELEASE THE MEMORY OF THE wString
	wchar_t * pWString = string2WChar(astrApplicationName + " " + astrArguments);

	if( !CreateProcess( NULL,	// No module name (use command line).
		pWString,				// Command line.
		NULL,					// Process handle not inheritable.
		NULL,					// Thread handle not inheritable.
		FALSE,					// Set handle inheritance to FALSE.
		NORMAL_PRIORITY_CLASS,	// No creation flags.
		NULL,					// Use parent's environment block.
		NULL,					// Use parent's starting directory.
		&si,					// Pointer to STARTUPINFO structure.
		&pi )					// Pointer to PROCESS_INFORMATION structure.
		)	{
	}

	delete [] pWString;

	// Close process and thread handles.
	CloseHandle( pi.hProcess );
	CloseHandle( pi.hThread );
}

void VRShopPlugin::runApplicationThread()	{
	string strLocation = m_host->getDOMWindow()->getLocation();
	string strOperatingSystem = getOS();
	string strBrowser = getBrowser();

	ofstream out;
	string strLog = AppData::getFPathLog() + "errors.txt";
	out.open(strLog,ios::app);
	out << "strLocation: " << strLocation << "; OS: " << strOperatingSystem << "; Browser: " << strBrowser << "; " << endl;

	//If exists, skip installer operation and run the application
	string strInstallDir = AppData::getFPathVRShop() + "VRShop_Virtual";

	bool bClientPlatformExist = AppData::checkIfExists(strInstallDir + "\\VRShop\\VRShop.exe");

	out << "bClientPlatformExist: " << bClientPlatformExist<< "; INSTDIR: " << strInstallDir << endl;

	if (bClientPlatformExist == false)	{
		//Struct for setting Installer download param values
		Download::DownloadParams dP;

		string strWebServer = AppData::getFPathServer();
		string strInstaller = "VRShop.exe";

		dP.m_strURL = strWebServer+"/"+strInstaller;

		//Installer download location
		dP.m_strDestinationFolder = AppData::getFPathVRShop();
		dP.m_bReload = false;

		out << "URL: " << dP.m_strURL << "DestinationFolder: " << dP.m_strDestinationFolder << endl;

		try	{
			Download::download(dP);
		} catch(DLExc exc) {
			string strError = exc.getError();
			out << "Download installer: " << strError << endl;
		}

		int nRes = EXIT_SUCCESS;

		if (nRes != 0)	{
			out << "Downloading failed" << endl;
			exit(-1);
		}

		string strInstallerFile = AppData::getFPathVRShop() + "VRShop.exe";

		string strInstallDirSystem = replaceAll(strInstallDir,"/","\\");

		system((strInstallerFile + " -Server=" + strWebServer + " -InstallDir=" + strInstallDirSystem).c_str());
		if (remove(strInstallerFile.c_str()) != 0)
			out << "Error deleting file: " + strInstallerFile << endl;
		else
			out << "Successfully deleted file: " + strInstallerFile << endl;
	}

	FB::PluginWindow * pWin = GetWindow();
	FB::PluginWindowWin * pWindow = reinterpret_cast<FB::PluginWindowWin*>(pWin);
	if (pWindow)	{

		HWND hWnd = pWindow->getHWND();

		string strArguments = to_string((_ULonglong)hWnd) + " 1";
		newProcess(replaceAll(strInstallDir,"/","\\") + "\\VRShop\\VRShop.exe", strArguments);
	}
	out.close();
}