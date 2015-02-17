#include "BasicStringDefinitions.h"

#include "VRDownloadFile.h"

using namespace std;
using namespace VR;

DLExc::DLExc(const std::string & astrException) : m_strError(astrException)	{
}

//------------------------------------------------------------------------------------------------

string DLExc::getError() const {
	return m_strError;
}

//================================================================================================

Download::DownloadParams::DownloadParams()	{
	m_bReload=false;
}

//================================================================================================

bool Download::download(DownloadParams & aDownloadParams)	{
	HINTERNET hIurl, hInet;
	ofstream out;

	try	{
		string & strURL = aDownloadParams.m_strURL;
		char chLCase[4];
		int nI;
		for (nI=0;nI<4;nI++)	{
			chLCase[nI]=tolower(strURL[nI]);
		}

		bool bRes = (strcmp("http", chLCase) == 0);
		if(bRes==false)
			throw DLExc("Must be HTTP url");

		// See if internet connection is available
		if(InternetAttemptConnect(0) != ERROR_SUCCESS)
			throw DLExc("Can't connect");

		// Open internet connection
#if UNICODE
		hInet = InternetOpen(L"downloader", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
#else
		hInet = InternetOpen("downloader", INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, 0);
#endif
		if(hInet == NULL)
			throw DLExc("Can't open connection");

		/*
		Open the file spcified by url.
		The open stream will be returned in fout. If reload is true, then any
		preexisting file will be truncated. The length of any preexisting file
		(after possible truncation) is returned.
		*/
		unsigned long ulFileLenght = openFile(aDownloadParams, out);

		// Construct header requesting range of data
		string strHeader = string("Range:bytes=") + to_string((long double)ulFileLenght) + string("-");


		// Open the URL and request range
		//hIurl = InternetOpenUrl(hInet, url, header, -1, INTERNET_FLAG_NO_CACHE_WRITE, 0);
#if UNICODE
		hIurl = InternetOpenUrl(hInet, string2WString(strURL).c_str(), string2WString(strHeader).c_str(), strHeader.length(), INTERNET_FLAG_NO_CACHE_WRITE, 0);
#else
		hIurl = InternetOpenUrl(hInet, strURL.c_str(), strHeader.c_str(), strHeader.length(), INTERNET_FLAG_NO_CACHE_WRITE, 0);
#endif
		if(hIurl == NULL)
			throw DLExc("Can't open url");

		// Confirm that HTTP/1.1 or greater is supported
		if(!isHttpVersionOK(hIurl))
			throw DLExc("HTTP/1.1 not supported");

		// Get content length
		unsigned long ulContentLenght;
		unsigned long len = sizeof ulContentLenght;
		if(!HttpQueryInfo(hIurl, HTTP_QUERY_CONTENT_LENGTH | HTTP_QUERY_FLAG_NUMBER, &ulContentLenght, &len, NULL))
			throw DLExc("File or content length not found");

		// If existing file (if any) is not complete, then finish downloading
		if(ulFileLenght != ulContentLenght && ulContentLenght)	{
			unsigned long unTotalWritten = 0;
			unsigned long unBytesRead;

			do	{
				unsigned char uchBuffer[BUF_SIZE];
				// Read a buffer of info
				if(!InternetReadFile(hIurl, &uchBuffer, BUF_SIZE, &unBytesRead))
					throw DLExc("Error occurred during download");

				// Write buffer to disk
				out.write((const char *)uchBuffer, unBytesRead);
				if(!out.good())
					throw DLExc("Error writing file");

				// update running total
				unTotalWritten += unBytesRead;
			} while (unBytesRead > 0);
		}

		out.close();
		InternetCloseHandle(hIurl);
		InternetCloseHandle(hInet);
	} catch (DLExc)	{
		out.close();
		InternetCloseHandle(hIurl);
		InternetCloseHandle(hInet);

		// rethrow the exception for use by the caller
		throw;
	}

	return true;
}

//-------------------------------------------------------------------------------------------------

bool Download::isHttpVersionOK(HINTERNET ahIUrl)	{
// Return true if HTTP version of 1.1 or greater
	char charrText[80];
	unsigned long ulLenght = 79;

	if(!HttpQueryInfo(ahIUrl, HTTP_QUERY_VERSION, &charrText, &ulLenght, NULL))
		return false;

	string & strVer = string(charrText);

	const int nFindSlash = strVer.find_first_of("/", 0);
	char chMajor = strVer[nFindSlash+1];
	if (chMajor == 0)	{
		return false;
	}

	const int nFindDot = strVer.find_first_of(".", nFindSlash+1);
	char chMinor = strVer[nFindDot+1];
	if (chMinor > 0)	{
		return true;
	}

	return false;
}

//-------------------------------------------------------------------------------------------------

unsigned long Download::openFile(DownloadParams & aDownloadParams, std::ofstream &aOfstream)	{
	string & strURL = aDownloadParams.m_strURL;
	const int nPos = strURL.find_last_of("/");
	string & strFileName = aDownloadParams.m_strDestinationFolder + strURL.substr(nPos+1,strURL.length());

	if (strFileName.empty())
		throw DLExc("File name error");

	bool bReload = aDownloadParams.m_bReload;
	if(!bReload)
		aOfstream.open(strFileName, ios::binary | ios::out | ios::app | ios::ate);
	else
		aOfstream.open(strFileName, ios::binary | ios::out | ios::trunc);

	if(!aOfstream)	{
		throw DLExc("Can't open output file");
	}

	// get current file length
	unsigned long ulFileLength = aOfstream.tellp();

	return ulFileLength;
}

//-------------------------------------------------------------------------------------------------