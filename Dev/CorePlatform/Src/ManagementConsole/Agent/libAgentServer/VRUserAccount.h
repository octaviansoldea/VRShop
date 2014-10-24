#ifndef VR_USER_ACCOUNT_H
#define VR_USER_ACCOUNT_H

#include <list>
#include <string>

namespace VR	{
	class UserAccount {
	public:
		UserAccount();
		~UserAccount();

		struct UserAccountParams	{
			std::string m_strUserIDName;
			std::string m_strEMail;
			std::string m_strPsw;
			std::string m_strFirstName;
			std::string m_strLastName;
		};

		bool trySignIn(std::string & astrUser, std::string & astrPsw);
		bool trySignUp(UserAccountParams & aUserAccountParams);
		bool trySignOut(std::string & astrUser);
		bool tryModifyUserAccount(UserAccountParams & aUserAccountParams);
		
		void removeUserAccount();
		static bool checkUserAccountValidity(const std::string & astrUserName);
		void resetUserAccount();
	private:
		int m_nID;
	};
}
#endif //VR_USER_ACCOUNT_H