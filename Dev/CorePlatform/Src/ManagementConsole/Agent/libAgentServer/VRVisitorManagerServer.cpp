#include <QString>
#include <iostream>

#include "BasicStringDefinitions.h"
#include "VRAppData.h"

#include <ctime>

#include "VRDatabaseInterface.h"

#include "VRVisitorManagerServer.h"

using namespace VR;
using namespace std;

DatabaseInterface VisitorManagerServer::m_DIVisitor(VisitorManagerServer::getDBParams());

//==============================================================================

VisitorManagerServer::VisitorManagerServer()	{
}

//------------------------------------------------------------------------------

VisitorManagerServer::~VisitorManagerServer()	{
}

//------------------------------------------------------------------------------

DatabaseInterfaceParams VisitorManagerServer::getDBParams()	{
	DatabaseInterfaceParams dbParams;
	dbParams.m_qstrConnectionName = "Visitor";
	dbParams.m_qstrDBName = getDatabaseName().c_str();

	return dbParams;
}

//------------------------------------------------------------------------------

string VisitorManagerServer::getTableName()	{
	return "Visitor";
}

//------------------------------------------------------------------------------

string VisitorManagerServer::getDatabaseName()	{
	string strFFullPath = AppData::getFPathDatabases() + "Visitors.db";
	
	return strFFullPath;
}

//------------------------------------------------------------------------------

vector<pair<string,string>> VisitorManagerServer::getDBElements()	{
	vector<pair<string,string>> vecpairDBElements;

	vecpairDBElements.push_back(make_pair("VisitorID", "INTEGER"));
	vecpairDBElements.push_back(make_pair("VisitorIP", "TEXT"));
	vecpairDBElements.push_back(make_pair("VisitorStartDateTime", "TEXT"));
	vecpairDBElements.push_back(make_pair("VisitorEndDateTime", "TEXT"));
	
	return vecpairDBElements;
}

//------------------------------------------------------------------------------

void VisitorManagerServer::createDB()	{
	m_DIVisitor.createTable(getTableName(), getDBElements());
}

//------------------------------------------------------------------------------

DatabaseInterface * VisitorManagerServer::getDatabaseInterface() {
	return(&m_DIVisitor);
}

//------------------------------------------------------------------------------

void VisitorManagerServer::registerVisitor(const string & astrVisitorIP, const int anUserID)	{
	string strSqlQuery = "INSERT INTO Visitor(VisitorID, VisitorIP, VisitorStartDateTime, VisitorEndDateTime) VALUES ('" + 
		tostr(anUserID) + "','" + astrVisitorIP + "','" + tostr(time(NULL)) + "',0)";

	m_DIVisitor.executeAndGetResult(strSqlQuery);
}

//------------------------------------------------------------------------------

void VisitorManagerServer::unregisterVisitor(const std::string & astrUserID)	{
	string strSqlQuery = "UPDATE Visitor SET VisitorEndDateTime = '" + tostr(time(NULL)) +
		"' WHERE VisitorID = '" + astrUserID + "' AND VisitorEndDateTime = '0'";

	m_DIVisitor.executeAndGetResult(strSqlQuery);
}
