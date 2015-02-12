#ifndef VR_SHOP_BUILDER_H
#define VR_SHOP_BUILDER_H

#include <osg/ref_ptr>

class QComboBox;
class QLineEdit;
class QDoubleSpinBox;
class QCheckBox;


#include "VRSceneObjectsSearchShopEditor.h"

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

		bool searchScene(const std::string & astrSearchTerm);

		void addNewItem();

		osg::ref_ptr<Scene> getScene() const;
		osg::ref_ptr<Scene> getScene(const std::string & astrSceneName);
		const std::string getSceneName(Scene * apScene);
		const std::string getSceneName(unsigned int i);

		ProductManager * getProducts();

		PickAndDragHandlerShopEditor * getPicker() const;

		std::string getCurrentFileName() const;

		void addNewProduct();
		void removeProductClicked(const std::string & astrProductCode);

		struct ProductClickedItems	{
			std::string m_strProductName;
			QComboBox * m_pComboBox_ProductSettings_ProductName;
			QLineEdit * m_pLineEdit_ProductSettings_Price;
			QLineEdit * m_pLineEdit_ProductSettings_Quantity;
			QLineEdit * m_pLineEdit_ProductSettings_NewPrice;
			QLineEdit * m_pLineEdit_ProductSettings_NewQuantity;
		};

		void productClicked(ProductClickedItems & aProductClickedItems);

		void productMoreSettingsClicked(const std::string & astrProductCode);

		void modifyProductClicked(ProductClickedItems & aProductClickedItems);
		void updateProductSettings(ProductClickedItems & aProductClickedItems);

	private:
		OSGQT_Widget * m_pOSGQTWidget;
		osg::ref_ptr<Scene> m_pScene;
		osg::ref_ptr<PickAndDragHandlerShopEditor> m_pPickAndDragHandlerShopEditor;
		osg::ref_ptr<KeyboardMouseManipulatorShopEditor> m_pKeyboardMouseManipulatorShopEditor;

		
		ProductManager * m_pProductMgr;

		std::string m_strDBFileName;

		void addScene(Scene * apScene);
		void removeScene(Scene * apScene);
		std::vector<osg::ref_ptr<Scene>> m_pvecScenes;

		void init();

		SceneObjectsSearchShopEditor * m_pSceneObjectsSearch;

	public:
		void groupItems();
		void splitItem();
		void duplicateSelection();
		void removeSelection();
		void editItem();

		void updateSearchList(std::string & astrSelectedItemName);
		void changeTransparency(float aflTransparencyFactor);
		void changeIsTargetLocked(bool abIsLocked);

		void itemPicked(QDoubleSpinBox * apTransparency, QCheckBox * apIsLocked);

		DataStructureModel * getSceneObjectsSearchModel();
	};
}
#endif //VR_SHOP_BUILDER_H