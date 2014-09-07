#ifndef VR_AGENT_MANAGER_H
#define VR_AGENT_MANAGER_H

#include <list>

namespace VR {
	class AbstractUser;
	
	class AgentManager	{
	public:
		AgentManager();
		~AgentManager();

		const char* className() const;

		void addUser(AbstractUser * apAbstractUser);
		void removeUser(AbstractUser * apAbstractUser);
		void updateUser(AbstractUser * apAbstractUser);

		//user switching status between being a visitor and a customer
		void userChangedStatus(AbstractUser * apAbstractUser);

		long getNumberOfUsers() const;

	private:
		std::list<AbstractUser*> m_lstUsers;
		int m_nMaxNrOfAgents;
	};
}
#endif //VR_AGENT_MANAGER_H