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
#include <osgDB/ReadFile>
#include <osgDB/writeFile>
#include <osgAnimation/AnimationManagerBase>
#include <osgAnimation/Bone>

using namespace std;
using namespace osg;

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


void AnimationManagerFinder::apply(osg::Node& node)	{
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
//			osgDB::writeNodeFile(node,"C:/Matej/test.osg");
			return;
	    }
        traverse(node);
    }
}