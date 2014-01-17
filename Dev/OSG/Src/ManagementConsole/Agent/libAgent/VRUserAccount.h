#ifndef VR_USER_ACCOUNT_H
#define VR_USER_ACCOUNT_H

#include <list>
#include <string>

namespace VR	{
	class UserAccount {
	public:
		UserAccount();
		UserAccount(const std::string & astrUserName, const std::string & astrPassword);
		
		void addUserAccount();
		void modifyUserAccount();
		void removeUserAccount();

		void createUserAccountDB() const;

	protected:
		std::string m_strUserName;
		std::string m_strPassword;
		std::string m_strEMail;
		std::list < std::string > m_lststrPhone;
		int m_nID;
	};
}
#endif //VR_USER_ACCOUNT_H