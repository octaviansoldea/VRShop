#include <string>
#include <fstream>
#include <iostream>

#include <vector>

#include "BasicStringDefinitions.h"
#include "Log.h"

#include "VRAbstractObject.h"
#include "VRDatabaseController.h"

#include "VRScene.h"

using namespace VR;
using namespace osg;
using namespace std;


//--------------------------------------------------------------

Scene::Scene() : m_nIteration(0) {
	setName("Scene");
}

//--------------------------------------------------------------

Scene::~Scene()	{
}

//=======================================================================

const char* Scene::className() const	{
	return "Scene";
}

//-----------------------------------------------------------------------

Scene * Scene::getScene(const std::string & astrSceneName)	{
	if (astrSceneName.empty())	{
		return 0;
	}
	int nI;
	Scene * pScene = 0;
	for (nI=0; nI < m_pvecScene.size(); nI++)	{
		pScene = m_pvecScene[nI];
		if (pScene->getName() == astrSceneName)	{
			return m_pvecScene[nI];
		}
	}
	return 0;
}

//-----------------------------------------------------------------------

Node * Scene::getChild(const string & astrChildName)	{
	Node * pChild = 0;
	if (astrChildName.empty())	{
		return pChild;
	}

	NodeList::iterator it = _children.begin();
	for (it; it != _children.end(); it++)	{
		const string & strChild = it->get()->getName();
		if (strChild == astrChildName)	{
			pChild = dynamic_cast<Node*>(it->get());

			return pChild;
		}
	}
	return pChild;
}

//--------------------------------------------------------------

bool Scene::addChild(Node *child)	{
	bool bRes = true;
	AbstractObject * pChild = dynamic_cast<AbstractObject*>(child);
	if(pChild == 0)	{
		bRes = Group::addChild(child);
		return bRes;
	}

	//If "Child" is a Scene, then only fill the vector of "scenes"
	//Can be put into a separate function
	if (pChild->className() == "Scene")	{
		m_pvecScene.push_back(dynamic_cast<Scene*>(pChild));
		return bRes;
	}

	//New child is an "Object"
	bRes = Group::addChild(child);

	//INSERT AN OBJECT (along with its children) into the SCENE
	const string * pstrScene = &getName();
	vector<string> vecstrData;
	pChild->addChild2DB(vecstrData);

	DatabaseController dbController(pstrScene,&vecstrData,DatabaseController::ADD);

	return bRes;
}

//--------------------------------------------------------------

bool Scene::removeChild(Node *child)	{
	bool bRes = Group::removeChild(child);

	return bRes;
}

//--------------------------------------------------------------

void Scene::clearScene()	{
	removeChildren(0,getNumChildren());
	setSceneHierarchy();
}

//--------------------------------------------------------------

void Scene::setSceneHierarchy()	{
	if (getNumChildren() == 0)	
		return;

	m_vecstrSceneHierarchy.clear();

	NodeList::iterator it = _children.begin();
	AbstractObject * pObject = 0;
	for (it; it != _children.end(); it++)	{
		pObject = dynamic_cast<AbstractObject*>(it->get());
		if (pObject != 0)	{
			pObject->writeObjectHierarchy(m_vecstrSceneHierarchy);
		}
	}
}

//--------------------------------------------------------------

vector<string> Scene::getSceneHierarchy()	{
	return m_vecstrSceneHierarchy;
}


//==============================================================

void Scene::print()	{

	string strFileName = getLogFile();
	ofstream output(strFileName, ios::app);
	output << "========================================================Begin Scene" << endl;

	int nI;

	output << "SCENE at iteration " << m_nIteration << endl;

	output << "Scene objects by name: " << endl;
	NodeList::iterator it;
	for (it = _children.begin(); it != _children.end(); it++)	{
		output << "Parent: " << it->get()->getParent(0)->getName()
			<< "; Class Name:" << it->get()->className() << "; Object Name: " <<it->get()->getName() << endl;
	}

	

	ref_ptr<VR::AbstractObject> pObject;
	for (it = _children.begin(); it != _children.end(); it++)	{
		nI = it - _children.begin();
		pObject = dynamic_cast<VR::AbstractObject*>(this->getChild(nI));
		if (!pObject.valid())
			continue;
		else
			pObject->print(output);
	}
	output << "========================================================End Scene" << endl;

	output.close();
	m_nIteration++;
	
}

//----------------------------------------------------------------------

string m_strSQLFormat =
	"CREATE TABLE IF NOT EXISTS Scene \
	(SceneID INTEGER PRIMARY KEY AUTOINCREMENT,\
	SceneName TEXT);";
