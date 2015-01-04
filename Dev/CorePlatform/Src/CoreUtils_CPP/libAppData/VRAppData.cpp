#include <string>
#include "VRAppData.h"

using namespace std;
using namespace VR;

string AppData::m_str_FPath_VRShop = AppData::init();

string AppData::init() {
	char * pchPathVRShop = getenv("VRSHOP_CLIENT_PATH");
	string strRes = string(pchPathVRShop);
	return(strRes);
}

string AppData::get_FPath_VRShop() {
	return(m_str_FPath_VRShop);
}

std::string AppData::get_FPath_Databases() {
	return(get_FPath_VRShop() + "/Databases/");
}

std::string AppData::get_FPath_Log() {
	return(get_FPath_VRShop() + "/Log/");
}

std::string AppData::get_FPath_Resources() {
	return(get_FPath_VRShop() + "/Resources/");
}
