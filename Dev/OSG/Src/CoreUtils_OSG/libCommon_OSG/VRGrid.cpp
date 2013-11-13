#include <osg/Geometry>
#include <osg/PolygonMode>
#include <osg/MatrixTransform>

#include "VRGrid.h"

using namespace osg;
using namespace VR;

GridParams::GridParams() :
m_nResLat(20),
	m_nResLong(30),
	m_flSpacing(0.5),
	m_dbStartCenter(0,0,0)	{
};

//-----------------------------------------------------------

VR::Grid::Grid()	{
	const GridParams gridParams;
	init(gridParams);
}

//-----------------------------------------------------------

VR::Grid::Grid(const GridParams & aGridParams)	{
	init(aGridParams);
}

//-----------------------------------------------------------

void VR::Grid::init(const GridParams & aGridParams)	{
	Vec3d dbCenter(aGridParams.m_dbStartCenter);
	int nNumColumns(aGridParams.m_nResLat);
	int nNumRows(aGridParams.m_nResLong);
	float step = aGridParams.m_flSpacing;

	int nNumPointsCol = 2 * (nNumColumns + 1);
	ref_ptr<Vec3Array> pPointsColumns = new Vec3Array(nNumPointsCol);

	osg::Vec3d point = (dbCenter - osg::Vec3d(step * nNumColumns/2,dbCenter.y(),0.0));
	int nI;
	for (nI = 0; nI < nNumColumns+1; nI++)	{
		(*pPointsColumns)[2*nI].set(point.x()+nI*step, point.y(), 0.0);
		(*pPointsColumns)[2*nI+1].set(point.x()+nI*step, point.y()+step*nNumRows, 0.0);
	}
	(*pPointsColumns)[nNumPointsCol-1].set(point.x()+(nNumColumns)*step, point.y()+step*nNumRows, 0.0);

	int nNumPointsRows = 2 * (nNumRows + 1);
	ref_ptr<Vec3Array> pPointsRows = new Vec3Array(nNumPointsRows);

	for (nI = 0; nI < nNumRows+1; nI++)	{
		(*pPointsRows)[2*nI].set(point.x(), point.y()+nI*step, 0.0);
		(*pPointsRows)[2*nI+1].set(point.x()+step*nNumColumns, point.y()+nI*step, 0.0);
	}
	(*pPointsRows)[nNumPointsRows-1].set(point.x()+step*(nNumColumns), point.y()+nNumRows*step, 0.0);

	//Set color of the bounding box
	osg::ref_ptr<osg::Vec4Array> pColor = new osg::Vec4Array;
	pColor->push_back(osg::Vec4(1,1,1,1));

	//Send points to the geometry
	osg::ref_ptr<osg::Geometry> pGeometry = new osg::Geometry;
	pGeometry->setVertexArray(pPointsColumns);
	pGeometry->setColorArray(pColor.get());
	pGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
	pGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, nNumPointsCol));	

	//Send points to the geometry
	osg::ref_ptr<osg::Geometry> pGeometry1 = new osg::Geometry;
	pGeometry1->setVertexArray(pPointsRows);
	pGeometry1->setColorArray(pColor.get());
	pGeometry1->setColorBinding(osg::Geometry::BIND_OVERALL);
	pGeometry1->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, nNumPointsRows));	

	ref_ptr<Vec3Array> pN = new Vec3Array;
	pN->push_back(Vec3(0.0, -1.0, 0.0));
	pGeometry->setNormalArray(pN.get());
	pGeometry->setNormalBinding(Geometry::BIND_OVERALL);
	pGeometry1->setNormalArray(pN.get());
	pGeometry1->setNormalBinding(Geometry::BIND_OVERALL);

	ref_ptr<Geode> pGeode = new Geode;
	pGeode->addDrawable(pGeometry.get());
	pGeode->addDrawable(pGeometry1.get());
	osg::StateSet* ss = pGeode->getOrCreateStateSet();
	ss->setAttributeAndModes(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE));

	this->addChild(pGeode);
}