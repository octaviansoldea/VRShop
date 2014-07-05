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

#ifndef VR_SCENE_HIERARCHY_CONTROLLER_H
#define VR_SCENE_HIERARCHY_CONTROLLER_H

#include <QObject>

#include "VRScene.h"

class QTreeView;

namespace VR {
	class PickAndDragHandlerShopEditor;

	struct SceneHierarchyController : public QObject {

		SceneHierarchyController(
			QTreeView * a_pQTreeView,
			PickAndDragHandlerShopEditor * a_pPickAndDragHandlerShopEditor,
			osg::ref_ptr<Scene> a_pScene);	//End of constructor

		void updateSceneHierarchyGUI();

	public slots:
			void slotItemClicked(const QModelIndex & anItemIndex);
			void slotItemDeleted(const QModelIndex & anItemIndex);

	private:
		Q_OBJECT

		QTreeView * m_pQTreeView;
		PickAndDragHandlerShopEditor * mpPickAndDragHandlerShopEditor;
		osg::ref_ptr<Scene> mp_Scene;

	};
}
#endif //VR_SCENE_HIERARCHY_CONTROLLER_H