#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for NSIS
#
#\**********************************************************/

set(PLUGIN_NAME "NSIS")
set(PLUGIN_PREFIX "NSIS")
set(COMPANY_NAME "VRShop")

# ActiveX constants:
set(FBTYPELIB_NAME NSISLib)
set(FBTYPELIB_DESC "NSIS 1.0 Type Library")
set(IFBControl_DESC "NSIS Control Interface")
set(FBControl_DESC "NSIS Control Class")
set(IFBComJavascriptObject_DESC "NSIS IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "NSIS ComJavascriptObject Class")
set(IFBComEventSource_DESC "NSIS IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID fb09a007-826b-5a1b-840d-6b2d8b086eae)
set(IFBControl_GUID 4336ae22-a86c-526c-bde4-2da610be5257)
set(FBControl_GUID 60c98c87-a945-53d7-a8bc-b34740e4658b)
set(IFBComJavascriptObject_GUID c50e68fb-6cd9-57f0-8c28-05735e83e8d0)
set(FBComJavascriptObject_GUID 4c3e3de8-5d09-5da7-97c2-e44a07c383c6)
set(IFBComEventSource_GUID 494c5f8d-76bb-53bc-a599-7b13b1217bab)
if ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID ef1deb71-f3cc-5ecd-bffb-7348785c3c21)
else ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID b8384c3a-10ce-598b-999a-4507a545faf0)
endif ( FB_PLATFORM_ARCH_32 )

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "VRShop.NSIS")
if ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "MatejTavi.com/NSIS")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "MatejTavi.com/NSIS_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )

# strings
set(FBSTRING_CompanyName "VRShop")
set(FBSTRING_PluginDescription "NSIS Installer plugin")
set(FBSTRING_PLUGIN_VERSION "1.0.0.0")
set(FBSTRING_LegalCopyright "Copyright 2015 VRShop")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}")
set(FBSTRING_ProductName "NSIS")
set(FBSTRING_FileExtents "")
if ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "NSIS")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "NSIS_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )
set(FBSTRING_MIMEType "application/x-nsis")

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
