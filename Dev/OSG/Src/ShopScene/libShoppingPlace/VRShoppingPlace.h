#ifndef VR_SHOPPING_PLACE_H
#define VR_SHOPPING_PLACE_H

#include <QString>
#include <osg/ref_ptr>

namespace VR	{
	class OSGQT_Widget;
	class Scene;
	class ProductManager;
	class AvatarManagerClient;
	class Grid;
	class PickAndDragHandlerShopClient;

	struct ShoppingPlace {
		ShoppingPlace(
			OSGQT_Widget * apOSGQTWidget,
			OSGQT_Widget * apOSGQTWidgetMap);

		~ShoppingPlace();

		void gridOnOff(bool abIndicator);

		osg::ref_ptr<Scene> getScene() const;
		osg::ref_ptr<ProductManager> getProducts() const;
		PickAndDragHandlerShopClient * getPicker() const;

	private:
		bool createClientScene();

		OSGQT_Widget * m_pOSGQTWidget;
		OSGQT_Widget * m_pOSGQTWidgetMap;

		osg::ref_ptr<PickAndDragHandlerShopClient> m_pPickAndDragHandlerShopClient;

		osg::ref_ptr<Scene> m_pScene;
		osg::ref_ptr<ProductManager> m_pProductMgr;

		QString m_strDBFileName;

		osg::ref_ptr<Grid> m_pGridlines;

		void insertProducts();

		AvatarManagerClient * m_pAvatarMgr;
	};
}
#endif //VR_SHOPPING_PLACE_H