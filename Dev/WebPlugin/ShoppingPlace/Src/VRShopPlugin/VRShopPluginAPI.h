/**********************************************************\

  Auto-generated VRShopPluginAPI.h

\**********************************************************/

#include <string>
#include <sstream>

#include <boost/weak_ptr.hpp>
#include <boost/optional.hpp>

#include "JSAPIAuto.h"
#include "BrowserHost.h"
#include "VRShopPlugin.h"

#ifndef H_VRShopPluginAPI
#define H_VRShopPluginAPI

class VRShopPluginAPI : public FB::JSAPIAuto	{
public:
    VRShopPluginAPI(const VRShopPluginPtr& plugin, const FB::BrowserHostPtr& host);
    virtual ~VRShopPluginAPI();

    VRShopPluginPtr getPlugin();

    // Read-only property ${PROPERTY.ident}
    std::string get_version();

    // Event helpers
	FB_JSAPI_EVENT(applicationready, 0, ());

    // Method test-event
	bool runApplication(const FB::JSObjectPtr &callback);

	void runApplicationThread(const FB::JSObjectPtr &callback);
private:
    VRShopPluginWeakPtr m_plugin;
    FB::BrowserHostPtr m_host;
};

#endif // H_VRShopPluginAPI

