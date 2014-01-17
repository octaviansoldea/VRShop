#ifndef VR_ABSTRACT_USER_H
#define VR_ABSTRACT_USER_H

namespace VR	{
	class AbstractUser {
	public:
		AbstractUser();
		virtual ~AbstractUser() = 0;

		//This function should be implemented in .cpp
		//Inputs directly taken from the GUI dialog
		void openAccount();
		virtual void trySignIn();	//If the user doesn't have an account yet, 
									//open him a create account dialog
	protected:
//		Agent m_Agent;
	};
}
#endif //VR_ABSTRACT_USER_H