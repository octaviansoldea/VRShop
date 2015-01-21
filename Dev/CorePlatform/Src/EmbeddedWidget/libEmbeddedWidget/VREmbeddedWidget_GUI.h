#ifndef VR_EMBEDDED_WIDGET_GUI_H
#define VR_EMBEDDED_WIDGET_GUI_H

#include <QMainWindow>
#include <QWidget>
#include "VRPipeClient.h"

#include "ui_VREmbeddedWidget_GUI.h"

namespace VR	{
	class EmbeddedWidget;
	class Client;

	class EmbeddedWidget_GUI : public QMainWindow, public Ui::MainCentralWindow {
		Q_OBJECT
	public:
		EmbeddedWidget_GUI(Client * apClient, std::string & astrPipeName, QObject * apParent=0);
		~EmbeddedWidget_GUI();

	private slots:
		void slotLinkHovered(bool abHovered);

		void slotHomeButtonClicked();
		void slotSelectShopClicked();
		void slotAboutClicked();
		void slotForDevsClicked();
		void slotContactClicked();

		void slotCurrentIndexChanged(const QString & aqstrShopName);

	private:
		EmbeddedWidget * m_pEmbeddedWidget;
		Client * m_pClient;
		PipeClient * m_pPipe;

	public:
		void checkIfParentExists();
		void slotAboutToQuit();
	};
}
#endif //VR_EMBEDDED_WIDGET_GUI_H