#/**********************************************************\ 
#
# Auto-Generated Plugin Configuration file
# for RedBall
#
#\**********************************************************/

set(PLUGIN_NAME "RedBall")
set(PLUGIN_PREFIX "RBA")
set(COMPANY_NAME "VRShop")

# ActiveX constants:
set(FBTYPELIB_NAME RedBallLib)
set(FBTYPELIB_DESC "RedBall 1.0 Type Library")
set(IFBControl_DESC "RedBall Control Interface")
set(FBControl_DESC "RedBall Control Class")
set(IFBComJavascriptObject_DESC "RedBall IComJavascriptObject Interface")
set(FBComJavascriptObject_DESC "RedBall ComJavascriptObject Class")
set(IFBComEventSource_DESC "RedBall IFBComEventSource Interface")
set(AXVERSION_NUM "1")

# NOTE: THESE GUIDS *MUST* BE UNIQUE TO YOUR PLUGIN/ACTIVEX CONTROL!  YES, ALL OF THEM!
set(FBTYPELIB_GUID aec3c84b-9676-57d7-af22-80c58fe1036c)
set(IFBControl_GUID 3e7d03cc-6a42-5c4e-9708-c930a52c7ae3)
set(FBControl_GUID ec870fee-064a-57d7-be1a-e6a0f6a32ab6)
set(IFBComJavascriptObject_GUID 3082b3df-9986-54fa-a05b-c5440866fe34)
set(FBComJavascriptObject_GUID b06eacec-141a-543e-bb91-eff729d8d8e1)
set(IFBComEventSource_GUID 627c0cf2-994e-5e69-a410-b0e4629dd322)
if ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID 0374deb4-51f3-5800-8795-b29e43250a3d)
else ( FB_PLATFORM_ARCH_32 )
    set(FBControl_WixUpgradeCode_GUID 2de9874b-a153-5c2a-99ca-9746ddef9d02)
endif ( FB_PLATFORM_ARCH_32 )

# these are the pieces that are relevant to using it from Javascript
set(ACTIVEX_PROGID "VRShop.RedBall")
if ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "MatejTavi.com/RedBall")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(MOZILLA_PLUGINID "MatejTavi.com/RedBall_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )

# strings
set(FBSTRING_CompanyName "VRShop")
set(FBSTRING_PluginDescription "RedBall plugin")
set(FBSTRING_PLUGIN_VERSION "1.0.0.0")
set(FBSTRING_LegalCopyright "Copyright 2014 VRShop")
set(FBSTRING_PluginFileName "np${PLUGIN_NAME}")
set(FBSTRING_ProductName "RedBall")
set(FBSTRING_FileExtents "")
if ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "RedBall")  # No 32bit postfix to maintain backward compatability.
else ( FB_PLATFORM_ARCH_32 )
    set(FBSTRING_PluginName "RedBall_${FB_PLATFORM_ARCH_NAME}")
endif ( FB_PLATFORM_ARCH_32 )
set(FBSTRING_MIMEType "application/x-redball")

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
