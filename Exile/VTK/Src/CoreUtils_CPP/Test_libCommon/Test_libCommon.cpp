#include <string>


#include "Array.h"
#include "Singleton.h"
#include "IniReader.h"
#include "IniWriter.h"
#include "Factorial.h"
#include "FileOperations.h"

using namespace std;

struct X {
	Array<string> m_arrstrNames;
};

struct Y {
	Y() {
		int indy = 1;
	}
};

int main() {

	T_VOL< float > volflData;
	int arrnSizes[3] = {5, 10, 2};
	volflData.init(arrnSizes, 0.0);
	
	{
		CIniWriter iniWriter(".\\u.txt");
		iniWriter.WriteDouble("Section", "Key", 10.000000000012);
	}

	double dbVal;
	{
		CIniReader iniReader(".\\u.txt");
		dbVal = iniReader.ReadDouble("Section", "Key", 2.0);
	}

	
	string strFileName = "sjkdfhksdf.hks";
	string strSuffix;
	try {
		strSuffix = getSuffix(strFileName);
	} catch(ExceptionSuffix & eS) {
		cerr << eS.what();
		int indy = 1;
	}

	int nRes = factorial(6);

	nRes = factorial(2);

	nRes = factorial(9);

	nRes = factorial(7);

	

	X * pX = Singleton<X>::instance();
	pX->m_arrstrNames.setSize(2);
	pX->m_arrstrNames[0] = "uu";
	pX->m_arrstrNames[1] = "vv";

	int indy = 1;


	Y * p1 = Singleton<Y>::instance();
	Y * p2 = Singleton<Y>::instance();


	return(0);
}