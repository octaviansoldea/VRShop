#ifndef VR_AGENT_MANAGER_CLIENT_H
#define VR_AGENT_MANAGER_CLIENT_H

#include <QObject>

#include "VRServerClientCommands.h"
#include "VRAbstractManagerClient.h"

namespace VR {
	class Visitor;

	class AgentManagerClient : public AbstractManagerClient	{
	public:
		AgentManagerClient(AbstractUser * apAbstractUser, QObject * apParent=0);
		~AgentManagerClient();

		const char* className() const;

		struct AgentClientParams : public AbstractManagerClientParams	{
			std::string strUserName;
			std::string strPassword;
			std::string strFirstName;
			std::string strLastName;
		};

		virtual void requestToServer(
			const ServerClientCommands::OPERATION_TYPE & aenumOperationType, 
			AbstractManagerClientParams * apAbstractManagerClientParams=0
		);

	private:
		Visitor * m_pVisitor;

		void userApproved(const std::string & astrUserName);

	public:
		virtual void slotReceiveDataFromServer();
	};
}
#endif //VR_AGENT_MANAGER_CLIENT_H