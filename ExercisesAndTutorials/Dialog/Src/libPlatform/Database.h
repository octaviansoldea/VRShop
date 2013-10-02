#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>

#include <QFile>
#include <QStandardItem>
#include <QStringList>
#include <qabstractitemmodel.h>

#include "DataModel.h"

class Database : public QObject	{
	Q_OBJECT

public:
	Database(QObject *parent = 0);
	~Database();

public slots:
	//adds entry to the table (ItemModel.h)
	void newEntry(QString &astrStore, QString &astrProduct, QString &astrPrice);
	void writeToFile(const QString &astrFileName);
	void readFromFile(const QString &astrFileName);

private:
	const QString fileName;
	QString m_filePath;

	DataModel dataModel;
};
#endif //DATABASE_H