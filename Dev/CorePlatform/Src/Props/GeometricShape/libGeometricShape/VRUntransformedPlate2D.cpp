    #include <iostream>
    
    #include <osg/Texture2D>
    #include <osg/Image>
    #include <osg/StateSet>
    #include <osg/TextureRectangle>
    #include <osg/TexMat>
    #include <osgDB/ReadFile>
  #include <osg/Material>
  
  #include <osg/Light>
 
 #include <osg/LightSource>
    
    #include "VRUntransformedPlate2D.h"
    
    using namespace osg;
    using namespace VR;
    using namespace std;
    
    UntransformedPlate2D::UntransformedPlate2D()	{
    	ref_ptr<Vec3Array> pPoints = new Vec3Array(4);
    	(*pPoints)[0].set(- 1.0 / 2.0, - 1.0 / 2.0, - 1.0 / 2.0);
    	(*pPoints)[1].set(- 1.0 / 2.0, - 1.0 / 2.0,   1.0 / 2.0);
    	(*pPoints)[2].set(  1.0 / 2.0, - 1.0 / 2.0,   1.0 / 2.0);
    	(*pPoints)[3].set(  1.0 / 2.0, - 1.0 / 2.0, - 1.0 / 2.0);
    
    	m_pGeometry = new Geometry;
    	m_pGeometry->setVertexArray(pPoints.get());
    	m_pGeometry->addPrimitiveSet(new DrawArrays(PrimitiveSet::QUADS,0,4));
    
    	ref_ptr<Vec3Array> pN = new Vec3Array;
    	m_pGeometry->setNormalArray(pN.get());
    	m_pGeometry->setNormalBinding(Geometry::BIND_OVERALL);
    	pN->push_back(Vec3(0.0, -1.0, 0.0));
    
    	addDrawable(m_pGeometry);
    }
    
    //--------------------------------------------------------------
    
    void UntransformedPlate2D::setColor(const vector < float > & aarrflColor) {
    	Vec4d vec4(aarrflColor[0], aarrflColor[1], aarrflColor[2], aarrflColor[3]);
    	ref_ptr<Vec4Array> pColors = new Vec4Array;
    	pColors->push_back(vec4);
    	pColors->push_back(vec4);
    	pColors->push_back(vec4);
    	pColors->push_back(vec4);
    	m_pGeometry->setColorArray(pColors.get());
    	m_pGeometry->setColorBinding(Geometry::BIND_PER_VERTEX);
    
    
  	osg::Light * pLight = new osg::Light();
  	pLight->setLightNum(1);
  	pLight->setAmbient(osg::Vec4(1.0, 1.0, 1.0, 1.0));
  	pLight->setDiffuse(osg::Vec4(1.0, 1.0, 1.0, 1.0));
  	pLight->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));
  	pLight->setPosition(osg::Vec4(0.0, 0.0, 1.0, 1.0));
  	osg::LightSource * pLightSource = new osg::LightSource();
  	pLightSource->setLight(pLight);
  	pLightSource->setLocalStateSetModes(osg::StateAttribute::ON);
 	osg::StateSet * pLightStateSet =  m_pGeometry->getOrCreateStateSet();
  	pLightSource->setStateSetModes(*pLightStateSet, osg::StateAttribute::ON);
  	pLightStateSet->setMode(GL_LIGHTING,osg::StateAttribute::OVERRIDE|osg::StateAttribute::INHERIT);
  	osg::ref_ptr<osg::Material> pMaterial = new osg::Material; 
  	pMaterial->setColorMode(Material::DIFFUSE);
  	pMaterial->setAmbient(Material::FRONT_AND_BACK, Vec4(1, 1, 1, 1.0));
  	pMaterial->setDiffuse(Material::FRONT_AND_BACK, Vec4(0.9, 0.3, 0.4, 1.0));
  	pMaterial->setSpecular(Material::FRONT_AND_BACK, Vec4(1.0, 1.0, 1.0, 1.0));
  	pMaterial->setShininess(Material::FRONT_AND_BACK, 64);
  
      pLightStateSet->setMode(GL_LIGHTING, StateAttribute::ON);
  	pLightStateSet->setAttributeAndModes(pMaterial.get(), osg::StateAttribute::ON);
    }
    
    //--------------------------------------------------------------
    
    void UntransformedPlate2D::setTexture(const string & astrFileName) {
        ref_ptr<Vec2Array> pTexCoords = new Vec2Array(4);
        //(*pTexCoords)[0].set(0.0, 0.0);
        //(*pTexCoords)[1].set(1.0, 0.0);
        //(*pTexCoords)[2].set(1.0, 1.0);
        //(*pTexCoords)[3].set(0.0, 1.0);
    
        (*pTexCoords)[0].set(0.0, 0.0);
        (*pTexCoords)[1].set(0.0, 1.0);
        (*pTexCoords)[2].set(1.0, 1.0);
        (*pTexCoords)[3].set(1.0, 0.0);
    	m_pGeometry->setTexCoordArray(0,pTexCoords);
    
    	ref_ptr<Vec4Array> pColors = new Vec4Array(1);
        (*pColors)[0].set(1.0,1.0,1.0,1.0);
        m_pGeometry->setColorArray(pColors);
        m_pGeometry->setColorBinding(Geometry::BIND_OVERALL);
    
        m_pGeometry->setUseDisplayList(false);
    
    	ref_ptr<Image> pImage = osgDB::readImageFile(astrFileName);
    
        ref_ptr<TextureRectangle> pTexture = new TextureRectangle(pImage);
    
        ref_ptr<TexMat> pTexMat = new TexMat;
        pTexMat->setScaleByTextureRectangleSize(true);
    
        ref_ptr<StateSet> pState = m_pGeometry->getOrCreateStateSet();
        pState->setTextureAttributeAndModes(0, pTexture, StateAttribute::ON);
        pState->setTextureAttributeAndModes(0, pTexMat, StateAttribute::ON);
    
        pState->setMode(GL_LIGHTING, StateAttribute::OFF);
    }
