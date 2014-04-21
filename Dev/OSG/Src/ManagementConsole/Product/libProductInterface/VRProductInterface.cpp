#include <string>

#include "VRProduct.h"

#include <QFrame>
#include <QLabel>
#include <QPushButton>

#include <osg/Group>
#include "BasicStringDefinitions.h"

#include "VRProductInterface.h"

using namespace VR;
using namespace osg;
using namespace std;

//----------------------------------------------------------------------

ProductInterface::ProductInterface(
	QFrame * apFrameProductInterface,
	QLabel * apLabelProductInterfaceImage,
	QLabel * apLabelProductInterfaceInfo,
	QPushButton * apPushButtonProductInterface2Basket,
	QPushButton * apPushButtonProductInterfaceDetails,
	QLabel * apLabelProductInterfacePrice)	{

	m_pFrameProductInterface = apFrameProductInterface;
	m_pLabelProductInterfaceImage = apLabelProductInterfaceImage;
	m_pLabelProductInterfaceInfo = apLabelProductInterfaceInfo;
	m_pPushButtonProductInterface2Basket = apPushButtonProductInterface2Basket;
	m_pPushButtonProductInterfaceDetails = apPushButtonProductInterfaceDetails;
	m_pLabelProductInterfacePrice = apLabelProductInterfacePrice;

	m_pFrameProductInterface->setVisible(false);
	m_pLabelProductInterfacePrice->setVisible(false);
}

//----------------------------------------------------------------------

ProductInterface::~ProductInterface()	{

}

//=======================================================================

void ProductInterface::initProductInterface(const Product * apProduct)	{
	const Product * pProduct = apProduct;

	ProductParams productParams;
	pProduct->getParams(productParams);

	string & strProductName = productParams.m_strProductName;
	int nProductManufacturer = productParams.m_nManufacturerID;

	m_pLabelProductInterfacePrice->setText(("€ " + tostr(productParams.m_flPricePerUnit)).c_str());

//	pProduct->

	m_pLabelProductInterfaceImage;
	m_pLabelProductInterfaceInfo;	//Product name and manufacturer

	m_pFrameProductInterface->setVisible(true);
	m_pLabelProductInterfacePrice->setVisible(true);


}