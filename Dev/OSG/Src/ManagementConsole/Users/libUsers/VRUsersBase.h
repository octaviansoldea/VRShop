#ifndef VR_USERS_BASE_H
#define VR_USERS_BASE_H

#include <string>

#include "VRUserAccount.h"

namespace VR	{
	struct UserBaseParams	{
		std::string m_strUserName;
		std::string m_strUserFamilyName;
		std::string m_strUserAddress;
		int m_nUserIDNumber;
		std::string m_strUserPassword;
	};

	class UsersBase {
	public:
		UsersBase();

	protected:
		bool authenticateUser();
	};
}
#endif //VR_USERS_BASE_H