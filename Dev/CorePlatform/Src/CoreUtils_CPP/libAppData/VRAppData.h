#ifndef APP_DATA_H
#define APP_DATA_H

#include <string>

namespace VR {
	struct AppData {
		static std::string init();

		static std::string get_FPath_VRShop();

		static std::string get_FPath_Databases();
		static std::string get_FPath_Log();
		static std::string get_FPath_Resources();

	private:
		static std::string m_str_FPath_VRShop;
	};
}
#endif //APP_DATA_H