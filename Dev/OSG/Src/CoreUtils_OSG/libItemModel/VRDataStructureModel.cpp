#include "VRDataStructureModel.h"

using namespace VR;
using namespace std;


DataStructureModelParams::DataStructureModelParams() : 
parent(0), aqvarRootHeader(QModelIndex())	{
}

//--------------------------------------------------------------------

DataStructureModel::DataStructureModel(const DataStructureModelParams & aDataStructureModelParams)
	: QAbstractItemModel(aDataStructureModelParams.parent)	{

		QVariant arrqRootHeader = aDataStructureModelParams.aqvarRootHeader;

		m_pRootItem = new DataStructureItem(arrqRootHeader);

		setupDataElements(aDataStructureModelParams.data, m_pRootItem);
}

//--------------------------------------------------------------------

DataStructureModel::~DataStructureModel()	{
	delete m_pRootItem;
}

//--------------------------------------------------------------------

QModelIndex DataStructureModel::index(int row, int column, const QModelIndex &parent) const	{
	if(!m_pRootItem || row < 0 || column < 0)
		return QModelIndex();

	DataStructureItem *parentItem;

	if (parent == QModelIndex::QModelIndex())	//The root
		parentItem = m_pRootItem;
	else
		parentItem = static_cast<DataStructureItem*>(parent.internalPointer());

	DataStructureItem *childItem = parentItem->child(row);
	if (childItem)
		return createIndex(row, 0, childItem);
	else
		return QModelIndex();
}

//--------------------------------------------------------------------

QModelIndex DataStructureModel::parent(const QModelIndex &index) const	{
	//Retrieve parent's index from a child
	if (index == QModelIndex::QModelIndex())	//Root doesn't have a parent
		return QModelIndex();

	DataStructureItem *childItem = static_cast<DataStructureItem*>(index.internalPointer());
	DataStructureItem *parentItem = childItem->parent();

	if (parentItem == m_pRootItem)
		return QModelIndex();

	return createIndex(parentItem->row(), 0, parentItem);
}

//--------------------------------------------------------------------

QVariant DataStructureModel::headerData(int section, Qt::Orientation orientation, int role) const	{
	if (orientation == Qt::Horizontal && role == Qt::DisplayRole)	{
		return m_pRootItem->data();
	}
	return QVariant();
}

//--------------------------------------------------------------------

int DataStructureModel::rowCount(const QModelIndex &parent) const	{
	//Rows equal to the number of children
	DataStructureItem *parentItem;

	if (parent == QModelIndex::QModelIndex())	//Root
		parentItem = m_pRootItem;
	else
		parentItem = static_cast<DataStructureItem*>(parent.internalPointer());

	return parentItem->childCount();
}

//--------------------------------------------------------------------

int DataStructureModel::columnCount(const QModelIndex &parent) const	{
	return 1;
}

//--------------------------------------------------------------------

QVariant DataStructureModel::data(const QModelIndex &index, int role) const	{
	if (role != Qt::DisplayRole && role != Qt::EditRole)
		return QVariant();

	//From the index number initialize an item
	DataStructureItem *item = static_cast<DataStructureItem*>(index.internalPointer());

	//See the content behind the item
	return item->data();
}

//--------------------------------------------------------------------

bool DataStructureModel::setData(const QModelIndex& index, const QVariant& value,int role)	{
	if (role != Qt::EditRole)	{
		return false;
	}

	DataStructureItem * item = static_cast<DataStructureItem*>(index.internalPointer());
	m_PreviousValue = item->data();

	item->setData(value);

	if (m_PreviousValue != value)
		emit dataChanged(index, index);

	return true;
}

//--------------------------------------------------------------------

Qt::ItemFlags DataStructureModel::flags(const QModelIndex& index) const {
	if(index.isValid())
		return Qt::ItemIsEditable | QAbstractItemModel::flags(index);
	else
		return 0;
}

//--------------------------------------------------------------------

bool DataStructureModel::insertRows(int position, int rows, const QModelIndex &parent)	{
	bool bOk = false;

	if (!parent.isValid())
		return bOk;

	//From the index retreive the parent item
	DataStructureItem *parentItem = static_cast<DataStructureItem*>(parent.internalPointer());

	beginInsertRows(parent, position, position + rows - 1);
	bOk = parentItem->insertChildren(position,rows);
	endInsertRows();

	return bOk;
}

//--------------------------------------------------------------------

bool DataStructureModel::removeRows(int position, int rows, const QModelIndex &parent)	{
	bool bOk = false;

	if (!parent.isValid())
		return bOk;

	//From the index retreive the parent item
	DataStructureItem *parentItem = static_cast<DataStructureItem*>(parent.internalPointer());

	beginRemoveRows(parent, position, position + rows - 1);
	bOk = parentItem->removeChildren(position, rows);
	endRemoveRows();

	return bOk;
}

//--------------------------------------------------------------------

QVariant DataStructureModel::getPrevValue() const	{
	return m_PreviousValue;
}

//--------------------------------------------------------------------

void DataStructureModel::setupDataElements(const QList <QString> & aarrstrSceneData, DataStructureItem *apParent)	{
	string strElementDataLine;
	QList <DataStructureItem*> parents;
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
		} else {
			//Iterate back to find adequate parent in the layer
			while (int(nPos / 2) < lstnLayer.last() && parents.count() > 0) {
				parents.pop_back();
				lstnLayer.pop_back();
			}
		}

		// new item is in any case a child
		int size =  parents.size();

		DataStructureItem * item = new DataStructureItem(strElementDataLine.c_str(), parents[size-1]);
		parents[size-1]->insertChild(item);

		parents[size-1]->child(parents[size-1]->childCount() - 1)->setData(strElementDataLine.c_str());
	}
}
