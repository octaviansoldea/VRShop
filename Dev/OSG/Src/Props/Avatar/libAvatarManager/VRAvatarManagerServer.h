#ifndef VR_AVATAR_MANAGER_SERVER_H
#define VR_AVATAR_MANAGER_SERVER_H

/*
	This class is a link from the server to the database. 
	It's created as to prevent clients to directly browse the Database
*/

#include <string>

namespace VR {
	class Avatar;
	class DatabaseManager;

	class AvatarManagerServer	{
	public:
		AvatarManagerServer();
		~AvatarManagerServer();

		const char* className() const;

		std::string getAvatarsDataFromDB();
		void updateAvatarData(const std::string & astrAvatarName, std::string & astrAvatarMatrix);

	private:
		DatabaseManager * m_pDb;
	};
}
#endif //VR_AVATAR_MANAGER_SERVER_H