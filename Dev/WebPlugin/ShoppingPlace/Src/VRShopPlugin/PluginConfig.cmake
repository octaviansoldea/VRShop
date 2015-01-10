#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for VRShopPlugin
#
#\**********************************************************/

set(PLUGIN_NAME "VRShopPlugin")
set(PLUGIN_PREFIX "VSP")
set(COMPANY_NAME "VRShop")

# ActiveX constants:
set(FBTYPELIB_NAME VRShopPluginLib)
set(FBTYPELIB_DESC "VRShopPlugin 1.0 Type Library")
set(IFBControl_DESC "VRShopPlugin Control Interface")
set(FBControl_DESC "VRShopPlugin Control Class")
set(IFBComJavascriptObject_DESC "VRShopPlugin IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "VRShopPlugin ComJavascriptObject Class")
set(IFBComEventSource_DESC "VRShopPlugin IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID 94cc0baf-af1c-528f-9cb2-30e9b170d317)
set(IFBControl_GUID 2bfb9baf-ca53-5a9e-b630-60c37c55f09a)
set(FBControl_GUID 737f802e-7de8-5d8c-8b4b-6c11893e69a3)
set(IFBComJavascriptObject_GUID 7009b15d-62f5-5414-b579-79f13da0053b)
set(FBComJavascriptObject_GUID 9e757313-f587-5de5-86ff-f49ed3022e9f)
set(IFBComEventSource_GUID a4ab68cd-c33b-5a05-825b-836f9d7f5d58)
if ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID b4a5b791-dccd-597c-ab7e-2b9b592866a8)
else ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID e989526a-b0c5-5bdd-ab98-8a4d7396a6aa)
endif ( FB_PLATFORM_ARCH_32 )

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "VRShop.VRShopPlugin")
if ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "MatejTavi.com/VRShopPlugin")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "MatejTavi.com/VRShopPlugin_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )

# strings
set(FBSTRING_CompanyName "VRShop")
set(FBSTRING_PluginDescription "VRShop plugin")
set(FBSTRING_PLUGIN_VERSION "1.0.0.0")
set(FBSTRING_LegalCopyright "Copyright 2015 VRShop")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}")
set(FBSTRING_ProductName "VRShopPlugin")
set(FBSTRING_FileExtents "")
if ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "VRShopPlugin")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "VRShopPlugin_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )
set(FBSTRING_MIMEType "application/x-vrshopplugin")

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
