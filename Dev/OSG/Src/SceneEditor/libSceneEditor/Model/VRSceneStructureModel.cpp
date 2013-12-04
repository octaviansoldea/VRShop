#include <iostream>
#include "StringManipulation.h"

#include "VRSceneStructureModel.h"

using namespace VR;
using namespace std;

//--------------------------------------------------------------------

SceneStructureModel::SceneStructureModel(const QList <QString> &data, QObject *parent)
	: QAbstractItemModel(parent)	{

		QList <QVariant> arrqRootHeader; 
		arrqRootHeader.push_back("Scene");
		m_pRootItem = new SceneStructureItem(arrqRootHeader);
		setupDataElements(data,m_pRootItem);
}

//--------------------------------------------------------------------

QModelIndex SceneStructureModel::index(int row, int column, const QModelIndex &parent) const	{
	SceneStructureItem *parentItem;

	if (parent == QModelIndex::QModelIndex())	//The root
		parentItem = static_cast<SceneStructureItem*>(m_pRootItem);
	else
		parentItem = static_cast<SceneStructureItem*>(parent.internalPointer());

	SceneStructureItem *childItem = parentItem->child(row);
	if (childItem)
		return createIndex(row, column, childItem);
	else
		return QModelIndex();
}

//--------------------------------------------------------------------

QModelIndex SceneStructureModel::parent(const QModelIndex &index) const	{
	if (index == QModelIndex::QModelIndex())	//Root doesn't have a parent
		return QModelIndex();

	SceneStructureItem *childItem = static_cast<SceneStructureItem*>(index.internalPointer());
	SceneStructureItem *parentItem = childItem->parent();

	if (parentItem == m_pRootItem)
		return QModelIndex();

	return createIndex(parentItem->row(), 0, parentItem);
}

//--------------------------------------------------------------------

QVariant SceneStructureModel::headerData(int section, Qt::Orientation orientation, int role) const	{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
		return QVariant(m_pRootItem->data(section));

    return QVariant();
}

//--------------------------------------------------------------------

int SceneStructureModel::rowCount(const QModelIndex &parent) const	{
	//Rows equals to the number of children
	SceneStructureItem *parentItem;

	if (parent == QModelIndex::QModelIndex())	//Root
		parentItem = m_pRootItem;
	else
		parentItem = static_cast<SceneStructureItem*>(parent.internalPointer());

	return parentItem->childCount();
}

//--------------------------------------------------------------------

int SceneStructureModel::columnCount(const QModelIndex &parent) const	{
	if (parent != QModelIndex::QModelIndex())	{
		//From the index number initialize an item
		SceneStructureItem *item = static_cast<SceneStructureItem*>(parent.internalPointer());

		//See the content behind the item
		return item->columnCount();
	}
	else	{
		return m_pRootItem->columnCount();
	}
}

//--------------------------------------------------------------------

QVariant SceneStructureModel::data(const QModelIndex &index, int role) const	{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

	//From the index number initialize an item
	SceneStructureItem *item = static_cast<SceneStructureItem*>(index.internalPointer());

	//See the content behind the item
	return item->data(index.column());
}

//--------------------------------------------------------------------

void SceneStructureModel::setupDataElements(const QList <QString> & aarrstrSceneData, SceneStructureItem *apParent)	{
	string strElementDataLine;
    QList <SceneStructureItem*> parents;
	parents.append(apParent);
	QList <int> lstnLayer;
	lstnLayer.push_back(0);

	for (auto it = aarrstrSceneData.begin(); it != aarrstrSceneData.end(); it++)	{
		int nPos = 0;
		strElementDataLine = it->toStdString();

		//Find the position of the first character & clear empty spaces
		strElementDataLine = (nPos = strElementDataLine.find_first_not_of(" ")) 
			? strElementDataLine.substr(nPos) : strElementDataLine;

		vector <string> strData = splitString(strElementDataLine,";");
		QList<QVariant> columnData;
		for (auto itt = strData.begin(); itt != strData.end(); itt++)	{
			columnData.push_back(itt->c_str());
		}

		//Layer determines Parent/Child relations
		//If it's a parent, put it into the list of parents
		if (int(nPos / 2) > lstnLayer.last())	{
			//The last child of the current parent is new parent
			parents.push_back(parents.last()->child(parents.last()->childCount()-1));
			lstnLayer.push_back(int(nPos / 2));
		}
		else {
			//Iterate back to find adequate parent in the layer
			while (int(nPos / 2) < lstnLayer.last() && parents.count() > 0) {
				parents.pop_back();
				lstnLayer.pop_back();
			}
		}

		// new item is in any case a child
		int size = parents.size();
		SceneStructureItem * item = new SceneStructureItem(columnData, parents[size-1]);
		parents[size-1]->insertChild(item);

		for (int column = 0; column < columnData.size(); column++)
			parents[size-1]->child(parents[size-1]->childCount() - 1)->setData(column, columnData[column]);
	}
}
