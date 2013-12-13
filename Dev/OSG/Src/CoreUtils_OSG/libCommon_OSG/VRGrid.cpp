#include <osg/Geometry>
#include <osg/PolygonMode>
#include <osg/MatrixTransform>

#include "VRGrid.h"

using namespace osg;
using namespace VR;

GridParams::GridParams() :
	m_nResLat(5),
	m_nResLong(5),
	m_flSpacing(0.5),
	m_vec3dStartCenter(0,0,0)	{
};

//-----------------------------------------------------------

VR::Grid::Grid()	{
	const GridParams gridParams;
	init(gridParams);
	setName("Grid");
}

//-----------------------------------------------------------

VR::Grid::Grid(const GridParams & aGridParams)	{
	init(aGridParams);
	setName("Grid");
}

//-----------------------------------------------------------

void VR::Grid::init(const GridParams & aGridParams)	{
	Vec3d vec3dCenter(aGridParams.m_vec3dStartCenter);
	int nNumColumns(aGridParams.m_nResLat);
	int nNumRows(aGridParams.m_nResLong);
	float flStep = aGridParams.m_flSpacing;

	int nNumPointsCol = nNumColumns;
	ref_ptr<Vec3Array> pPointsColumns = new Vec3Array(2 * nNumPointsCol);

	osg::Vec3d point = (vec3dCenter - osg::Vec3d(flStep * (nNumColumns/2),flStep * (nNumRows/2),0.0));
	int nI;
	for (nI = 0; nI < nNumColumns; nI++)	{
		(*pPointsColumns)[2*nI].set(point.x()+nI*flStep, point.y(), 0.0);
		(*pPointsColumns)[2*nI+1].set(point.x()+nI*flStep, point.y()+flStep*(nNumRows - 1), 0.0);
	}
	//(*pPointsColumns)[nNumPointsCol-1].set(point.x()+(nNumColumns)*flStep, point.y()+flStep*nNumRows, 0.0);

	int nNumPointsRows = nNumRows;
	ref_ptr<Vec3Array> pPointsRows = new Vec3Array(2 * nNumPointsRows);

	for (nI = 0; nI < nNumRows; nI++)	{
		(*pPointsRows)[2*nI].set(point.x(), point.y()+nI*flStep, 0.0);
		(*pPointsRows)[2*nI+1].set(point.x()+flStep*(nNumColumns - 1), point.y()+nI*flStep, 0.0);
	}
	//(*pPointsRows)[nNumPointsRows-1].set(point.x()+(nNumColumns)*flStep, point.y()+flStep*nNumRows, 0.0);

	//Set color of the bounding box
	osg::ref_ptr<osg::Vec4Array> pColor = new osg::Vec4Array;
	pColor->push_back(osg::Vec4(1,1,1,1));

	//Send points to the geometry
	osg::ref_ptr<osg::Geometry> pGeometry = new osg::Geometry;
	pGeometry->setVertexArray(pPointsColumns);
	pGeometry->setColorArray(pColor.get());
	pGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
	pGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2 * nNumPointsCol));	

	ref_ptr<Vec3Array> pN = new Vec3Array;
	pN->push_back(Vec3(0.0, -1.0, 0.0));
	pGeometry->setNormalArray(pN.get());
	pGeometry->setNormalBinding(Geometry::BIND_OVERALL);
	ref_ptr<Geode> pGeode = new Geode;
	pGeode->addDrawable(pGeometry.get());


	//Send points to the geometry
	pGeometry = new osg::Geometry;
	pGeometry->setVertexArray(pPointsRows);
	pGeometry->setColorArray(pColor.get());
	pGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);
	pGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, 2 * nNumPointsRows));	

	pGeometry->setNormalArray(pN.get());
	pGeometry->setNormalBinding(Geometry::BIND_OVERALL);
	pGeode->addDrawable(pGeometry.get());

	osg::StateSet* ss = pGeode->getOrCreateStateSet();
	ss->setAttributeAndModes(new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE));

	addChild(pGeode);
}