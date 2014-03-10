#include <iostream>
#include "BasicStringDefinitions.h"

#include "VRSceneStructureModel.h"

#include "VRAbstractObject.h"
#include "VRScene.h"

#include "VRSceneObjectsSearchShopEditor.h"

using namespace VR;
using namespace std;

//--------------------------------------------------------------------

SceneObjectsSearchShopEditor::SceneObjectsSearchShopEditor() : SceneObjectsSearch()	{
}

//--------------------------------------------------------------------

SceneObjectsSearchShopEditor::SceneObjectsSearchShopEditor(const QString & aqstrSearchQuery, Scene * apScene) :
SceneObjectsSearch(aqstrSearchQuery,apScene) {

	connect(m_pSceneStructureModel,
		SIGNAL(dataChanged(const QModelIndex &,const QModelIndex &)),
		this, SLOT(slotChangeName(const QModelIndex &))
	);
}

//--------------------------------------------------------------------

SceneObjectsSearchShopEditor::~SceneObjectsSearchShopEditor()	{
}

//--------------------------------------------------------------------

SceneStructureModel * SceneObjectsSearchShopEditor::getModel() const	{
	return this->m_pSceneStructureModel;
}

//--------------------------------------------------------------------

void SceneObjectsSearchShopEditor::slotChangeName(const QModelIndex & anIndex)	{
	string & strPrevName = m_pSceneStructureModel->getPrevValue().toString().toStdString();
	AbstractObject * pObject = dynamic_cast<AbstractObject*>(m_pScene->getChild(strPrevName));

	if (!pObject)
		return;

	string & strNewName = anIndex.data().toString().toStdString();
	pObject->setName(strNewName);
}