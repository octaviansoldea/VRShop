#ifndef VR_AGENT_MANAGER_CLIENT_H
#define VR_AGENT_MANAGER_CLIENT_H

#include <QObject>

#include "VRServerClientCommands.h"

namespace VR {
	class AbstractUser;
	class Visitor;
	class Client;

	class AgentManagerClient : public QObject	{
		Q_OBJECT
	public:
		AgentManagerClient(AbstractUser * apAbstractUser);
		~AgentManagerClient();

		const char* className() const;

		struct AgentClientParams	{
			std::string strUserName;
			std::string strPassword;
			std::string strFirstName;
			std::string strLastName;
		};

		void requestToServer(
			const enum ServerClientCommands::OPERATION_TYPE & aenumOperationType, 
			AgentClientParams * apAgentClientParams=0
		);

	private:
		Client * m_pClient;
//		AbstractUser * m_pAbstractUser;
		Visitor * m_pAbstractUser;

		void userApproved(const std::string & astrUserName);

	public slots:
		void slotReceiveDataFromServer();

	signals:
		void done();
	};
}
#endif //VR_AGENT_MANAGER_CLIENT_H