/*  -*-c++-*-
 *  Copyright (C) 2008 Cedric Pinson <mornifle@plopbyte.net>
 *
 * This library is open source and may be redistributed and/or modified under
 * the terms of the OpenSceneGraph Public License (OSGPL) version 0.0 or
 * (at your option) any later version.  The full license is in LICENSE file
 * included with this distribution, and on the openscenegraph.org website.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * OpenSceneGraph Public License for more details.
 *
 * Authors:
 * Cedric Pinson <mornifle@plopbyte.net>
 * jeremy Moles <jeremy@emperorlinux.com>
*/

#include "AnimtkViewerKeyHandler"
#include "AnimtkViewerGUI"

#include <iostream>
#include <osg/io_utils>
#include <osg/Geometry>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgWidget/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgDB/ReadFile>
#include <osgDB/writeFile>
#include <osgAnimation/AnimationManagerBase>
#include <osgAnimation/Bone>

const int WIDTH  = 1440;
const int HEIGHT = 900;


osg::Geode* createAxis()
{
    osg::Geode*     geode    = new osg::Geode();
    osg::Geometry*  geometry = new osg::Geometry();
    osg::Vec3Array* vertices = new osg::Vec3Array();
    osg::Vec4Array* colors   = new osg::Vec4Array();

    vertices->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(0.0f, 1.0f, 0.0f));
    vertices->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
    vertices->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));

    colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
    colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
    colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
    colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
    colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
    colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));

    geometry->setVertexArray(vertices);
    geometry->setColorArray(colors, osg::Array::BIND_PER_VERTEX);
    geometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 6));
    geometry->getOrCreateStateSet()->setMode(GL_LIGHTING, false);

    geode->addDrawable(geometry);

    return geode;
}


struct AnimationManagerFinder : public osg::NodeVisitor
{
    osg::ref_ptr<osgAnimation::BasicAnimationManager> _am;
    AnimationManagerFinder() : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) {}
    void apply(osg::Node& node) {
        if (_am.valid())
            return;
        if (node.getUpdateCallback()) {
            osgAnimation::AnimationManagerBase* b = dynamic_cast<osgAnimation::AnimationManagerBase*>(node.getUpdateCallback());
			if (b) {
				_am = new osgAnimation::BasicAnimationManager(*b);
				const osgAnimation::AnimationList & pAL = b->getAnimationList();
				for(osgAnimation::AnimationList::const_iterator citAL = pAL.begin();
					citAL != pAL.end();
					citAL++) {

						osgAnimation::ChannelList & channelList = (*citAL)->getChannels();
						for(osgAnimation::ChannelList::iterator itCL = channelList.begin();
							itCL != channelList.end();
							itCL++) {
								osgAnimation::Sampler * pSampler = (*itCL)->getSampler();
								osgAnimation::KeyframeContainer * pKFC = pSampler->getKeyframeContainer();

								{
									osgAnimation::TemplateKeyframeContainer<osg::Vec3f> *pTKFC_Vec3f =
										dynamic_cast<osgAnimation::TemplateKeyframeContainer<osg::Vec3f> *>(pKFC);
									if((pTKFC_Vec3f != 0) && (pTKFC_Vec3f->size() > 199)) {
										pTKFC_Vec3f->erase(pTKFC_Vec3f->begin()+110, pTKFC_Vec3f->end());
									}
								}
								{

									osgAnimation::TemplateKeyframeContainer<osg::Quat> *pTKFC_Quat =
										dynamic_cast<osgAnimation::TemplateKeyframeContainer<osg::Quat> *>(pKFC);
									if((pTKFC_Quat != 0) && (pTKFC_Quat->size() > 199)) {
										pTKFC_Quat->erase(pTKFC_Quat->begin()+110, pTKFC_Quat->end());
									}
								}
						}		
				}

//				osgDB::writeNodeFile(node,"C:/Matej/test.osg");
                return;
            }
        }
        traverse(node);
    }
};

struct AddHelperBone : public osg::NodeVisitor
{
    AddHelperBone() : osg::NodeVisitor(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN) {}
    void apply(osg::Transform& node) {
        osgAnimation::Bone* bone = dynamic_cast<osgAnimation::Bone*>(&node);
        if (bone)
            bone->addChild(createAxis());
        traverse(node);
    }
};

int main_(int argc, char** argv)
{
    osg::ArgumentParser arguments(&argc, argv);
    arguments.getApplicationUsage()->setApplicationName(arguments.getApplicationName());
    arguments.getApplicationUsage()->setDescription(arguments.getApplicationName()+" is an example for viewing osgAnimation animations.");
    arguments.getApplicationUsage()->addCommandLineOption("-h or --help","List command line options.");
    arguments.getApplicationUsage()->addCommandLineOption("--drawbone","draw helps to display bones.");

    if (arguments.read("-h") || arguments.read("--help"))
    {
        arguments.getApplicationUsage()->write(std::cout, osg::ApplicationUsage::COMMAND_LINE_OPTION);
        return 0;
    }

    if (arguments.argc()<=1)
    {
        arguments.getApplicationUsage()->write(std::cout, osg::ApplicationUsage::COMMAND_LINE_OPTION);
        return 1;
    }

    bool drawBone = false;
    if (arguments.read("--drawbone"))
        drawBone = true;

    osgViewer::Viewer viewer(arguments);
    osg::ref_ptr<osg::Group> group = new osg::Group();

    osg::Group* node = dynamic_cast<osg::Group*>(osgDB::readNodeFile("C:/Matej/test_1.osg"));
		//dynamic_cast<osg::Group*>(osgDB::readNodeFiles(arguments)); //dynamic_cast<osgAnimation::AnimationManager*>(osgDB::readNodeFile(psr[1]));
    if(!node)
    {
        std::cout << arguments.getApplicationName() <<": No data loaded" << std::endl;
        return 1;
    }

    // Set our Singleton's model.
    AnimationManagerFinder finder;
    node->accept(finder);
    if (finder._am.valid()) {
        node->setUpdateCallback(finder._am.get());
        AnimtkViewerModelController::setModel(finder._am.get());

		osgAnimation::BasicAnimationManager* model = finder._am.get();
		const osgAnimation::AnimationList & lstAnimation = model->getAnimationList();
		const osg::ref_ptr<osgAnimation::Animation> & canim = *(lstAnimation.begin());
		osg::ref_ptr<osgAnimation::Animation> & anim = const_cast<osg::ref_ptr<osgAnimation::Animation> &>(canim);
		//anim->setDuration(0.1);
	} else {
        osg::notify(osg::WARN) << "no osgAnimation::AnimationManagerBase found in the subgraph, no animations available" << std::endl;
    }

    if (drawBone) {
        osg::notify(osg::INFO) << "Add Bones Helper" << std::endl;
        AddHelperBone addHelper;
        node->accept(addHelper);
    }
    node->addChild(createAxis());

    AnimtkViewerGUI* gui    = new AnimtkViewerGUI(&viewer, WIDTH, HEIGHT, 0x1234);
    osg::Camera*     camera = gui->createParentOrthoCamera();

    node->setNodeMask(0x0001);

    group->addChild(node);
    group->addChild(camera);

    viewer.addEventHandler(new AnimtkKeyEventHandler());
    viewer.addEventHandler(new osgViewer::StatsHandler());
    viewer.addEventHandler(new osgViewer::WindowSizeHandler());
    viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
    viewer.addEventHandler(new osgWidget::MouseHandler(gui));
    viewer.addEventHandler(new osgWidget::KeyboardHandler(gui));
    viewer.addEventHandler(new osgWidget::ResizeHandler(gui, camera));
    viewer.setSceneData(group.get());

    viewer.setUpViewInWindow(40, 40, WIDTH, HEIGHT);

    return viewer.run();
}

#include "osg/Group"

void cutSimulation(osg::Node* apNode) {
	osg::Group * pGroup = dynamic_cast<osg::Group *>(apNode);
	if(pGroup != NULL) {
		int nChildrenNr = pGroup->getNumChildren();
		int nIndxChild;
		for(nIndxChild = 0; nIndxChild < nChildrenNr; nIndxChild++) {
			osg::Node* pNode = pGroup->getChild(nIndxChild);
			cutSimulation(pNode);
		}
	} else {
		//osg::NodeVisitor * pNV = dynamic_cast<osg::NodeVisitor *>(apNode);
		/*if(pNV != NULL) {
			int indy = 1;
		}*/
	}
}


int main(int argc, char** argv)
{
    osg::ArgumentParser arguments(&argc, argv);
    arguments.getApplicationUsage()->setApplicationName(arguments.getApplicationName());
    arguments.getApplicationUsage()->setDescription(arguments.getApplicationName()+" is an example for viewing osgAnimation animations.");
    arguments.getApplicationUsage()->addCommandLineOption("-h or --help","List command line options.");
    arguments.getApplicationUsage()->addCommandLineOption("--drawbone","draw helps to display bones.");

    if (arguments.read("-h") || arguments.read("--help"))
    {
        arguments.getApplicationUsage()->write(std::cout, osg::ApplicationUsage::COMMAND_LINE_OPTION);
        return 0;
    }

    //if (arguments.argc()<=1)
    //{
    //    arguments.getApplicationUsage()->write(std::cout, osg::ApplicationUsage::COMMAND_LINE_OPTION);
    //    return 1;
    //}

    bool drawBone = true;
    if (arguments.read("--drawbone"))
        drawBone = true;

    osgViewer::Viewer viewer(arguments);
    osg::ref_ptr<osg::Group> group = new osg::Group();

    osg::Group* node = dynamic_cast<osg::Group*>(osgDB::readNodeFile("C:/Matej/test_1.osg"));
		//dynamic_cast<osg::Group*>(osgDB::readNodeFiles(arguments)); //dynamic_cast<osgAnimation::AnimationManager*>(osgDB::readNodeFile(psr[1]));
    if(!node)
    {
        std::cout << arguments.getApplicationName() <<": No data loaded" << std::endl;
        return 1;
    }

	cutSimulation(node);

    // Set our Singleton's model.
    AnimationManagerFinder finder;
    node->accept(finder);
    if (finder._am.valid()) {
        node->setUpdateCallback(finder._am.get());
        AnimtkViewerModelController::setModel(finder._am.get());

		osgAnimation::BasicAnimationManager* model = finder._am.get();
		const osgAnimation::AnimationList & lstAnimation = model->getAnimationList();
		const osg::ref_ptr<osgAnimation::Animation> & canim = *(lstAnimation.begin());
		osg::ref_ptr<osgAnimation::Animation> & anim = const_cast<osg::ref_ptr<osgAnimation::Animation> &>(canim);

	} else {
        osg::notify(osg::WARN) << "no osgAnimation::AnimationManagerBase found in the subgraph, no animations available" << std::endl;
    }

    if (drawBone) {
        osg::notify(osg::INFO) << "Add Bones Helper" << std::endl;
        AddHelperBone addHelper;
        node->accept(addHelper);
    }
    node->addChild(createAxis());

    AnimtkViewerGUI* gui    = new AnimtkViewerGUI(&viewer, WIDTH, HEIGHT, 0x1234);
    osg::Camera*     camera = gui->createParentOrthoCamera();

    node->setNodeMask(0x0001);

    group->addChild(node);
    group->addChild(camera);

    viewer.addEventHandler(new AnimtkKeyEventHandler());
    viewer.addEventHandler(new osgViewer::StatsHandler());
    viewer.addEventHandler(new osgViewer::WindowSizeHandler());
    viewer.addEventHandler(new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()));
    viewer.addEventHandler(new osgWidget::MouseHandler(gui));
    viewer.addEventHandler(new osgWidget::KeyboardHandler(gui));
    viewer.addEventHandler(new osgWidget::ResizeHandler(gui, camera));
    //viewer.setSceneData(group.get());

    viewer.setUpViewInWindow(40, 40, WIDTH, HEIGHT);

	 // Create the root node Group.
	osg::ref_ptr<osg::Group> root = new osg::Group;
	// Read the object
	//osg::ref_ptr<osg::Node> cow = osgDB::readNodeFile( "D:/Programs64/OSG/Data/OpenSceneGraph-Data-3.0.0/cow.osg" );
	// Define a matrix transform 
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
	// Set scene graph
	mt->addChild(group);
	root->addChild(mt);

	// Create animation path
	osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath;
	
	// Define control points
	osg::AnimationPath::ControlPoint CP0(osg::Vec3( 0.f, 5.f, 0.f ));
	osg::AnimationPath::ControlPoint CP1(osg::Vec3( -2.5f, -2.5f, 0.f ),osg::Quat(-osg::PI/4,osg::Vec3( 0.f, 0.f, 1.f ))
		);
	//osg::AnimationPath::ControlPoint CP2 (osg::Vec3( -2.f, -1.f, 0.f ),osg::Quat(-osg::PI*2/6,osg::Vec3( 0.f, 0.f, 1.f )),osg::Vec3( 0.5f, 0.5f, 0.5f ));
	//osg::AnimationPath::ControlPoint CP3 (osg::Vec3( 2.f, -1.f, 0.f ),osg::Quat(-osg::PI*3/6,osg::Vec3( 0.f, 0.f, 1.f )));
	//osg::AnimationPath::ControlPoint CP4 (osg::Vec3( 2.f, 1.f, 0.f ));

	// Insert them to the path
	path->insert( 0.0f, CP0 ); // time, point
	path->insert( 1.0f, CP1 );
	//path->insert( 2.0f, CP2 );
	//path->insert( 3.0f, CP3 );
	//path->insert( 4.0f, CP4 );	
	//path->setLoopMode(osg::AnimationPath::LoopMode::SWING);

	// Define animation path callback
	osg::ref_ptr<osg::AnimationPathCallback> APCallback = new osg::AnimationPathCallback(path.get() );
	
	// Update the matrix transform
	mt->setUpdateCallback( APCallback.get() );

	viewer.setSceneData(root.get());

    return viewer.run();
}

////

#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgUtil/PolytopeIntersector>
#include <osg/Camera>
#include <osg/NodeCallback>
#include <osg/Group>
#include <osg/MatrixTransform>
#include <iostream>
#include <osg/Notify>
#include <osg/AnimationPath>

int main__(int argc, char * argv[])
{
    // Create the root node Group.
	osg::ref_ptr<osg::Group> root = new osg::Group;
	// Read the object
	osg::ref_ptr<osg::Node> cow = osgDB::readNodeFile( "D:/Programs64/OSG/Data/OpenSceneGraph-Data-3.0.0/cow.osg" );
	// Define a matrix transform 
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
	// Set scene graph
	mt->addChild(cow);
	root->addChild(mt);

	// Create animation path
	osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath;
	
	// Define control points
	osg::AnimationPath::ControlPoint CP0(osg::Vec3( 2.f, -1.f, 0.f ));
	osg::AnimationPath::ControlPoint CP1(osg::Vec3( 2.f, 1.f, 0.f )//,osg::Quat(-osg::PI/6,osg::Vec3( 0.f, 0.f, 1.f ))
		);
	//osg::AnimationPath::ControlPoint CP2 (osg::Vec3( -2.f, -1.f, 0.f ),osg::Quat(-osg::PI*2/6,osg::Vec3( 0.f, 0.f, 1.f )),osg::Vec3( 0.5f, 0.5f, 0.5f ));
	//osg::AnimationPath::ControlPoint CP3 (osg::Vec3( 2.f, -1.f, 0.f ),osg::Quat(-osg::PI*3/6,osg::Vec3( 0.f, 0.f, 1.f )));
	//osg::AnimationPath::ControlPoint CP4 (osg::Vec3( 2.f, 1.f, 0.f ));

	// Insert them to the path
	path->insert( 0.0f, CP0 ); // time, point
	path->insert( 1.0f, CP1 );
	//path->insert( 2.0f, CP2 );
	//path->insert( 3.0f, CP3 );
	//path->insert( 4.0f, CP4 );	
	//path->setLoopMode(osg::AnimationPath::LoopMode::SWING);

	// Define animation path callback
	osg::ref_ptr<osg::AnimationPathCallback> APCallback = new osg::AnimationPathCallback(path.get() );
	
	// Update the matrix transform
	mt->setUpdateCallback( APCallback.get() );

	// create the view of the scene.
    osgViewer::Viewer viewer;
    viewer.setSceneData( root.get() );

    return( viewer.run() );
}
