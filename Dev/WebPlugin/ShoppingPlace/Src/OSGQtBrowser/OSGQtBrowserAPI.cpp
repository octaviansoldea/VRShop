/**********************************************************\

Auto-generated OSGQtBrowserAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"

#include "OSGQtBrowserAPI.h"

////////////////////////////////////////////////////////////////////////////
/// @fn OSGQtBrowserAPI::OSGQtBrowserAPI(const OSGQtBrowserPtr& plugin, const FB::BrowserHostPtr host)
///
/// @brief  Constructor for your JSAPI object.
///         You should register your methods, properties, and events
///         that should be accessible to Javascript from here.
///
/// @see FB::JSAPIAuto::registerMethod
/// @see FB::JSAPIAuto::registerProperty
/// @see FB::JSAPIAuto::registerEvent
////////////////////////////////////////////////////////////////////////////
OSGQtBrowserAPI::OSGQtBrowserAPI(const OSGQtBrowserPtr& plugin, const FB::BrowserHostPtr& host) :
m_plugin(plugin), m_host(host)
{
	//std::string strFPExe = "C:/Users/Gregi_Laptop/Downloads/VRShop.exe";
	//system(strFPExe.c_str());


	registerMethod("echo",      make_method(this, &OSGQtBrowserAPI::echo));
	registerMethod("testEvent", make_method(this, &OSGQtBrowserAPI::testEvent));

	// Read-write property
	registerProperty("testString",
		make_property(this,
		&OSGQtBrowserAPI::get_testString,
		&OSGQtBrowserAPI::set_testString));

	// Read-only property
	registerProperty("version",
		make_property(this,
		&OSGQtBrowserAPI::get_version));
}


///////////////////////////////////////////////////////////////////////////////
/// @fn FB::variant OSGQtBrowserAPI::echo(const FB::variant& msg)
///
/// @brief  Echos whatever is passed from Javascript.
///         Go ahead and change it. See what happens!
///////////////////////////////////////////////////////////////////////////////
FB::variant OSGQtBrowserAPI::echo(const FB::variant& msg)
{
	static int n(0);
	fire_echo("So far, you clicked this many times: ", n++);

	// return "foobar";
	return msg;
}

///////////////////////////////////////////////////////////////////////////////
/// @fn OSGQtBrowserPtr OSGQtBrowserAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
OSGQtBrowserPtr OSGQtBrowserAPI::getPlugin()
{
	OSGQtBrowserPtr plugin(m_plugin.lock());
	if (!plugin) {
		throw FB::script_error("The plugin is invalid");
	}
	return plugin;
}

// Read/Write property testString
std::string OSGQtBrowserAPI::get_testString()
{
	return m_testString;
}

void OSGQtBrowserAPI::set_testString(const std::string& val)
{
	m_testString = val;
}

// Read-only property version
std::string OSGQtBrowserAPI::get_version()
{
	return FBSTRING_PLUGIN_VERSION;
}

void OSGQtBrowserAPI::testEvent()
{
	fire_test();
}
