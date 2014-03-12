#include <iostream>

#include "BasicStringDefinitions.h"

#include "VRAbstractObject.h"
#include "VRScene.h"

#include "VRSceneHierarchy.h"

using namespace VR;
using namespace osg;
using namespace std;

//====================================================================

SceneHierarchy::SceneHierarchy()	{

	m_vecstrSceneHierarchy.push_back("Agents");
	m_vecstrSceneHierarchy.push_back("Furniture");
	m_vecstrSceneHierarchy.push_back("Products");

	setSceneHierarchy();
}

//--------------------------------------------------------------------

void SceneHierarchy::setSceneHierarchy()	{
}

//--------------------------------------------------------------------

QList < QString > SceneHierarchy::getSceneHierarchy() const	{
	
	return m_vecstrSceneHierarchy;
}

//--------------------------------------------------------------------

void SceneHierarchy::updateHierarchy()	{
}

//====================================================================
