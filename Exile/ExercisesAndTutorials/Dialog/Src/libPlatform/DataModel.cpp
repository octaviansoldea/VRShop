#include "DataModel.h"

DataModel::DataModel(QObject *parent) : QAbstractTableModel(parent)	{
}

//------------------------------------------------------

DataModel::~DataModel()	{
}

//------------------------------------------------------

int DataModel::rowCount(const QModelIndex &parent) const	{
	return m_lsData.size();
}

//------------------------------------------------------

int DataModel::columnCount(const QModelIndex &parent) const	{
	return 3;	//It is always 3
}

//------------------------------------------------------

QVariant DataModel::data(const QModelIndex &index, int role) const	{
	if (!index.isValid())	{
		std::cout << "No valid index in the QVariant data() const.\n";
        return QVariant();
	}
	if (role == Qt::DisplayRole)	{
		QStringList stringList = m_lsData.at(index.row());

		return QVariant(stringList.value(index.column()));
	}
	return QVariant();
}

//------------------------------------------------------

bool DataModel::insertRows(int position, int noOfRows, const QModelIndex &index)	{
	beginInsertRows(index,position, position+noOfRows-1);
					//QModelIndex() constructor used since there's no parent
	int row;
	QStringList stringList;
	for (row=0; row<noOfRows; row++)	{
		for (int col=0;col<3;col++)	{
			stringList.value(col) = "";
		}
		m_lsData.insert(position, stringList);
	}
	endInsertRows();
	return true;
}

//------------------------------------------------------

bool DataModel::setData(QModelIndex &index, const QVariant &astrItemValue, int role)	{
	if (index.isValid() && role == Qt::EditRole)	{
		int row = index.row();
		QStringList stringList = m_lsData.value(row);

		if (index.column() == 0)	{
			stringList.insert(0,astrItemValue.toString());
		}
		else if (index.column() == 1)	{
			stringList.insert(1,astrItemValue.toString());
		}
		else if (index.column() == 2)	{
			stringList.insert(2,astrItemValue.toString());
		}
		else	{
			std::cout << "Column is out of range.\n";
			return false;
		}
		m_lsData.replace(row,stringList);
		emit dataChanged(index,index);

		return true;
	}
	return false;
}

//------------------------------------------------------

QList< QStringList > DataModel::getDataList() const	{
	return m_lsData;
}

//------------------------------------------------------

Qt::ItemFlags DataModel::flags(const QModelIndex &index) const	{
	if (!index.isValid())
		return Qt::ItemIsEnabled;

	return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}


//================================================================================
