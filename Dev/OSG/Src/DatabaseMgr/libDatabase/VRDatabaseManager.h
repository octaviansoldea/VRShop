#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <QObject>

#include <QSqlRelationalTableModel>

#include <QSqlDatabase>
#include <QSqlField>

#include <vector>

namespace VR	{
	struct DatabaseManagerParams	{
		QString m_qstrDBName;
		QString m_qstrConnectionName;

		DatabaseManagerParams();
	};

	class DatabaseManager : public QObject {
		Q_OBJECT

	public:
		DatabaseManager(QObject * parent = 0);
		DatabaseManager(const DatabaseManagerParams & aDBMgrParams, QObject * parent = 0);
		virtual ~DatabaseManager();

	protected:
		bool createTable(const std::string & aqstrTableName, const std::string & astrTableStmt);
		bool removeTable(const QString& aqstrTableName);

		void insertRow(const std::string & astrTableName, std::string &astrTblFieldValues);
		void deleteRow(const std::string & astrTableName, const std::string & astrObjectName);
		void updateDB();

		bool execute(const std::string & astrQuery);

		bool createConnection(const DatabaseManagerParams & aDBMgrParams);
		bool removeConnection();

		bool dropDatabase(const QString & aqstrDBName);

		DatabaseManagerParams m_DatabaseManagerParams;

	private:
		void printError(const QString & aqstrMessage);
		void printWarning(const QString & aqstrMessage);

		bool containsTable(const QString & aqstrTableName);
	};
}
#endif //DATABASE_MANAGER_H