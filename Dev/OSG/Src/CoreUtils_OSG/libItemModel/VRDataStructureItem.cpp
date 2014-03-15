#include <iostream>

#include "VRDataStructureItem.h"

using namespace VR;
using namespace std;

//--------------------------------------------------------------------

DataStructureItem::DataStructureItem(const QVariant & aarrData, DataStructureItem *parent)	{
	m_pParent = parent;
	m_parrItemData = aarrData;
}

//--------------------------------------------------------------------

DataStructureItem::~DataStructureItem()	{
	delete m_pParent;
}

//--------------------------------------------------------------------

DataStructureItem *DataStructureItem::child(int row)	{
	return m_arrChildren[row];
}

//--------------------------------------------------------------------

DataStructureItem *DataStructureItem::parent()	{	
	return m_pParent;
}

//--------------------------------------------------------------------

QVariant DataStructureItem::data() const	{
	
	return m_parrItemData;
}

//--------------------------------------------------------------------

bool DataStructureItem::setData(const QVariant &value)	{
	m_parrItemData = value;

	return true;
}

//--------------------------------------------------------------------

int DataStructureItem::childCount() const	{
	return m_arrChildren.size();
}

//--------------------------------------------------------------------

int DataStructureItem::row() const	{
	if (m_pParent)
		return m_pParent->m_arrChildren.indexOf(const_cast<DataStructureItem*>(this));

	return 0;
}

//--------------------------------------------------------------------

void DataStructureItem::insertChild(DataStructureItem * apChild)	{
	m_arrChildren.append(apChild);
}

//--------------------------------------------------------------------
