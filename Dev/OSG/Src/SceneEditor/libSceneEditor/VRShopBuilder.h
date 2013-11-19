#ifndef VR_SHOP_BUILDER_H
#define VR_SHOP_BUILDER_H

#include <osg/Group>

#include "VRGrid.h"

class OSGQT_Widget;

namespace VR	{
	struct ShopBuilder {
		ShopBuilder();

		void init(OSGQT_Widget * apOSGQTWidget);

		osg::ref_ptr<osg::Group> m_pScene;

		void gridOnOff(bool abIndicator);
	private:
		OSGQT_Widget * m_pOSGQTWidget;
		osg::ref_ptr<Grid> m_pGridlines;
	};
}
#endif //VR_SHOP_BUILDER_H