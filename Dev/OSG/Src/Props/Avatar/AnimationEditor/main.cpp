#include <iostream>
#include <string>

#include <osgDB/ReadFile>
#include <osgDB/writeFile>
#include <osg/AnimationPath>

#include "AnimtkViewer.h"
#include "AnimtkViewerGUI.h"
#include "AnimtkViewerKeyHandler.h"

#include <osgViewer/Viewer>

using namespace std;
using namespace osg;

int main(int argc, char * argv[])	{
    if(argc != 5) {
		cerr << "Usage: " << argv[0] << " InFIle OutFile keyFrameFrom keyFrameTo" << endl;
		exit(-1);
	}

	string strFileIn = argv[1];
	const string strFileOut = argv[2];
	int nKeyFrameFrom = atoi(argv[3]);
	int nKeyFrameTo = atoi(argv[4]);

    osgViewer::Viewer viewer;
    osg::ref_ptr<osg::Group> group = new osg::Group();

    osg::Group* node = dynamic_cast<osg::Group*>(osgDB::readNodeFile(strFileIn));
	if(!node)
    {
        cerr << "No data loaded" << std::endl;
        exit(-1);
    }

    // Set our Singleton's model.
    AnimationManagerFinder finder(nKeyFrameFrom, nKeyFrameTo);
    node->accept(finder);

	//Save edited animation into the new file
	osgDB::writeNodeFile(*node,strFileOut);

	double dbAnimationDuration = 0;
	if (finder._am.valid()) {
		node->setUpdateCallback(finder._am.get());
		AnimtkViewerModelController::setModel(finder._am.get());

		osgAnimation::BasicAnimationManager* model = finder._am.get();
		const osgAnimation::AnimationList & lstAnimation = model->getAnimationList();
		const osg::ref_ptr<osgAnimation::Animation> & canim = *(lstAnimation.begin());
		osg::ref_ptr<osgAnimation::Animation> & anim = const_cast<osg::ref_ptr<osgAnimation::Animation> &>(canim);
		anim->computeDuration();
		dbAnimationDuration = anim->getDuration();
	} else {
		cerr << "no osgAnimation::AnimationManagerBase found in the subgraph, no animations available" << std::endl;
	}

	viewer.addEventHandler(new AnimtkKeyEventHandler());

	// Create the root node Group.
	osg::ref_ptr<osg::Group> root = new osg::Group;
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform;
	mt->addChild(node);
	root->addChild(mt);

	// Create animation path
	osg::ref_ptr<osg::AnimationPath> path = new osg::AnimationPath;
	osg::AnimationPath::ControlPoint CP0(osg::Vec3( 0.f, 5.f, 0.f ));
	osg::AnimationPath::ControlPoint CP1(osg::Vec3( -2.5f, -2.5f, 0.f ),osg::Quat(-osg::PI/4,osg::Vec3( 0.f, 0.f, 1.f )));
	path->insert( 0.0f, CP0 ); // time, point
	path->insert( dbAnimationDuration, CP1 );
	

	// Define animation path callback
	osg::ref_ptr<osg::AnimationPathCallback> APCallback = new osg::AnimationPathCallback(path.get() );
	mt->setUpdateCallback( APCallback.get() );

	viewer.setSceneData(root.get());

	osg::ref_ptr<osg::AnimationPathCallback> apc =
		dynamic_cast<osg::AnimationPathCallback *>(mt->getUpdateCallback());

	osg::AnimationPath * pp = apc->getAnimationPath();
	osg::AnimationPath::ControlPoint CP2(osg::Vec3( -5.f, -5.f, 0.f ),osg::Quat(-osg::PI/4,osg::Vec3( 0.f, 0.f, 1.f )));
	pp->insert( dbAnimationDuration*2,CP2);

	return viewer.run();
}


//Examples of tunning
//C:/Matej/avatar.osg C:/Matej/avatarEdited.osg 0 110
