/**********************************************************\

Auto-generated VRShopPluginAPI.cpp

\**********************************************************/

#include <string>

#include "BasicStringDefinitions.h"
#include "VRDownloadFile.h"
#include "VRAppData.h"

#include <Win/PluginWindowWin.h>

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Window.h"
#include "DOM/Document.h"
#include "global/config.h"

#include <boost/make_shared.hpp>

#include "VRShopPluginAPI.h"

using namespace std;
using namespace VR;

VRShopPluginAPI::VRShopPluginAPI(const VRShopPluginPtr& plugin, const FB::BrowserHostPtr& host) :
m_plugin(plugin), m_host(host)	{
	registerMethod("runApplication",make_method(this, &VRShopPluginAPI::runApplication));

	registerProperty("version",make_property(this,&VRShopPluginAPI::get_version));

	ofstream out;
	string strLog = AppData::getFPathLog() + "errors.txt";
	out.open(strLog,ios::app);
	out << "Constructor of the FB." << endl;
	out.close();
}

//--------------------------------------------------------------------------------------

VRShopPluginAPI::~VRShopPluginAPI()	{
	ofstream out;
	string strLog = AppData::getFPathLog() + "errors.txt";
	out.open(strLog,ios::app);
	out << "Destructor of the FB." << endl;
	out.close();
}

//==========================================================================

VRShopPluginPtr VRShopPluginAPI::getPlugin()	{
	VRShopPluginPtr plugin(m_plugin.lock());
	if (!plugin) {
		throw FB::script_error("The plugin is invalid");
	}
	return plugin;
}

//--------------------------------------------------------------------------------------

std::string VRShopPluginAPI::get_version()	{
	return FBSTRING_PLUGIN_VERSION;
}

//--------------------------------------------------------------------------------------

bool VRShopPluginAPI::runApplication(const FB::JSObjectPtr &callback)	{
//	boost::thread t(boost::bind(&VRShopPluginAPI::runApplicationThread, this, callback));

	return true; // the thread is started
}

//--------------------------------------------------------------------------------------