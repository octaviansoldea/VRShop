#ifndef VR_SHOP_BUILDER_H
#define VR_SHOP_BUILDER_H

#include <QMainWindow>

#include <osg/Group>

#include "ui_VRShopBuilder.h"

namespace VR	{
	class ShopBuilder : public QMainWindow, public Ui::MainWindow	{
		Q_OBJECT
	public:
		ShopBuilder();
		osg::ref_ptr<osg::Group> pScene;


	private:
		void signalSlotComm();
	};
}
#endif //VR_SHOP_BUILDER_H