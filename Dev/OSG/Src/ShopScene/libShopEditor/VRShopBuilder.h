#ifndef VR_SHOP_BUILDER_H
#define VR_SHOP_BUILDER_H

#include <QTreeView>

#include <osgGA/GUIEventHandler>

class OSGQT_Widget;
class Grid;

namespace VR	{
	class AbstractObject;
	class Scene;
	class ProductManager;
	class DataStructureModel;
	class DatabaseManagerShopEditor;

	struct ShopBuilder {
		ShopBuilder();
		ShopBuilder(OSGQT_Widget * apOSGQTWidget);
		
		~ShopBuilder();

		void gridOnOff(bool abIndicator);

		void newDB(const std::string & astrDBFileName);
		void readDB(const std::string & astrDBFileName);
		void saveDB(const std::string & astrDBFileName);

		bool searchScene(const std::string & astrSearchTerm, DataStructureModel ** appDataStructureModel);

		void addNewItem(const std::string & astrObjectName);
		void addNewItem(osg::ref_ptr<AbstractObject> apAbstractObject);

		osgGA::GUIEventHandler * m_pEventHandler;

		osg::ref_ptr<Scene> getScene() const;
		osg::ref_ptr<Scene> getScene(const std::string & astrSceneName);
		const std::string getSceneName(Scene * apScene);
		const std::string getSceneName(unsigned int i);

		osg::ref_ptr<ProductManager> getProducts() const;

	private:
		OSGQT_Widget * m_pOSGQTWidget;
		osg::ref_ptr<Scene> m_pScene;
		osg::ref_ptr<ProductManager> m_pProductMgr;

		std::string m_strDBFileName;

		void addScene(Scene * apScene);
		void removeScene(Scene * apScene);
		std::vector<Scene*> m_pvecScenes;

		DatabaseManagerShopEditor * m_pdbMgr;
	};
}
#endif //VR_SHOP_BUILDER_H