#ifndef VR_AGENT_MANAGER_CLIENT_H
#define VR_AGENT_MANAGER_CLIENT_H

#include <QObject>

#include "VRServerClientCommands.h"
#include "VRAbstractManagerClient.h"

#include "VRVisitor.h"

namespace VR {
	class Visitor;
	class Client;

	class AgentManagerClient : public AbstractManagerClient	{
	public:
		AgentManagerClient(Client * apClient, QObject * apParent=0);
		AgentManagerClient(Client * apClient, AbstractUser * apAbstractUser, QObject * apParent=0);
		~AgentManagerClient();

		const char* className() const;

		struct AgentClientParams : public AbstractManagerClientParams	{
			std::string m_strUserName;
			std::string m_strPassword;
			std::string m_strFirstName;
			std::string m_strLastName;
			std::string m_strUserID;

			std::string m_strMiddleName;
			std::string m_strAddress;
			std::string m_strCity;
			std::string m_strPostalCode;
			std::string m_strState;
			std::string m_strCountry;
		};

	protected:
		virtual void requestToServer(
			const ServerClientCommands::OperationType & aenumOperationType, 
			AbstractManagerClientParams * apAbstractManagerClientParams=0
		);


	private:
		Visitor * m_pVisitor;

	public:
		void signInRequest(const std::string & astrUserName, const std::string & astrPassword);
		void signUpRequest();
		void signOutRequest(const std::string & astrUserName);
		void modifyAccountRequest();
		void fillUserDetailsRequest(AgentManagerClient::AgentClientParams & aAgentClientParams, const std::string &astrUserID);


		bool signInRespond(QDataStream & aDataStreamProduct);
		bool signUpRespond(QDataStream & aDataStreamProduct);
		bool signOutRespond(QDataStream & aDataStreamProduct);
		bool modifyAccountRespond(QDataStream & aDataStreamProduct);
	};
}
#endif //VR_AGENT_MANAGER_CLIENT_H