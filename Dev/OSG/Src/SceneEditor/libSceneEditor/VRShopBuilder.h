#ifndef VR_SHOP_BUILDER_H
#define VR_SHOP_BUILDER_H

#include <osg/Group>

namespace VR	{
	struct ShopBuilder {
		ShopBuilder();

		osg::ref_ptr<osg::Group> m_pScene;
	};
}
#endif //VR_SHOP_BUILDER_H