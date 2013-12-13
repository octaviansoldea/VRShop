#include <iostream>

#include "VRSceneStructureItem.h"

using namespace VR;
using namespace std;

//--------------------------------------------------------------------

SceneStructureItem::SceneStructureItem(const QVariant & aarrData, SceneStructureItem *parent)	{
	m_pParent = parent;
	m_parrItemData = aarrData;
}

//--------------------------------------------------------------------

SceneStructureItem::~SceneStructureItem()	{
	delete m_pParent;
}

//--------------------------------------------------------------------

SceneStructureItem *SceneStructureItem::child(int row)	{
	return m_arrChildren[row];
}

//--------------------------------------------------------------------

SceneStructureItem *SceneStructureItem::parent()	{	
	return m_pParent;
}

//--------------------------------------------------------------------

QVariant SceneStructureItem::data() const	{
	
	return m_parrItemData;
}

//--------------------------------------------------------------------

bool SceneStructureItem::setData(const QVariant &value)	{
	m_parrItemData = value;

	return true;
}

//--------------------------------------------------------------------

int SceneStructureItem::childCount() const	{
	return m_arrChildren.size();
}

//--------------------------------------------------------------------

int SceneStructureItem::row() const	{
	if (m_pParent)
		return m_pParent->m_arrChildren.indexOf(const_cast<SceneStructureItem*>(this));

	return 0;
}

//--------------------------------------------------------------------

void SceneStructureItem::insertChild(SceneStructureItem * apChild)	{
	m_arrChildren.append(apChild);
}

//--------------------------------------------------------------------
