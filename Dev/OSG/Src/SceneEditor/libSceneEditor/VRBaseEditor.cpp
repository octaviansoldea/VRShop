#include "VRQOSGWidget.h"

#include <osgDB/readFile>

#include "OSGCameraManipulator.h"

#include <string>

#include "VRBaseEditor.h"

using namespace VR;
using namespace osg;
using namespace std;

//--------------------------------------------------------------------------------

BaseEditor::BaseEditor() {
	string strDB = "../../Databases/Products.db";
	pDatabaseMgr = &DatabaseMgr::Create(strDB.c_str(), DatabaseMgr::QSQLITE);
}

//--------------------------------------------------------------------------------

BaseEditor::~BaseEditor() {
	delete pDatabaseMgr;
}

//--------------------------------------------------------------------------------

void BaseEditor::setQOSGWidgets(QOSGWidget * apQOSGWidget) {
	m_pQOSGWidget = apQOSGWidget;

	//Define a scene as a group
	ref_ptr<Group> pScene = new Group;

	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../Resources/Models3D/axes.osgt");
	pScene->addChild(pAxes);

	//Send scene to the Widget
	m_pQOSGWidget->setSceneData(pScene);
	m_pQOSGWidget->setCameraManipulator(new OSGCameraManipulator);

	m_pQOSGWidget->show();
}

//--------------------------------------------------------------------------------
