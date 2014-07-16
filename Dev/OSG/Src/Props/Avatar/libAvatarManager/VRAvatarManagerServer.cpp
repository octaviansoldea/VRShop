#include "VRDatabaseManager.h"

#include "VRAvatarManagerServer.h"


using namespace VR;
using namespace std;

//==============================================================================

AvatarManagerServer::AvatarManagerServer()	{
	DatabaseManagerParams dbParams;
	dbParams.m_qstrConnectionName = "Avatar";
	dbParams.m_qstrDBName = "../../../Databases/Avatar.db";

	m_pDb = new DatabaseManager(dbParams);

	createAvatarDB();
}

//------------------------------------------------------------------------------

AvatarManagerServer::~AvatarManagerServer()	{
	delete m_pDb;
}

//------------------------------------------------------------------------------

const char* AvatarManagerServer::className() const	{
	return "AvatarManagerServer";
}

//------------------------------------------------------------------------------

void AvatarManagerServer::createAvatarDB()	{
	string strSQLFormat =
		"CREATE TABLE IF NOT EXISTS Avatars ( \
		AvatarID INTEGER PRIMARY KEY AUTOINCREMENT UNIQUE, \
		AvatarName TEXT, \
		AvatarMatrix TEXT, \
		AvatarDateTime TEXT);";

	m_pDb->execute(strSQLFormat);
}

//------------------------------------------------------------------------------

void AvatarManagerServer::updateAvatarData(const string & astrAvatarName, string & astrAvatarMatrix)	{
	string strQuery;

	strQuery = "UPDATE Avatars "
		"SET AvatarMatrix = '" + astrAvatarMatrix +
		"' WHERE AvatarName = " + astrAvatarName + "';";

	m_pDb->execute(strQuery);
}

//------------------------------------------------------------------------------

string AvatarManagerServer::getAvatarsDataFromDB()	{
	string strResult;

	string strQuery;

	list<string>::iterator it = m_pDb->executeAndGetResult(strQuery).begin();
	string & strProductData = *it;

	return strProductData;
}