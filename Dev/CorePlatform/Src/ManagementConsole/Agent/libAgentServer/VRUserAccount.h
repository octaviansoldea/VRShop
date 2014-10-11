#ifndef VR_USER_ACCOUNT_H
#define VR_USER_ACCOUNT_H

#include <list>
#include <string>

namespace VR	{
	class UserAccount {
	public:
		UserAccount();
		~UserAccount();

		bool trySignIn(std::string & astrSqlRequest);
		bool trySignUp(std::string & astrSqlRequest);
		bool trySignOut(std::string & astrSqlRequest);
		bool tryModifyUserAccount(std::string & astrSqlRequest);
		
		void removeUserAccount();
		bool checkUserAccountValidity(const std::string & astrUserName) const;
		void resetUserAccount();
	private:
		int m_nID;
	};
}
#endif //VR_USER_ACCOUNT_H