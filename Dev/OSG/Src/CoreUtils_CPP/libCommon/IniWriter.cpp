#include "IniWriter.h"
#include <iostream>
#include <Windows.h> 

#include "BasicStringDefinitions.h"

CIniWriter::CIniWriter(const char* szFileName)
{
	memset(m_szFileName, 0x00, 255);
	memcpy(m_szFileName, szFileName, strlen(szFileName));
}
void CIniWriter::WriteInteger(const char* szSection, const char* szKey, int iValue)
{
	char szValue[255];
	sprintf(szValue, "%d", iValue);
	BOOL bOk = WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName);
	if(bOk == 0) {
		std::cerr << "Problems in WritePrivateProfileString at line " << __LINE__ << " in file " << __FILE__ << std::endl;
		std::cerr << "Last error" << GetLastErrorString() << " " << std::endl;
		exit(-1);
	}
}
void CIniWriter::WriteFloat(const char* szSection, const char* szKey, float fltValue)
{
	char szValue[255];
	sprintf(szValue, "%f", fltValue);
	BOOL bOk = WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName);
	if(bOk == 0) {
		std::cerr << "Problems in WritePrivateProfileString at line " << __LINE__ << " in file " << __FILE__ << std::endl;
		std::cerr << "Last error" << GetLastErrorString() << " " << std::endl;
		exit(-1);
	}
}

void CIniWriter::WriteDouble(const char* szSection, const char* szKey, double dbValue)
{
	char szValue[255];
	sprintf(szValue, "%.15lf", dbValue);
	BOOL bOk = WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName);
	if(bOk == 0) {
		std::cerr << "Problems in WritePrivateProfileString at line " << __LINE__ << " in file " << __FILE__ << std::endl;
		std::cerr << "Last error" << GetLastErrorString() << " " << std::endl;
		exit(-1);
	}
}

void CIniWriter::WriteBoolean(const char* szSection, const char* szKey, bool bolValue)
{
	char szValue[255];
	sprintf(szValue, "%s", bolValue ? "True" : "False");
	BOOL bOk = WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName);
	if(bOk == 0) {
		std::cerr << "Problems in WritePrivateProfileString at line " << __LINE__ << " in file " << __FILE__ << std::endl;
		std::cerr << "Last error" << GetLastErrorString() << " " << std::endl;
		exit(-1);
	}
}
void CIniWriter::WriteString(const char* szSection, const char* szKey, const char* szValue)
{
	BOOL bOk = WritePrivateProfileString(szSection,  szKey, szValue, m_szFileName);
	if(bOk == 0) {
		std::cerr << "Problems in WritePrivateProfileString at line " << __LINE__ << " in file " << __FILE__ << std::endl;
		std::cerr << "Last error" << GetLastErrorString() << " " << std::endl;
		exit(-1);
	}
}
