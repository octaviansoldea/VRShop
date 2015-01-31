#ifndef VR_EMBEDDED_WIDGET_H
#define VR_EMBEDDED_WIDGET_H

#include <QWidget>
#include <QString>

namespace VR	{
	class Client;

	class EmbeddedWidget {
	public:
		EmbeddedWidget(QWidget * apWidgetCentralContent, Client * apClient);
		~EmbeddedWidget();

		void home();
		void selectShop(const QString & aqstrShopName);
		void about();
		void forDevelopers();
		void contact();

		void resize();

	private:
		QWidget * m_pWidgetCentralContent;

		QMainWindow * m_pWidget;

		Client * m_pClient;
	};
}
#endif //VR_EMBEDDED_WIDGET_H