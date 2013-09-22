#ifndef VR_DATABASE_MGR_H
#define VR_DATABASE_MGR_H

#include <vector>
#include <string>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

namespace VR {

	struct DatabaseMgrParams	{
		QString m_qstrObjectType;
		QString m_qstrObjectName;
		std::vector < float > m_arrflParams;

		DatabaseMgrParams();
	};

	void printError(const char * apchMessage);
	void printWarning(const char * apchMessage);

	class DatabaseMgr {

	public:
		typedef enum {QODBC = 1, QSQLITE = 2} DRIVER_NAME;
		int m_nDriverSelection;
		virtual QString getDriverName() const = 0;

		static DatabaseMgr & Create(const QString & aqstrDBPathName, DRIVER_NAME aDriverName);
		static DatabaseMgr * CreateSQLite(const QString & aqstrDBPathName);
		static DatabaseMgr * CreateODBC(const QString & aqstrDBPathName);

		virtual ~DatabaseMgr() = 0;

		QSqlError lastError() const;

		virtual void deleteItem(const QString &aqstrSceneObjectID) = 0;
		virtual void saveScene(const QString &aqstrOldSceneName, const QString &aqstrNewSceneName) = 0;
		virtual void loadScene(const QString &aqstrSceneName) = 0;
		virtual void newScene() = 0;


		virtual bool createTable() = 0;

		virtual void fillPrimitiveTable(std::string & astrCommand) = 0;
		virtual std::string getSQLData(const int & anElement) = 0;

		virtual void insertIntoDatabase(const DatabaseMgrParams & aDatabaseMgrParams) = 0;
		virtual std::vector<float> selectFromDatabase(const int & anElementID) = 0;


	protected:

		DatabaseMgr(const QString & aqstrDBPathName);
		bool connect2SQLDatabase();

		QSqlDatabase m_QSqlDatabase;

		const QString m_qstrDBPathName;
	};
}
#endif //VR_DATABASE_MGR_H