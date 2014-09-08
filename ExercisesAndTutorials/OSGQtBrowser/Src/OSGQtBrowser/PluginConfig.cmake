#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for OSGQtBrowser
#
#\**********************************************************/

set(PLUGIN_NAME "OSGQtBrowser")
set(PLUGIN_PREFIX "OQT")
set(COMPANY_NAME "OSGQtBrowser")

# ActiveX constants:
set(FBTYPELIB_NAME OSGQtBrowserLib)
set(FBTYPELIB_DESC "OSGQtBrowser 1.0 Type Library")
set(IFBControl_DESC "OSGQtBrowser Control Interface")
set(FBControl_DESC "OSGQtBrowser Control Class")
set(IFBComJavascriptObject_DESC "OSGQtBrowser IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "OSGQtBrowser ComJavascriptObject Class")
set(IFBComEventSource_DESC "OSGQtBrowser IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID 7907c690-f5b5-5a8d-8672-fc77a6418fca)
set(IFBControl_GUID 9fd962a3-9f52-5759-b0dc-0cbf28883d11)
set(FBControl_GUID 4523b7f0-cb55-587b-b9db-7b3f1a927627)
set(IFBComJavascriptObject_GUID 23d9b5e3-b28d-5dd6-a08e-e37f944c7b13)
set(FBComJavascriptObject_GUID 38433379-b9df-5c43-a91a-f2be48d2fa8b)
set(IFBComEventSource_GUID 826d79d6-3680-55a2-bd9f-3e3bcbc61491)
if ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID b906e072-e541-57be-9037-cf328ffa80f1)
else ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID 2933ad51-def3-5884-97b6-cac7aa6c85d6)
endif ( FB_PLATFORM_ARCH_32 )

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "OSGQtBrowser.OSGQtBrowser")
if ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "OSGQtBrowser.com/OSGQtBrowser")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "OSGQtBrowser.com/OSGQtBrowser_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )

# strings
set(FBSTRING_CompanyName "OSGQtBrowser")
set(FBSTRING_PluginDescription "OSGQtBrowser")
set(FBSTRING_PLUGIN_VERSION "1.0.0.0")
set(FBSTRING_LegalCopyright "Copyright 2014 OSGQtBrowser")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}")
set(FBSTRING_ProductName "OSGQtBrowser")
set(FBSTRING_FileExtents "")
if ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "OSGQtBrowser")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "OSGQtBrowser_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )
set(FBSTRING_MIMEType "application/x-osgqtbrowser")

# Uncomment this next line if you're not planning on your plugin doing
# any drawing:

#set (FB_GUI_DISABLED 1)

# Mac plugin settings. If your plugin does not draw, set these all to 0
set(FBMAC_USE_QUICKDRAW 0)
set(FBMAC_USE_CARBON 1)
set(FBMAC_USE_COCOA 1)
set(FBMAC_USE_COREGRAPHICS 1)
set(FBMAC_USE_COREANIMATION 0)
set(FBMAC_USE_INVALIDATINGCOREANIMATION 0)

# If you want to register per-machine on Windows, uncomment this line
#set (FB_ATLREG_MACHINEWIDE 1)
