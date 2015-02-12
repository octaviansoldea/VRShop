#include <osg/Material>
#include <osg/BlendFunc>

#include "VRAbstractObject.h"

#include "VRSurfaceOperations.h"

using namespace osg;
using namespace VR;

SurfaceOperations::SurfaceOperations()	{
}

//=========================================================================

void SurfaceOperations::setTransparency(AbstractObject * apAO, float aflTransparencyFactor)	{
	ref_ptr<Material> pMaterial = new Material;
	pMaterial->setAmbient(Material::FRONT_AND_BACK,Vec4(0.0f,0.0f,0.0f,1.0f));
	pMaterial->setDiffuse(Material::FRONT_AND_BACK,Vec4(1.0f,1.0f,1.0f,1.0f));
	pMaterial->setAlpha(Material::Face::FRONT_AND_BACK,aflTransparencyFactor);
	ref_ptr<StateSet> pStateSet = apAO->getOrCreateStateSet();
	pStateSet->setAttributeAndModes(pMaterial.get(), StateAttribute::ON | StateAttribute::OVERRIDE);
	ref_ptr<BlendFunc> pBlendFunc = new BlendFunc(BlendFunc::SRC_ALPHA,BlendFunc::ONE_MINUS_SRC_ALPHA);
	pStateSet->setAttributeAndModes(pBlendFunc);

	pStateSet->setRenderBinDetails(1000,"RenderBin");
}