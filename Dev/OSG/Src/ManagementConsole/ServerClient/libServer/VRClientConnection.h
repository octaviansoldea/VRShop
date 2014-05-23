#ifndef VR_CLIENT_CONNECTION_H
#define VR_CLIENT_CONNECTION_H

//Handles single client (socket) connection to the server

#include <QTcpSocket>


namespace VR	{
	class DatabaseNetworkManager;

	class ClientConnection : public QTcpSocket	{
		Q_OBJECT

	public:
		ClientConnection(QObject *parent=0);
		~ClientConnection();

	private slots:
		void slotReadClient();
		void slotTransferSuccess();

	signals:
		void done();

	private:
		void processRequest(QByteArray & data /*QDataStream & in*/);
		void writeToClient(QByteArray & data);

		bool m_bIsFirstPackage;
		quint64 m_unPackageSize;

		DatabaseNetworkManager * m_pDatabaseNetworkManager;
	};
}
#endif //VR_CLIENT_CONNECTION_H