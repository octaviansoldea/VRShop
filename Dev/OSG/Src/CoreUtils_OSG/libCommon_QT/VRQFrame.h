#ifndef VR_QFRAME_H
#define VR_QFRAME_H

#include <QFrame>

namespace VR	{
	class VRQFrame : public QFrame	{
		Q_OBJECT
	public:
		VRQFrame(QWidget * parent = 0);

	protected:
		virtual void mouseMoveEvent(QMouseEvent *event);
		
	signals:
		void hovered(bool);
	};
}
#endif //VR_QFRAME_H