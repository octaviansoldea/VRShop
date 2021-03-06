#include <string>
#include <fstream>
#include <iostream>

#include <vector>

#include "BasicStringDefinitions.h"
#include "Log.h"

#include "VRAbstractObject.h"

#include <osg/ComputeBoundsVisitor>

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

//=======================================================================

const char* Scene::className() const	{
	return "Scene";
}

//-----------------------------------------------------------------------

Node * Scene::getChild(const string & astrChildName)	{
	if (astrChildName.empty())	{
		return 0;
	}

	NodeList::iterator it = _children.begin();
	for (it; it != _children.end(); it++)	{
		const string strChild = it->get()->getName();
		if (strChild == astrChildName)	{
			Node * pChild = dynamic_cast<Node*>(it->get());

			return pChild;
		}
	}
	return 0;
}

//--------------------------------------------------------------

bool Scene::addChild(Node *child)	{
	bool bRes = true;
	ref_ptr<AbstractObject> pChild = dynamic_cast<AbstractObject*>(child);
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

Matrixd Scene::calculateInitialCameraMatrix()	{
	ComputeBoundsVisitor cbv;
	accept(cbv);

	Vec3d vec3dSceneCorner = cbv.getBoundingBox().corner(5);	//Camera positioned 
	Vec3d vec3dSceneCenter = cbv.getBoundingBox().center();

	Vec3d vec3dEye = Vec3d(vec3dSceneCenter.x(),vec3dSceneCorner.y(),vec3dSceneCorner.z());
	Vec3d vec3dCenter = Vec3d(vec3dEye.x(),0.0,0.0);
	Vec3d vec3dDiff = vec3dCenter - vec3dEye;
	Vec3d vec3dPerp = Vec3d(0,0,1)^vec3dDiff;
	Vec3d vec3dUp = vec3dDiff^vec3dPerp;
	vec3dUp.normalize();

	//Also set the camera
	Matrixd mtrxSceneCameraMatrix = Matrix::inverse(Matrix::lookAt(vec3dEye, vec3dCenter, vec3dUp));

	return mtrxSceneCameraMatrix;
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

	
	for (it = _children.begin(); it != _children.end(); it++)	{
		nI = it - _children.begin();
		ref_ptr<VR::AbstractObject> pObject = dynamic_cast<VR::AbstractObject*>(this->getChild(nI));
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

Node* Scene::findNamedNode(const string& searchName, Node* currNode)	{
	osg::Group* currGroup;
	osg::Node* foundNode;

	// check to see if we have a valid (non-NULL) node.
	// if we do have a null node, return NULL.
	if ( !currNode)	{
		return NULL;
	}

	// We have a valid node, check to see if this is the node we 
	// are looking for. If so, return the current node.
	if (currNode->getName() == searchName)	{
		return currNode;
	}

	// We have a valid node, but not the one we are looking for.
	// Check to see if it has children (non-leaf node). If the node
	// has children, check each of the child nodes by recursive call.
	// If one of the recursive calls returns a non-null value we have
	// found the correct node, so return this node.
	// If we check all of the children and have not found the node,
	// return NULL
	currGroup = currNode->asGroup(); // returns NULL if not a group.
	if ( currGroup )	{
		for (unsigned int i = 0 ; i < currGroup->getNumChildren(); i ++)	{
			foundNode = findNamedNode(searchName, currGroup->getChild(i));
			if (foundNode)
				return foundNode; // found a match!
		}
		return NULL; // We have checked each child node - no match found.
	} else {
		return NULL; // leaf node, no match 
	}
}