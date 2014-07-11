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

	private:
		QTcpSocket m_TcpSocket;

		bool m_bIsFirstPackage;
		quint64 m_unPackageSize;

		QByteArray m_ReceivedData;
		void processReceivedData(QByteArray & data);

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

	public:
		QString m_qstrAvatarsData;
	};
}
#endif //VR_CLIENT_H