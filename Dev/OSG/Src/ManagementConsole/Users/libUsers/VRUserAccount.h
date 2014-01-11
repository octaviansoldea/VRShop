#ifndef VR_USER_ACCOUNT_H
#define VR_USER_ACCOUNT_H

#include <string>

namespace VR	{
	struct UserAccountParams	{
		std::string m_strUserName;
		std::string m_strUserPassword;
		std::string m_strUserEMailAddress;
		std::string m_strUserSecurityQuestion;
		std::string m_strUserSecurityQuestionAnswer;

		typedef enum {CREATE=0, MODIFY, USE, TERMINATE} ACCOUNT_ACTION;

		//Fill with other params "required" as to define the account
		UserAccountParams();
	};

	class UserAccount {
	public:
		UserAccount();
		UserAccount(const UserAccountParams & aUserAccountParams);

		void createNewAccount(const UserAccountParams & aUserAccountParams);
		void modifyCurrentAccount(const UserAccountParams & aUserAccountParams);

		void validateUser(const UserAccount & aUserAccount) const;

	private:
		UserAccountParams m_UserAccountParams;
	};
}
#endif //VR_USER_ACCOUNT_H