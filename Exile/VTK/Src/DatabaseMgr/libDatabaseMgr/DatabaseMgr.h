#ifndef DATABASE_MGR_H
#define DATABASE_MGR_H

#include <vector>

#include <qimage.h>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class Cupboard;

void printError(const char * apchMessage);
void printWarning(const char * apchMessage);

class DatabaseMgr {

public:
		//Misc
	typedef enum {QODBC = 1, QSQLITE = 2} DRIVER_NAME;
	int m_nDriverSelection;
	virtual QString getDriverName() const = 0;

	static DatabaseMgr & Create(const QString & aqstrDBPathName, DRIVER_NAME aDriverName);
	static DatabaseMgr * CreateSQLite(const QString & aqstrDBPathName);
	static DatabaseMgr * CreateODBC(const QString & aqstrDBPathName);

	virtual ~DatabaseMgr() = 0;

	QSqlError lastError() const;

	void insertItem(const QString &aqstrObjectType, const QString &aqstrCategory, const QString &aqstrProduct, const QString &aqstrProductCodeNumber, const QString &aqstrProductCodeImage, const QString aqstrarrLocation[3],const QString aqstrarrOrientation[3]);
	virtual void deleteItem(const QString &aqstrSceneObjectID) = 0;	//NOT YET FINISHED
	virtual void saveScene(const QString &aqstrOldSceneName, const QString &aqstrNewSceneName) = 0;
	virtual void loadScene(const QString &aqstrSceneName) = 0;
	virtual void newScene()	 = 0;

	virtual bool createTable() = 0;

	virtual void insertPrimitive(const QString &aqstrPrimitiveName, 
								 int anPrimitiveParameterNumber, 
								 const std::vector < double > & aarrdbParams) = 0;
	
	virtual void insertTexture(const QString &aqstrTextureName, const QString &aqstrTexturePath) = 0;
	virtual void insertCupboard(const Cupboard & aCupboard) = 0;

protected:

	DatabaseMgr(const QString & aqstrDBPathName);

	//Insert functions
	virtual bool insertObjectType(const QString &aqstrObjectType) = 0;
	virtual bool insertCategory(const QString &aqstrCategory, const QString &aqstrObjectType) = 0;
	virtual bool insertProduct(const QString &aqstrProduct, const QString &aqstrCategory) = 0;
	virtual bool insertProductCode(const QString &aqstrProduct, const QString &aqstrProductCodeNumber) = 0;
	virtual bool insertProductCodeImage(const QString &aqstrProductCodeNumber, const QString &aqstrProductCodeImage) = 0;


	virtual bool insertLocation(const QString &aqstrProductCodeNumber, const QString aqstrarrLocation[3]) = 0;
	virtual bool insertOrientation(const QString &aqstrProductCodeNumber, const QString aqstrarrOrientation[3]) = 0;
	virtual bool insertProperties(const QString &aqstrProductCodeNumber, unsigned int m_LocationID, unsigned int m_OrientationID) = 0;
	virtual bool insertObject(unsigned int m_ProductCodeID, unsigned int m_PropertiesID) = 0;
	virtual bool insertScene(const QString &aqstrSceneName="temp") = 0;
	virtual bool insertSceneObject(unsigned int m_SceneID, unsigned int m_ObjectID) = 0;


	//This function establishes a connection
	//called automatically via a constructor
	bool connect2SQLDatabase();

	QSqlDatabase m_QSqlDatabase;

	const QString m_qstrDBPathName;

};
#endif //DATABASE_MGR_H