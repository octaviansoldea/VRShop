#include <string>
#include <fstream>
#include <iostream>

#include <vector>

#include "BasicStringDefinitions.h"
#include "Log.h"

#include "VRAbstractObject.h"

#include "VRScene.h"

using namespace VR;
using namespace osg;
using namespace std;


//--------------------------------------------------------------

Scene::Scene() : m_nIteration(0) {
	setName("Untitled");
}

//--------------------------------------------------------------

Scene::Scene(const std::string & astrDBFileName) :
m_strDBFileName(astrDBFileName),
m_nIteration(0)	{
	setName(m_strDBFileName);
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

	//New child is an "Object"
	bRes = Group::addChild(child);

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
}

//--------------------------------------------------------------

string Scene::SQLFieldValues(const string & astrParentName)	{
	return (getName());
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
