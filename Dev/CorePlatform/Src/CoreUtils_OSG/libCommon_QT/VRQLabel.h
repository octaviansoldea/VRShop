#ifndef VR_QLABEL_H
#define VR_QLABEL_H

#include <QLabel>

namespace VR	{
	class VRQLabel : public QLabel	{
		Q_OBJECT
	public:
		VRQLabel(QWidget * parent = 0, Qt::WindowFlags f = 0);
		VRQLabel(const QString & text, QWidget * parent = 0, Qt::WindowFlags f = 0);

		~VRQLabel();

	signals:
		void clicked();
		void hovered(bool);
	 
	protected:
		virtual void mousePressEvent(QMouseEvent * event);
		virtual void mouseMoveEvent(QMouseEvent *event);
		virtual void leaveEvent(QEvent * event);
	};
}
#endif //VR_QLABEL_H