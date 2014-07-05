#include "VRDatabaseMgrODBC.h"

using namespace VR;
using namespace std;

QString DatabaseMgrODBC::getDriverName() const {
	return(QString("ODBC"));
}

//-----------------------------------------------------------------------------------------

DatabaseMgrODBC::DatabaseMgrODBC(const QString & astrDBPathName) :
DatabaseMgr(astrDBPathName) {
	bool bOk = connect2SQLDatabase();
	if(bOk == false) {
		printError("Could not connect to ODBC database");
		exit(-1);
	}
}

//-----------------------------------------------------------------------------------------

bool DatabaseMgrODBC::executeQuery(const DatabaseMgrParams & aDatabaseMgrParams)	{
	return(false);
}

//-----------------------------------------------------------------------------------------

void DatabaseMgrODBC::fillPrimitiveTable(const DatabaseMgrParams & aDatabaseMgrParams)	{
}

//-----------------------------------------------------------------------------------------

string DatabaseMgrODBC::readFromDB(string & astrCommand)	{
	return ("");
}
