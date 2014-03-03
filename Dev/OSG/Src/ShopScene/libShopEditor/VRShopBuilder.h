#ifndef VR_SHOP_BUILDER_H
#define VR_SHOP_BUILDER_H

#include <QTreeView>

#include <osgGA/GUIEventHandler>

#include "VRSceneHierarchy.h"

class OSGQT_Widget;
class Grid;

namespace VR	{
	class Scene;

	struct ShopBuilder {
		ShopBuilder();
		ShopBuilder(OSGQT_Widget * apOSGQTWidget);
		
		~ShopBuilder();

		void gridOnOff(bool abIndicator);

		void newDB(const std::string & astrDBFileName);
		void readDB(const std::string & astrDBFileName);
		void saveDB(const std::string & astrDBFileName);

		osg::ref_ptr<Scene> getScene() const;

		void addNewItem(const std::string & astrObjectName);

		osgGA::GUIEventHandler * m_pEvent;

	private:


		OSGQT_Widget * m_pOSGQTWidget;
		osg::ref_ptr<Scene> m_pScene;

		void updateQTreeView();
		QTreeView * m_pTreeView;

		osg::ref_ptr<Grid> m_pGridlines;
	};
}
#endif //VR_SHOP_BUILDER_H