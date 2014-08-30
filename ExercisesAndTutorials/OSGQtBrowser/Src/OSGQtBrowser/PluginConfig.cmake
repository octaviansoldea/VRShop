#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for OSGQtBrowser
#
#\**********************************************************/

set(PLUGIN_NAME "OSGQtBrowser")
set(PLUGIN_PREFIX "OQT")
set(COMPANY_NAME "VRShop")

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
set(FBTYPELIB_GUID 6af72188-feab-5ec3-8606-f6f1cf529aeb)
set(IFBControl_GUID fdc55d90-3487-5a48-8ca9-a79e57f9dd01)
set(FBControl_GUID 2db12cb5-0d59-5160-84c4-1e25a564c64b)
set(IFBComJavascriptObject_GUID a8a57b1d-aeef-5132-9f5a-ebb77abcbce5)
set(FBComJavascriptObject_GUID 88d29b4d-c3a6-5861-a42c-228b2ccbd7b0)
set(IFBComEventSource_GUID a3430d60-90ce-5309-9ff0-cf62ecd89c3f)
if ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID 342352b3-fead-5061-8033-cf4b2192bea9)
else ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID c4931784-4e58-5e77-9aa6-4d148824e438)
endif ( FB_PLATFORM_ARCH_32 )

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "VRShop.OSGQtBrowser")
if ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "vrshop.com/OSGQtBrowser")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "vrshop.com/OSGQtBrowser_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )

# strings
set(FBSTRING_CompanyName "VRShop")
set(FBSTRING_PluginDescription "OSGQt browser plugin")
set(FBSTRING_PLUGIN_VERSION "1.0.0.0")
set(FBSTRING_LegalCopyright "Copyright 2014 VRShop")
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
