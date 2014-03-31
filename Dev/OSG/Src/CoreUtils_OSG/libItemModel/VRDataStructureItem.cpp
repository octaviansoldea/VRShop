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

bool DataStructureItem::insertChildren(int position, int count)	{
	if (position < 0 || position > m_arrChildren.size())
		return false;

	int nI;
	for (nI = 0; nI < count; ++nI) {
		const QVariant data;
		DataStructureItem *item = new DataStructureItem(data, this);
		m_arrChildren.insert(position, item);
	}

	return true;
}

//--------------------------------------------------------------------

bool DataStructureItem::removeChildren(int position, int count)	{
	if (position < 0 || position + count > m_arrChildren.size())
		return false;

	int nI;
	for (nI = 0; nI < count; ++nI)
		delete m_arrChildren[position];

	return true;
}
