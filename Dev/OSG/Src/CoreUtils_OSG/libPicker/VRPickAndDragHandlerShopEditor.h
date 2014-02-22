/* -*-c++-*- OpenSceneGraph - Copyright (C) 1998-2006 Robert Osfield
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
*/

#ifndef VR_PICK_AND_DRAG_HANDLER_SHOP_EDITOR_H
#define VR_PICK_AND_DRAG_HANDLER_SHOP_EDITOR_H

#include <QObject>

#include "VRPickAndDragHandler.h"

#include "VRAbstractObject.h"

namespace VR {

	class PickAndDragHandlerShopEditor : public QObject, public PickAndDragHandler	{

		Q_OBJECT

	public:
		PickAndDragHandlerShopEditor();
		virtual bool handle(const osgGA::GUIEventAdapter& ea, osgGA::GUIActionAdapter& aa);

		void setPropertiesPosition(const osg::Vec3d & avec3dPosition);
		void setPropertiesScaling(const osg::Vec3d & avec3dScaling);
		void setPropertiesRotation(const osg::Vec3d & avec3dRotation);

	public slots:
		void slotSetTransformParams(const QString & astrText);

	signals:
		void signalPropertiesSettingsChanged();

	private:
		osg::ref_ptr<AbstractObject> m_pPickedObjects;
		void addPart(osg::ref_ptr < AbstractObject > apAbstractObject);
		void removePart(osg::ref_ptr < AbstractObject > apAbstractObject);
		void clearList();

		std::vector<osg::ref_ptr<AbstractObject>> m_pvecPickedObjects;
	};
}
#endif //VR_PICK_AND_DRAG_HANDLER_SHOP_EDITOR_H