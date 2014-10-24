#ifndef VR_MODEL_VIEW_CONTROLLER_CLIENT_H
#define VR_MODEL_VIEW_CONTROLLER_CLIENT_H

#include <QObject>

#include "VRProductShopClient.h"

namespace VR	{
	class ModelViewControllerClient : public QObject	{
		Q_OBJECT
	public:
		ModelViewControllerClient();
		~ModelViewControllerClient();

	signals:
		void signalProductInitialized(const ProductShopClient * apProductShopClient);
		void signalNewProductQuantity(float flNewProductQuantity);
	};
}
#endif //VR_PRODUCT_CLIENT_CONTROLLER_H