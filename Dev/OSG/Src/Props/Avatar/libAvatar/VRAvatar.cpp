#include "VRPlate3D.h"
#include "VRCylinder.h"

#include "VRAvatar.h"

using namespace VR;

//==============================================================================

Avatar::Avatar(QObject * parent): QObject(parent)	{
	Plate3DParams pParams;
	pParams.m_flLenX = 0.3;
	pParams.m_flLenY = 0.05;
	pParams.m_flLenZ = 0.5;
	pParams.m_strFileNameTexture = "../../../../Resources/Textures/MetallicWood.png";
	osg::ref_ptr<Plate3D> pAvatar = new Plate3D(pParams);

	addChild(pAvatar);
}

//------------------------------------------------------------------------------

Avatar::~Avatar()	{
}

//==============================================================================

const char* Avatar::className() const	{
	return "Avatar";
}