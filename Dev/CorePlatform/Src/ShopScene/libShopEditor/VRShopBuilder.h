#ifndef VR_SHOP_BUILDER_H
#define VR_SHOP_BUILDER_H

#include <osg/ref_ptr>

namespace VR	{
	class OSGQT_Widget;
	class AbstractObject;
	class Scene;
	class Grid;
	class ProductManager;
	class DataStructureModel;
	class PickAndDragHandlerShopEditor;
	class KeyboardMouseManipulatorShopEditor;

	struct ShopBuilder {
		ShopBuilder();
		ShopBuilder(OSGQT_Widget * apOSGQTWidget);
		
		~ShopBuilder();

		void gridOnOff(bool abIndicator);

		void readDB(const std::string & astrDBFileName);
		void closeDB(const std::string & astrDBFileName);
		void saveDB(const std::string & astrDBFileName);
		void newDB();
		void saveDB();
		void saveAsDB();

		bool searchScene(const std::string & astrSearchTerm, DataStructureModel ** appDataStructureModel);

		void addNewItem(const std::string & astrObjectName);
		void addNewItem(osg::ref_ptr<AbstractObject> apAbstractObject);

		Scene * getScene() const;
		Scene * getScene(const std::string & astrSceneName);
		const std::string getSceneName(Scene * apScene);
		const std::string getSceneName(unsigned int i);

		ProductManager * getProducts();

		PickAndDragHandlerShopEditor * getPicker() const;

		std::string getCurrentFileName() const;

	private:
		OSGQT_Widget * m_pOSGQTWidget;
		osg::ref_ptr<Scene> m_pScene;
		osg::ref_ptr<PickAndDragHandlerShopEditor> m_pPickAndDragHandlerShopEditor;
		osg::ref_ptr<KeyboardMouseManipulatorShopEditor> m_pKeyboardMouseManipulatorShopEditor;

		
		ProductManager * m_pProductMgr;

		std::string m_strDBFileName;

		void addScene(Scene * apScene);
		void removeScene(Scene * apScene);
		std::vector<Scene*> m_pvecScenes;
	};
}
#endif //VR_SHOP_BUILDER_H