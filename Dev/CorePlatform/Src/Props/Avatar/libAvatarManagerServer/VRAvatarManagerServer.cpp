#include "BasicStringDefinitions.h"

#include "VRDatabaseManager.h"

#include "VRAvatarManagerServer.h"


using namespace VR;
using namespace std;

#define DEBUG_AVATARS 0

//==============================================================================

AvatarManagerServer::AvatarManagerServer()	{
	DatabaseManagerParams dbParams;
	dbParams.m_qstrConnectionName = "Avatar";
	dbParams.m_qstrDBName = "../../../../Databases/Avatars.db";

	m_pDb = new DatabaseManager(dbParams);
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

void AvatarManagerServer::registerAvatar(string & astrRequest)	{
	vector<string> vecstrSplitString = splitString(astrRequest,";");

	string strSqlQuery = "INSERT INTO Avatar(AvatarName, AvatarMatrix) VALUES ('" + 
		vecstrSplitString[0] + "','" + vecstrSplitString[1] + "')";

	m_pDb->executeAndGetResult(strSqlQuery);
}

//------------------------------------------------------------------------------

void AvatarManagerServer::updateAvatarData(std::string & astrRequest)	{
	vector<string> vecstrSplitString = splitString(astrRequest,";");
	string strSqlQuery = "UPDATE Avatar" 
		" SET AvatarMatrix = '" + vecstrSplitString[1] + 
//		"', AvatarDateTime = CURRENT_TIMESTAMP" + 
		"', AvatarDateTime = '" + tostr(0
										//m_pTimer->getCurrTimeInMiliSeconds()
										) + "'"+ 
		" WHERE AvatarName = '" + vecstrSplitString[0] + "'";

	m_pDb->executeAndGetResult(strSqlQuery);
}

//------------------------------------------------------------------------------

list<string> AvatarManagerServer::getAvatarsDataFromDB()	{
#if DEBUG_AVATARS
	vector<string> vecstrSplitString = splitString(astrRequest,";");
	int nI;
	string strSqlCondition = "'" + vecstrSplitString[0] + "'";
	for (nI=1;nI<vecstrSplitString.size();nI++)	{
		strSqlCondition += " OR AvatarName = '" + vecstrSplitString[nI] + "'";
	}
	strSqlQuery = "SELECT * FROM Avatar WHERE AvatarName = " + strSqlCondition;
#else
	string strSqlQuery = "SELECT AvatarName, AvatarMatrix FROM Avatar";
#endif //DEBUG_AVATAR

	list<string> lststrResult = m_pDb->executeAndGetResult(strSqlQuery);

	return lststrResult;
}