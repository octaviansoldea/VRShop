#ifndef VR_AGENT_MANAGER_H
#define VR_AGENT_MANAGER_H

#include <vector>

namespace VR {
	class AbstractUser;
	
	class AgentManager	{
	public:
		AgentManager();
		~AgentManager();

		virtual const char* className() const;

		void addUser(AbstractUser * apAbstractUser);
		void removeUser(AbstractUser * apAbstractUser);

		//user switching status between being a visitor and a customer
		void userChangedStatus(AbstractUser * apAbstractUser);

		long getNumberOfUsers() const;

	private:
		std::vector<AbstractUser*> m_vecUsers;
	};
}
#endif //VR_AGENT_MANAGER_H