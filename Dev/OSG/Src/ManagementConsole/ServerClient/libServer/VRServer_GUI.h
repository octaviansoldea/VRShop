#ifndef VR_SERVER_GUI_H
#define VR_SERVER_GUI_H

#include <QWidget>

namespace VR	{
	class Server;

	class Server_GUI : public QWidget {
		Q_OBJECT

	public:
		Server_GUI(QWidget * parent =0);
		~Server_GUI();

	private:
		void init(const std::string & astrIPAddress, const int & anPort);

		Server * m_pServer;
	};
}
#endif //VR_SERVER_GUI_H