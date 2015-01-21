/**********************************************************\

Auto-generated VRShopPlugin.cpp

This file contains the auto-generated main plugin object
implementation for the VRShopPlugin project

\**********************************************************/

#include "BasicStringDefinitions.h"
#include "VRDownloadFile.h"
#include "VRAppData.h"

#include "VRPipeServer.h"

#include "DOM/Window.h"
#include "DOM/Document.h"

#include "VRShopPluginAPI.h"
#include <fstream>

#include "VRShopPlugin.h"

using namespace std;
using namespace VR;

PROCESS_INFORMATION pi;
HANDLE ghJob = 0;

Process::Process()	{
}

Process::~Process()	{
	//Close process and thread handles.
	CloseHandle(pi.hProcess);
	CloseHandle(pi.hThread);

	CloseHandle(ghJob);
}


void Process::newProcess(string & astrApplicationName, string & astrArguments)	{
	STARTUPINFO si = { sizeof(STARTUPINFO) };
	si.cb = sizeof(si);
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = SW_HIDE;

	//Check the name of the pipe
	wchar_t * pWString = string2WChar(astrApplicationName + " " + astrArguments);
	LPWSTR lName = pWString;

	if (!CreateProcess(NULL,	// No module name (use command line).
		lName,				// Command line.
		NULL,					// Process handle not inheritable.
		NULL,					// Thread handle not inheritable.
		FALSE,					// Set handle inheritance to FALSE.
		NORMAL_PRIORITY_CLASS,	// No creation flags.
		NULL,					// Use parent's environment block.
		NULL,					// Use parent's starting directory.
		&si,					// Pointer to STARTUPINFO structure.
		&pi)					// Pointer to PROCESS_INFORMATION structure.
	)	{

		delete [] pWString;
		return;
	}

	delete [] pWString;
}


//=======================================================================================

void VRShopPlugin::StaticInitialize()	{
	// Place one-time initialization stuff here; As of FireBreath 1.4 this should only
	// be called once per process
}

//--------------------------------------------------------------------------------------

void VRShopPlugin::StaticDeinitialize()	{
	// Place one-time deinitialization stuff here. As of FireBreath 1.4 this should
	// always be called just before the plugin library is unloaded
}

//--------------------------------------------------------------------------------------

VRShopPlugin::VRShopPlugin()	{
}

//--------------------------------------------------------------------------------------

VRShopPlugin::~VRShopPlugin()	{
	// This is optional, but if you reset m_api (the shared_ptr to your JSAPI
	// root object) and tell the host to free the retained JSAPI objects then
	// unless you are holding another shared_ptr reference to your JSAPI object
	// they will be released here.
	releaseRootJSAPI();
	m_host->freeRetainedObjects();
}

//--------------------------------------------------------------------------------------

void VRShopPlugin::onPluginReady()	{
	// When this is called, the BrowserHost is attached, the JSAPI object is
	// created, and we are ready to interact with the page and such.  The
	// PluginWindow may or may not have already fire the AttachedEvent at
	// this point.

	m_pProcess = new Process;
	m_pPipe = new PipeServer;
}

//--------------------------------------------------------------------------------------

void VRShopPlugin::shutdown()	{
	// This will be called when it is time for the plugin to shut down;
	// any threads or anything else that may hold a shared_ptr to this
	// object should be released here so that this object can be safely
	// destroyed. This is the last point that shared_from_this and weak_ptr
	// references to this object will be valid

	delete m_pPipe;
	delete m_pProcess;
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

//---------------------------------------------------------------------------

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

	if (bClientPlatformExist == false)	{
		//Struct for setting Installer download param values
		Download::DownloadParams dP;

		string strWebServer = AppData::getFPathServer();
		string strInstaller = "VRShop.exe";
		dP.m_strURL = strWebServer+"/"+strInstaller;

//GOOGLE AS WEB SERVER
//		string strWebServer = "https://0c446f69db3816158c2da15fa6f0faceb2a6fff1-www.googledrive.com/host/0B2PTBoEUslueYzRHT3ZyZUxMUG8/";
//		dP.m_strURL = strWebServer;
//GOOGLE AS WEB SERVER

		//Installer download location
		dP.m_strDestinationFolder = AppData::getFPathVRShop();
		dP.m_bReload = false;

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

		//Create pipe server
		string strPipeName = "\\\\.\\pipe\\VRShopPluginPipe";
		m_pPipe->initializeAndRunServer(strPipeName);

		string strArguments = tostr(hWnd) + " 1 " + strPipeName;

		//Create process
		ghJob = CreateJobObject( NULL, NULL);
		if( ghJob == NULL)	{
			out << "Could not create job object" << endl;
		} else {
			JOBOBJECT_EXTENDED_LIMIT_INFORMATION jeli = { 0 };

			// Configure all child processes associated with the job to terminate when the
			jeli.BasicLimitInformation.LimitFlags = JOB_OBJECT_LIMIT_KILL_ON_JOB_CLOSE;
			if( 0 == SetInformationJobObject( ghJob, JobObjectExtendedLimitInformation, &jeli, sizeof(jeli)))	{
				out << "Could not SetInformationJobObject" << endl;
			}
		}

		m_pProcess->newProcess(replaceAll(strInstallDir,"/","\\") + "\\VRShop\\VRShop.exe", strArguments);
	}
	out.close();
}