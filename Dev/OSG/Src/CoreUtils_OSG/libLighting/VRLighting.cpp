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
	osg::ref_ptr<osg::Light> pLight = new osg::Light();
	Vec4d diffuse(osg::Vec4(1., 1., 1.0, 1.0));

	pLight->setAmbient(osg::Vec4(147/255, 226/255, 240/255, 1.0));	//147 226 240
	pLight->setDiffuse(diffuse);
	pLight->setSpecular(diffuse);
	pLight->setPosition(osg::Vec4(-3.0, -2.0, 3.0, 1.0));

	ref_ptr<LightSource> pLightSource = new osg::LightSource();
	pLightSource->setLight(pLight.get());
	pLightSource->setDataVariance(osg::Object::STATIC);
	pLightSource->setLocalStateSetModes(osg::StateAttribute::ON);
	pLightSource->getOrCreateStateSet()->setMode(GL_LIGHTING,osg::StateAttribute::OVERRIDE|osg::StateAttribute::INHERIT); 

	return pLightSource;
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