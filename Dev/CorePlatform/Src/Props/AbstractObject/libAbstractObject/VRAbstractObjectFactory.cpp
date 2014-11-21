#include "VRCustomFurniture.h"
#include "VRContainer.h"
#include "VRCupboard.h"
#include "VRCylinder.h"
#include "VRPlate3D.h"
#include "VRPrism.h"
#include "VRSphere.h"

#include "VRAbstractObject.h"
#include "VRAbstractObjectFactory.h"

using namespace VR;
using namespace osg;
using namespace std;

//==============================================================

AbstractObjectFactory::AbstractObjectFactory()	{
}

//--------------------------------------------------------------

AbstractObjectFactory::~AbstractObjectFactory() {
}

//=======================================================================

ref_ptr<AbstractObject> AbstractObjectFactory::createAbstractObject(const string & astrClassName)	{
	if (astrClassName == "Cupboard")	{
		CupboardParams cP;
		ref_ptr<Cupboard> pCupboard = new Cupboard(cP);
		return (pCupboard);
	} else if (astrClassName == "Container")	{
		ContainerParams cP;
		ref_ptr<Container> pContainer = new Container(cP);
		return (pContainer);
	} else if (astrClassName == "CustomFurniture")	{
		CustomFurnitureParams cF;
		ref_ptr<CustomFurniture> pCustomFurniture = new CustomFurniture(cF);
		return (pCustomFurniture);
	} else if (astrClassName == "Plate3D")	{
		Plate3DParams p3DP;
		ref_ptr<Plate3D> pPlate3D = new Plate3D(p3DP);
		return (pPlate3D);
	} else if (astrClassName == "Cylinder")	{
		CylinderParams cP;
		ref_ptr<VR::Cylinder> pCylinder = new VR::Cylinder(cP);
		return (pCylinder);
	} else if (astrClassName == "Prism")	{
		PrismParams pP;
		ref_ptr<Prism> pPrism = new Prism(pP);
		return (pPrism);
	} else if (astrClassName == "Sphere")	{
		SphereParams sP;
		ref_ptr<Sphere> pSphere = new Sphere(sP);
		return (pSphere);
	} else {
		return NULL;
	}
}

//=======================================================================

