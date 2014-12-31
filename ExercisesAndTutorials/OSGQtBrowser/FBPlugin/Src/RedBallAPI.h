/**********************************************************\

  Auto-generated RedBallAPI.h

\**********************************************************/

#include <string>
#include <sstream>
#include <boost/weak_ptr.hpp>
#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "RedBall.h"

#ifndef H_RedBallAPI
#define H_RedBallAPI

class RedBallAPI : public FB::JSAPIAuto
{
public:
    ////////////////////////////////////////////////////////////////////////////
    /// @fn RedBallAPI::RedBallAPI(const RedBallPtr& plugin, const FB::BrowserHostPtr host)
    ///
    /// @brief  Constructor for your JSAPI object.
    ///         You should register your methods, properties, and events
    ///         that should be accessible to Javascript from here.
    ///
    /// @see FB::JSAPIAuto::registerMethod
    /// @see FB::JSAPIAuto::registerProperty
    /// @see FB::JSAPIAuto::registerEvent
    ////////////////////////////////////////////////////////////////////////////
    RedBallAPI(const RedBallPtr& plugin, const FB::BrowserHostPtr& host) :
        m_plugin(plugin), m_host(host)
    {
        registerMethod("echo",      make_method(this, &RedBallAPI::echo));
        registerMethod("testEvent", make_method(this, &RedBallAPI::testEvent));
        
        // Read-write property
        registerProperty("testString",
                         make_property(this,
                                       &RedBallAPI::get_testString,
                                       &RedBallAPI::set_testString));
        
        // Read-only property
        registerProperty("version",
                         make_property(this,
                                       &RedBallAPI::get_version));
    }

    ///////////////////////////////////////////////////////////////////////////////
    /// @fn RedBallAPI::~RedBallAPI()
    ///
    /// @brief  Destructor.  Remember that this object will not be released until
    ///         the browser is done with it; this will almost definitely be after
    ///         the plugin is released.
    ///////////////////////////////////////////////////////////////////////////////
    virtual ~RedBallAPI() {};

    RedBallPtr getPlugin();

    // Read/Write property ${PROPERTY.ident}
    std::string get_testString();
    void set_testString(const std::string& val);

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    // Method echo
    FB::variant echo(const FB::variant& msg);
    
    // Event helpers
    FB_JSAPI_EVENT(test, 0, ());
    FB_JSAPI_EVENT(echo, 2, (const FB::variant&, const int));

    // Method test-event
    void testEvent();

private:
    RedBallWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;

    std::string m_testString;
};

#endif // H_RedBallAPI

