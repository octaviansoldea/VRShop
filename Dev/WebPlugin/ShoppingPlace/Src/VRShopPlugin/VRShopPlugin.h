/**********************************************************\

  Auto-generated VRShopPlugin.h

  This file contains the auto-generated main plugin object
  implementation for the VRShopPlugin project

\**********************************************************/
#ifndef H_VRShopPluginPLUGIN
#define H_VRShopPluginPLUGIN

#include <string>

#include "PluginWindow.h"
#include "PluginEvents/MouseEvents.h"
#include "PluginEvents/AttachedEvent.h"

#include <Win/PluginWindowWin.h>

#include "PluginCore.h"

namespace VR {class PipeServer;};

namespace VR	{
	class Process	{
	public:
		Process();
		~Process();

		void newProcess(std::string & astrApplicationName, std::string & astrArguments);
	};
}

FB_FORWARD_PTR(VRShopPlugin)
class VRShopPlugin : public FB::PluginCore	{
public:
    static void StaticInitialize();
    static void StaticDeinitialize();

public:
    VRShopPlugin();
    virtual ~VRShopPlugin();

public:
    void onPluginReady();
    void shutdown();
    virtual FB::JSAPIPtr createJSAPI();
    // If you want your plugin to always be windowless, set this to true
    // If you want your plugin to be optionally windowless based on the
    // value of the "windowless" param tag, remove this method or return
    // FB::PluginCore::isWindowless()
    virtual bool isWindowless() { return false; };

    BEGIN_PLUGIN_EVENT_MAP()
        EVENTTYPE_CASE(FB::MouseDownEvent, onMouseDown, FB::PluginWindow)
        EVENTTYPE_CASE(FB::MouseUpEvent, onMouseUp, FB::PluginWindow)
        EVENTTYPE_CASE(FB::MouseMoveEvent, onMouseMove, FB::PluginWindow)
        EVENTTYPE_CASE(FB::MouseMoveEvent, onMouseMove, FB::PluginWindow)
        EVENTTYPE_CASE(FB::AttachedEvent, onWindowAttached, FB::PluginWindow)
        EVENTTYPE_CASE(FB::DetachedEvent, onWindowDetached, FB::PluginWindow)
    END_PLUGIN_EVENT_MAP()

    /** BEGIN EVENTDEF -- DON'T CHANGE THIS LINE **/
    virtual bool onMouseDown(FB::MouseDownEvent *evt, FB::PluginWindow *);
    virtual bool onMouseUp(FB::MouseUpEvent *evt, FB::PluginWindow *);
    virtual bool onMouseMove(FB::MouseMoveEvent *evt, FB::PluginWindow *);
    virtual bool onWindowAttached(FB::AttachedEvent *evt, FB::PluginWindow *);
    virtual bool onWindowDetached(FB::DetachedEvent *evt, FB::PluginWindow *);
    /** END EVENTDEF -- DON'T CHANGE THIS LINE **/

	void runApplicationThread();

private:
	VR::PipeServer * m_pPipe;
	VR::Process * m_pProcess;
};


#endif

