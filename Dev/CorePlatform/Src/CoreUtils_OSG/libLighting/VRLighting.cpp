#include <osg/LightSource>
#include <osg/Light>

#include "VRLighting.h"

using namespace VR;
using namespace osg;

//--------------------------------------------------------------------

Lighting::Lighting(QObject * apQObject) : QObject(apQObject)	{
}

//--------------------------------------------------------------------

Lighting::~Lighting()	{
}

//--------------------------------------------------------------------

ref_ptr<LightSource> Lighting::createLights()	{
	osg::ref_ptr<osg::Light> light0 = new osg::Light();
	light0->setLightNum(0); //light0 is now GL-Light0

	light0->setAmbient(osg::Vec4f(0.15, 0.15, 0.15, 0.0));
	light0->setDiffuse(osg::Vec4f(0.15, 0.15, 0.15, 0.0f));
	light0->setSpecular(osg::Vec4f(0.15, 0.15, 0.15, 0.0f));
	light0->setPosition(osg::Vec4f(0, -100, 10, 0));			//w=0 => directional light; w=1 => positional light
	light0->setDirection(osg::Vec3f(0, 50, 10));
	light0->setLinearAttenuation(2);


	osg::ref_ptr< osg::LightSource > ls0 = new osg::LightSource();
	ls0->setLight(light0.get());
	ls0->setDataVariance(osg::Object::STATIC);
	ls0->setLocalStateSetModes(osg::StateAttribute::ON);

	return ls0;
}

//====================================================================
//====================================================================

LightFollowsNodeCallback::LightFollowsNodeCallback(osg::Node * apNode)	{
	m_pNode = apNode;
}

//--------------------------------------------------------------------

LightFollowsNodeCallback::~LightFollowsNodeCallback()	{
}

//--------------------------------------------------------------------

void LightFollowsNodeCallback::operator()(Node* node, NodeVisitor* nv)	{
	osg::LightSource * pLightSource = dynamic_cast<osg::LightSource*>(node);

	if (pLightSource)	{
		osg::Light * pLight = pLightSource->getLight();

		if (pLight)	{
//			pLight->setPosition(osg::Vec4((position-_at->centralBodyPosition(simulationTime)).getVec3d(),1.0));
		} else {
			return;
		}
		return;
	}

	traverse(node,nv);
}