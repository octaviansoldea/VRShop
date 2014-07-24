#include <QDebug>
#include <QMenuBar>

#include <osg/Geode>
#include <osg/Shape>
#include <osg/ShapeDrawable>

#include "VROSGQT_Widget.h"
#include "VRMainWindow_GUI.h"


using namespace VR;

#include <osg/StateSet>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/Material>
#include <osg/PositionAttitudeTransform>
#include <osg/StateAttribute>


MainWindow_GUI::MainWindow_GUI()
{
  setupUi(this);

  osg::Sphere* sphere    = new osg::Sphere( osg::Vec3( 0.f, 0.f, 0.f ), 0.25f );
  osg::ShapeDrawable* sd = new osg::ShapeDrawable( sphere );
  sd->setColor( osg::Vec4( 1.f, 0.f, 0.f, 1.f ) );

  osg::Geode* geode = new osg::Geode;
  geode->addDrawable( sd );

  osg::Light * pLight = new osg::Light();
  pLight->setAmbient(osg::Vec4(1.0, 1.0, 1.0, 1.0));
  pLight->setDiffuse(osg::Vec4(1.0, 1.0, 1.0, 1.0));
  pLight->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));
  pLight->setPosition(osg::Vec4(0.0, 0.0, 1.0, 1.0));

  osg::LightSource * pLightSource = new osg::LightSource();
  pLightSource->setLight(pLight);
  pLightSource->setLocalStateSetModes(osg::StateAttribute::ON);
  osg::Group *pScene = new osg::Group();
  osg::StateSet * pLightStateSet =  pScene->getOrCreateStateSet();
  pLightSource->setStateSetModes(*pLightStateSet, osg::StateAttribute::ON);

  osg::ref_ptr<osg::Material> pMaterial = new osg::Material; 
  pLightStateSet->setAttributeAndModes(pMaterial,osg::StateAttribute::OVERRIDE|osg::StateAttribute::ON); 
  pLightStateSet->setMode(GL_LIGHTING,osg::StateAttribute::OVERRIDE|osg::StateAttribute::INHERIT); 
  pMaterial->setColorMode(osg::Material::EMISSION);
  
  pScene->addChild(geode);
  pScene->addChild(pLightSource);

  m_pOSGQT_Widget->setSceneData(pScene);
}

MainWindow_GUI::~MainWindow_GUI()
{
}
