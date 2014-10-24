#ifndef VR_CLIENT_CONNECTION_H
#define VR_CLIENT_CONNECTION_H

//Handles single client (socket) connection to the server

#include <QTcpSocket>


namespace VR	{
	class ClientConnection : public QTcpSocket	{
		Q_OBJECT

	public:
		ClientConnection(QObject *parent=0);
		~ClientConnection();

	private slots:
		void slotReadClient();

	private:
		bool m_bIsFirstPackage;
		quint64 m_unPackageSize;
	};
}
#endif //VR_CLIENT_CONNECTION_H