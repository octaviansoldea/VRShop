#General
!define APP_VERSION "1_0"
!define APP_NAME "VRShop"

Name ${APP_NAME}
OutFile "${APP_NAME}.exe" #where to write the installer to
InstallDir "$LOCALAPPDATA\${APP_NAME}" #App's installation directory

!define WEB_SERVER "127.0.0.1/Website"

#--------------------------------------------------------------

Function .onInit
    SetSilent silent
FunctionEnd

#--------------------------------------------------------------

!macro unzipFile aFileName aDirName
	nsisunz::Unzip ${aFileName} ${aDirName}	#nsisunz writes either "success" or an error onto a stack
	Pop $0	#Pops a string off of the stack into the variable $0
	StrCmp $0 "success" unzipDone
	DetailPrint "$0"
	Goto unzipFailed
	unzipDone:
	unzipFailed:
!macroend

#--------------------------------------------------------------

#Main section
Section "${APP_NAME}"
	#Check if directory present
	IfFileExists "$INSTDIR" +3
	Call fullInstall
	Goto end
	IfFileExists "$INSTDIR\Qt5*.dll" +4
	Push "Qt"
	Push ""
	Call downloadAndUnzip
	IfFileExists "$INSTDIR\osg*.dll" +4
	Push "osg"
	Push ""
	Call downloadAndUnzip
	end:
		Call runApplication
SectionEnd

#--------------------------------------------------------------

Function fullInstall
	CreateDirectory "$INSTDIR"
	Push "package"
	Push ""
	Call downloadAndUnzip
FunctionEnd

#--------------------------------------------------------------

Function downloadAndUnzip
	Exch
	#IMPORTANT: DON'T USE VARIABLE $2 IN THE "unzipFile" MACRO
	Pop $2	#a package
	Pop $1	#a folder
	
	NSISdl::download "${WEB_SERVER}/$2.zip" "$INSTDIR\$2.zip"	
	Pop $R0 #Get the return value NOTE: NSISdl::download pushes result ("success") to the stack
	StrCmp $R0 "success" proceed error
	
	proceed:
		!insertmacro unzipFile "$INSTDIR\$2.zip" "$INSTDIR\$1"
		Delete $INSTDIR\$2.zip
	error:
FunctionEnd

#--------------------------------------------------------------

Function runApplication
	Quit	#quits the installer ASAP
FunctionEnd

#==============================================================
