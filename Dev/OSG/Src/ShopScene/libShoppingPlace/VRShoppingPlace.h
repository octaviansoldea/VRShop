#ifndef VR_SHOPPING_PLACE_H
#define VR_SHOPPING_PLACE_H

#include <osg/Group>

#include "VRGrid.h"

class OSGQT_Widget;

namespace VR	{
	struct ShoppingPlace {
		ShoppingPlace();
		~ShoppingPlace();

		void gridOnOff(bool abIndicator);
		void init(OSGQT_Widget * apOSGQTWidget);

	private:
		OSGQT_Widget * m_pOSGQTWidget;
		osg::ref_ptr<osg::Group> m_pScene;
		osg::ref_ptr < osg::Group > m_pObjects;

		QString m_qstrFileName;

		osg::ref_ptr<Grid> m_pGridlines;
	};
}
#endif //VR_SHOPPING_PLACE_H