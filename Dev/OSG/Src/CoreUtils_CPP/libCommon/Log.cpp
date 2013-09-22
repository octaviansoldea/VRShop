#include <sstream>
#include <fstream>
#include <string>
#include "Log.h"
#include "time.h"


void FileLogImpl::AddTimeStamp(std::string& LogStr)
{
	time_t long_time;
	time( &long_time );                
	struct tm *pt = localtime( &long_time ); 
	if(pt)
	{
		std::ostringstream stream;
		stream<<"AT:"<<pt->tm_hour<<':'<<pt->tm_min<<':'<<pt->tm_sec<<','<<pt->tm_year+1900<<'/'<<pt->tm_mon+1<<'/'<<pt->tm_mday<<"-------->";
		LogStr=stream.str()+LogStr;
	}
}
bool FileLogImpl::AddLog(std::string& LogStr)
{
	AddTimeStamp(LogStr);
	std::ofstream os(m_LogFileName.c_str(),std::ios::app);
	os<<LogStr;
	os<<std::endl;
	os.flush();
	os.close();
	return true;
}
void FileLogImpl::Clear()	   //clear file content
{
	std::ofstream os(m_LogFileName.c_str(),std::ios::out);
	os.flush();
	os.close();
}

//int main()
//{
//	MjTools::CFileLog m_Log("test.log");
//	std::string a="aaa";
//	m_Log.Clear();
//	m_Log.AddLog("Abc");
//	m_Log.AddLog(a);
//	MjTools::CFileLog m_Log1=m_Log;
//	m_Log1.AddLog("From Log1");
//	return 0;
//}

