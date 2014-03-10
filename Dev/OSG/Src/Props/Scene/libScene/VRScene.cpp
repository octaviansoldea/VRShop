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
}

//--------------------------------------------------------------

Scene::~Scene()	{
}

//=======================================================================

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
}

//--------------------------------------------------------------

void Scene::removeElement(ref_ptr<Node> apElement)	{
	removeChild(apElement);
}

//--------------------------------------------------------------

void Scene::clearScene()	{
	removeChildren(0,getNumChildren());
}

//--------------------------------------------------------------

void Scene::print()	{

	string strFileName = string("C:/Projekti/VRShop/Dev/OSG/Log/" + itostr(m_nIteration) + string(".txt"));
	ofstream output(strFileName);

	int nI;

	output << "SCENE" << endl;

	output << "Scene objects by name: " << endl;
	for (nI=0;nI<this->getNumChildren(); nI++)	{
		output << this->getChild(nI)->getName() << endl;
	}

	output << "========================================================" << endl;

	ref_ptr<VR::AbstractObject> pObject;
	for (nI = 2; nI < this->getNumChildren(); nI++)	{
		pObject = dynamic_cast<VR::AbstractObject*>(this->getChild(nI));
		pObject->print(output);
	}

	output.close();
	m_nIteration++;
}

//----------------------------------------------------------------------
