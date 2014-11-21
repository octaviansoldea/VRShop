#include "VRShopBuilderCommands.h"

using namespace VR;
using namespace std;

//=====================================================================

string ShopBuilderCommands::getOperationType(OBJECT_NAME aenumOBJECT_NAME)	{
	int nType = aenumOBJECT_NAME;

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