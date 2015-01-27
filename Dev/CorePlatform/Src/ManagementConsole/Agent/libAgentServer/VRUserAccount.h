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

		struct UserPersonalData	{
			std::string m_strFirstName;
			std::string m_strLastName;
			std::string m_strMiddleName;
			std::string m_strAddress;
			std::string m_strCity;
			std::string m_strPostalCode;
			std::string m_strState;
			std::string m_strCountry;
			std::string m_strUserID;
		};

		bool trySignIn(std::string & astrUser, std::string & astrPsw, std::string & astrUserID);
		bool trySignUp(UserAccountParams & aUserAccountParams);
		void trySignOut(std::string & astrUser);
		bool tryModifyUserAccount(UserAccountParams & aUserAccountParams);
		
		void removeUserAccount();
		static bool checkUserAccountValidity(const std::string & astrUserName);

		bool insertUserPersonalData(UserPersonalData & aUserPersonalData);
	private:
		int m_nID;
	};
}
#endif //VR_USER_ACCOUNT_H