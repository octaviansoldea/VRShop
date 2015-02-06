#ifndef VR_SHOPPING_PLACE_H
#define VR_SHOPPING_PLACE_H

#include <osg/ref_ptr>
#include <string>

#include "VRProductManager.h"
#include "VRProductShopClient.h"

#include "VRVisitor.h"

namespace VR	{
	class OSGQT_Widget;
	class Client;
	class Scene;
	class Avatar;
	class AbstractUser;
	class Visitor;
	struct VisitorParams;
	class Lighting;
	class AvatarManagerClient;
	class ProductManagerClient;
	class PickAndDragHandlerShopClient;
	class BasketClient;
	class ProductShopClient;

	class ModelViewControllerClient;

	struct ShoppingPlace {
		ShoppingPlace(
			Client * apClient,
			OSGQT_Widget * apOSGQTWidget,
			OSGQT_Widget * apOSGQTWidgetMap,
			std::string & astrShopScene,
			std::string & astrAvatarName);

		~ShoppingPlace();

		void avatarClicked(const std::string & astrAvatarName);
		void product2BasketRequest(ProductShopClient * apProduct);
		void removeProductRequest(ProductShopClient * apProduct);
		void modifyProductQuantityRequest(ProductShopClient * apProduct, float aflNewQuantity);

		void handleClientData(int anType, QDataStream & aDataStream);

		void purchaseRequest();

		osg::ref_ptr<Scene> getScene() const;
		osg::ref_ptr<osg::Node> getProducts();
		PickAndDragHandlerShopClient * getPicker() const;

		AbstractUser * getAbstractUser();
		bool isUserAuthorized() const;

		ModelViewControllerClient * getModelViewController() const;

	private:
		bool createClientScene(const std::string & astrSceneFileName);

		Client * m_pClient;

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

		ProductShopClient * m_pProduct;
	};
}
#endif //VR_SHOPPING_PLACE_H