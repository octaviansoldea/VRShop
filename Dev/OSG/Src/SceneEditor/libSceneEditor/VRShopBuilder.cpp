#include <osgDB/ReadFile>

#include "VRGrid.h"
#include "VRShopBuilder.h"

using namespace osg;
using namespace VR;

//----------------------------------------------------------------------

ShopBuilder::ShopBuilder() {	

	//Define a scene as a group
	m_pScene = new Group;

	ref_ptr<Node> pAxes = osgDB::readNodeFile("../../../Resources/Models3D/axes.osgt");
	m_pScene->addChild(pAxes);
//	m_pScene->addChild(new Grid);
}
