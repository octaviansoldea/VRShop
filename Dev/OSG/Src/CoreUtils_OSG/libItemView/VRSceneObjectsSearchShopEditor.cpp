#include <iostream>
#include "BasicStringDefinitions.h"

#include "VRScene.h"

#include "VRSceneObjectsSearchShopEditor.h"

using namespace VR;
using namespace std;

//--------------------------------------------------------------------

SceneObjectsSearchShopEditor::SceneObjectsSearchShopEditor(const string & astrSearchQuery, const Scene * apScene) :
SceneObjectsSearch(astrSearchQuery,apScene) {
}

//--------------------------------------------------------------------

SceneObjectsSearchShopEditor::~SceneObjectsSearchShopEditor()	{
}

//--------------------------------------------------------------------

SceneStructureModel * SceneObjectsSearchShopEditor::getModel() const	{
	return this->m_pSceneStructureModel;
}

//--------------------------------------------------------------------
