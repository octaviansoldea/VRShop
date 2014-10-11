#ifndef VR_DATABASE_INTERFACE_H
#define VR_DATABASE_INTERFACE_H

#include <QObject>

#include <QSqlRelationalTableModel>

#include <QSqlDatabase>
#include <QSqlField>

#include <vector>
#include <list>

namespace VR	{
	struct DatabaseInterfaceParams	{
		QString m_qstrDBName;
		QString m_qstrConnectionName;

		DatabaseInterfaceParams(const QString & aqstrDBName = "", const QString & aqstrConnectionName = "");
	};

	class DatabaseInterface {

	public:

		DatabaseInterface();
		DatabaseInterface(const DatabaseInterfaceParams & aDBInterfaceParams);
		virtual ~DatabaseInterface();

		virtual void init(const DatabaseInterfaceParams & aDBInterfaceParams);

		bool execute(const std::string & astrQuery);
		std::list<std::string> executeAndGetResult(const std::string & astrQuery);

		bool createTable(const std::string & astrTableName, std::vector<std::pair<std::string,std::string>> & avecTableElements);

//	protected:
		bool createTable(const std::string & astrTableName, const std::string & astrTableStmt);
		bool removeTable(const QString& aqstrTableName);

		int insertRow(const std::string & astrTableName, std::string &astrTblFieldValues);

		void deleteRow(const std::string & astrTableName, const std::string & astrObjectName);
		void updateDB();

		bool createConnection(const DatabaseInterfaceParams & aDBInterfaceParams);
		bool removeConnection();

		bool dropDatabase(const QString & aqstrDBName);

		DatabaseInterfaceParams m_DBInterfaceParams;

		virtual void systemOfTables(std::vector<std::pair<std::string,std::string>> & avecStmtPairs);

	private:
		bool containsTable(const QString & aqstrTableName);
	};
}
#endif //VR_DATABASE_INTERFACE_H