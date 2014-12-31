Introduction

This example shows a dll runnable inside a web using FireBreath.
The dll uses an exe included in ExeForWebAndNormal. ExeForWebAndNormal
includes an exe which can also be executed normally (not in the web).

Compilation Instructions

This example is adjusted for Matej's computer. 
1. Compile ExeForWebAndNormal. For running in the web or normally, choose 
the correct line in main.cpp:

	int main(int argc, char * argv[])	{
		main_Plugin(argc, argv);
	//	main_GIT(argc, argv);
	}

2. Optional: For web, generate RedBall project in FireBreath and copy the
directories Chrome, Mac, ..., xpi - or use the ones in the distribution
3. Run prep2010.cmd "C:\Projekti\VRShop\ExercisesAndTutorials\OSGQtBrowser\FBPlugin\Src" "C:\Projekti\VRShop\ExercisesAndTutorials\OSGQtBrowser\FBPlugin\Build"
4. Open CMake and assign in "Where to build the binaries" the value "C:\Projekti\VRShop\ExercisesAndTutorials\OSGQtBrowser\FBPlugin\Build"
Please note that somehow the "Where is the source code" points to
"C:/Programi/FireBreath/firebreath-FireBreath-105dcc6"
5. Feel in the FB/FB_PROJECTS_DIR variable the value
"C:\Projekti\VRShop\ExercisesAndTutorials\OSGQtBrowser\FBPlugin\Src"
6. Configure
7. Generate
8. regsvr32 npRedBall.dll in the correct directory, i.e.:

C:\Projekti\VRShop\ExercisesAndTutorials\OSGQtBrowser\FBPlugin\Build\bin\RedBall\Debug>regsvr32 npRedBall.dll

9. Load the file FBControl.htm in the browser which was generated in 
C:\Projekti\VRShop\ExercisesAndTutorials\OSGQtBrowser\FBPlugin\Build\projects\RedBall\gen


Note: Please see the connection to the exe in file RedBall.cpp as follows:
QString strFPExe = 
	"C:/Projekti/VRShop/ExercisesAndTutorials/OSGQtBrowser/ExeForWebAndNormal/Build/Test_libModel/Debug/Test_libModel.exe";
