#ifndef VR_SERVER_GUI_H
#define VR_SERVER_GUI_H

#include <QWidget>

class QPushButton;

namespace VR	{
	class Server;

	class Server_GUI : public QWidget {
	public:
		Server_GUI(Server * apServer, QWidget * parent =0);

		QPushButton * m_pPushButtonPrint;

	private:
		void init(const std::string & astrIPAddress, const int & anPort);

		Server * m_pServer;

		virtual void close();
	};
}
#endif //VR_SERVER_GUI_H