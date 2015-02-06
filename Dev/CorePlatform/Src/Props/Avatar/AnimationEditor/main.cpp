#include <QApplication>
#include "VRKeyboardMouseManipulator.h"

#include <iostream>
#include <string>

#include <osgDB/ReadFile>
#include <osgDB/writeFile>
#include <osg/AnimationPath>

#include "AnimtkViewer.h"
#include "AnimtkViewerGUI.h"
#include "AnimtkViewerKeyHandler.h"

#include "VRAxes.h"

#include "VRAnimationEditorGUI.h"

#include <osgViewer/Viewer>

using namespace std;
using namespace osg;
using namespace Ui;
using namespace VR;

int main(int argc, char * argv[])	{

	QApplication app(argc,argv);
	AnimationEditorGUI animGUI;

	int nRes = app.exec();
	return nRes;
}