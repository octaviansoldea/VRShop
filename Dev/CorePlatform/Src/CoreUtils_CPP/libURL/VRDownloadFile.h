#ifndef VR_DOWNLOAD_H
#define VR_DOWNLOAD_H

//==============================================================================================

/*
An Internet File Donloader
Can download (large) files from internet and resume the download after an
interuption

Based on an example from the book "The Art of C++" by Herbert Schildt

Jos de Jong, sept 2007
c++ program

Modified by Matej Steinbacher and Octavian Soldea, 2015
*/


#include <string>
#include <windows.h>
#include <wininet.h>
#include <fstream>

namespace VR	{
	const int BUF_SIZE = 10240;             // 10 KB

	// Exception class for donwload errors;
	class DLExc	{
	private:
		std::string m_strError;
	public:
		DLExc(const std::string & astrException);

		std::string getError() const;
	};


	// A class for downloading files from the internet
	class Download	{
	public:
		struct DownloadParams	{
			std::string m_strURL;
			std::string m_strDestinationFolder;
			bool m_bReload;
			DownloadParams();
		};

		static bool download(DownloadParams & aDownloadParams);

	private:
		static bool isHttpVersionOK(HINTERNET ahIUrl);
		static unsigned long openFile(DownloadParams & aDownloadParams, std::ofstream &aOfstream);
	};
}
#endif