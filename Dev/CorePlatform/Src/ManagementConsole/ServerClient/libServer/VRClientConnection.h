#ifndef VR_CLIENT_CONNECTION_H
#define VR_CLIENT_CONNECTION_H

//Handles single client (socket) connection to the server

#include <QTcpSocket>


namespace VR	{
	class ClientConnection : public QTcpSocket	{
		Q_OBJECT

	public:
		ClientConnection(QObject *parent=0);
		void registerClientVisitor(const std::string & astrIP, const int & anUserID);

	private slots:
		void slotReadClient();

	private:
		quint64 m_unPackageSize;
		void clientDisconnected();

		int m_nUserID;
	};
}
#endif //VR_CLIENT_CONNECTION_H