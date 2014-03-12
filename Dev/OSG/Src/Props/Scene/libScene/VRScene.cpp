#include <string>
#include <fstream>

#include "BasicStringDefinitions.h"

#include "VRAbstractObject.h"
#include "VRScene.h"

using namespace VR;
using namespace osg;
using namespace std;

int Scene::m_nIteration = 0;

//--------------------------------------------------------------

Scene::Scene()	{
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

Node * Scene::getChild(const string & astrChildName)	{
	Node * pChild = 0;
	if (astrChildName.empty())	{
		return pChild;
	}

	NodeList::iterator it = _children.begin();
	for (it; it != _children.end(); it++)	{
		string strChild = it->get()->getName();
		if (strChild == astrChildName)	{
			pChild = dynamic_cast<Node*>(it->get());

			return pChild;
		}
	}
	return pChild;
}

//--------------------------------------------------------------

void Scene::addElement(ref_ptr<Node> apElement)	{
	addChild(apElement);
	setSceneHierarchy();
}

//--------------------------------------------------------------

void Scene::removeElement(ref_ptr<Node> apElement)	{
	removeChild(apElement);
	setSceneHierarchy();
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
		if (pObject != 0)
			pObject->writeObjectHierarchy(m_vecstrSceneHierarchy);
	}
}

//--------------------------------------------------------------

vector<string> Scene::getSceneHierarchy()	{
	return m_vecstrSceneHierarchy;
}


//==============================================================

void Scene::print()	{

	string strFileName = string("../../../Log/" + itostr(m_nIteration) + string(".txt"));
	ofstream output(strFileName);

	int nI;

	output << "SCENE" << endl;

	output << "Scene objects by name: " << endl;
	NodeList::iterator it;
	for (it = _children.begin(); it != _children.end(); it++)	{
		output << "Parent: " << it->get()->getParent(0)->getName()
			<< "; Class Name:" << it->get()->className() << "; Object Name: " <<it->get()->getName() << endl;
	}

	output << "========================================================" << endl;

	ref_ptr<VR::AbstractObject> pObject;
	for (it = _children.begin() + 2; it != _children.end(); it++)	{
		nI = it - _children.begin();
		pObject = dynamic_cast<VR::AbstractObject*>(this->getChild(nI));
		pObject->print(output);
	}

	output.close();
	m_nIteration++;
}

//----------------------------------------------------------------------
