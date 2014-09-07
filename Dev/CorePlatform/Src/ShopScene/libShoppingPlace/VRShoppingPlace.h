#ifndef VR_SHOPPING_PLACE_H
#define VR_SHOPPING_PLACE_H

#include <osg/ref_ptr>

namespace VR	{
	class OSGQT_Widget;
	class Scene;
	class Avatar;
	class AbstractUser;
	class Lighting;
	class ProductManager;
	class AvatarManagerClient;
	class PickAndDragHandlerShopClient;
	class Basket;

	struct ShoppingPlace {
		ShoppingPlace(
			OSGQT_Widget * apOSGQTWidget,
			OSGQT_Widget * apOSGQTWidgetMap,
			std::string & astrShopScene,
			std::string & astrAvatarName);

		~ShoppingPlace();

		osg::ref_ptr<Scene> getScene() const;
		osg::ref_ptr<osg::Node> getProducts();
		PickAndDragHandlerShopClient * getPicker() const;
		Basket * getBasket();

	private:
		bool createClientScene(const std::string & astrSceneFileName);

		OSGQT_Widget * m_pOSGQTWidget;
		OSGQT_Widget * m_pOSGQTWidgetMap;
		std::string m_strDBFileName;
		std::string m_strAvatarName;

		osg::ref_ptr<PickAndDragHandlerShopClient> m_pPickAndDragHandlerShopClient;

		osg::ref_ptr<Scene> m_pScene;
		
		
		ProductManager * m_pProductMgr;

		AbstractUser * m_pAbstractUser;
		osg::ref_ptr<Avatar> m_pAvatar;
		Basket * m_pBasket;

		AvatarManagerClient * m_pAvatarMgr;

		void insertProducts();
	};
}
#endif //VR_SHOPPING_PLACE_H