#include <osg/Geode>
#include <osg/Shape>
#include <osg/ShapeDrawable>

#include <osg/StateSet>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/Material>
#include <osg/StateAttribute>

#include <osgGA/TrackballManipulator>

#include "VROSGQT_Widget.h"
#include "VRMainWindow_GUI.h"

using namespace osg;
using namespace VR;


MainWindow_GUI::MainWindow_GUI()	{
	setupUi(this);

	ref_ptr<osg::Group> pScene = new osg::Group();

	ref_ptr<osg::Sphere> sphere    = new osg::Sphere( osg::Vec3( 0.f, 0.f, 0.f ), 0.25f );
	ref_ptr<osg::ShapeDrawable> sd = new osg::ShapeDrawable( sphere );
	sd->setColor( osg::Vec4( 1.f, 0.f, 0.f, 1.f ) );

	ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable( sd );


	ref_ptr<Light> pLight = new osg::Light();
	pLight->setPosition(osg::Vec4(1,-1, 1, 1));
	pLight->setAmbient(osg::Vec4(0.2, 0.2, 0.2, 1.0));
	pLight->setDiffuse(osg::Vec4(0.7, 0.4, 0.6, 1.0));
	pLight->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));

	ref_ptr<LightSource> pLightSource = new osg::LightSource();
	pLightSource->setLight(pLight);
	pLightSource->setLocalStateSetModes(osg::StateAttribute::ON);
	osg::StateSet * pLightStateSet = pScene->getOrCreateStateSet();
	pLightSource->setStateSetModes(*pLightStateSet, osg::StateAttribute::ON);
	pLightStateSet->setMode(GL_LIGHTING,osg::StateAttribute::OVERRIDE|osg::StateAttribute::INHERIT); 

	osg::ref_ptr<osg::Material> pMaterial = new osg::Material; 
	pLightStateSet->setAttributeAndModes(pMaterial,osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON); 
	pMaterial->setColorMode(osg::Material::DIFFUSE);

	pScene->addChild(geode);
	pScene->addChild(pLightSource);

	m_pOSGQT_Widget->setSceneData(pScene);
	m_pOSGQT_Widget->setCameraManipulator(new osgGA::TrackballManipulator);

}