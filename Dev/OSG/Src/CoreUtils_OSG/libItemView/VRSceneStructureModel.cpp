#include <iostream>

#include "VRSceneStructureModel.h"

using namespace VR;
using namespace std;


SceneStructureModelParams::SceneStructureModelParams() : 
parent(0), aqvarRootHeader(QModelIndex())	{
}

//--------------------------------------------------------------------

SceneStructureModel::SceneStructureModel()	{
}

//--------------------------------------------------------------------

SceneStructureModel::SceneStructureModel(const SceneStructureModelParams & aSceneStructureModelParams)
	: QAbstractItemModel(aSceneStructureModelParams.parent)	{

		QVariant arrqRootHeader = aSceneStructureModelParams.aqvarRootHeader;

		m_pRootItem = new SceneStructureItem(arrqRootHeader);

		setupDataElements(aSceneStructureModelParams.data, m_pRootItem);
}

//--------------------------------------------------------------------

SceneStructureModel::~SceneStructureModel()	{
	delete m_pRootItem;
}

//--------------------------------------------------------------------

QModelIndex SceneStructureModel::index(int row, int column, const QModelIndex &parent) const	{
	if(!m_pRootItem || row < 0 || column < 0)
		return QModelIndex();

	SceneStructureItem *parentItem;

	if (parent == QModelIndex::QModelIndex())	//The root
		parentItem = static_cast<SceneStructureItem*>(m_pRootItem);
	else
		parentItem = static_cast<SceneStructureItem*>(parent.internalPointer());

	SceneStructureItem *childItem = parentItem->child(row);
	if (childItem)
		return createIndex(row, 0, childItem);
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
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)	{
		return m_pRootItem->data();
	}
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
	return 1;
}

//--------------------------------------------------------------------

QVariant SceneStructureModel::data(const QModelIndex &index, int role) const	{
    if (role != Qt::DisplayRole)
        return QVariant();

	//From the index number initialize an item
	SceneStructureItem *item = static_cast<SceneStructureItem*>(index.internalPointer());

	//See the content behind the item
	return item->data();
}

//--------------------------------------------------------------------

bool SceneStructureModel::setData(const QModelIndex& index, const QVariant& value,int role)	{
	if (role != Qt::EditRole)	{
		return false;
	}

	SceneStructureItem * item = static_cast<SceneStructureItem*>(index.internalPointer());
	QVariant prevValue = item->data();

	item->setData(value);

	if (prevValue != value)
		emit dataChanged(index, index);

	return true;
}

//--------------------------------------------------------------------

Qt::ItemFlags SceneStructureModel::flags(const QModelIndex& index) const {
	if(index.isValid())
		return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
	else
		return 0;
}

//--------------------------------------------------------------------

void SceneStructureModel::setupDataElements(const QList <QString> & aarrstrSceneData, SceneStructureItem *apParent)	{
	string strElementDataLine;
    QList <SceneStructureItem*> parents;
	parents.append(apParent);
	QList <int> lstnLayer;
	lstnLayer.push_back(0);

	QList<QString>::const_iterator it;
	for (it = aarrstrSceneData.begin(); it != aarrstrSceneData.end(); it++)	{
		int nPos = 0;
		strElementDataLine = it->toStdString();

		//Find the position of the first character & clear empty spaces
		nPos = strElementDataLine.find_first_not_of(" ");
		strElementDataLine.erase(0,nPos);

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
		int size =  parents.size();
		SceneStructureItem * item = new SceneStructureItem(strElementDataLine.c_str(), parents[size-1]);
		parents[size-1]->insertChild(item);

		parents[size-1]->child(parents[size-1]->childCount() - 1)->setData(strElementDataLine.c_str());
	}
}
