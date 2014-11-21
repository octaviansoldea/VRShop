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

//=====================================================================================

/*
	T* release() { T* tmp=_ptr; if (_ptr) _ptr->unref_nodelete(); _ptr=0; return tmp; }
	T* get() const { return _ptr; }
*/
class MonitoringTarget : public osg::Referenced	{
public:
	MonitoringTarget( int id ) : m_nId(id)	{
		std::cout << "Constructing target " << m_nId << std::endl;
	}

	MonitoringTarget* createMonitoringTarget( unsigned int id );
	osg::ref_ptr<MonitoringTarget> createMonitoringTargetRef( unsigned int id );

	static MonitoringTarget* createMonitoringTargetStatic( unsigned int id );
	static osg::ref_ptr<MonitoringTarget> createMonitoringTargetRefStatic( unsigned int id );

protected:
	virtual ~MonitoringTarget()	{ 
		std::cout << "Destroying target " << m_nId << std::endl; 
	}
	int m_nId;
};

MonitoringTarget* MonitoringTarget::createMonitoringTarget( unsigned int id )
{
	//Fails because ref_ptr is run out of scope before assigning of the return value
	osg::ref_ptr<MonitoringTarget> target = new MonitoringTarget(id);
	return target.get();

	//potential memory leak if the caller can't assign the return value to a ref_ptr<>.
	//MonitoringTarget * target1 = new MonitoringTarget(id);
	//return target1;
}

osg::ref_ptr<MonitoringTarget> MonitoringTarget::createMonitoringTargetRef( unsigned int id )
{
	osg::ref_ptr<MonitoringTarget> target = new MonitoringTarget(id);
	return target;
}

MonitoringTarget* MonitoringTarget::createMonitoringTargetStatic( unsigned int id )
{
	//Fails because ref_ptr is run out of scope before assigning of the return value
	//osg::ref_ptr<MonitoringTarget> target = new MonitoringTarget(id);
	//return target.get();

	//potential memory leak if the caller can't assign the return value to a ref_ptr<>.
	MonitoringTarget * target1 = new MonitoringTarget(id);
	return target1;
}

osg::ref_ptr<MonitoringTarget> MonitoringTarget::createMonitoringTargetRefStatic( unsigned int id )
{
	osg::ref_ptr<MonitoringTarget> target = new MonitoringTarget(id);
	return target;
}



int main_MonitorTarget(int argc, char * argv[])	{
	osg::ref_ptr<MonitoringTarget> pMonitoringTarget = new MonitoringTarget(0);
	for ( unsigned int i=1; i<5; ++i )
	{
		std::cout << "reference count before: " << pMonitoringTarget->referenceCount() << std::endl;
		osg::ref_ptr<MonitoringTarget> subTarget = pMonitoringTarget->createMonitoringTarget(i);
		std::cout << "reference count after: " << pMonitoringTarget->referenceCount() << std::endl;
	}

	return 0;
}

int main_MonitorTargetRef(int argc, char * argv[])	{
	osg::ref_ptr<MonitoringTarget> pMonitoringTarget = new MonitoringTarget(0);
	for ( unsigned int i=1; i<5; ++i )	{
		std::cout << "reference count before: " << pMonitoringTarget->referenceCount() << std::endl;
		osg::ref_ptr<MonitoringTarget> subTarget = pMonitoringTarget->createMonitoringTargetRef(i);
		std::cout << "reference count after: " << pMonitoringTarget->referenceCount() << std::endl;
	}

	return 0;
}


int main_MonitorTargetStatic(int argc, char * argv[])	{
	osg::ref_ptr<MonitoringTarget> pMonitoringTarget = new MonitoringTarget(0);
	for ( unsigned int i=1; i<5; ++i )
	{
		osg::ref_ptr<MonitoringTarget> subTarget = MonitoringTarget::createMonitoringTargetStatic(i);
		std::cout << "reference count after: " << subTarget->referenceCount() << std::endl;
	}

	return 0;
}

int main_MonitorTargetRefStatic(int argc, char * argv[])	{
	osg::ref_ptr<MonitoringTarget> pMonitoringTarget = new MonitoringTarget(0);
	for ( unsigned int i=1; i<5; ++i )	{
		osg::ref_ptr<MonitoringTarget> subTarget = MonitoringTarget::createMonitoringTargetRefStatic(i);
		std::cout << "reference count after: " << subTarget->referenceCount() << std::endl;
	}

	return 0;
}



int main(int argc, char * argv[])	{
	//main_MonitorTarget(argc,argv);
	//main_MonitorTargetRef(argc,argv);

	main_MonitorTargetStatic(argc,argv);
	//main_MonitorTargetRefStatic(argc,argv);

}

//=========================================================================================================

int main_Geography(int argc, char * argv[])	{
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

	root->addChild(new VR::Grid);
	root->addChild(pMt);
	root->addChild(axes);

	osgViewer::Viewer viewer;
	viewer.setSceneData( root.get() );

	return viewer.run();
}

//==============================================================================================
/*
class Base	{
public:
	Base() {std::cout << "Base class created" << std::endl;}

	virtual ~Base() {
		std::cout << "Base class destructor" << std::endl;
	}
};

class A : public Base	{
public:
	A(float aflIndy) : m_flIndy(aflIndy) {std::cout << "A class created" << std::endl;}

private:
	float m_flIndy;
public:
	virtual ~A() {std::cout << "A class destructor" << std::endl;}
};

class C : public Base	{
public:
	C(int anIndy) : m_nIndy(anIndy) {std::cout << "C class created" << std::endl;}

private:
	int m_nIndy;

public:
	virtual ~C() {std::cout << "C class destructor" << std::endl;}

	void display() {std::cout << "C class display" << std::endl;};
};

int main(int argc, char * argv[])	{

	Base * pB = new C(3);
	delete pB;

	return 0;
}
*/

//=====================================================================================================