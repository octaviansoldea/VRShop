#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for VRShop
#
#\**********************************************************/

set(PLUGIN_NAME "VRShop")
set(PLUGIN_PREFIX "VSH")
set(COMPANY_NAME "VRShop")

# ActiveX constants:
set(FBTYPELIB_NAME VRShopLib)
set(FBTYPELIB_DESC "VRShop 1.0 Type Library")
set(IFBControl_DESC "VRShop Control Interface")
set(FBControl_DESC "VRShop Control Class")
set(IFBComJavascriptObject_DESC "VRShop IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "VRShop ComJavascriptObject Class")
set(IFBComEventSource_DESC "VRShop IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID db22d8ce-7397-5941-8cff-31483eaf18ae)
set(IFBControl_GUID 96595a30-9e29-554b-acb6-f0650cde534f)
set(FBControl_GUID 5a384e78-a335-555e-88da-b4a75450e4cd)
set(IFBComJavascriptObject_GUID a14579f9-ff2a-5781-80f4-c82f609d717d)
set(FBComJavascriptObject_GUID 0c5dce17-6a2a-5fb7-b9a8-43ff47cd0caa)
set(IFBComEventSource_GUID c2c1c9a0-ef10-5e8d-bc62-122af0ac8c66)
if ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID 2bde5297-66b0-5da8-988f-c9ffdb887228)
else ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID 33142632-eb3b-50e7-b03d-bb4b14c4f98c)
endif ( FB_PLATFORM_ARCH_32 )

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "VRShop.VRShop")
if ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "vrshop.com/VRShop")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "vrshop.com/VRShop_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )

# strings
set(FBSTRING_CompanyName "VRShop")
set(FBSTRING_PluginDescription "VRShop Web plugin")
set(FBSTRING_PLUGIN_VERSION "1.0.0.0")
set(FBSTRING_LegalCopyright "Copyright 2014 VRShop")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}")
set(FBSTRING_ProductName "VRShop")
set(FBSTRING_FileExtents "")
if ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "VRShop")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "VRShop_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )
set(FBSTRING_MIMEType "application/x-vrshop")

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
