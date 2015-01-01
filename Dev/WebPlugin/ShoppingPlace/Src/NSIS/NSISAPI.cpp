/**********************************************************\

  Auto-generated NSISAPI.cpp

\**********************************************************/

#include "JSObject.h"
#include "variant_list.h"
#include "DOM/Document.h"
#include "global/config.h"

#include "NSISAPI.h"

///////////////////////////////////////////////////////////////////////////////
/// @fn FB::variant NSISAPI::echo(const FB::variant& msg)
///
/// @brief  Echos whatever is passed from Javascript.
///         Go ahead and change it. See what happens!
///////////////////////////////////////////////////////////////////////////////
FB::variant NSISAPI::echo(const FB::variant& msg)
{
    static int n(0);
    fire_echo("So far, you clicked this many times: ", n++);

    // return "foobar";
    return msg;
}

///////////////////////////////////////////////////////////////////////////////
/// @fn NSISPtr NSISAPI::getPlugin()
///
/// @brief  Gets a reference to the plugin that was passed in when the object
///         was created.  If the plugin has already been released then this
///         will throw a FB::script_error that will be translated into a
///         javascript exception in the page.
///////////////////////////////////////////////////////////////////////////////
NSISPtr NSISAPI::getPlugin()
{
    NSISPtr plugin(m_plugin.lock());
    if (!plugin) {
        throw FB::script_error("The plugin is invalid");
    }
    return plugin;
}

// Read/Write property testString
std::string NSISAPI::get_testString()
{
    return m_testString;
}

void NSISAPI::set_testString(const std::string& val)
{
    m_testString = val;
}

// Read-only property version
std::string NSISAPI::get_version()
{
    return FBSTRING_PLUGIN_VERSION;
}

void NSISAPI::testEvent()
{
    fire_test();
}
