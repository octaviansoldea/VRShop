#ifndef VR_CLIENT_H
#define VR_CLIENT_H

//#include "VRSession.h"

#include <QTcpSocket>

namespace VR	{
	class Client : public QTcpSocket	{
		Q_OBJECT

	public:
		Client(const std::string & astrIPAddress, const int anPort, QTcpSocket *apParent=0);
		~Client();

	private:
		const std::string m_strIPAddress;
		const int m_nPort;

		bool m_bIsFirstPackage;
		unsigned int m_unPackageSize;

//		Session m_Session;

	signals:
		void done();

	private slots:
		void slotReadReceivedData();
		void slotError(QAbstractSocket::SocketError socketError);
		void slotConnected();
		void slotTransferSuccess();
	};
}
#endif //VR_CLIENT_H