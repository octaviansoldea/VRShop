#ifndef VR_AGENT_MANAGER_CLIENT_H
#define VR_AGENT_MANAGER_CLIENT_H

#include <QObject>

#include "VRServerClientCommands.h"
#include "VRAbstractManagerClient.h"

namespace VR {
	class Visitor;
	class Client;

	class AgentManagerClient : public AbstractManagerClient	{
	public:
		AgentManagerClient(Client * apClient, AbstractUser * apAbstractUser, QObject * apParent=0);
		~AgentManagerClient();

		const char* className() const;

		struct AgentClientParams : public AbstractManagerClientParams	{
			std::string strUserName;
			std::string strPassword;
			std::string strFirstName;
			std::string strLastName;
		};

	protected:
		virtual void requestToServer(
			const ServerClientCommands::OPERATION_TYPE & aenumOperationType, 
			AbstractManagerClientParams * apAbstractManagerClientParams=0
		);


	private:
		Visitor * m_pVisitor;

		void userApproved(const std::string & astrUserName);

	public:
		void signInRequest(const std::string & astrUserName, const std::string & astrPassword);
		void signUpRequest();
		void signOutRequest(const std::string & astrUserName);
		void modifyAccountRequest();


		bool signInRespond(QDataStream & aDataStreamProduct);
		bool signUpRespond(QDataStream & aDataStreamProduct);
		bool signOutRespond(QDataStream & aDataStreamProduct);
		bool modifyAccountRespond(QDataStream & aDataStreamProduct);
	};
}
#endif //VR_AGENT_MANAGER_CLIENT_H