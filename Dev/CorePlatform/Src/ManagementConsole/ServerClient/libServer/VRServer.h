#ifndef VR_SERVER_H
#define VR_SERVER_H

#include <QTcpServer>

namespace VR	{
	class ClientConnection;

	class Server : public QTcpServer	{
		Q_OBJECT

	public:
		Server(QObject *parent=0, const int anConnMax=5);
		~Server();

		bool init(const std::string & astrIP, const unsigned int anPort);

	private:
		virtual void incomingConnection(qintptr handle);

		void addConnection(ClientConnection * apDevice, quint64 anClientID);
		void removeConnection(ClientConnection * apDevice, quint64 anClientID);

		const int m_nMaxNoOfConnections;

	private slots:
		void slotNewConnection();
		void slotDisconnected();

	public:
		QHash<quint64, ClientConnection*> m_Clients;	//QHash is like QMap but faster

		int clientCount() const;
		QList<quint64> clients() const;			//Clients' IDs
		ClientConnection * getClient(quint64 clientID) const;
	};
}
#endif //VR_SERVER_H