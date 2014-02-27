#include "VRScene.h"

using namespace VR;
using namespace osg;

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