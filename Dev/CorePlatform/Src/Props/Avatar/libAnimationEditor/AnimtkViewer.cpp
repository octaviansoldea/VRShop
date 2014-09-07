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

#include "AnimtkViewerKeyHandler.h"
#include "AnimtkViewerGUI.h"

#include <iostream>
#include <string>
#include <osg/io_utils>
#include <osg/Geometry>
#include <osg/MatrixTransform>
#include <osg/Geode>
#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>
#include <osgWidget/ViewerEventHandlers>
#include <osgGA/TrackballManipulator>
#include <osgGA/StateSetManipulator>
#include <osgAnimation/AnimationManagerBase>
#include <osgAnimation/Bone>

using namespace std;
using namespace osg;

AnimationManagerFinder::AnimationManagerFinder() : 
NodeVisitor(NodeVisitor::TRAVERSE_ALL_CHILDREN), m_nKeyFrameFrom(0), m_nKeyFrameTo(0) {
}

//----------------------------------------------------------------------------------------

AnimationManagerFinder::AnimationManagerFinder(int anKeyFrameFrom, int anKeyFrameTo) : 
NodeVisitor(NodeVisitor::TRAVERSE_ALL_CHILDREN), m_nKeyFrameFrom(anKeyFrameFrom), m_nKeyFrameTo(anKeyFrameTo) {
}

//============================================================================

void AnimationManagerFinder::apply(Node& node)	{
	if (_am.valid())
	    return;
	
	if (node.getUpdateCallback()) {
		osgAnimation::AnimationManagerBase* b = dynamic_cast<osgAnimation::AnimationManagerBase*>(node.getUpdateCallback());
		if (b) {
			_am = new osgAnimation::BasicAnimationManager(*b);
			return;
	    }
        traverse(node);
    }
}