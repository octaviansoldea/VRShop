#include <string>
#include "VRAppData.h"

using namespace std;
using namespace VR;

int main() {

//	AppData appData;

	string str_FPath_Databases = AppData::getFPathDatabases();
	string str_FPath_Log       = AppData::getFPathLog();
	string str_FPath_Resources = AppData::getFPathResources();

	return(0);
}