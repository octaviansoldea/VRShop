#ifndef VR_EMBEDDED_WIDGET_H
#define VR_EMBEDDED_WIDGET_H

#include <QWidget>
#include <QString>

namespace VR	{
	class EmbeddedWidget {
	public:
		EmbeddedWidget(QWidget * apWidgetCentralContent);
		~EmbeddedWidget();

		void home();
		void selectShop(const QString & aqstrShopName);
		void about();
		void forDevelopers();
		void contact();

	private:
		QWidget * m_pWidgetCentralContent;

		QMainWindow * m_pWidget;
	};
}
#endif //VR_EMBEDDED_WIDGET_H