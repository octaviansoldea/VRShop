#ifndef ITEM_MODEL_H
#define ITEM_MODEL_H

#include <iostream>

#include <qabstracttablemodel>
#include <qobject>
#include <qlist>
#include <qstringlist>

/**********************************************************
* This class is a container of data provided by the user  *
**********************************************************/

class DataModel : public QAbstractTableModel	{
	Q_OBJECT

public:
	DataModel(QObject *parent=0);
	~DataModel();

	//Initializing data from the stringList
	QVariant data(const QModelIndex &index, int role=Qt::DisplayRole) const;	//returns a single data item per row
	QList< QStringList > getDataList() const;		//Get function returns the whole list of items

	bool insertRows(int position, int noOfRows, const QModelIndex &index=QModelIndex());	//inserts empty rows to be filled with the data	
	bool setData(QModelIndex &index, const QVariant &string, int role=Qt::EditRole); //fills table with data and emits the change

	//Necessary for the sake of the abstract class
	int rowCount(const QModelIndex &parent = QModelIndex()) const;
	int columnCount(const QModelIndex &parent = QModelIndex()) const;

	Qt::ItemFlags flags(const QModelIndex &index) const;

public:
	QList< QStringList > m_lsData;	//Database stored as a list of string lists each made of 3 columns
};
#endif // ITEM_MODEL_H
