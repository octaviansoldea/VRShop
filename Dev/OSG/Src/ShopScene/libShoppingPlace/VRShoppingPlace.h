#ifndef VR_SHOPPING_PLACE_H
#define VR_SHOPPING_PLACE_H

#include <QString>
#include <osg/ref_ptr>


namespace VR	{
	class OSGQT_Widget;
	class Scene;
	class ProductManager;
	class Grid;
	class PickAndDragHandlerShopClient;

	struct ShoppingPlace {
		ShoppingPlace(
			OSGQT_Widget * apOSGQTWidget,
			PickAndDragHandlerShopClient * apPickAndDragHandlerShopClient);

		~ShoppingPlace();

		void gridOnOff(bool abIndicator);

		osg::ref_ptr<Scene> getScene() const;
		osg::ref_ptr<ProductManager> getProducts() const;

	private:
		OSGQT_Widget * m_pOSGQTWidget;

		osg::ref_ptr<Scene> m_pScene;
		osg::ref_ptr<ProductManager> m_pProductMgr;

		QString m_strDBFileName;

		osg::ref_ptr<Grid> m_pGridlines;
	};
}
#endif //VR_SHOPPING_PLACE_H