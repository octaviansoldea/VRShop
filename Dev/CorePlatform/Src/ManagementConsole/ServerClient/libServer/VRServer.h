#ifndef VR_SERVER_H
#define VR_SERVER_H

#include <QTcpServer>

namespace VR	{
	class AgentManager;

	class Server : public QTcpServer	{
		Q_OBJECT

	public:
		Server(QObject *parent=0, int anConnMax=100);
		~Server();

		bool init();

		void setMaxNoOfConnections(int anConnMax);
		int getNoOfConnections() const;

	private:
		virtual void incomingConnection(qintptr handle);
		int m_nNoOfConnections;
		int m_nMaxNoOfConnections;

	private slots:
		void slotDisconnected();

	private:
		AgentManager * m_pAgentManager;
	};
}
#endif //VR_SERVER_H