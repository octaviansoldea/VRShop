#ifndef VR_SERVER_H
#define VR_SERVER_H

#include <QTcpServer>

namespace VR	{
	class Server : public QTcpServer	{
		Q_OBJECT

	public:
		Server(QObject *parent=0);
		~Server();

		bool init();

	private:
		virtual void incomingConnection(qintptr handle);

	private slots:
		void slotDisconnected();
	};
}
#endif //VR_SERVER_H