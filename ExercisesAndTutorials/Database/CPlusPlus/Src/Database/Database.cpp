#include "Database.h"

#include <iostream>

#include <QMessageBox>
#include <QDebug>
#include <QFile>
#include <QSettings>
#include <qsqlresult.h>
#include <QBuffer>
#include <QImageWriter>

DatabaseManager::DatabaseManager(const QString &astrDBName, const QString &astrDBType, QObject *parent)
	: m_strDBName(astrDBName),m_strDBType(astrDBType),QObject(parent)	{
	qDebug() << "Installed database drivers include: " << QSqlDatabase::drivers();
	
	//Connects to a given database
	createConnection();
	//connect2SQLDatabase();
}

//-----------------------------------------------------------------------------------------

DatabaseManager::~DatabaseManager()	{
	db.close();
}

//-----------------------------------------------------------------------------------------

bool DatabaseManager::createConnection()	{
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
//    db.setHostName("mysql17.000webhost.com");
	db.setHostName("localhost");
    db.setDatabaseName("a7252794_main");
    db.setUserName("a7252794_user");
    db.setPassword("jetam1");
    if (!db.open()) {
        qDebug() << "Database error occurred" << db.databaseName() << db.lastError();
        return false;
    } else {
		std::cout << "DB successfully opened." << std::endl;
	}
    return true;
}

//-----------------------------------------------------------------------------------------

bool DatabaseManager::connect2SQLDatabase()	{
	if (!QSqlDatabase::drivers().contains(m_strDBType)) {
		std::cout << "Given driver not supported." << std::endl;
		return false;
	}

	db = QSqlDatabase::addDatabase(m_strDBType);
	if (m_strDBType == "QODBC") {
		// do nothing
		return false;
	}

	else if (m_strDBType == "QSQLITE") {
		db.setDatabaseName(m_strDBName);
		std::cout << "QSQLITE used." << std::endl;
		dbName=m_strDBName;

		//Store info about the DB driver
		m_nDriverSelection = DatabaseManager::QSQLITE;
	}
	
	if (db.open())	{
		std::cout << "Database opened!" << std::endl;
		return true;
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
		return false;
	}
}

//-----------------------------------------------------------------------------------------

QSqlError DatabaseManager::lastError()	{
	// If opening database has failed user can ask 
	// error description by QSqlError::text()
	return db.lastError();
}

//-----------------------------------------------------------------------------------------

bool DatabaseManager::createTable()	{
	// Create a table within the given database
	if (db.isOpen())	{
		qDebug() << "The database contains the following tables: " << db.tables();

		QSqlQuery query;
		if (m_nDriverSelection == DatabaseManager::QODBC)	{
			//do nothing
			return false;
		}

		else if (m_nDriverSelection == DatabaseManager::QSQLITE)	{
			//Create table Category if not already created
			QString qry = "CREATE TABLE IF NOT EXISTS Category "
				"(CategoryID INTEGER PRIMARY KEY AUTOINCREMENT,"
				"CategoryName VARCHAR(20))";
			query.exec(qry);

			//Create table Product if not already created
			qry = "CREATE TABLE IF NOT EXISTS Product "
				"(ProductID INTEGER PRIMARY KEY AUTOINCREMENT,"
				"ProductName VARCHAR(20), "
				"CategoryID INTEGER, "
				"FOREIGN KEY (CategoryID) REFERENCES Category(CategoryID))";
			query.exec(qry);

			//Create table ProductCode if not already created
			qry = "CREATE TABLE IF NOT EXISTS ProductCode "
				"(ProductCodeID INTEGER PRIMARY KEY AUTOINCREMENT,"
				"ProductCodeNumber UNSIGNED INT, "
				"ProductID INTEGER,"
				"FOREIGN KEY (ProductID) REFERENCES Product(ProductID))";
			query.exec(qry);

			//Create table ProductCodeImage if not already created
			qry = "CREATE TABLE IF NOT EXISTS ProductCodeImage "
				"(ProductCodeImageID INTEGER PRIMARY KEY AUTOINCREMENT,"
				"ProductCodeImageName UNSIGNED INT, "
				"ProductCodeID INTEGER,"
				"FOREIGN KEY (ProductCodeID) REFERENCES ProductCode(ProductCodeID))";
			query.exec(qry);

			//Create table Location if not already created
			qry = "CREATE TABLE IF NOT EXISTS Location "
				"(LocationID INTEGER PRIMARY KEY AUTOINCREMENT,"
				"ProductCodeID INTEGER, "
				"LocationX REAL, "
				"LocationY REAL, "
				"LocationZ REAL, "
				"FOREIGN KEY (ProductCodeID) REFERENCES ProductCode(ProductCodeID))";
			query.exec(qry);

			//Create table Orientation if not already created
			qry = "CREATE TABLE IF NOT EXISTS Orientation "
				"(OrientationID INTEGER PRIMARY KEY AUTOINCREMENT,"
				"ProductCodeID INTEGER, "
				"OrientationX REAL, "
				"OrientationY REAL, "
				"OrientationZ REAL, "
				"FOREIGN KEY (ProductCodeID) REFERENCES ProductCode(ProductCodeID))";
			query.exec(qry);

			//Create table Properties if not already created
			qry = "CREATE TABLE IF NOT EXISTS Properties "
				"(PropertiesID INTEGER PRIMARY KEY AUTOINCREMENT,"
				"LocationID INTEGER, "
				"OrientationID INTEGER, "
				"FOREIGN KEY (LocationID) REFERENCES Location(LocationID), "
				"FOREIGN KEY (OrientationID) REFERENCES Orientation(OrientationID))";
			query.exec(qry);

			//Create table Object if not already created
			qry = "CREATE TABLE IF NOT EXISTS Object "
				"(ObjectID INTEGER PRIMARY KEY AUTOINCREMENT,"
				"CodeID INTEGER, "
				"PropertiesID INTEGER, "
				"FOREIGN KEY (CodeID) REFERENCES Code(CodeID), "
				"FOREIGN KEY (PropertiesID) REFERENCES Properties(PropertiesID))";
			query.exec(qry);

			//Create table Scene if not already created
			qry = "CREATE TABLE IF NOT EXISTS Scene "
				"(SceneID INTEGER PRIMARY KEY AUTOINCREMENT,"
				"SceneName VARCHAR(20))";
			query.exec(qry);

			//Create table ObjectScene if not already created
			qry = "CREATE TABLE IF NOT EXISTS SceneObject "
				"(SceneObjectID INTEGER PRIMARY KEY AUTOINCREMENT,"
				"SceneID INTEGER, "
				"ObjectID INTEGER, "
				"FOREIGN KEY (SceneID) REFERENCES Scene(SceneID) ON DELETE CASCADE, "
				"FOREIGN KEY (ObjectID) REFERENCES Object(ObjectID))";
			query.exec(qry);

			std::cout << "QSQLITE Table created." << std::endl;
		}
		return true;
	}
	else	{
		//If error occurs, report it and give false
		std::cout << "Error creating table: " << lastError().text().toStdString() << std::endl;
		return false;
	}
}

//-----------------------------------------------------------------------------------------

void DatabaseManager::insertItem(const QString &astrCategory, const QString &astrProduct, const QString &astrProductCodeNumber, const QString &astrProductCodeImage, const QString astrarrLocation[3],const QString astrarrOrientation[3])	{
	if(db.isOpen())	{
		insertCategory(astrCategory);
		insertProduct(astrProduct, CategoryID);
		insertProductCode(ProductID, astrProductCodeNumber);
		insertProductCodeImage(ProductCodeID, astrProductCodeImage);
		insertLocation(ProductCodeID, astrarrLocation);
		insertOrientation(ProductCodeID, astrarrOrientation);
		insertProperties(ProductCodeID, LocationID, OrientationID);
		insertObject(ProductCodeID, PropertiesID);
		insertScene();
		insertSceneObject(SceneID,ObjectID);
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
	}
}

//-----------------------------------------------------------------------------------------

bool DatabaseManager::insertScene(const QString &astrSceneName)	{
	if(db.isOpen())	{
		QString qry;
		QSqlQuery tempQuery;
	
		//Prepare the string to be later used in the query.
		if (m_nDriverSelection == DatabaseManager::QODBC)	{
			//Currently do nothing
			return false;
		}
		else if (m_nDriverSelection == DatabaseManager::QSQLITE)	{
			//Check if the Scene defined via the argument is already in the table
			QString tqry = QString("SELECT SceneID FROM Scene WHERE SceneName = '%1'").arg(astrSceneName);
			tempQuery.exec(tqry);
			if(tempQuery.last() == '\0')	{
				//Category not found and should be inserted
				qry = QString("INSERT INTO Scene(SceneName) "
					"VALUES('%1')").arg(astrSceneName);
				QSqlQuery query(qry);

				//store "SceneID" which will be later used in a junction table
				SceneID=tempQuery.lastInsertId().toInt();
			}
			else	{
				//Scene already in the table and just store its "SceneID"
				SceneID=tempQuery.value(0).toInt();

				qDebug() << QString("Scene %1 already in the database.").arg(astrSceneName);
			}
		}
		return true;
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
		return false;
	}
}

//=========================================================================================

bool DatabaseManager::insertCategory(const QString &astrCategory)	{
	if(db.isOpen())	{
		QString qry;
		QSqlQuery tempQuery;
	
		//Prepare the string to be later used in the query.
		if (m_nDriverSelection == DatabaseManager::QODBC)	{
			//Currently do nothing
			return false;
		}
		else if (m_nDriverSelection == DatabaseManager::QSQLITE)	{
			//Check if the Category defined via the argument is already in the table
			QString tqry = QString("SELECT CategoryID FROM Category WHERE CategoryName = '%1'").arg(astrCategory);
			tempQuery.exec(tqry);
			if(tempQuery.last() == '\0')	{
				//Category not found and should be inserted
				qry = QString("INSERT INTO Category(CategoryName) "
					"VALUES('%1')").arg(astrCategory);
				QSqlQuery query(qry);

				//store "CategoryID" which will be later used in a junction table
				CategoryID=tempQuery.lastInsertId().toInt();
			}
			else	{
				//Category already in the table and just store its "CategoryID"
				CategoryID=tempQuery.value(0).toInt();

				qDebug() << QString("Category %1 already in the database.").arg(astrCategory);
			}
		}
		return true;
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
		return false;
	}
}

//-----------------------------------------------------------------------------------------

bool DatabaseManager::insertProduct(const QString &astrProduct, unsigned int &m_CategoryID)	{
	if(db.isOpen())	{
		QString qry;
		QSqlQuery tempQuery;
	
		//Prepare the string to be later used in the query.
		if (m_nDriverSelection == DatabaseManager::QODBC)	{
			//Currently do nothing
			return false;
		}
		else if (m_nDriverSelection == DatabaseManager::QSQLITE)	{
			//Check if the Product defined via the argument is already in the table
			QString tqry = QString("SELECT ProductID FROM Product WHERE ProductName = '%1'").arg(astrProduct);
			tempQuery.exec(tqry);
			if(tempQuery.last() == '\0')	{
				//Product not found and should be inserted
				qry = QString("INSERT INTO Product(ProductName, CategoryID) "
					"VALUES('%1', '%2')").arg(astrProduct).arg(m_CategoryID);
				QSqlQuery query(qry);

				//store "ProductID" which will be later used in a junction table
				ProductID=tempQuery.lastInsertId().toInt();
			}
			else	{
				//Category already in the table and just store its "CategoryID"
				ProductID=tempQuery.value(0).toInt();

				qDebug() << QString("Product %1 already in the database").arg(astrProduct);
			}
		}
		return true;
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
		return false;
	}
}

//---------------------------------------------------------------------------------------------

bool DatabaseManager::insertProductCode(unsigned int &m_ProductID, const QString &astrProductCodeNumber)	{
	if(db.isOpen())	{
		QString qry;
		QSqlQuery tempQuery;
	
		//Prepare the string to be later used in the query.
		if (m_nDriverSelection == DatabaseManager::QODBC)	{
			return false;
		}
		else if (m_nDriverSelection == DatabaseManager::QSQLITE)	{
			//Check if the Product defined via the argument is already in the table
			QString tqry = QString("SELECT ProductCodeID FROM ProductCode WHERE ProductCodeNumber = '%1'").arg(astrProductCodeNumber);
			tempQuery.exec(tqry);
			if(tempQuery.last() == '\0')	{
				//Product not found and should be inserted
				qry = QString("INSERT INTO ProductCode(ProductCodeNumber, ProductID) "
					"VALUES('%1', '%2')").arg(astrProductCodeNumber).arg(m_ProductID);
				QSqlQuery query(qry);

				//store "ProductCodeID" which will be later used in a junction table
				ProductCodeID=tempQuery.lastInsertId().toInt();
			}
			else	{
				//ProductCode already in the table and just store its "ProductCodeID"
				ProductCodeID=tempQuery.value(0).toInt();

				//EAN already in the database.
				qDebug() << QString("Product Code %1 already in the database.").arg(astrProductCodeNumber);
			}
		}
		return true;
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
		return false;
	}
}

//---------------------------------------------------------------------------------------------
bool DatabaseManager::insertProductCodeImage(unsigned int &m_ProductCodeID, const QString &astrProductCodeImage)	{
	if(db.isOpen())	{
		QString qry;
		QSqlQuery tempQuery;
	
		//Prepare the string to be later used in the query.
		if (m_nDriverSelection == DatabaseManager::QODBC)	{
			return false;
		}
		else if (m_nDriverSelection == DatabaseManager::QSQLITE)	{
			//Check if the Product defined via the argument is already in the table
			QString tqry = QString("SELECT ProductCodeImageID FROM ProductCodeImage WHERE ProductCodeImageName = '%1'").arg(astrProductCodeImage);
			tempQuery.exec(tqry);
			if(tempQuery.last() == '\0')	{
				//Product not found and should be inserted
				qry = QString("INSERT INTO ProductCodeImage(ProductCodeImageName, ProductCodeID) "
					"VALUES('%1', '%2')").arg(astrProductCodeImage).arg(m_ProductCodeID);
				QSqlQuery query(qry);

				//store "ProductCodeID" which will be later used in a junction table
				ProductCodeImageID=tempQuery.lastInsertId().toInt();
			}
			else	{
				//ProductCode already in the table and just store its "ProductCodeID"
				ProductCodeImageID=tempQuery.value(0).toInt();

				//EAN already in the database.
				qDebug() << QString("Product Code Image %1 already in the database.").arg(astrProductCodeImage);
			}
		}
		return true;
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
		return false;
	}
}

//=============================================================================================

bool DatabaseManager::insertLocation(unsigned int &m_ProductCodeID, const QString astrarrLocation[3])	{
	if(db.isOpen())	{
		QString qry;
		QSqlQuery tempQuery;
	
		//Prepare the string to be later used in the query.
		if (m_nDriverSelection == DatabaseManager::QODBC)	{
			return false;
		}
		else if (m_nDriverSelection == DatabaseManager::QSQLITE)	{
			//Check if the Location defined via the argument is already in the table
			QString tqry = QString("SELECT LocationID FROM Location WHERE LocationX = '%1' AND LocationY = '%2' AND LocationZ = '%3'")
				.arg(astrarrLocation[0]).arg(astrarrLocation[1]).arg(astrarrLocation[2]);
			tempQuery.exec(tqry);
			if(tempQuery.last() == '\0')	{
				//Product not found and should be inserted
				qry = QString("INSERT INTO Location(ProductCodeID, LocationX, LocationY, LocationZ) "
					"VALUES('%1', '%2', '%3', '%4')").arg(m_ProductCodeID).arg(astrarrLocation[0]).arg(astrarrLocation[1]).arg(astrarrLocation[2]);
				QSqlQuery query(qry);

				//store "LocationID" which will be later used in a junction table
				LocationID=tempQuery.lastInsertId().toInt();
			}
			else	{
				//Location already in the table and just store its "LocationID"
				LocationID=tempQuery.value(0).toInt();

				//EAN already in the database.
				qDebug() << QString("Location (%1,%2,%3) already in the database.").arg(astrarrLocation[0]).arg(astrarrLocation[1]).arg(astrarrLocation[2]);
			}
		}
		return true;
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
		return false;
	}
}

//---------------------------------------------------------------------------------------------

bool DatabaseManager::insertOrientation(unsigned int &m_ProductCodeID, const QString astrarrOrientation[3])	{
	if(db.isOpen())	{
		QString qry;
		QSqlQuery tempQuery;
	
		//Prepare the string to be later used in the query.
		if (m_nDriverSelection == DatabaseManager::QODBC)	{
			return false;
		}
		else if (m_nDriverSelection == DatabaseManager::QSQLITE)	{
			//Check if the Orientation defined via the argument is already in the table
			QString tqry = QString("SELECT OrientationID FROM Orientation WHERE OrientationX = '%1' AND OrientationY = '%2' AND OrientationZ = '%3'").arg(astrarrOrientation[0]).arg(astrarrOrientation[1]).arg(astrarrOrientation[2]);
			tempQuery.exec(tqry);
			if(tempQuery.last() == '\0')	{
				//Orientation not found and should be inserted
				qry = QString("INSERT INTO Orientation(ProductCodeID, OrientationX, OrientationY, OrientationZ) "
					"VALUES('%1', '%2', '%3', '%4')").arg(m_ProductCodeID).arg(astrarrOrientation[0]).arg(astrarrOrientation[1]).arg(astrarrOrientation[2]);
				QSqlQuery query(qry);

				//store "OrientationID" which will be later used in a junction table
				OrientationID=tempQuery.lastInsertId().toInt();
			}
			else	{
				//Orientation already in the table and just store its "OrientationID"
				OrientationID=tempQuery.value(0).toInt();

				//Orientation already in the database.
				qDebug() << QString("Orientation (%1,%2,%3) already in the database.").arg(astrarrOrientation[0]).arg(astrarrOrientation[1]).arg(astrarrOrientation[2]);
			}
		}
		return true;
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
		return false;
	}
}

//---------------------------------------------------------------------------------------------

bool DatabaseManager::insertProperties(unsigned int &m_ProductCodeID, unsigned int &m_LocationID, unsigned int &m_OrientationID)	{
	if(db.isOpen())	{
		QString qry;
		QSqlQuery tempQuery;

		if (m_nDriverSelection == DatabaseManager::QODBC)	{
			return false;
		}

		else if (m_nDriverSelection == DatabaseManager::QSQLITE)	{
			//Check if the Orientation defined via the argument is already in the table
			QString tqry = QString("SELECT PropertiesID FROM Properties WHERE LocationID = '%1' AND OrientationID = '%2'").arg(m_LocationID).arg(m_OrientationID);
			tempQuery.exec(tqry);
			if(tempQuery.last() == '\0')	{
				//Properties not found and should be inserted
				qry = QString("INSERT INTO Properties "
					"(LocationID, OrientationID) "
					"VALUES (%1, %2)").arg(m_LocationID).arg(m_OrientationID);
				QSqlQuery query(qry);

				//store "PropertiesID" which will be later used in a junction table
				PropertiesID=tempQuery.lastInsertId().toInt();
			}
			else	{
				//Orientation already in the table and just store its "OrientationID"
				PropertiesID=tempQuery.value(0).toInt();

				//Orientation already in the database.
				qDebug() << QString("LocationID = '%1' and OrientationID = '%2' already in the database").arg(m_LocationID).arg(m_OrientationID);
			}
		}
		return true;
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
		return false;
	}
}

//---------------------------------------------------------------------------------------------

bool DatabaseManager::insertObject(unsigned int &m_ProductCodeID, unsigned int &m_PropertiesID)	{
	if(db.isOpen())	{
		QString qry;

		if (m_nDriverSelection == DatabaseManager::QODBC)	{
			return false;
		}

		else if (m_nDriverSelection == DatabaseManager::QSQLITE)	{
			qry = QString("INSERT INTO Object "
				"(CodeID, PropertiesID) "
				"VALUES (%1, %2)").arg(m_ProductCodeID).arg(m_PropertiesID);
			QSqlQuery query(qry);

			//store "OrientationID" which will be later used in a junction table
			ObjectID=query.lastInsertId().toInt();

			return true;
		}
		else	{
			std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
			return false;
		}
	}
	return false;
}

//-------------------------------------------------------------------------------------------------

bool DatabaseManager::insertSceneObject(unsigned int &m_SceneID, unsigned int &m_ObjectID)	{
	if(db.isOpen())	{
		QString qry;

		if (m_nDriverSelection == DatabaseManager::QODBC)	{
			//Curently do nothing
			return false;
		}
		else if (m_nDriverSelection == DatabaseManager::QSQLITE)	{
			qry = QString("INSERT INTO SceneObject(SceneID, ObjectID) VALUES (%1, %2)").arg(m_SceneID).arg(m_ObjectID);
			QSqlQuery query(qry);

			//store "SceneObjectID" which will be later used in a junction table
			SceneObjectID=query.lastInsertId().toInt();
			return true;
		}
		else	{
			std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
			return false;
		}
	}
	return false;
}

//=================================================================================================

void DatabaseManager::saveScene(const QString &astrOldSceneName, const QString &astrNewSceneName) {
//Update the name of the "temp scene" if not pressed, delete "temp scene"
	if(db.isOpen())	{
		QString qry;
		QSqlQuery tempQuery;
	
		//Prepare the string to be later used in the query.
		if (m_nDriverSelection == DatabaseManager::QODBC)	{
		}
		else if (m_nDriverSelection == DatabaseManager::QSQLITE)	{
			//Check if the Scene defined via the argument is in the table
			QString tqry = QString("SELECT SceneID FROM Scene WHERE SceneName = '%1'").arg(astrOldSceneName);
			tempQuery.exec(tqry);
			if(tempQuery.last() == '\0')	{
				//Scene not found report this and exit
				qDebug() << QString("Item %1 not in the table.").arg(astrOldSceneName);
			}
			else	{
			qry = QString("UPDATE Scene SET SceneName = '%1' WHERE SceneName = '%2'").arg(astrNewSceneName).arg(astrOldSceneName);
			QSqlQuery query(qry);

			qDebug() << QString("Scene %1 renamed to %2.").arg(astrOldSceneName).arg(astrNewSceneName);
			}
		}
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
	}
}

//-------------------------------------------------------------------------------------------------

void DatabaseManager::deleteItem(const QString &astrSceneObjectID)	{
	if(db.isOpen())	{
		QString qry;
		QSqlQuery tempQuery;
	
		//Prepare the string to be later used in the query.
		if (m_nDriverSelection == DatabaseManager::QODBC)	{
		}
		else if (m_nDriverSelection == DatabaseManager::QSQLITE)	{
			//Check if the Product defined via the argument is in the table
			QString tqry = QString("SELECT SceneID, ObjectID FROM SceneObject WHERE SceneObjectID = '%1'").arg(astrSceneObjectID);
			tempQuery.exec(tqry);
			if(tempQuery.last() == '\0')	{
				//Product not found report this and exit
				qDebug() << QString("Item %1 not in the table.").arg(astrSceneObjectID);
			}
			else	{
				//We have picked something. Store SceneID and ObjectID
				int nSceneID = tempQuery.value(0).toInt();
				int nObjectID = tempQuery.value(1).toInt();

				qDebug() << QString("Scene ID = %1. Deleted item = %2.").arg(nSceneID).arg(nObjectID);
			}
		}
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
	}
}

//=============================================================================================