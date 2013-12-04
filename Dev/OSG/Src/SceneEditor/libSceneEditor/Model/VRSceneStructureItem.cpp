#include <iostream>

#include "VRSceneStructureItem.h"

using namespace VR;
using namespace std;

//--------------------------------------------------------------------

SceneStructureItem::SceneStructureItem(const QList <QVariant> &aarrData, SceneStructureItem *parent)	{
	m_pParent = parent;
	for (auto it = aarrData.begin(); it != aarrData.end(); it++)	{
		m_parrItemData.push_back(*it);
	}
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

QVariant SceneStructureItem::data(int column) const	{
	return m_parrItemData[column];
}

//--------------------------------------------------------------------

bool SceneStructureItem::setData(int column, const QVariant &value)	{
	m_parrItemData[column] = value;

    return true;
}

//--------------------------------------------------------------------

int SceneStructureItem::childCount() const	{
	return m_arrChildren.count();
}

//--------------------------------------------------------------------

int SceneStructureItem::columnCount() const	{
	return m_parrItemData.size();
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
