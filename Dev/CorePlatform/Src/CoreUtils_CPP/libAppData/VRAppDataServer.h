#ifndef APP_DATA_SERVER_H
#define APP_DATA_SERVER_H

#include <string>
#include <vector>

namespace VR {
	struct AppDataServer {
		static std::string init();

		static std::string getFPathVRShop();

		static std::string getFPathDatabases();
		static std::string getFPathLog();
		static std::string getFPathResources();
		static std::string getFPathServer();
		static std::string getFPathDependencies();

		static bool checkIfExists(const std::string & astrApplicationFolder);

	private:
		static std::string m_strFPathVRShop;
	};
}
#endif //APP_DATA_SERVER_H