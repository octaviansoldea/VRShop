#ifndef VR_USER_ACCOUNT_H
#define VR_USER_ACCOUNT_H

#include <list>
#include <string>

namespace VR	{
	class UserAccount {
	public:
		UserAccount();
		UserAccount(const std::string & astrUserName, const std::string & astrPassword);
		
		//If cells are not filled correctly, report warning for mandatory fields
		void addUserAccount();				//userName should be different than those already in the DB
		void modifyUserAccount();			//Open user's profile filled with his data (password hidden)
		void removeUserAccount();			//Make sure to offer him a confirmation dialog
		bool checkUserAccountValidity();
		void resetUserAccount() {};			//If the user forgot password

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