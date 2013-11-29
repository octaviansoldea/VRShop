#ifndef VR_SHOP_BUILDER_H
#define VR_SHOP_BUILDER_H

#include <QTreeWidget>

#include <osg/Group>

#include "VRGrid.h"

class OSGQT_Widget;

namespace VR	{
	struct ShopBuilder {
		ShopBuilder();

		void init(OSGQT_Widget * apOSGQTWidget,
				  QTreeWidget * apTreeWidget);

		osg::ref_ptr<osg::Group> m_pScene;

		void gridOnOff(bool abIndicator);

		void readDB(const std::string & astrDBFileName);
	private:
		OSGQT_Widget * m_pOSGQTWidget;
		QTreeWidget * m_pTreeWidget;
		void updateQTreeWidget();

		osg::ref_ptr<Grid> m_pGridlines;
	};
}
#endif //VR_SHOP_BUILDER_H