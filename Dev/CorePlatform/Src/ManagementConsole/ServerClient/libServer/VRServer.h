#ifndef VR_SERVER_H
#define VR_SERVER_H

#include <QTimer>

#include <QTcpServer>

namespace VR	{
	class Server : public QTcpServer	{
		Q_OBJECT

	public:
		Server(QObject *parent=0, int anConnMax=100);

		bool init();

		void setMaxNoOfConnections(int anConnMax);
		int getNoOfConnections() const;

	private:
		virtual void incomingConnection(qintptr handle);
		int m_nNoOfConnections;
		int m_nMaxNoOfConnections;

	private slots:
		void slotDisconnected();
		void slotCleanAvatarDB();

	private:
		QTimer m_Timer;
	};
}
#endif //VR_SERVER_H