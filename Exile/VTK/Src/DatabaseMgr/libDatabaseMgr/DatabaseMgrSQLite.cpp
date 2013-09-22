#include <iostream>

#include <QDebug>
#include <QFile>
#include <QSettings>
#include <qsqlresult.h>
#include <QImageWriter>

#include "Cupboard.h"
#include "DatabaseMgrSQLite.h"

QString DatabaseMgrSQLite::getDriverName() const {
	return(QString("QSQLITE"));
}

//-----------------------------------------------------------------------------------------

DatabaseMgrSQLite::DatabaseMgrSQLite(const QString & aqstrDBPathName) :
DatabaseMgr(aqstrDBPathName) {
	bool bOk = connect2SQLDatabase();
	if(bOk == false) {
		printError("Could not connect to SQLite database");
		exit(-1);
	}
}

//-----------------------------------------------------------------------------------------

void DatabaseMgrSQLite::saveScene(const QString &aqstrOldSceneName, const QString &aqstrNewSceneName) {
	//Update the name of the "temp scene" if not pressed, delete "temp scene"
	if(m_QSqlDatabase.isOpen())	{
		QString qry;
		QSqlQuery tempQuery;

		//Check if the Scene defined via the argument is in the table
		QString tqry = QString("SELECT SceneID FROM Scene WHERE SceneName = '%1'").arg(aqstrOldSceneName);
		tempQuery.exec(tqry);
		if(tempQuery.last() == '\0')	{
			//Scene not found report this and exit
			qDebug() << QString("Item %1 not in the table.").arg(aqstrOldSceneName);
		}
		else	{
			qry = QString("UPDATE Scene SET SceneName = '%1' WHERE SceneName = '%2'").arg(aqstrNewSceneName).arg(aqstrOldSceneName);
			QSqlQuery query(qry);

			qDebug() << QString("Scene %1 renamed to %2.").arg(aqstrOldSceneName).arg(aqstrNewSceneName);
		}
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
	}
}

//-------------------------------------------------------------------------------------------------

void DatabaseMgrSQLite::loadScene(const QString &aqstrSceneName) {
}

//-------------------------------------------------------------------------------------------------

void DatabaseMgrSQLite::newScene() {
}

//-------------------------------------------------------------------------------------------------

void DatabaseMgrSQLite::deleteItem(const QString &aqstrSceneObjectID)	{
	if(m_QSqlDatabase.open())	{
		QString qry;
		QSqlQuery tempQuery;

		//Check if the Product defined via the argument is in the table
		QString tqry = QString("SELECT SceneID, ObjectID FROM SceneObject WHERE SceneObjectID = '%1'").arg(aqstrSceneObjectID);
		tempQuery.exec(tqry);
		if(tempQuery.last() == '\0')	{
			//Product not found report this and exit
			qDebug() << QString("Item %1 not in the table.").arg(aqstrSceneObjectID);
		}
		else	{
			//We have picked something. Store SceneID and ObjectID
			int nSceneID = tempQuery.value(0).toInt();
			int nObjectID = tempQuery.value(1).toInt();

			qDebug() << QString("Scene ID = %1. Deleted item = %2.").arg(nSceneID).arg(nObjectID);
		}
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
	}
}

//-----------------------------------------------------------------------------------------

bool DatabaseMgrSQLite::createTable() {
	// Create a table within the given database
	if (m_QSqlDatabase.open())	{
		qDebug() << "The database contains the following tables: " << m_QSqlDatabase.tables();

		QSqlQuery query;
		//Create table ObjectType if not already created
		QString qry = "CREATE TABLE IF NOT EXISTS ObjectType "
			"(ObjectTypeID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"ObjectTypeName VARCHAR(20))";
		query.exec(qry);

		//Create table ObjectType if not already created
		qry = "CREATE TABLE IF NOT EXISTS Category "
			"(CategoryID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"ObjectTypeID INTEGER, "
			"CategoryName VARCHAR(20), "
			"FOREIGN KEY (ObjectTypeID) REFERENCES ObjectType(ObjectTypeID))";
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
			"ProductCodeImageName VARCHAR(20), "
			"ProductCodeID INTEGER,"
			"FOREIGN KEY (ProductCodeID) REFERENCES ProductCode(ProductCodeID))";
		query.exec(qry);


		/*PART/EQUIPMENT MANIPULATION*/

		//Create table Transform if not already created
		qry = "CREATE TABLE IF NOT EXISTS Transform "
			"(TransformID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"LocationX REAL, "
			"LocationY REAL, "
			"LocationZ REAL, "
			"Matrix00 REAL, "
			"Matrix01 REAL, "
			"Matrix02 REAL, "
			"Matrix10 REAL, "
			"Matrix11 REAL, "
			"Matrix12 REAL, "
			"Matrix20 REAL, "
			"Matrix21 REAL, "
			"Matrix22 REAL)";
		query.exec(qry);

		//Create table Primitive if not already created
		qry = "CREATE TABLE IF NOT EXISTS Primitive "
			"(PrimitiveID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"PrimitiveName TEXT, "
			"PrimitiveParameterNumber INTEGER,"
			"Param0 REAL,"
			"Param1 REAL,"
			"Param2 REAL)";
		query.exec(qry);

		//Create table Part if not already created
		qry = "CREATE TABLE IF NOT EXISTS Part "
			"(PartID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"PartName TEXT,"
			"PartPrimitiveID INTEGER,"
			"FOREIGN KEY (PartPrimitiveID) REFERENCES Primitive(PrimitiveID))";
		query.exec(qry);

		//Create table PartTransform if not already created
		qry = "CREATE TABLE IF NOT EXISTS PartTransform "
			"(PartTransformID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"PartID INTEGER,"
			"TransformID INTEGER,"
			"FOREIGN KEY (PartID) REFERENCES Part(PartID),"
			"FOREIGN KEY (TransformID) REFERENCES Transform(TransformID))";
		query.exec(qry);

		//Create table Equipment if not already created
		qry = "CREATE TABLE IF NOT EXISTS Equipment "
			"(EquipmentID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"EquipmentName TEXT,"
			"EquipmentComponentNo INTEGER,"
			"EquipmentSpecificationMethod INTEGER,"
			"EquipmentPrimitiveID INTEGER,"
			"FOREIGN KEY (EquipmentPrimitiveID) REFERENCES Primitive(PrimitiveID))";
		query.exec(qry);

		//Create table EquipmentTransform if not already created
		qry = "CREATE TABLE IF NOT EXISTS EquipmentTransform "
			"(EquipmentTransformID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"EquipmentID INTEGER,"
			"TransformID INTEGER,"
			"FOREIGN KEY (EquipmentID) REFERENCES Equipment(EquipmentID),"
			"FOREIGN KEY (TransformID) REFERENCES Transform(TransformID))";
		query.exec(qry);

		//Create table EquipmentPart if not already created
		qry = "CREATE TABLE IF NOT EXISTS EquipmentPart "
			"(EquipmentPartID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"EquipmentTransformID UNSIGNED INTEGER,"
			"PartTransformID UNSIGNED INTEGER,"
			"FOREIGN KEY (EquipmentTransformID) REFERENCES Equipment(EquipmentTransformID),"
			"FOREIGN KEY (PartTransformID) REFERENCES PartTransform(PartTransformID))";
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
			"ProductCodeID INTEGER, "
			"PropertiesID INTEGER, "
			"FOREIGN KEY (ProductCodeID) REFERENCES ProductCode(ProductCodeID), "
			"FOREIGN KEY (PropertiesID) REFERENCES Properties(PropertiesID))";
		query.exec(qry);

		//Create table Texture if not already created
		qry = "CREATE TABLE IF NOT EXISTS Texture "
			"(TextureID INTEGER PRIMARY KEY AUTOINCREMENT,"
			"TextureName TEXT,"
			"TexturePath TEXT)";
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
		m_QSqlDatabase.close();
		return true;
	}
	else	{
		//If error occurs, report it and give false
		std::cout << "Error creating table: " << lastError().text().toStdString() << std::endl;
		return false;
	}
}

//=========================================================================================

bool DatabaseMgrSQLite::insertObjectType(const QString &aqstrObjectType) {
	if(m_QSqlDatabase.open())	{
		QString qry;
		QSqlQuery tempQuery;

		//Check if the Category defined via the argument is already in the table
		QString tqry = QString("SELECT ObjectTypeID FROM ObjectType WHERE ObjectTypeName = '%1'").arg(aqstrObjectType);
		tempQuery.exec(tqry);

		if(tempQuery.last() == '\0')	{
			//Category not found and should be inserted
			qry = QString("INSERT INTO ObjectType(ObjectTypeName) "
				"VALUES('%1')").arg(aqstrObjectType);
			QSqlQuery query(qry);
		}
		else	{
			qDebug() << QString("ObjectType %1 already in the database.").arg(aqstrObjectType);
		}
		return true;
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
		return false;
	}
}

//------------------------------------------------------------------------------------------
bool DatabaseMgrSQLite::insertCategory(const QString &aqstrCategory, const QString &aqstrObjectType) {
	if(m_QSqlDatabase.open())	{
		QString qry;
		QSqlQuery tempQuery;

		//Check if the Category defined via the argument is already in the table
		QString tqry = QString("SELECT CategoryID FROM Category WHERE CategoryName = '%1'").arg(aqstrCategory);
		tempQuery.exec(tqry);

		if(tempQuery.last() == '\0')	{
			//Category not found and should be inserted
			qry = QString("INSERT INTO Category(CategoryName, ObjectTypeID) "
				"SELECT '%1', ObjectTypeID FROM ObjectType WHERE ObjectTypeName = '%2'").arg(aqstrCategory).arg(aqstrObjectType);
			QSqlQuery query(qry);
		}
		else	{
			qDebug() << QString("Category %1 already in the database.").arg(aqstrCategory);
		}
		return true;
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
		return false;
	}
}

//-----------------------------------------------------------------------------------------

bool DatabaseMgrSQLite::insertProduct(const QString &aqstrProduct, const QString &aqstrCategory)	{
	if(m_QSqlDatabase.open())	{
		QString qry;
		QSqlQuery tempQuery;

		//Check if the Product defined via the argument is already in the table
		QString tqry = QString("SELECT ProductID FROM Product WHERE ProductName = '%1'").arg(aqstrProduct);
		tempQuery.exec(tqry);

		if(tempQuery.last() == '\0')	{
			//Product not found and should be inserted
			qry = QString("INSERT INTO Product(ProductName, CategoryID) "
				"SELECT '%1', CategoryID FROM Category WHERE CategoryName = '%2'").arg(aqstrProduct).arg(aqstrCategory);
			QSqlQuery query(qry);
		}
		else	{
			qDebug() << QString("Product %1 already in the database").arg(aqstrProduct);
		}
		return true;
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
		return false;
	}
}

//---------------------------------------------------------------------------------------------

bool DatabaseMgrSQLite::insertProductCode(const QString &aqstrProduct, const QString &aqstrProductCodeNumber)	{
	if(m_QSqlDatabase.open())	{
		QString qry;
		QSqlQuery tempQuery;

		//Check if the Product defined via the argument is already in the table
		QString tqry = QString("SELECT ProductCodeID FROM ProductCode WHERE ProductCodeNumber = '%1'").arg(aqstrProductCodeNumber);
		tempQuery.exec(tqry);
		if(tempQuery.last() == '\0')	{
			//Product not found and should be inserted
			qry = QString("INSERT INTO ProductCode(ProductCodeNumber, ProductID) "
				"SELECT '%1', ProductID FROM Product WHERE ProductName = '%2'").arg(aqstrProductCodeNumber).arg(aqstrProduct);
			QSqlQuery query(qry);
		}
		else	{
			//EAN already in the database.
			qDebug() << QString("Product Code %1 already in the database.").arg(aqstrProductCodeNumber);
		}
		return true;
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
		return false;
	}
}

//---------------------------------------------------------------------------------------------
bool DatabaseMgrSQLite::insertProductCodeImage(const QString &aqstrProductCodeNumber, const QString &aqstrProductCodeImage)	{
	if(m_QSqlDatabase.open())	{
		QString qry;
		QSqlQuery tempQuery;

		//Check if the Product code image defined via the argument is already in the table
		QString tqry = QString("SELECT ProductCodeImageID FROM ProductCodeImage WHERE ProductCodeImageName = '%1'").arg(aqstrProductCodeImage);
		tempQuery.exec(tqry);
		if(tempQuery.last() == '\0')	{
			//Product not found and should be inserted
			qry = QString("INSERT INTO ProductCodeImage(ProductCodeImageName, ProductCodeID) "
				"SELECT '%1', ProductCodeID FROM ProductCode WHERE ProductCodeNumber = '%2'").arg(aqstrProductCodeImage).arg(aqstrProductCodeNumber);
			QSqlQuery query(qry);
		}
		else	{
			//Product code Image already in the database.
			qDebug() << QString("Product Code Image %1 already in the database.").arg(aqstrProductCodeImage);
		}
		return true;
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
		return false;
	}
}

//=============================================================================================

void DatabaseMgrSQLite::insertPrimitive(
	const QString &aqstrPrimitiveName, 
	int anPrimitiveParameterNumber, 
	const std::vector < double > & aarrdbParams) {


	if(m_QSqlDatabase.open())	{
		
		//Check if the Primitive defined via the argument is already in the table
	 	QString tqry = QString("SELECT PrimitiveID FROM Primitive WHERE PrimitiveName = '%1'").arg(aqstrPrimitiveName);
		QSqlQuery tempQuery;
		tempQuery.exec(tqry);
		if(tempQuery.last() == '\0')	{

			QString qry = QString("INSERT INTO Primitive(PrimitiveName, PrimitiveParameterNumber, ");
			int nParamsNr = aarrdbParams.size();
			int nI;
			for(nI = 0; nI < nParamsNr-1; nI++) {
				qry += QString("Param%1, ").arg(nI);
			}
			qry+=QString("Param%1)").arg(aarrdbParams.size()-1);

			qry+= QString("VALUES ('%1',%2,").arg(aqstrPrimitiveName).arg(anPrimitiveParameterNumber);
			for(nI = 0; nI < nParamsNr-1; nI++) {
				qry += QString("%1, ").arg(aarrdbParams[nI]);
			}
			qry+=QString("%1").arg(aarrdbParams[nParamsNr-1]);
			qry += ")";
			QSqlQuery query(qry);
		}
		else	{
			//Primitive already in the database.
			qDebug() << QString("Primitive '%1' already in the database.").arg(aqstrPrimitiveName);
		}
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
	}
}

//---------------------------------------------------------------------------------------------

void DatabaseMgrSQLite::insertTexture(const QString &aqstrTextureName, const QString &aqstrTexturePath)	{
	if(m_QSqlDatabase.open())	{
		
		//Check if the Primitive defined via the argument is already in the table
	 	QString tqry = QString("SELECT TextureID FROM Texture WHERE TextureName = '%1'").arg(aqstrTextureName);
		QSqlQuery tempQuery;
		tempQuery.exec(tqry);
		if(tempQuery.last() == '\0')	{

			QString qry = QString("INSERT INTO Texture(TextureName, TexturePath)"
				"VALUES('%1', '%2')").arg(aqstrTextureName).arg(aqstrTexturePath);
			QSqlQuery query(qry);
		}
		else	{
			//Primitive already in the database.
			qDebug() << QString("Texture '%1' already in the database.").arg(aqstrTextureName);
		}
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
	}
}

//---------------------------------------------------------------------------------------------

void DatabaseMgrSQLite::insertCupboard(const Cupboard & aCupboard) {
	if(m_QSqlDatabase.open())	{

		QString qry = aCupboard.getSQLPrintCommand().c_str();
		QSqlQuery query(qry);

	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
	}
}


//=============================================================================================

bool DatabaseMgrSQLite::insertLocation(const QString &aqstrProductCodeNumber, const QString aqstrarrLocation[3])	{
	return false;
}

//---------------------------------------------------------------------------------------------

bool DatabaseMgrSQLite::insertOrientation(const QString &aqstrProductCodeNumber, const QString aqstrarrOrientation[3])	{
	return false;
}

//---------------------------------------------------------------------------------------------

bool DatabaseMgrSQLite::insertProperties(const QString &aqstrProductCodeNumber, unsigned int m_LocationID, unsigned int m_OrientationID)	{
	return true;
}

//---------------------------------------------------------------------------------------------

bool DatabaseMgrSQLite::insertObject(unsigned int m_ProductCodeID, unsigned int m_PropertiesID)	{
	if(m_QSqlDatabase.open())	{
		QString qry;

		qry = QString("INSERT INTO Object "
			"(CodeID, PropertiesID) "
			"VALUES (%1, %2)").arg(m_ProductCodeID).arg(m_PropertiesID);
		QSqlQuery query(qry);

		return true;
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
		return false;
	}
	return false;
}

//-----------------------------------------------------------------------------------------

bool DatabaseMgrSQLite::insertScene(const QString &aqstrSceneName)	{
	if(m_QSqlDatabase.open())	{
		QString qry;
		QSqlQuery tempQuery;

		//Check if the Scene defined via the argument is already in the table
		QString tqry = QString("SELECT SceneID FROM Scene WHERE SceneName = '%1'").arg(aqstrSceneName);
		tempQuery.exec(tqry);
		if(tempQuery.last() == '\0')	{
			//Category not found and should be inserted
			qry = QString("INSERT INTO Scene(SceneName) "
				"VALUES('%1')").arg(aqstrSceneName);
			QSqlQuery query(qry);
		}
		else	{
			qDebug() << QString("Scene %1 already in the database.").arg(aqstrSceneName);
		}
		return true;
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
		return false;
	}
}

//-------------------------------------------------------------------------------------------------

bool DatabaseMgrSQLite::insertSceneObject(unsigned int m_SceneID, unsigned int m_ObjectID)	{
	if(m_QSqlDatabase.open())	{
		QString qry;

		qry = QString("INSERT INTO SceneObject(SceneID, ObjectID) VALUES (%1, %2)").arg(m_SceneID).arg(m_ObjectID);
		QSqlQuery query(qry);

		return true;
	}
	else	{
		std::cout << "Error opening: " << lastError().text().toStdString() << std::endl;
		return false;
	}
	return false;
}

//=============================================================================================