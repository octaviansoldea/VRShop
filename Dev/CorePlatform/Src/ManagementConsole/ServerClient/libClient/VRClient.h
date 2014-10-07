#ifndef VR_CLIENT_H
#define VR_CLIENT_H

#include <QTcpSocket>
#include <QObject>
#include <QString>

#include <QDataStream>

namespace VR	{
	class Client : public QObject	{
		Q_OBJECT

	public:
		Client(QObject *apParent=0);		
		~Client();

		void sendRequest(QByteArray & aarrRequest);
		QTcpSocket & getTcpSocket();
		QByteArray getTransmittedData();

	private:
		QTcpSocket m_TcpSocket;

		bool m_bIsFirstPackage;
		quint64 m_unPackageSize;

		QByteArray m_ReceivedData;
		QByteArray m_TransmitData;

	signals:
		void done();

	private slots:
		void slotReadReceivedData();
		void slotError(QAbstractSocket::SocketError socketError);
		void slotConnected();
		void slotDisconnected();

	public slots:
		void slotNewUserRequest();
		void slotTryToConnect();
		void close();
	};
}
#endif //VR_CLIENT_H