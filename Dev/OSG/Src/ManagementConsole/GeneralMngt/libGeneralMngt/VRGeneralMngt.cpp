#include <string>

#include "VRGeneralMngt.h"

using namespace VR;
using namespace std;

GeneralMngt::GeneralMngt()	{
}

//------------------------------------------------------------------------------

void GeneralMngt::createTableManufacturer()	{
	string strCommand;

	strCommand = "CREATE TABLE IF NOT EXISTS Manufacturer "
		"(ManufacturerID INTEGER AUTOINCREMENT, "
		"ManufacturerName TEXT, "
		"ManufacturerAddress TEXT, "
		"ManufacturerOrigin TEXT, "
		"ManufacturerURL TEXT, "
		"ManufacturerEmail TEXT, "
		"ManufacturerPhone TEXT, "
		"ManufacturerLogo TEXT, "
		"ManufacturerDateAdded TEXT, "
		"ManufacturerDateModified TEXT)";
}

//------------------------------------------------------------------------------

void GeneralMngt::modifyTableManufacturer()	{
}