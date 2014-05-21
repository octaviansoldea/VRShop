#ifndef DATABASE_MANAGER_H
#define DATABASE_MANAGER_H

#include <QObject>

#include <QSqlRelationalTableModel>

#include <QSqlDatabase>
#include <QSqlField>

#include <vector>
#include <list>

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

		bool execute(const std::string & astrQuery);
		std::list<std::string> executeAndGetResult(const std::string & astrQuery);

	protected:
		bool createTable(const std::string & astrTableName, const std::string & astrTableStmt);
		bool removeTable(const QString& aqstrTableName);

		void insertRow(const std::string & astrTableName, std::string &astrTblFieldValues);
		void deleteRow(const std::string & astrTableName, const std::string & astrObjectName);
		void updateDB();

		bool createConnection(const DatabaseManagerParams & aDBMgrParams);
		bool removeConnection();

		bool dropDatabase(const QString & aqstrDBName);

		DatabaseManagerParams m_DBMgrParams;

		virtual void systemOfTables(std::vector<std::pair<std::string,std::string>> & avecStmtPairs);

	private:
		bool containsTable(const QString & aqstrTableName);
	};
}
#endif //DATABASE_MANAGER_H