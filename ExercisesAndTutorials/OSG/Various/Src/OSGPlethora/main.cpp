#include <osg/PolygonMode>
#include <osgText/Font>
#include <osgViewer/View>
#include <osg/AnimationPath>
#include <osg/Texture>
#include <osg/Camera>
#include <osgGA/GUIEventHandler>
#include <osgText/Text>
#include <osgUtil/LineSegmentIntersector>
#include <osgUtil/DelaunayTriangulator>

osg::AnimationPathCallback* createAnimationPathCallback( float radius, float time );
osg::Camera* createRTTCamera( osg::Camera::BufferComponent buffer, osg::Texture* tex, bool isAbsolute=false );
osg::Camera* createHUDCamera( double left, double right, double bottom, double top );
osg::Geode* createScreenQuad( float width, float height, float scale=1.0f );
osgText::Text* createText( const osg::Vec3& pos, const std::string& content, float size );
    
float randomValue( float min, float max );
osg::Vec3 randomVector( float min, float max );
osg::Matrix randomMatrix( float min, float max );
    
    class PickHandler : public osgGA::GUIEventHandler
    {
    public:
        virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa );
        virtual void doUserOperations( osgUtil::LineSegmentIntersector::Intersection& result ) = 0;
    };


osg::ref_ptr<osgText::Font> g_font = osgText::readFontFile("fonts/arial.ttf");
    
    osg::AnimationPathCallback* createAnimationPathCallback( float radius, float time )
    {
        osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath;
        path->setLoopMode( osg::AnimationPath::LOOP );
        
        unsigned int numSamples = 32;
        float delta_yaw = 2.0f * osg::PI/((float)numSamples - 1.0f);
        float delta_time = time / (float)numSamples;
        for ( unsigned int i=0; i<numSamples; ++i )
        {
            float yaw = delta_yaw * (float)i;
            osg::Vec3 pos( sinf(yaw)*radius, cosf(yaw)*radius, 0.0f );
            osg::Quat rot( -yaw, osg::Z_AXIS );
            path->insert( delta_time * (float)i, osg::AnimationPath::ControlPoint(pos, rot) );
        }
        
        osg::ref_ptr<osg::AnimationPathCallback> apcb = new osg::AnimationPathCallback;
        apcb->setAnimationPath( path.get() );
        return apcb.release();    
    }
    
    osg::Camera* createRTTCamera( osg::Camera::BufferComponent buffer, osg::Texture* tex, bool isAbsolute )
    {
        osg::ref_ptr<osg::Camera> camera = new osg::Camera;
        camera->setClearColor( osg::Vec4() );
        camera->setClearMask( GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT );
        camera->setRenderTargetImplementation( osg::Camera::FRAME_BUFFER_OBJECT );
        camera->setRenderOrder( osg::Camera::PRE_RENDER );
        if ( tex )
        {
            tex->setFilter( osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR );
            tex->setFilter( osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR );
            camera->setViewport( 0, 0, tex->getTextureWidth(), tex->getTextureHeight() );
            camera->attach( buffer, tex );
        }
        
        if ( isAbsolute )
        {
            camera->setReferenceFrame( osg::Transform::ABSOLUTE_RF );
            camera->setProjectionMatrix( osg::Matrix::ortho2D(0.0, 1.0, 0.0, 1.0) );
            camera->setViewMatrix( osg::Matrix::identity() );
            camera->addChild( createScreenQuad(1.0f, 1.0f) );
        }
        return camera.release();
    }
    
    osg::Camera* createHUDCamera( double left, double right, double bottom, double top )
    {
        osg::ref_ptr<osg::Camera> camera = new osg::Camera;
        camera->setReferenceFrame( osg::Transform::ABSOLUTE_RF );
        camera->setClearMask( GL_DEPTH_BUFFER_BIT );
        camera->setRenderOrder( osg::Camera::POST_RENDER );
        camera->setAllowEventFocus( false );
        camera->setProjectionMatrix( osg::Matrix::ortho2D(left, right, bottom, top) );
        camera->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
        return camera.release();
    }
    
    osg::Geode* createScreenQuad( float width, float height, float scale )
    {
        osg::Geometry* geom = osg::createTexturedQuadGeometry(
            osg::Vec3(), osg::Vec3(width,0.0f,0.0f), osg::Vec3(0.0f,height,0.0f),
            0.0f, 0.0f, width*scale, height*scale );
        osg::ref_ptr<osg::Geode> quad = new osg::Geode;
        quad->addDrawable( geom );
        
        int values = osg::StateAttribute::OFF|osg::StateAttribute::PROTECTED;
        quad->getOrCreateStateSet()->setAttribute(
            new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::FILL), values );
        quad->getOrCreateStateSet()->setMode( GL_LIGHTING, values );
        return quad.release();
    }
    
    osgText::Text* createText( const osg::Vec3& pos, const std::string& content, float size )
    {
        osg::ref_ptr<osgText::Text> text = new osgText::Text;
        text->setDataVariance( osg::Object::DYNAMIC );
        text->setFont( g_font.get() );
        text->setCharacterSize( size );
        text->setAxisAlignment( osgText::TextBase::XY_PLANE );
        text->setPosition( pos );
        text->setText( content );
        return text.release();
    }
    
    float randomValue( float min, float max )
    {
        return (min + (float)rand()/(RAND_MAX+1.0f) * (max - min));
    }
    
    osg::Vec3 randomVector( float min, float max )
    {
        return osg::Vec3( randomValue(min, max),
                          randomValue(min, max),
                          randomValue(min, max) );
    }
    
    osg::Matrix randomMatrix( float min, float max )
    {
        osg::Vec3 rot = randomVector(-osg::PI, osg::PI);
        osg::Vec3 pos = randomVector(min, max);
        return osg::Matrix::rotate(rot[0], osg::X_AXIS, rot[1], osg::Y_AXIS, rot[2], osg::Z_AXIS) *
               osg::Matrix::translate(pos);
    }
    
    bool PickHandler::handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )
    {
        if ( ea.getEventType()!=osgGA::GUIEventAdapter::RELEASE ||
             ea.getButton()!=osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON ||
             !(ea.getModKeyMask()&osgGA::GUIEventAdapter::MODKEY_CTRL) )
            return false;
        
        osgViewer::View* viewer = dynamic_cast<osgViewer::View*>(&aa);
        if ( viewer )
        {
            osg::ref_ptr<osgUtil::LineSegmentIntersector> intersector =
                new osgUtil::LineSegmentIntersector(osgUtil::Intersector::WINDOW, ea.getX(), ea.getY());
            osgUtil::IntersectionVisitor iv( intersector.get() );
            viewer->getCamera()->accept( iv );
            
            if ( intersector->containsIntersections() )
            {
                osgUtil::LineSegmentIntersector::Intersection result = *(intersector->getIntersections().begin());
                doUserOperations( result );
            }
        }
        return false;
    }



/* -*-c++-*- OpenSceneGraph Cookbook
 * Chapter 3 Recipe 1
 * Author: Wang Rui <wangray84 at gmail dot com>
*/

#include <osg/Geometry>
#include <osg/Geode>
#include <osg/LineWidth>
#include <osgUtil/Tessellator>
#include <osgViewer/Viewer>

#include <osg/Geode>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>


int main_( int argc, char** argv )	{
    // The vertex array shared by both the polygon and the border
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(8);
    (*vertices)[0].set( 0.0f, 0.0f, 0.0f );
    (*vertices)[1].set( 3.0f, 0.0f, 0.0f );
    (*vertices)[2].set( 3.0f, 0.0f, 3.0f );
    (*vertices)[3].set( 0.0f, 0.0f, 3.0f );
    (*vertices)[4].set( 1.0f, 0.0f, 1.0f );
    (*vertices)[5].set( 2.0f, 0.0f, 1.0f );
    (*vertices)[6].set( 2.0f, 0.0f, 2.0f );
    (*vertices)[7].set( 1.0f, 0.0f, 2.0f );
    
    // The normal array
    osg::ref_ptr<osg::Vec3Array> normals = new osg::Vec3Array(1);
    (*normals)[0].set( 0.0f,-1.0f, 0.0f );
    
    // Construct the polygon geometry
    osg::ref_ptr<osg::Geometry> polygon = new osg::Geometry;
    polygon->setVertexArray( vertices.get() );
    polygon->setNormalArray( normals.get() );
    polygon->setNormalBinding( osg::Geometry::BIND_OVERALL );
    polygon->addPrimitiveSet( new osg::DrawArrays(GL_QUADS, 0, 4) );
    polygon->addPrimitiveSet( new osg::DrawArrays(GL_QUADS, 4, 4) );
    
    osgUtil::Tessellator tessellator;
	tessellator.setTessellationType( osgUtil::Tessellator::TessellationType::TESS_TYPE_GEOMETRY );
	tessellator.setWindingType( osgUtil::Tessellator::WindingType::TESS_WINDING_ODD);
    tessellator.retessellatePolygons( *polygon );
    
    // Construct the borderlines geometry
    osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array(1);
    (*colors)[0].set( 1.0f, 1.0f, 0.0f, 1.0f );
    
    osg::ref_ptr<osg::Geometry> border = new osg::Geometry;
    border->setVertexArray( vertices.get() );
    border->setColorArray( colors.get() );
    border->setColorBinding( osg::Geometry::BIND_OVERALL );
    border->addPrimitiveSet( new osg::DrawArrays(GL_LINE_LOOP, 0, 4) );
    border->addPrimitiveSet( new osg::DrawArrays(GL_LINE_LOOP, 4, 4) );
    border->getOrCreateStateSet()->setAttribute( new osg::LineWidth(5.0f) );
    
    // Add them to the scene graph
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( polygon.get() );
    geode->addDrawable( border.get() );
    
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild( geode.get() );
    
    osgViewer::Viewer viewer;
    viewer.setSceneData( root.get() );
    return viewer.run();
}


//=============================================================================================

/* -*-c++-*- OpenSceneGraph Cookbook
 * Chapter 3 Recipe 2
 * Author: Wang Rui <wangray84 at gmail dot com>
*/

#include <osg/Geometry>
#include <osg/Geode>
#include <osgUtil/SmoothingVisitor>
#include <osgUtil/Tessellator>
#include <osgGA/StateSetManipulator>
#include <osgViewer/Viewer>


osg::Geometry* createExtrusion( osg::Vec3Array* vertices, const osg::Vec3& direction, float length )
{
    osg::ref_ptr<osg::Vec3Array> newVertices = new osg::Vec3Array;
    newVertices->insert( newVertices->begin(), vertices->begin(), vertices->end() );
    
    unsigned int numVertices = vertices->size();
    osg::Vec3 offset = direction * length;
    for ( osg::Vec3Array::reverse_iterator ritr=vertices->rbegin();
          ritr!=vertices->rend(); ++ritr )
    {
        newVertices->push_back( (*ritr) + offset );
    }
    
    osg::ref_ptr<osg::Geometry> extrusion = new osg::Geometry;
    extrusion->setVertexArray( newVertices.get() );
    extrusion->addPrimitiveSet( new osg::DrawArrays(GL_POLYGON, 0, numVertices) );
    extrusion->addPrimitiveSet( new osg::DrawArrays(GL_POLYGON, numVertices, numVertices) );
    
    osgUtil::Tessellator tessellator;
    tessellator.setTessellationType( osgUtil::Tessellator::TESS_TYPE_POLYGONS );
    tessellator.setWindingType( osgUtil::Tessellator::TESS_WINDING_ODD );
    tessellator.retessellatePolygons( *extrusion );
    
    osg::ref_ptr<osg::DrawElementsUInt> sideIndices = new osg::DrawElementsUInt( GL_QUAD_STRIP );
    for ( unsigned int i=0; i<numVertices; ++i )
    {
        sideIndices->push_back( i );
        sideIndices->push_back( (numVertices-1-i) + numVertices );
    }
    sideIndices->push_back( 0 );
    sideIndices->push_back( numVertices*2 - 1 );
    extrusion->addPrimitiveSet( sideIndices.get() );
    
    osgUtil::SmoothingVisitor::smooth( *extrusion );
    return extrusion.release();
}

int main_1( int argc, char** argv )
{
    osg::ArgumentParser arguments( &argc, argv );
    
    osg::Vec3 direction(0.0f, 0.0f, -1.0f);
    arguments.read( "--direction", direction.x(), direction.y(), direction.z() );
    
    float length = 5.0f;
    arguments.read( "--length", length );
    
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(6);
    (*vertices)[0].set( 0.0f, 4.0f, 0.0f );
    (*vertices)[1].set(-2.0f, 5.0f, 0.0f );
    (*vertices)[2].set(-5.0f, 0.0f, 0.0f );
    (*vertices)[3].set( 0.0f,-1.0f, 0.0f );
    (*vertices)[4].set( 5.0f, 0.0f, 0.0f );
    (*vertices)[5].set( 2.0f, 5.0f, 0.0f );
    
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( createExtrusion(vertices.get(), direction, length) );
    
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild( geode.get() );
    
    osgViewer::Viewer viewer;
    viewer.setSceneData( root.get() );
    viewer.addEventHandler( new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()) );
    return viewer.run();
}

//==========================================================================================================

/* -*-c++-*- OpenSceneGraph Cookbook
 * Chapter 5 Recipe 7
 * Author: Wang Rui <wangray84 at gmail dot com>
*/

#include <osg/Program>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>



static const char* vertSource = {
    "uniform vec3 lightPosition;\n"
    "varying vec3 normal, eyeVec, lightDir;\n"
    "void main()\n"
    "{\n"
    "    vec4 vertexInEye = gl_ModelViewMatrix * gl_Vertex;\n"
    "    eyeVec = -vertexInEye.xyz;\n"
    "    lightDir = vec3(lightPosition - vertexInEye.xyz);\n"
    "    normal = gl_NormalMatrix * gl_Normal;\n"
    "    gl_Position = ftransform();\n"
    "}\n"
};

static const char* fragSource = {
    "uniform vec4 lightDiffuse;\n"
    "uniform vec4 lightSpecular;\n"
    "uniform float shininess;\n"
    "varying vec3 normal, eyeVec, lightDir;\n"
    "void main (void)\n"
    "{\n"
    "  vec4 finalColor = gl_FrontLightModelProduct.sceneColor;\n"
    "  vec3 N = normalize(normal);\n"
    "  vec3 L = normalize(lightDir);\n"
    "  float lambert = dot(N,L);\n"
    "  if (lambert > 0.0)\n"
    "  {\n"
    "    finalColor += lightDiffuse * lambert;\n"
    "    vec3 E = normalize(eyeVec);\n"
    "    vec3 R = reflect(-L, N);\n"
    "    float specular = pow(max(dot(R, E), 0.0), shininess);\n"
    "    finalColor += lightSpecular * specular;\n"
    "  }\n"
    "  gl_FragColor = finalColor;\n"
    "}\n"
};

class LightPosCallback : public osg::Uniform::Callback
{
public:
    virtual void operator()( osg::Uniform* uniform, osg::NodeVisitor* nv )
    {
        const osg::FrameStamp* fs = nv->getFrameStamp();
        if ( !fs ) return;
        
        float angle = osg::inDegrees( (float)fs->getFrameNumber() );
        uniform->set( osg::Vec3(20.0f * cosf(angle), 20.0f * sinf(angle), 1.0f) );
    }
};

int main_2( int argc, char** argv )
{
    osg::ref_ptr<osg::Node> model = osgDB::readNodeFile( "C:/Programi/OSG/OpenSceneGraph-Data-3.0.0/cessna.osgt" );
    
    osg::ref_ptr<osg::Program> program = new osg::Program;
    program->addShader( new osg::Shader(osg::Shader::VERTEX, vertSource) );
    program->addShader( new osg::Shader(osg::Shader::FRAGMENT, fragSource) );
    
    osg::StateSet* stateset = model->getOrCreateStateSet();
    stateset->setAttributeAndModes( program.get() );
    stateset->addUniform( new osg::Uniform("lightDiffuse", osg::Vec4(0.8f, 0.8f, 0.8f, 1.0f)) );
    stateset->addUniform( new osg::Uniform("lightSpecular", osg::Vec4(1.0f, 1.0f, 0.4f, 1.0f)) );
    stateset->addUniform( new osg::Uniform("shininess", 64.0f) );
    
    osg::ref_ptr<osg::Uniform> lightPos = new osg::Uniform( "lightPosition", osg::Vec3() );
    lightPos->setUpdateCallback( new LightPosCallback );
    stateset->addUniform( lightPos.get() );
    
    osgViewer::Viewer viewer;
    viewer.setSceneData( model.get() );
    return viewer.run();
}


//====================================================================================================

#include <osg/MatrixTransform>
#include <osgGA/GUIEventAdapter>
#define RAND(min, max) ((min) + (float)rand()/(RAND_MAX) * ((max)-(min)))

class Player : public osg::MatrixTransform
{
public:
    Player();
    Player( float width, float height, const std::string& texfile );
    
    float width() const { return _size[0]; }
    float height() const { return _size[1]; }
    
    void setSpeedVector( const osg::Vec3& sv ) { _speedVec = sv; }
    const osg::Vec3& getSpeedVector() const { return _speedVec; }
    
    enum PlayerType
    {
        INVALID_OBJ=0, PLAYER_OBJ, ENEMY_OBJ,
        PLAYER_BULLET_OBJ, ENEMY_BULLET_OBJ
    };
    void setPlayerType( PlayerType t ) { _type = t; }
    PlayerType getPlayerType() const { return _type; }
    
    bool isBullet() const
    { return _type==PLAYER_BULLET_OBJ || _type==ENEMY_BULLET_OBJ; }
    
    bool update( const osgGA::GUIEventAdapter& ea, osg::Group* root );
    bool intersectWith( Player* player ) const;
    
protected:
    osg::Vec2 _size;
    osg::Vec3 _speedVec;
    PlayerType _type;
};

#include <osg/Texture2D>
#include <osg/Geometry>
#include <osg/Geode>
#include <osgDB/ReadFile>


Player::Player()
:   _type(INVALID_OBJ)
{
}

Player::Player( float width, float height, const std::string& texfile )
:   _type(INVALID_OBJ)
{
    _size.set( width, height );
    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setImage( osgDB::readImageFile(texfile) );
    
    osg::ref_ptr<osg::Drawable> quad = osg::createTexturedQuadGeometry(
        osg::Vec3(-width*0.5f, -height*0.5f, 0.0f),
        osg::Vec3(width, 0.0f, 0.0f), osg::Vec3(0.0f, height, 0.0f) );
    quad->getOrCreateStateSet()->setTextureAttributeAndModes( 0, texture.get() );
    quad->getOrCreateStateSet()->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
    quad->getOrCreateStateSet()->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
    
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( quad.get() );
    addChild( geode.get() );
}

bool Player::update( const osgGA::GUIEventAdapter& ea, osg::Group* root )
{
    bool emitBullet = false;
    switch ( _type )
    {
    case PLAYER_OBJ:
        if ( ea.getEventType()==osgGA::GUIEventAdapter::KEYDOWN )
        {
            switch ( ea.getKey() )
            {
            case osgGA::GUIEventAdapter::KEY_Left:
                _speedVec = osg::Vec3(-0.1f, 0.0f, 0.0f);
                break;
            case osgGA::GUIEventAdapter::KEY_Right:
                _speedVec = osg::Vec3(0.1f, 0.0f, 0.0f);
                break;
            case osgGA::GUIEventAdapter::KEY_Return:
                emitBullet = true;
                break;
            default: break;
            }
        }
        else if ( ea.getEventType()==osgGA::GUIEventAdapter::KEYUP )
            _speedVec = osg::Vec3();
        break;
    case ENEMY_OBJ:
        if ( RAND(0, 2000)<1 ) emitBullet = true;
        break;
    default: break;
    }
    
    osg::Vec3 pos = getMatrix().getTrans();
    if ( emitBullet )
    {
        osg::ref_ptr<Player> bullet = new Player(0.4f, 0.8f, "bullet.png");
        if ( _type==PLAYER_OBJ )
        {
            bullet->setPlayerType( PLAYER_BULLET_OBJ );
            bullet->setMatrix( osg::Matrix::translate(pos + osg::Vec3(0.0f, 0.9f, 0.0f)) );
            bullet->setSpeedVector( osg::Vec3(0.0f, 0.2f, 0.0f) );
        }
        else
        {
            bullet->setPlayerType( ENEMY_BULLET_OBJ );
            bullet->setMatrix( osg::Matrix::translate(pos - osg::Vec3(0.0f, 0.9f, 0.0f)) );
            bullet->setSpeedVector( osg::Vec3(0.0f,-0.2f, 0.0f) );
        }
        root->addChild( bullet.get() );
    }
    
    if ( ea.getEventType()!=osgGA::GUIEventAdapter::FRAME )
        return true;
    
    float halfW = width() * 0.5f, halfH = height() * 0.5f;
    pos += _speedVec;
    if ( pos.x()<halfW || pos.x()>ea.getWindowWidth()-halfW )
        return false;
    if ( pos.y()<halfH || pos.y()>ea.getWindowHeight()-halfH )
        return false;
    setMatrix( osg::Matrix::translate(pos) );
    return true;
}

bool Player::intersectWith( Player* player ) const
{
    osg::Vec3 pos = getMatrix().getTrans();
    osg::Vec3 pos2 = player->getMatrix().getTrans();
    return fabs(pos[0] - pos2[0]) < (width() + player->width()) * 0.5f &&
           fabs(pos[1] - pos2[1]) < (height() + player->height()) * 0.5f;
}


#include <osg/Texture2D>
#include <osg/Geometry>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>


class GameControllor : public osgGA::GUIEventHandler
{
public:
    GameControllor( osg::Group* root )
    : _root(root), _direction(0.1f), _distance(0.0f) {}
    
    virtual bool handle( const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa )
    {
        _distance += fabs(_direction);
        if ( _distance>30.0f )
        {
            _direction = -_direction;
            _distance = 0.0f;
        }
        
        osg::NodePath toBeRemoved;
        for ( unsigned i=0; i<_root->getNumChildren(); ++i )
        {
            Player* player = static_cast<Player*>( _root->getChild(i) );
            if ( !player ) continue;
            
            if ( !player->update(ea, _root.get()) )
            {
                if ( player->isBullet() )
                    toBeRemoved.push_back( player );
            }
            
            if ( player->getPlayerType()==Player::ENEMY_OBJ )
                player->setSpeedVector( osg::Vec3(_direction, 0.0f, 0.0f) );
            if ( !player->isBullet() ) continue;
            
            for ( unsigned j=0; j<_root->getNumChildren(); ++j )
            {
                Player* player2 = static_cast<Player*>( _root->getChild(j) );
                if ( !player2 || player==player2 ) continue;
                
                if ( player->getPlayerType()==Player::ENEMY_BULLET_OBJ &&
                     player2->getPlayerType()==Player::ENEMY_OBJ )
                {
                    continue;
                }
                else if ( player->intersectWith(player2) )
                {
                    toBeRemoved.push_back( player );
                    toBeRemoved.push_back( player2 );
                }
            }
        }
        
        for ( unsigned i=0; i<toBeRemoved.size(); ++i )
            _root->removeChild( toBeRemoved[i] );
        return false;
    }
    
protected:
    osg::observer_ptr<osg::Group> _root;
    float _direction;
    float _distance;
};


int main_3( int argc, char** argv )
{
    osg::ref_ptr<Player> player = new Player(1.0f, 1.0f, "player.png");
    player->setMatrix( osg::Matrix::translate(40.0f, 5.0f, 0.0f) );
    player->setPlayerType( Player::PLAYER_OBJ );
    
    osg::ref_ptr<osg::Camera> hudCamera = createHUDCamera(0, 80, 0, 30);
    hudCamera->addChild( player.get() );
    
    for ( unsigned int i=0; i<5; ++i )
    {
        for ( unsigned int j=0; j<10; ++j )
        {
            osg::ref_ptr<Player> enemy = new Player(1.0f, 1.0f, "enemy.png");
            enemy->setMatrix( osg::Matrix::translate(
                20.0f+1.5f*(float)j, 25.0f-1.5f*(float)i, 0.0f) );
            enemy->setPlayerType( Player::ENEMY_OBJ );
            hudCamera->addChild( enemy.get() );
        }
    }
    
    osgViewer::Viewer viewer;
    viewer.getCamera()->setClearColor( osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f) );
    viewer.addEventHandler( new GameControllor(hudCamera.get()) );
    viewer.setSceneData( hudCamera.get() );
    return viewer.run();
}

//======================================================================================


int main_4( int argc, char** argv )
{
    osg::ArgumentParser arguments( &argc, argv );
    osg::ref_ptr<osg::Node> scene = osgDB::readNodeFiles( arguments );
    if ( !scene ) scene = osgDB::readNodeFile("cessna.osg");
    
    osg::ref_ptr<osg::Texture2D> tex2D = new osg::Texture2D;
    tex2D->setTextureSize( 1024, 1024 );
    tex2D->setInternalFormat( GL_DEPTH_COMPONENT24 );
    tex2D->setSourceFormat( GL_DEPTH_COMPONENT );
    tex2D->setSourceType( GL_FLOAT );
    
    osg::ref_ptr<osg::Camera> rttCamera = createRTTCamera(osg::Camera::DEPTH_BUFFER, tex2D.get());
    rttCamera->addChild( scene.get() );
    
    osg::ref_ptr<osg::Camera> hudCamera = createHUDCamera(0.0, 1.0, 0.0, 1.0);
    hudCamera->addChild( createScreenQuad(0.5f, 1.0f) );
    hudCamera->getOrCreateStateSet()->setTextureAttributeAndModes( 0, tex2D.get() );
    
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild( rttCamera.get() );
    root->addChild( hudCamera.get() );
    root->addChild( scene.get() );
    
    osgViewer::Viewer viewer;
    viewer.getCamera()->setComputeNearFarMode( osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR );
    viewer.setSceneData( root.get() );
    return viewer.run();
}

//=======================================================================

int main_Delauney( int argc, char** argv )
{
    osg::ref_ptr<osg::Vec3Array> va = new osg::Vec3Array(9);
    (*va)[0].set(-5.0f,-5.0f, 0.4f);
    (*va)[1].set( 1.0f,-5.6f, 0.0f);
    (*va)[2].set( 5.0f,-4.0f,-0.5f);
    (*va)[3].set(-6.2f, 0.0f, 4.2f);
    (*va)[4].set(-1.0f,-0.5f, 4.8f);
    (*va)[5].set( 4.3f, 1.0f, 3.0f);
    (*va)[6].set(-4.8f, 5.4f, 0.3f);
    (*va)[7].set( 0.6f, 5.1f,-0.8f);
    (*va)[8].set( 5.2f, 4.5f, 0.1f);
    
    osg::ref_ptr<osgUtil::DelaunayTriangulator> dt = new osgUtil::DelaunayTriangulator;
    dt->setInputPointArray( va.get() );
    dt->setOutputNormalArray( new osg::Vec3Array );
    dt->triangulate();
    
    osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry;
    geometry->setVertexArray( dt->getInputPointArray() );
    geometry->setNormalArray( dt->getOutputNormalArray() );
	geometry->setNormalBinding( osg::Geometry::BIND_PER_PRIMITIVE_SET);
    geometry->addPrimitiveSet( dt->getTriangles() );
    
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( geometry.get() );
    
    osgViewer::Viewer viewer;
    viewer.setSceneData( geode.get() );
    return viewer.run();
}

//========================================================================================================

#include <osg/AlphaFunc>
#include <osg/BlendFunc>
#include <osg/Camera>
#include <osg/Geometry>
#include <osg/Material>
#include <osg/TexGenNode>
#include <osg/TexMat>
#include <osg/TextureRectangle>
#include <osgDB/ReadFile>
#include <osgUtil/CullVisitor>
#include <osgViewer/Viewer>

unsigned int g_width = 800, g_height = 600;
unsigned int g_offset = 8;
int g_unit = 1;

class CullCallback : public osg::NodeCallback
{
public:
    CullCallback( unsigned int unit, unsigned int off )
    : _unit(unit), _offset(off) {}
    
    virtual void operator()( osg::Node* node, osg::NodeVisitor* nv )
    {
        osgUtil::CullVisitor* cullVisitor = static_cast<osgUtil::CullVisitor*>(nv);
        osgUtil::RenderStage* renderStage = cullVisitor->getCurrentRenderStage();
        const osg::Viewport* vp = renderStage->getViewport();
        if ( !vp ) return;
        
        osg::Matrixd m( *cullVisitor->getProjectionMatrix() );
        m.postMultTranslate( osg::Vec3d(1.0, 1.0, 1.0) );
        m.postMultScale( osg::Vec3d(0.5, 0.5, 0.5) );
        m.postMultScale( osg::Vec3d(vp->width(), vp->height(), 1.0) );
        m.postMultTranslate( osg::Vec3d(0.0, 0.0, -ldexp(double(_offset), -24.0)) );
        
        _stateset = new osg::StateSet;
        _stateset->setTextureAttribute( _unit, new osg::TexMat(m) );
        cullVisitor->pushStateSet( _stateset.get() );
        traverse( node, nv );
        cullVisitor->popStateSet();
    }
    
protected:
    osg::ref_ptr<osg::StateSet> _stateset;
    unsigned int _unit, _offset;
};

osg::Texture* createTexture( GLenum format, bool asMidLayer )
{
    osg::ref_ptr<osg::TextureRectangle> texture = new osg::TextureRectangle;
    texture->setTextureSize( g_width, g_height );
    texture->setFilter( osg::Texture::MIN_FILTER, osg::Texture::NEAREST );
    texture->setFilter( osg::Texture::MAG_FILTER, osg::Texture::NEAREST );
    texture->setWrap( osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_BORDER );
    texture->setWrap( osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_BORDER );
    texture->setInternalFormat( format );
    
    if ( asMidLayer )
    {
        texture->setSourceFormat( GL_DEPTH_STENCIL_EXT );
        texture->setSourceType( GL_UNSIGNED_INT_24_8_EXT );
        
        texture->setShadowComparison( true );
        texture->setShadowAmbient( 0 );
        texture->setShadowCompareFunc( osg::Texture::GREATER );
        texture->setShadowTextureMode( osg::Texture::INTENSITY );
    }
    return texture.release();
}

typedef std::pair<osg::Camera*, osg::Texture*> CameraAndTexture;
CameraAndTexture createProcessCamera( int order, osg::Node* scene,
                                      osg::Texture* depth, osg::Texture* prevDepth )
{
    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setDataVariance( osg::Object::DYNAMIC );
    camera->setInheritanceMask( osg::Camera::ALL_VARIABLES );
    camera->setRenderTargetImplementation( osg::Camera::FRAME_BUFFER_OBJECT );
    camera->setRenderOrder( osg::Camera::PRE_RENDER, order );
    camera->setClearColor( osg::Vec4() );
    camera->setComputeNearFarMode( osg::Camera::DO_NOT_COMPUTE_NEAR_FAR );
    
    osg::ref_ptr<osg::Texture> color = createTexture(GL_RGBA, false);
    camera->attach( osg::Camera::COLOR_BUFFER, color.get() );
    camera->attach( osg::Camera::PACKED_DEPTH_STENCIL_BUFFER, depth );
    
    osg::StateSet* ss = camera->getOrCreateStateSet();
    ss->setMode( GL_BLEND, osg::StateAttribute::OFF|osg::StateAttribute::OVERRIDE );
    if ( order!=0 )  // not the first camera?
    {
        ss->setAttributeAndModes( new osg::AlphaFunc(osg::AlphaFunc::GREATER, 0.01),
            osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE );
        ss->setTextureMode( g_unit, GL_TEXTURE_GEN_S, osg::StateAttribute::ON );
        ss->setTextureMode( g_unit, GL_TEXTURE_GEN_T, osg::StateAttribute::ON );
        ss->setTextureMode( g_unit, GL_TEXTURE_GEN_R, osg::StateAttribute::ON );
        ss->setTextureMode( g_unit, GL_TEXTURE_GEN_Q, osg::StateAttribute::ON );
        ss->setTextureAttributeAndModes( g_unit, prevDepth );
        
        osg::ref_ptr<osg::TexGenNode> texGenNode = new osg::TexGenNode;
        texGenNode->setReferenceFrame( osg::TexGenNode::ABSOLUTE_RF );
        texGenNode->setTextureUnit( g_unit );
        texGenNode->getTexGen()->setMode( osg::TexGen::EYE_LINEAR );
        texGenNode->addChild( scene );
        
        camera->addChild( texGenNode.get() );
        camera->addCullCallback( new CullCallback(g_unit, g_offset) );
    }
    else camera->addChild( scene );
    return CameraAndTexture(camera.release(), color.get());
}

osg::Camera* createCompositionCamera()
{
    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setDataVariance( osg::Object::DYNAMIC );
    camera->setReferenceFrame( osg::Transform::ABSOLUTE_RF );
    camera->setInheritanceMask( osg::Camera::READ_BUFFER|osg::Camera::DRAW_BUFFER );
    camera->setRenderOrder( osg::Camera::POST_RENDER );
    camera->setComputeNearFarMode( osg::Camera::COMPUTE_NEAR_FAR_USING_PRIMITIVES );
    camera->setClearMask( 0 );
    
    camera->setViewMatrix( osg::Matrix() );
    camera->setProjectionMatrix( osg::Matrix::ortho2D(0, 1, 0, 1) );
    camera->addCullCallback( new CullCallback(0, 0) );
    
    osg::StateSet* ss = camera->getOrCreateStateSet();
    ss->setRenderBinDetails( 0, "TraversalOrderBin" );
    return camera.release();
}

int main_Depth( int argc, char** argv )
{
    osg::ref_ptr<osg::Material> material = new osg::Material;
    material->setAmbient( osg::Material::FRONT_AND_BACK, osg::Vec4(0.0f, 0.0f, 0.0f, 1.0f) );
    material->setDiffuse( osg::Material::FRONT_AND_BACK, osg::Vec4(1.0f, 1.0f, 1.0f, 0.5f) );
    
    osg::Node* loadedModel = osgDB::readNodeFile( "cessna.osg" );
    loadedModel->getOrCreateStateSet()->setAttributeAndModes(
        material.get(), osg::StateAttribute::ON|osg::StateAttribute::OVERRIDE );
    loadedModel->getOrCreateStateSet()->setAttributeAndModes( new osg::BlendFunc );
    loadedModel->getOrCreateStateSet()->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
    
    osg::Camera* compositeCamera = createCompositionCamera();
	osg::ref_ptr<osg::Texture> depth[2];
	depth[0] = createTexture(GL_DEPTH24_STENCIL8_EXT, true);
	depth[1] = createTexture(GL_DEPTH24_STENCIL8_EXT, true);
	
	osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild( compositeCamera );
	
	unsigned int numPasses = 8;
	for ( unsigned int i=0; i<numPasses; ++i )
	{
	    CameraAndTexture cat = createProcessCamera(
	        i, loadedModel, depth[i%2].get(), depth[(i+1)%2].get() );
	    root->addChild( cat.first );
	    
	    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	    geode->addDrawable( osg::createTexturedQuadGeometry(
	        osg::Vec3(), osg::X_AXIS, osg::Y_AXIS) );
	    
        osg::StateSet* ss = geode->getOrCreateStateSet();
        ss->setTextureAttributeAndModes( 0, cat.second );
        ss->setAttributeAndModes( new osg::BlendFunc );
        ss->setMode( GL_LIGHTING, osg::StateAttribute::OFF );
        ss->setMode( GL_DEPTH_TEST, osg::StateAttribute::OFF );
        compositeCamera->insertChild( 0, geode.get() );
	}
	
    osgViewer::Viewer viewer;
    viewer.setSceneData( root.get() );
    viewer.setUpViewInWindow( 50, 50, g_width, g_height );
    return viewer.run();
}

//===========================================================================

#include <osg/Geometry>
#include <osg/Group>
#include <osgDB/ReadFile>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/Viewer>

//#define MERGE_GEOMETRY  // Comment this to disable merging geometries

#ifndef MERGE_GEOMETRY
osg::Node* createTiles( unsigned int cols, unsigned int rows )
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    for ( unsigned int y=0; y<rows; ++y )
    {
        for ( unsigned int x=0; x<cols; ++x )
        {
            osg::Vec3 center((float)x, 0.0f, (float)y);
            
            osg::ref_ptr<osg::Vec3Array> va = new osg::Vec3Array(4);
            (*va)[0] = center + osg::Vec3(-0.45f, 0.0f,-0.45f);
            (*va)[1] = center + osg::Vec3( 0.45f, 0.0f,-0.45f);
            (*va)[2] = center + osg::Vec3( 0.45f, 0.0f, 0.45f);
            (*va)[3] = center + osg::Vec3(-0.45f, 0.0f, 0.45f);
            
            osg::ref_ptr<osg::Vec3Array> na = new osg::Vec3Array(1);
            na->front() = osg::Vec3(0.0f, -1.0f, 0.0f);
            
            osg::ref_ptr<osg::Vec4Array> ca = new osg::Vec4Array(1);
            ca->front() = osg::Vec4(randomVector(0.0f, 1.0f), 1.0f);
            
            osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
            geom->setVertexArray( va.get() );
            geom->setNormalArray( na.get() );
            geom->setNormalBinding( osg::Geometry::BIND_OVERALL );
            geom->setColorArray( ca.get() );
            geom->setColorBinding( osg::Geometry::BIND_OVERALL );
            geom->addPrimitiveSet( new osg::DrawArrays(GL_QUADS, 0, 4) );
            geode->addDrawable( geom.get() );
        }
    }
    return geode.release();
}

#else

osg::Node* createTiles( unsigned int cols, unsigned int rows )
{
    unsigned int totalNum = cols * rows, index = 0;
    osg::ref_ptr<osg::Vec3Array> va = new osg::Vec3Array(totalNum * 4);
    osg::ref_ptr<osg::Vec3Array> na = new osg::Vec3Array(totalNum);
    osg::ref_ptr<osg::Vec4Array> ca  = new osg::Vec4Array(totalNum);
    
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    geom->setVertexArray( va.get() );
    geom->setNormalArray( na.get() );
    geom->setNormalBinding( osg::Geometry::BIND_PER_PRIMITIVE_SET );
    geom->setColorArray( ca.get() );
    geom->setColorBinding( osg::Geometry::BIND_PER_PRIMITIVE_SET );
    
    for ( unsigned int y=0; y<rows; ++y )
    {
        for ( unsigned int x=0; x<cols; ++x )
        {
            unsigned int vIndex = 4 * index;
            osg::Vec3 center((float)x, 0.0f, (float)y);
            (*va)[vIndex+0] = center + osg::Vec3(-0.45f, 0.0f,-0.45f);
            (*va)[vIndex+1] = center + osg::Vec3( 0.45f, 0.0f,-0.45f);
            (*va)[vIndex+2] = center + osg::Vec3( 0.45f, 0.0f, 0.45f);
            (*va)[vIndex+3] = center + osg::Vec3(-0.45f, 0.0f, 0.45f);
            
            (*na)[index] = osg::Vec3(0.0f, -1.0f, 0.0f);
            (*ca)[index] = osg::Vec4(randomVector(0.0f, 1.0f), 1.0f);
            geom->addPrimitiveSet( new osg::DrawArrays(GL_QUADS, vIndex, 4) );
            index++;
        }
    }
    
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( geom.get() );
    return geode.release();
}

#endif

int main_MergeGeometry( int argc, char** argv )
{
    osgViewer::Viewer viewer;
    viewer.setSceneData( createTiles(300, 300) );
    viewer.addEventHandler( new osgViewer::StatsHandler );
    return viewer.run();
}

//===============================================================================

#include <osg/Point>
#include <osg/Group>
#include <osgDB/ReadFile>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/Viewer>
#include <fstream>
#include <iostream>

const char* vertCode = {
    "uniform sampler2D defaultTex;\n"
    "uniform int width;\n"
    "uniform int height;\n"
    "varying float brightness;\n"
    "void main()\n"
    "{\n"
    "    float r = float(gl_InstanceID) / float(width);\n"
    "    vec2 uv = vec2(fract(r), floor(r) / float(height));\n"
    "    vec4 texValue = texture2D(defaultTex, uv);\n"
    "    vec4 pos = gl_Vertex + vec4(texValue.xyz, 1.0);\n"
    "    brightness = texValue.a;\n"
    "    gl_Position = gl_ModelViewProjectionMatrix * pos;\n"
    "}\n"
};

const char* fragCode = {
    "varying float brightness;\n"
    "void main()\n"
    "{\n"
    "    gl_FragColor = vec4(brightness, brightness, brightness, 1.0);\n"
    "}\n"
};

osg::Geometry* createInstancedGeometry( osg::Image* img, unsigned int numInstances )
{
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    geom->setUseDisplayList( false );
    geom->setUseVertexBufferObjects( true );
    geom->setVertexArray( new osg::Vec3Array(1) );
    geom->addPrimitiveSet( new osg::DrawArrays(GL_POINTS, 0, 1, numInstances) );
    
    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    texture->setImage( img );
    texture->setInternalFormat( GL_RGBA32F_ARB );
    texture->setFilter( osg::Texture2D::MIN_FILTER, osg::Texture2D::LINEAR );
    texture->setFilter( osg::Texture2D::MAG_FILTER, osg::Texture2D::LINEAR );
    geom->getOrCreateStateSet()->setTextureAttributeAndModes( 0, texture.get() );
    geom->getOrCreateStateSet()->addUniform( new osg::Uniform("defaultTex", 0) );
    geom->getOrCreateStateSet()->addUniform( new osg::Uniform("width", (int)img->s()) );
    geom->getOrCreateStateSet()->addUniform( new osg::Uniform("height", (int)img->t()) );
    
    //osg::ref_ptr<osg::Program> program = new osg::Program;
    //program->addShader( new osg::Shader(osg::Shader::VERTEX, vertCode) );
    //program->addShader( new osg::Shader(osg::Shader::FRAGMENT, fragCode) );
    //geom->getOrCreateStateSet()->setAttributeAndModes( program.get() );
    return geom.release();
}

osg::Geometry* readPointData( const std::string& file, unsigned int w, unsigned int h )
{
    std::ifstream is( file.c_str() );
    if ( !is ) return NULL;
    
    osg::ref_ptr<osg::Image> image = new osg::Image;
    image->allocateImage( w, h, 1, GL_RGBA, GL_FLOAT );
    
    unsigned int density, brightness;
    osg::BoundingBox boundBox;
    float* data = (float*)image->data();
    while ( !is.eof() )
    {
        osg::Vec3 pos;
        is >> pos[0] >> pos[1] >> pos[2] >> density >> brightness;
        boundBox.expandBy( pos );
        
        *(data++) = pos[0];
        *(data++) = pos[1];
        *(data++) = pos[2];
        *(data++) = brightness / 255.0;
    }
    
    osg::ref_ptr<osg::Geometry> geom = createInstancedGeometry( image.get(), w*h );
    geom->setInitialBound( boundBox );
    geom->getOrCreateStateSet()->setAttributeAndModes( new osg::Point(5.0f) );
    return geom.release();
}

int main_ReadPoints( int argc, char** argv )
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( readPointData("C:/Matej/data.txt", 512, 512) );
    
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild( geode.get() );
    
    osgViewer::Viewer viewer;
    viewer.setSceneData( root.get() );
    viewer.addEventHandler( new osgViewer::StatsHandler );
    return viewer.run();
}


//============================================================================

int main_DepthBuffer( int argc, char** argv )
{
    osg::ArgumentParser arguments( &argc, argv );
    osg::ref_ptr<osg::Node> scene = osgDB::readNodeFiles( arguments );
    if ( !scene ) scene = osgDB::readNodeFile("cessna.osg");
    
    osg::ref_ptr<osg::Texture2D> tex2D = new osg::Texture2D;
    tex2D->setTextureSize( 1024, 1024 );
    tex2D->setInternalFormat( GL_DEPTH_COMPONENT24 );
    tex2D->setSourceFormat( GL_DEPTH_COMPONENT );
    tex2D->setSourceType( GL_FLOAT );
    
    osg::ref_ptr<osg::Camera> rttCamera = createRTTCamera(osg::Camera::DEPTH_BUFFER, tex2D.get());
    rttCamera->addChild( scene.get() );
    
    osg::ref_ptr<osg::Camera> hudCamera = createHUDCamera(0.0, 1.0, 0.0, 1.0);
    hudCamera->addChild( createScreenQuad(0.5f, 1.0f) );
    hudCamera->getOrCreateStateSet()->setTextureAttributeAndModes( 0, tex2D.get() );
    
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild( rttCamera.get() );
    root->addChild( hudCamera.get() );
    root->addChild( scene.get() );
    
    osgViewer::Viewer viewer;
    viewer.getCamera()->setComputeNearFarMode( osg::CullSettings::DO_NOT_COMPUTE_NEAR_FAR );
    viewer.setSceneData( root.get() );
    return viewer.run();
}


//==============================================================================================

#include <osg/ShapeDrawable>
#include <osg/MatrixTransform>
#include <osgAnimation/BasicAnimationManager>
#include <osgAnimation/UpdateMatrixTransform>
#include <osgAnimation/StackedRotateAxisElement>
#include <osgViewer/Viewer>
#include <algorithm>

osg::Node* createWall()
{
    osg::ref_ptr<osg::ShapeDrawable> wallLeft =
        new osg::ShapeDrawable( new osg::Box(osg::Vec3(-5.5f, 0.0f, 0.0f), 10.0f, 0.3f, 10.0f) );
    osg::ref_ptr<osg::ShapeDrawable> wallRight =
        new osg::ShapeDrawable( new osg::Box(osg::Vec3(10.5f, 0.0f, 0.0f), 10.0f, 0.3f, 10.0f) );
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( wallLeft.get() );
    geode->addDrawable( wallRight.get() );
    return geode.release();
}

osg::MatrixTransform* createDoor()
{
    osg::ref_ptr<osg::ShapeDrawable> doorShape =
        new osg::ShapeDrawable( new osg::Box(osg::Vec3(2.5f, 0.0f, 0.0f), 6.0f, 0.2f, 10.0f) );
    doorShape->setColor( osg::Vec4(1.0f, 1.0f, 0.8f, 1.0f) );
    
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable( doorShape.get() );
    
    osg::ref_ptr<osg::MatrixTransform> trans = new osg::MatrixTransform;
    trans->addChild( geode.get() );
    return trans.release();
}

void generateDoorKeyframes( osgAnimation::FloatLinearChannel* ch, bool closed )
{
    osgAnimation::FloatKeyframeContainer* kfs = ch->getOrCreateSampler()->getOrCreateKeyframeContainer();
    kfs->clear();
    if ( closed )
    {
        kfs->push_back( osgAnimation::FloatKeyframe(0.0, 0.0f) );
        kfs->push_back( osgAnimation::FloatKeyframe(1.0, osg::PI_2) );
    }
    else
    {
        kfs->push_back( osgAnimation::FloatKeyframe(0.0, osg::PI_2) );
        kfs->push_back( osgAnimation::FloatKeyframe(1.0, 0.0f) );
    }
}

class OpenDoorHandler : public PickHandler
{
public:
    OpenDoorHandler() : _closed(true) {}
    
    virtual void doUserOperations( osgUtil::LineSegmentIntersector::Intersection& result )
    {
        osg::NodePath::iterator itr = std::find(
            result.nodePath.begin(), result.nodePath.end(), _door.get() );
        if ( itr!=result.nodePath.end() )
        {
            if ( _manager->isPlaying(_animation.get()) )
                return;
            
            osgAnimation::FloatLinearChannel* ch = dynamic_cast<osgAnimation::FloatLinearChannel*>(
                _animation->getChannels().front().get() );
            if ( ch )
            {
                generateDoorKeyframes( ch, _closed );
                _closed = !_closed;
            }
            _manager->playAnimation( _animation.get() );
        }
    }
    
    osg::observer_ptr<osgAnimation::BasicAnimationManager> _manager;
    osg::observer_ptr<osgAnimation::Animation> _animation;
    osg::observer_ptr<osg::MatrixTransform> _door;
    bool _closed;
};

int main_OpenDoor( int argc, char** argv )
{
    // Create the animation callback
    osg::ref_ptr<osgAnimation::FloatLinearChannel> ch = new osgAnimation::FloatLinearChannel;
    ch->setName( "euler" );
    ch->setTargetName( "DoorAnimCallback" );
    generateDoorKeyframes( ch.get(), true );
    
    osg::ref_ptr<osgAnimation::Animation> animation = new osgAnimation::Animation;
    animation->setPlayMode( osgAnimation::Animation::ONCE );
    animation->addChannel( ch.get() );
    
    osg::ref_ptr<osgAnimation::UpdateMatrixTransform> updater =
        new osgAnimation::UpdateMatrixTransform("DoorAnimCallback");
    updater->getStackedTransforms().push_back(
        new osgAnimation::StackedRotateAxisElement("euler", osg::Z_AXIS, 0.0) );
    
    osg::ref_ptr<osgAnimation::BasicAnimationManager> manager = new osgAnimation::BasicAnimationManager;
    manager->registerAnimation( animation.get() );
    
    // Create the scene graph
    osg::MatrixTransform* animDoor = createDoor();
    animDoor->setUpdateCallback( updater.get() );
    
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild( createWall() );
    root->addChild( animDoor );
    root->setUpdateCallback( manager.get() );
    
    osg::ref_ptr<OpenDoorHandler> handler = new OpenDoorHandler;
    handler->_manager = manager.get();
    handler->_animation = animation.get();
    handler->_door = animDoor;
    
    osgViewer::Viewer viewer;
    viewer.addEventHandler( handler.get() );
    viewer.setSceneData( root.get() );
    return viewer.run();
}

//===========================================================================

int main_Polydata(int argc, char * argv[])	{
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(15);
	(*vertices)[0].set(0.0f, 0.0f, 0.0f );
	(*vertices)[1].set(2.024650, -0.107820, -2.377140);
	(*vertices)[2].set(2.024650, -0.107820, -2.294330);
	(*vertices)[3].set(-0.110020, -0.107820, -2.335730);
	(*vertices)[4].set(-2.244690, -0.107820, -2.377140);
	(*vertices)[5].set(-2.244690, -0.107820, -2.294330);
	(*vertices)[6].set(-0.110020, 0.058400, -2.377140);
	(*vertices)[7].set(-2.244690, 0.224620, -2.377140);
	(*vertices)[8].set(2.024650, 0.224620, -2.377140);
	(*vertices)[9].set(2.024650, 0.058400, -2.335730);
	(*vertices)[10].set(2.024650, 0.224620, -2.294330);
	(*vertices)[11].set(-0.110020, 0.058400, -2.294330);
	(*vertices)[12].set(-2.244690, 0.224620, -2.294330);
	(*vertices)[13].set(-0.110020, 0.224620, -2.335730);
	(*vertices)[14].set(-2.244690, 0.058400, -2.335730);

	osg::ref_ptr<osg::DrawElementsUInt> de = new osg::DrawElementsUInt(GL_TRIANGLES);
	de->push_back(1);	de->push_back(2);	de->push_back(3);
	de->push_back(4);	de->push_back(1);	de->push_back(3);
	de->push_back(5);	de->push_back(4);	de->push_back(3);
	de->push_back(2);	de->push_back(5);	de->push_back(3);
	de->push_back(1);	de->push_back(4);	de->push_back(6);
	de->push_back(4);	de->push_back(7);	de->push_back(6);
	de->push_back(7);	de->push_back(8);	de->push_back(6);
	de->push_back(8);	de->push_back(1);	de->push_back(6);
	de->push_back(2);	de->push_back(1);	de->push_back(9);
	de->push_back(1);	de->push_back(8);	de->push_back(9);
	de->push_back(8);	de->push_back(10);	de->push_back(9);
	de->push_back(10);	de->push_back(2);	de->push_back(9);
	de->push_back(5);	de->push_back(2);	de->push_back(11);
	de->push_back(2);	de->push_back(10);	de->push_back(11);
	de->push_back(10);	de->push_back(12);	de->push_back(11);
	de->push_back(12);	de->push_back(5);	de->push_back(11);
	de->push_back(10);	de->push_back(8);	de->push_back(13);
	de->push_back(8);	de->push_back(7);	de->push_back(13);
	de->push_back(7);	de->push_back(12);	de->push_back(13);
	de->push_back(12);	de->push_back(10);	de->push_back(13);
	de->push_back(4);	de->push_back(5);	de->push_back(14);
	de->push_back(5);	de->push_back(12);	de->push_back(14);
	de->push_back(12);	de->push_back(7);	de->push_back(14);
	de->push_back(7);	de->push_back(4);	de->push_back(14);

	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	geom->setVertexArray(vertices.get());
	geom->addPrimitiveSet(de.get());
	osgUtil::SmoothingVisitor::smooth(*geom);

	osg::ref_ptr<osg::Geode> root = new osg::Geode;
	root->addDrawable(geom.get());
	osgViewer::Viewer viewer;
	viewer.setSceneData(root.get());
	return viewer.run();
}


//=======================================================================
using namespace std;
using namespace osg;

#include <ctime>
#include <string>

void splitString(string vecstrSplitData[4], std::string & astrName, const std::string & astrDelimiters, const std::string & astrComp)	{
	int indexCh = 0;
	int iI = 0;
	while (indexCh != std::string::npos) {
		indexCh = astrName.find_first_of(astrDelimiters);
		string strTmp = astrName.substr(0,indexCh);
		if(iI < 4) {
			vecstrSplitData[iI] = strTmp;
		}
		astrName.erase(0, indexCh+1);
		iI++;
		}
};

int main_Z(int argc, char * argv[])	{
//	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();
//	osg::ref_ptr<osg::DrawElementsUInt> de = new osg::DrawElementsUInt(GL_TRIANGLES);

//	vertices->push_back(osg::Vec3d(0,0,0));

	std::string strFile="C:/Users/Gregi_Laptop/Downloads/staircase.obj";
	
	std::cout << std::time(NULL) << std::endl;
	/*for(int i = 0; i < 100; i++)
	{

		std::ifstream input(strFile);

		std::string strLine;
		while (std::getline(input, strLine))	{
			if (strLine=="")
				continue;
		}
		input.close();

	}*/
	time_t t1 = std::time(NULL);
	for(int i = 0; i < 1; i++)
	{
		osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();
		osg::ref_ptr<osg::DrawElementsUInt> de = new osg::DrawElementsUInt(GL_TRIANGLES);

		std::ifstream input(strFile);

		std::string strLine;
		while (std::getline(input, strLine))	{
			if (strLine=="")
				continue;
			string vecstrSplitData[4];
			string strComp = strLine.substr(0,2);
			splitString(vecstrSplitData, strLine," ",strComp);
			if (vecstrSplitData[0].compare("v") == 0)	{
				vertices->push_back(osg::Vec3d(stof(vecstrSplitData[1]), stof(vecstrSplitData[2]), stof(vecstrSplitData[3])));
			} else if (vecstrSplitData[0].compare("f") == 0)	{
				de->push_back(stoi(vecstrSplitData[1]));
				de->push_back(stoi(vecstrSplitData[2]));
				de->push_back(stoi(vecstrSplitData[3]));
			}
		}
		input.close();
	}
	time_t t2 = std::time(NULL);

	std::cout << t1 << std::endl;
	std::cout << t2 << std::endl;
	

	//osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	//geom->setVertexArray(vertices.get());
	//geom->addPrimitiveSet(de.get());
	//osgUtil::SmoothingVisitor::smooth(*geom);

	//osg::ref_ptr<osg::Geode> root = new osg::Geode;
	//root->addDrawable(geom.get());
	osgViewer::Viewer viewer;
	//viewer.setSceneData(root.get());

	return viewer.run();
}

//==================================================================

#include <iterator>

int main_Fastest(int argc, char * argv[])	{
	//osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();
	//osg::ref_ptr<osg::DrawElementsUInt> de = new osg::DrawElementsUInt(GL_TRIANGLES);

	//vertices->push_back(Vec3d(0,0,0));

	std::string strFile="C:/Users/Gregi_Laptop/Downloads/staircase.obj";
	
	time_t t1 = std::time(NULL);
	for(int i = 0; i < 10; i++)	{
		osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array();
		osg::ref_ptr<osg::DrawElementsUInt> de = new osg::DrawElementsUInt(GL_TRIANGLES);

		std::ifstream input(strFile);

		std::string strLine;
		while (std::getline(input, strLine))	{
			if (strLine == "") continue;
			string strType = strLine.substr(0,2);
			
			char* pchLine =  &strLine[0];
			strtok(pchLine, " ");

			if (strType.compare("v ") == 0)	{
				vertices->push_back(Vec3d(atof(strtok(NULL, " ")),atof(strtok(NULL, " ")),atof(strtok(NULL, " "))));
			} else if (strType.compare("f ") == 0)	{
				int nDe[3];
				for (int i=0;i<3;i++)	{
					nDe[i]=atoi(strtok(NULL, " "));
					de->push_back(nDe[i]);
				}
			}
			//delete [] pchLine;
		}
		input.close();
	}
	time_t t2 = std::time(NULL);

	std::cout << t1 << std::endl;
	std::cout << t2 << std::endl;
	

	//osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	//geom->setVertexArray(vertices.get());
	//geom->addPrimitiveSet(de.get());
	//osgUtil::SmoothingVisitor::smooth(*geom);

	//osg::ref_ptr<osg::Geode> root = new osg::Geode;
	//root->addDrawable(geom.get());
	osgViewer::Viewer viewer;
	//viewer.setSceneData(root.get());

	return viewer.run();
}

//=============================================================

bool isAtEndOfString(const std::string & astrName, const std::string & astrField)	{
	//int nDataSize = astrField.size();
	//int nNameSize = astrName.size();
	//char * pchStr = new char[nDataSize+1];
	//char * chStr = &astrName[0];
	//int nchStr = sizeof(chStr);

	int nDataSize = astrField.size();
	int nNameSize = astrName.size();
	char * pchStr = new char[nDataSize+1];
	memcpy(pchStr, &astrName[0] + sizeof(char)*(nNameSize-nDataSize), sizeof(char)*(nDataSize+1));

	bool bRes = (strcmp(pchStr, astrField.c_str()) == 0);
	delete [] pchStr;

	return bRes;
}

int main(int argc, char * argv[])	{
	string str = "text.db";
	string end = ".db";

	bool bRes = isAtEndOfString(str,end);

	cout << str << " " << bRes << endl;

	return 0;
}