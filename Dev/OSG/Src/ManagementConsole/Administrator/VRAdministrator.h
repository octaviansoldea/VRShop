#ifndef VR_ADMINISTRATOR_H
#define VR_ADMINISTRATOR_H

#include "VRServer.h"
#include "VRAgentManager.h"

#include <QObject>

namespace VR	{
	class Server_GUI;

	class Administrator : public QObject	{
		Q_OBJECT
	public:
		Administrator(QObject * parent=0);
		~Administrator();

		bool runServer();
		void closeServer();

		bool activateAgentManager();

	private:
		Server m_Server;
		Server_GUI * m_pServer_GUI;

		AgentManager * m_pAgentManager;

	public slots:
		void slotNewUser();
	};
}
#endif //VR_ADMINISTRATOR_H