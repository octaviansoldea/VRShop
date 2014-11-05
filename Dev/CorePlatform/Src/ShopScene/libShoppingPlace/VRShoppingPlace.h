#ifndef VR_SHOPPING_PLACE_H
#define VR_SHOPPING_PLACE_H

#include <osg/ref_ptr>
#include <string>

#include "VRProductManager.h"

namespace VR	{
	class OSGQT_Widget;
	class Scene;
	class Avatar;
	class AbstractUser;
	class Visitor;
	class Lighting;
	class AvatarManagerClient;
	class ProductManagerClient;
	class PickAndDragHandlerShopClient;
	class BasketClient;
	class ProductShopClient;

	class ModelViewControllerClient;

	struct ShoppingPlace {
		ShoppingPlace(
			OSGQT_Widget * apOSGQTWidget,
			OSGQT_Widget * apOSGQTWidgetMap,
			std::string & astrShopScene,
			std::string & astrAvatarName);

		~ShoppingPlace();

		void avatarClicked(const std::string & astrAvatarName);
		void productClicked(const std::string & astrProductName);
		void product2BasketRequest(ProductShopClient * apProduct);
		void removeProductRequest(ProductShopClient * apProduct);
		void modifyProductQuantityRequest(ProductShopClient * apProduct, float aflNewQuantity);

		void purchaseRequest();

		osg::ref_ptr<Scene> getScene() const;
		osg::ref_ptr<osg::Node> getProducts();
		PickAndDragHandlerShopClient * getPicker() const;
		BasketClient * getBasket();

		AbstractUser * getAbstractUser();

		ModelViewControllerClient * getModelViewController() const;

	private:
		bool createClientScene(const std::string & astrSceneFileName);

		OSGQT_Widget * m_pOSGQTWidget;
		OSGQT_Widget * m_pOSGQTWidgetMap;
		std::string m_strDBFileName;
		std::string m_strAvatarName;

		osg::ref_ptr<PickAndDragHandlerShopClient> m_pPickAndDragHandlerShopClient;

		osg::ref_ptr<Scene> m_pScene;
		
		
		ProductManager m_ProductManager;

		Visitor * m_pVisitor;
		osg::ref_ptr<Avatar> m_pAvatar;

		AvatarManagerClient * m_pAvatarMgr;
		ProductManagerClient * m_pProductMgr;

		ModelViewControllerClient * m_pMVCClient;

		void insertProducts();
	};
}
#endif //VR_SHOPPING_PLACE_H