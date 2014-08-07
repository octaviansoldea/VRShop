CMAKE_MINIMUM_REQUIRED(VERSION 2.8)

PROJECT(SceneEditorDlg)

SET(CMAKE_DEBUG_POSTFIX "D")
	
SUBDIRS(
  libPopUpGUIs
  libShopEditor
  Test_libShopEditor
  libShoppingPlace
  Test_libShoppingPlace
)