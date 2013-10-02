#include "Database.h"
#include <qdatastream>
#include <qtextstream>


Database::Database(QObject *parent) : QObject(parent)	{
	m_filePath = "C:/Projekti/QT/PriceComparison/Src/";
}

//-------------------------------------------------------------------

Database::~Database()	{
}

//-------------------------------------------------------------------

void Database::newEntry(QString &astrStore, QString &astrProduct, QString &astrPrice)	{
	//Works fine
	QVariant m_strStore(astrStore);
	QVariant m_strProduct(astrProduct);
	QVariant m_strPrice(astrPrice);

	//makes three empty columns to be latter filled with the adequate data - works
	dataModel.insertRows(0,1,QModelIndex());

	//fills empty cells with appropriate data
	QModelIndex index;
	index = dataModel.index(0,0,QModelIndex());
	dataModel.setData(index,m_strStore,Qt::EditRole);

	index = dataModel.index(0,1,QModelIndex());
	dataModel.setData(index,m_strProduct,Qt::EditRole);

	index = dataModel.index(0,2,QModelIndex());
	dataModel.setData(index,m_strPrice,Qt::EditRole);
}

//-------------------------------------------------------------------

void Database::writeToFile(const QString &astrFileName)	{
	QFile file(m_filePath + astrFileName);
	if (!file.open(QIODevice::WriteOnly | QFile::Append | QFile::Text))	{
		std::cout << "Error opening the file.\n";
		return;
	}
	QList <QStringList > entries = dataModel.getDataList();

	int row, rows, col;
	rows = dataModel.rowCount();
	QStringList lines;
	QTextStream out(&file);
	for (row=0; row < rows; row++)	{
		lines = entries.at(row);
		for (col=0; col<lines.size();col++)	{
			out << lines.value(col) << "\t";
		}
		out << endl;
	}
	file.close();
}

//---------------------------------------------------------------------------

void Database::readFromFile(const QString &astrFileName)	{
	QFile file(m_filePath+astrFileName);
	if (!file.open(QIODevice::ReadOnly | QFile::Text))	{
		std::cout << "Error opening the file for reading.\n";
		return;
	}

	else	{
		QList <QStringList > entries = dataModel.getDataList();
		QTextStream in(&file);

		QStringList lineSplit;
		while (!file.atEnd())	{
			QString line = file.readLine();	//reads the whole line as a stream
			lineSplit = line.split("\t");	//tabulator splits data entries in the data file

			newEntry(lineSplit.value(0),lineSplit.value(1),lineSplit.value(2));
//			entries.push_back(lineSplit);	//fill the QList with the QStringList
		}

		std::cout << entries.size();
	}
	file.close();
}

//============================================================================
