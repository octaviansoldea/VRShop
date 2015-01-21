#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
#include <qimage.h>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>


struct init	{
public:
	const QString &astrCategory;
	const QString &astrProduct;
	const QString &astrProductCode;
	const int aarrLocation[3];
	const int aarrOrientation[3];
};

class DatabaseManager : public QObject    {
	Q_OBJECT

public:
	//Set DB type QODBC (default) or QSQLITE
	DatabaseManager(const QString &astrDBName, const QString &astrDBType = "QSQLITE", QObject *parent = 0);
	~DatabaseManager();

	//This function establishes a connection
	//called automatically via a constructor
	bool createConnection();
	bool connect2SQLDatabase();

	//Creates table within the database
	bool createTable();

	QSqlError lastError();

public slots:
	void insertItem(const QString &astrCategory, const QString &astrProduct, const QString &astrProductCodeNumber, const QString &astrProductCodeImage, const QString astrarrLocation[3],const QString astrarrOrientation[3]);
	void deleteItem(const QString &astrSceneObjectID);	//NOT YET FINISHED
	void saveScene(const QString &astrOldSceneName, const QString &astrNewSceneName);
	void loadScene(const QString &astrSceneName)	{};
	void newScene()	{};

private:
	QSqlDatabase db;
	const QString m_strDBType;
	const QString m_strDBName;
	QString dbName;

	//functions
	bool insertCategory(const QString &astrCategory);
	bool insertProduct(const QString &astrProduct, unsigned int &m_CategoryID);
	bool insertProductCode(unsigned int &m_ProductID, const QString &astrProductCodeNumber);
	bool insertProductCodeImage(unsigned int &m_ProductCodeID, const QString &astrProductCodeImage);
	bool insertLocation(unsigned int &m_ProductCodeID, const QString astrarrLocation[3]);
	bool insertOrientation(unsigned int &m_ProductCodeID, const QString astrarrOrientation[3]);
	bool insertProperties(unsigned int &m_ProductCodeID, unsigned int &m_LocationID, unsigned int &m_OrientationID);
	bool insertObject(unsigned int &m_ProductCodeID, unsigned int &m_PropertiesID);
	bool insertScene(const QString &astrSceneName="temp");
	bool insertSceneObject(unsigned int &m_SceneID, unsigned int &m_ObjectID);

	//IDdeclarations
	unsigned int CategoryID;
	unsigned int ProductID;
	unsigned int ProductCodeID;
	unsigned int ProductCodeImageID;
	unsigned int LocationID;
	unsigned int OrientationID;
	unsigned int PropertiesID;
	unsigned int ObjectID;
	unsigned int SceneID;
	unsigned int SceneObjectID;

	//Misc
	typedef enum {QODBC = 1, QSQLITE = 2} DRIVER_NAME;
	int m_nDriverSelection;
};
#endif //DATABASE_H