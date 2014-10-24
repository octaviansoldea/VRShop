#ifndef VR_AVATAR_MANAGER_SERVER_H
#define VR_AVATAR_MANAGER_SERVER_H

/*
	This class is a link from the server to the database. 
	It's created as to prevent clients to directly browse the Database
*/

#include <string>
#include <list>

namespace VR {
	class Avatar;
	class DatabaseInterface;
	struct DatabaseInterfaceParams;

	class AvatarManagerServer	{
	public:
		AvatarManagerServer();
		~AvatarManagerServer();

		const char* className() const;

		

		void registerAvatar(std::string & astrAvatarName, std::string & astrAvatarMatrix);
		std::list<std::string> getAvatarsDataFromDB();
		void updateAvatarData(std::string & astrAvatarName, std::string & astrAvatarMatrix);

	public:
		static DatabaseInterfaceParams getDBParams();
		static std::vector<std::pair<std::string,std::string>> getDBElements();
		static std::string getTableName();
		static std::string getDatabaseName();

		static void createAvatarDB();

		static DatabaseInterface * getDatabaseInterface();

	private:
		static DatabaseInterface m_DIAvatar;
	};
}
#endif //VR_AVATAR_MANAGER_SERVER_H