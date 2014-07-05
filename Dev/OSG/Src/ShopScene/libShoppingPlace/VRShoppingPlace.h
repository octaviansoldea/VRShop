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

		osg::ref_ptr<Scene> getScene() const;

		osg::ref_ptr<osg::Node> getProducts();

		PickAndDragHandlerShopClient * getPicker() const;

	private:
		bool createClientScene(const std::string & astrSceneFileName);

		OSGQT_Widget * m_pOSGQTWidget;
		OSGQT_Widget * m_pOSGQTWidgetMap;

		osg::ref_ptr<PickAndDragHandlerShopClient> m_pPickAndDragHandlerShopClient;

		osg::ref_ptr<Scene> m_pScene;
		
		ProductManager * m_pProductMgr;

		QString m_strDBFileName;

		void insertProducts();

		AvatarManagerClient * m_pAvatarMgr;
	};
}
#endif //VR_SHOPPING_PLACE_H