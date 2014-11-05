#include <osgViewer/Viewer>
#include <osg/MatrixTransform>

#include "Model2D.h"
#include "Model3D.h"

#include "VRBoundingBox.h"


#include "VRGrid.h"

#include <osgDB/readFile>

void main_Model2D(osg::ref_ptr<osg::Group> pScene)	{
	osg::ref_ptr<Model2D> pModel2D = new Model2D();
	pModel2D->setColor(osg::Vec4(1.0, 0.0, 0.0, 1.0));
	pScene->addChild(pModel2D);
}

bool computeClosestPointOnLine(const osg::Vec3d& lineStart, const osg::Vec3d& lineEnd,
                               const osg::Vec3d& fromPoint, osg::Vec3d& closestPoint)
{
    osg::Vec3d v = lineEnd - lineStart;
    osg::Vec3d w = fromPoint - lineStart;

    double c1 = w * v;
    double c2 = v * v;

    double almostZero = 0.000001;
    if (c2 < almostZero) return false;

    double b = c1 / c2;
    closestPoint = lineStart + v * b;

    return true;
}

//----------------------------------------------------------------------

void main_Model3D(osg::ref_ptr<osg::Group> pScene)	{
	osg::ref_ptr<Model3D> pModel3D = new Model3D();
	pModel3D->setColor(osg::Vec4(0.0, 1.0, 0.0, 1.0));
	pModel3D->setIsTargetPick(true);

	osg::ref_ptr<VR::BoundingBox> bb = new VR::BoundingBox(pModel3D);

	pScene->addChild(bb);
	pScene->addChild(pModel3D.get());
}

//----------------------------------------------------------------------

int main(int argc, char * argv[])	{
	osg::Vec3d closestPoint;
	computeClosestPointOnLine(osg::Vec3d(0,0,0), osg::Vec3d(2,0,0), osg::Vec3d(1,2,0), closestPoint);



	osg::ref_ptr<osg::Node> axes = osgDB::readNodeFile( "../../Resources/axes.osgt");

	osg::ref_ptr<Model3D> pModel3D = new Model3D();
	pModel3D->setColor(osg::Vec4(0.0, 1.0, 0.0, 1.0));
	pModel3D->setIsTargetPick(true);

	osg::ref_ptr<Model2D> pModel2D = new Model2D();
	pModel2D->setColor(osg::Vec4(1.0, 0.0, 0.0, 1.0));
	pModel2D->setIsTargetPick(true);

	osg::ref_ptr<osg::Group> root = new osg::Group;

	osg::ref_ptr<osg::MatrixTransform > pMt = new osg::MatrixTransform;
	pMt->addChild(pModel3D);
	pMt->setMatrix(osg::Matrix::rotate(-20,osg::Z_AXIS));

	osg::ref_ptr<VR::BoundingBox> bb = new VR::BoundingBox(pMt);
	root->addChild(bb);

//	root->addChild(new VR::Grid);
	root->addChild(pMt);
	root->addChild(axes);

	osgViewer::Viewer viewer;
	viewer.setSceneData( root.get() );

	return viewer.run();
}

