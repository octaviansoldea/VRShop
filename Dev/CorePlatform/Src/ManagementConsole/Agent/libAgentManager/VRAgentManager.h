#ifndef VR_AGENT_MANAGER_H
#define VR_AGENT_MANAGER_H

#include <list>

#include <QObject>

namespace VR {
	class AbstractUser;
	class Client;
	
	class AgentManager : public QObject	{
		Q_OBJECT
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

		Client * m_pClient;

	public:
		void trySigningIn(const std::string & astrUserName, const std::string & astrPassword);
	};
}
#endif //VR_AGENT_MANAGER_H