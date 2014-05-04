#ifndef VR_SERVER_H
#define VR_SERVER_H

#include <QTcpServer>
#include <QTimer>

#include <string>
#include <list>

class QTcpSocket;

namespace VR	{
	class AgentManager;
	class Session;
	class DatabaseManager;	//Server communicates with the DB

	class Server : public QTcpServer	{
		Q_OBJECT

	private slots:
		void slotNewConnection();
		void slotRemoveConnection();
		void slotSendData();

	public:
		Server(QObject *parent=0);
		~Server();

		std::string serverIP() const;

		void SendNewSessionID();
		void SendShopTreeScene();
		void SendLocationAndClothesOnUsersAroundUntilRadiusX();
		void SendBasketContent();
		void SendInfoAboutProduct();

//	protected:
			
		QTimer m_Timer;

		void readInputReuestsAndUpdate();
		void sendAnswer();

		// If a user was not active for a long time, we close her/him session
		void maintenance();

		AgentManager * m_pAgentManager;
		
		//Scene tree and products
		std::string m_strDBFileName;
		
		void readSceneFromSceneDB(std::string & astrDBFileName);		

//	private:
		void init();

		QTcpSocket * m_pSocket;

		std::string m_strServerIP;
		int m_nPort;

		std::list<QTcpSocket *> m_lstConnections;	//Collect active connections
		
		DatabaseManager * m_pDatabaseManager;	//DBs object; server communicates with the DB
	};
}
#endif //VR_SERVER_H