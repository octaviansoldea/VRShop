#include <iostream>
#include <string>
#include <fstream>

using namespace std;

int mainTest() {

	string s1 = ".\\Test.txt";
	string s2 = ".\\test.txt";

	if(s1 == s2) {
		int indy = 1;
	}

	ofstream myfile1 (s1.c_str());
	if (myfile1.is_open())
	{
		myfile1 << "This is a line.\n";
		myfile1 << "This is another line.\n";
		myfile1.close();
	}

	ofstream myfile2 (s2.c_str());
	if (myfile2.is_open())
	{
		myfile2 << "This is aNOTHER line.\n";
		myfile2 << "This is another line.\n";
		myfile2.close();
	}

	cout << "Hello world" << endl;

	return(0);
}



//==============================================================================================

/*
An Internet File Donloader
Can download (large) files from internet and resume the download after an
interuption

Based on an example from the book "The Art of C++" by Herbert Schildt

Jos de Jong, sept 2007
c++ program

*/


#include <cstdlib>
#include "VRDownloadFile.h"

using namespace std;

// This function displays the download progress as a percentage
void showprogress(unsigned long total, unsigned long part)
{
    int val = (int) ((double)part / total * 100);
    printf("progress: %i%%\n", val);
}


int main(int argc, char *argv[])
{
	VR::Download::DownloadParams dP;
	dP.m_strURL = "http://127.0.0.1/Website/VRShop.exe";
	dP.m_strDestinationFolder = "";
	dP.m_bReload = true;

    bool reload = false;

    if(argc==2 && !strcmp(argv[1], "reload"))
        reload = true;

    printf("Beginning download\n");

    try
    {
//        if(Download::download(url, reload, showprogress))
		if(VR::Download::download(dP))
            printf("Download Complete\n");
    }
    catch(VR::DLExc exc)
    {
		printf("%s\n", exc.getError());
        printf("Download interrupted\n");
    }

	int nRes = EXIT_SUCCESS;

    return nRes;
}

