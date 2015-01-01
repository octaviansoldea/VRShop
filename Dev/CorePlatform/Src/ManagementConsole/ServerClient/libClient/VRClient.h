#ifndef VR_CLIENT_H
#define VR_CLIENT_H

#include <QTcpSocket>
#include <QObject>

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

		void tryToConnect();

		int getUserID() const;

	private:

		QTcpSocket m_TcpSocket;

		quint64 m_unPackageSize;

		QByteArray m_TransmitData;

		int m_nUserID;

	signals:
		void done();

	private slots:
		void slotHostFound();
		void slotIsConnectionApproved();
		void slotReadReceivedData();
		void slotError(QAbstractSocket::SocketError socketError);
		void slotConnected();
		void slotDisconnected();

	public slots:
		void close();

	private:
		void readSocket(QByteArray & aData);
	};
}
#endif //VR_CLIENT_H