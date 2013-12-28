#ifndef VR_SHOP_BUILDER_H
#define VR_SHOP_BUILDER_H

#include <QTreeView>

#include <osg/Group>

#include "VRGrid.h"

#include "VRFurniture.h"

#include "VRSceneHierarchy.h"

class OSGQT_Widget;

namespace VR	{
	struct ShopBuilder {
		ShopBuilder();
		~ShopBuilder();

		void init(OSGQT_Widget * apOSGQTWidget, QTreeView * apTreeView);

		osg::ref_ptr<osg::Group> m_pScene;

		void gridOnOff(bool abIndicator);

		void newDB(const std::string & astrDBFileName);
		void readDB(const std::string & astrDBFileName);
		void saveDB(const std::string & astrDBFileName);

		void addNewItem(const std::string & astrObjectName, const std::string & astrDBFileName);
		
	private:
		OSGQT_Widget * m_pOSGQTWidget;
		QTreeView * m_pTreeView;
		void updateQTreeView();

		SceneHierarchy * m_pSceneHierarchy;
		osg::ref_ptr<Grid> m_pGridlines;
	};
}
#endif //VR_SHOP_BUILDER_H