#ifndef VR_CENTRAL_CONTROL_H
#define VR_CENTRAL_CONTROL_H

#include "VRServer.h"
#include "VRAgentManager.h"

#include <QObject>

namespace VR	{
	class Server_GUI;

	class CentralControl : public QObject	{
		Q_OBJECT
	public:
		CentralControl(QObject * parent=0);
		~CentralControl();

		void closeServer();

	private:
		Server m_Server;
		Server_GUI * m_pServer_GUI;

		AgentManager * m_pAgentManager;

	public slots:
		void slotNewUserRequest();
	};
}
#endif //VR_CENTRAL_CONTROL_H