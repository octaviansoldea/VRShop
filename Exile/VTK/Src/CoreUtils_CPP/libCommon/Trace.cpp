#include <string>

#include "Log.h"
#include "Trace.h"

using namespace std;

void Trace::init(string astrLogFileName) { 
	m_pLog = new CFileLog(astrLogFileName);
	m_pLog->Clear(); 
}

void Trace::printNormalMessage(const char * astrMessage) {
#ifdef DEBUG_PRINT	
	printf("%s\n", astrMessage);
#endif //DEBUG_PRINT
	if(m_pLog == NULL)
		return;

	m_pLog->AddLog(astrMessage);

}

void Trace::printWarningMessage(const char * astrMessage) {
	//if(m_pLog == NULL)
	//	return;
	static string strDSPVWarning("DSPV Warning - ");
	string strMsg = strDSPVWarning + astrMessage;
	printNormalMessage(strMsg.c_str());
}

void Trace::printErrorMessage(const char * astrMessage) {
	//if(m_pLog == NULL)
	//	return;
	static string strDSPVError("DSPV Error - ");
	string strMsg = strDSPVError + astrMessage;
	printNormalMessage(strMsg.c_str());
	exit(-1);
}
