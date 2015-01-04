#include <string>
#include "VRAppData.h"

using namespace std;
using namespace VR;

int main() {

	//AppData appData;

	string str_FPath_VRShop    = AppData::get_FPath_VRShop();
	string str_FPath_Databases = AppData::get_FPath_Databases();
	string str_FPath_Log       = AppData::get_FPath_Log();
	string str_FPath_Resources = AppData::get_FPath_Resources();

	return(0);
}