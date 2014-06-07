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
									pTKFC_Vec3f->erase(pTKFC_Vec3f->begin(), pTKFC_Vec3f->begin() + m_nKeyFrameFrom - 1);
									pTKFC_Vec3f->erase(pTKFC_Vec3f->begin() + m_nKeyFrameTo + 1, pTKFC_Vec3f->end());
								}
							}

							{
								osgAnimation::TemplateKeyframeContainer<osg::Quat> *pTKFC_Quat =
									dynamic_cast<osgAnimation::TemplateKeyframeContainer<osg::Quat> *>(pKFC);
								if((pTKFC_Quat != 0) && (pTKFC_Quat->size() > 199)) {
									pTKFC_Quat->erase(pTKFC_Quat->begin(), pTKFC_Quat->begin() + m_nKeyFrameFrom - 1);
									pTKFC_Quat->erase(pTKFC_Quat->begin() + m_nKeyFrameTo + 1, pTKFC_Quat->end());

								}
							}
					}		
			}
			return;
	    }
        traverse(node);
    }
}