#ifndef VR_SHOP_BUILDER_H
#define VR_SHOP_BUILDER_H

#include <QTreeView>

#include <osgGA/GUIEventHandler>

#include "VRSceneHierarchy.h"

class OSGQT_Widget;
class Grid;

namespace VR	{
	class Scene;
	class SceneStructureModel;

	struct ShopBuilder {
		ShopBuilder();
		ShopBuilder(OSGQT_Widget * apOSGQTWidget, QTreeView * apQTreeView);
		
		~ShopBuilder();

		void gridOnOff(bool abIndicator);

		void newDB(const std::string & astrDBFileName);
		void readDB(const std::string & astrDBFileName);
		void saveDB(const std::string & astrDBFileName);

		bool searchScene(const std::string & astrSearchTerm, SceneStructureModel ** appSceneStructureModel);
		bool setTreeStructure();

		osg::ref_ptr<Scene> getScene() const;

		void addNewItem(const std::string & astrObjectName);

		osgGA::GUIEventHandler * m_pEventHandler;

	private:


		OSGQT_Widget * m_pOSGQTWidget;
		QTreeView * m_pQTreeView;
		SceneStructureModel * m_pSceneStructureModel;
		osg::ref_ptr<Scene> m_pScene;
	};
}
#endif //VR_SHOP_BUILDER_H