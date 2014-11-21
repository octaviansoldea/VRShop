#include <iostream>
#include "BasicStringDefinitions.h"

#include "VRDataStructureModel.h"

#include "VRAbstractObject.h"
#include "VRScene.h"

#include "VRSceneObjectsSearchShopEditor.h"

using namespace VR;
using namespace std;
using namespace osg;

//--------------------------------------------------------------------

SceneObjectsSearchShopEditor::SceneObjectsSearchShopEditor() : SceneObjectsSearch()	{
}

//--------------------------------------------------------------------

SceneObjectsSearchShopEditor::SceneObjectsSearchShopEditor(const QString & aqstrSearchQuery, Scene * apScene) :
SceneObjectsSearch(aqstrSearchQuery,apScene) {

	connect(m_pDataStructureModel,
		SIGNAL(dataChanged(const QModelIndex &,const QModelIndex &)),
		this, SLOT(slotChangeName(const QModelIndex &))
	);
}

//--------------------------------------------------------------------

DataStructureModel * SceneObjectsSearchShopEditor::getModel() const	{
	return this->m_pDataStructureModel;
}

//--------------------------------------------------------------------

void SceneObjectsSearchShopEditor::slotChangeName(const QModelIndex & anIndex)	{
	string strPrevName = m_pDataStructureModel->getPrevValue().toString().toStdString();
	ref_ptr<Node> pObject = dynamic_cast<Node*>(m_pScene->getChild(strPrevName));

	if (!pObject)
		return;

	string strNewName = anIndex.data().toString().toStdString();
	pObject->setName(strNewName);
}