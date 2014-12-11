#ifndef VR_EMBEDDED_WIDGET_GUI_H
#define VR_EMBEDDED_WIDGET_GUI_H

#include <QMainWindow>
#include <QWidget>

#include "ui_VREmbeddedWidget_GUI.h"

namespace VR	{
	class EmbeddedWidget;
	class Client;

	class EmbeddedWidget_GUI : public QMainWindow, public Ui::MainCentralWindow {
		Q_OBJECT
	public:
		EmbeddedWidget_GUI(QObject * apParent=0, Client * apClient=0);
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
	};
}
#endif //VR_EMBEDDED_WIDGET_GUI_H