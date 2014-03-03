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
	ofstream output;
	output.open(strFileName);

	int nI;
	ref_ptr<VR::AbstractObject> pObject;
	for (nI = 2; nI < this->getNumChildren(); nI++)	{
		pObject = dynamic_cast<VR::AbstractObject*>(this->getChild(nI));
		pObject->print(output);
	}

	output.close();
	m_nIteration++;
}

//----------------------------------------------------------------------
