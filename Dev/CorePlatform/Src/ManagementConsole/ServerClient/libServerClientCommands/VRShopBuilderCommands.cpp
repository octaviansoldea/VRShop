#include "VRShopBuilderCommands.h"

using namespace VR;
using namespace std;

//=====================================================================

string ShopBuilderCommands::getOperationType(const ObjectName & aObjectName)	{
	int nType = aObjectName;

	string strResult;

	switch (nType)	{
	case PRODUCT:
		{
			strResult = "Products";
			break;
		}
	case PRODUCT_DISPLAY:
		{
			strResult = "ProductDisplay";
			break;
		}
	case GRID:
		{
			strResult = "Grid";
			break;
		}
	default:
		break;
	}

	return strResult;
}