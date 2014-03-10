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

#ifndef VR_SEARCH_LIST_CONTROLLER_H
#define VR_SEARCH_LIST_CONTROLLER_H

#include <QObject>

#include "VRScene.h"

namespace VR {
	class PickAndDragHandlerShopEditor;
	
	struct SearchListController : public QObject {

		SearchListController(
			QString & astrSelectedItemName,
			PickAndDragHandlerShopEditor * a_pPickAndDragHandlerShopEditor,
			osg::ref_ptr<Scene> a_pScene);	//End of constructor

		void updateSearchListGUI();

	private:
		Q_OBJECT

		QString m_strSelectedItemName;
		PickAndDragHandlerShopEditor * mpPickAndDragHandlerShopEditor;
		osg::ref_ptr<Scene> mp_Scene;
	};
}
#endif //VR_SEARCH_LIST_CONTROLLER_H