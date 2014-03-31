#ifndef VR_SHOP_BUILDER_H
#define VR_SHOP_BUILDER_H

#include <QTreeView>

#include <osgGA/GUIEventHandler>

class OSGQT_Widget;
class Grid;

namespace VR	{
	class Scene;
	class DataStructureModel;

	struct ShopBuilder {
		ShopBuilder();
		ShopBuilder(OSGQT_Widget * apOSGQTWidget);
		
		~ShopBuilder();

		void gridOnOff(bool abIndicator);

		void newDB(const std::string & astrDBFileName);
		void readDB(const std::string & astrDBFileName);
		void saveDB(const std::string & astrDBFileName);

		bool searchScene(const std::string & astrSearchTerm, DataStructureModel ** appDataStructureModel);

		osg::ref_ptr<Scene> getScene() const;

		void addNewItem(const std::string & astrObjectName);

		osgGA::GUIEventHandler * m_pEventHandler;

	private:
		OSGQT_Widget * m_pOSGQTWidget;
		osg::ref_ptr<Scene> m_pScene;

		std::string m_strDBFileName;
	};
}
#endif //VR_SHOP_BUILDER_H