#include <osg/MatrixTransform>

#include "VRUntransformedPlate2D.h"
#include "VRUntransformedPlate3D.h"

using namespace osg;
using namespace VR;

UntransformedPlate3D::UntransformedPlate3D()	{
	ref_ptr<UntransformedPlate2D> plate2D = new UntransformedPlate2D;

	ref_ptr<MatrixTransform> pMatrixTransform;
	Matrix matrix;
	{
		matrix.set(
			1.0, 0.0, 0.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0);

		pMatrixTransform = new MatrixTransform;
		pMatrixTransform->setMatrix(matrix);
		pMatrixTransform->addChild(plate2D);

		addChild(pMatrixTransform.get());
	}
	{
		matrix.set(
			1.0, 0.0, 0.0, 0.0,
			0.0,-1.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0);

		pMatrixTransform = new MatrixTransform;
		pMatrixTransform->setMatrix(matrix);
		pMatrixTransform->addChild(plate2D);

		addChild(pMatrixTransform.get());
	}
	{
		matrix.set(
			0.0, 1.0, 0.0, 0.0,
		   -1.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0, 0.0, 0.0, 1.0);

		pMatrixTransform = new MatrixTransform;
		pMatrixTransform->setMatrix(matrix);
		pMatrixTransform->addChild(plate2D);

		addChild(pMatrixTransform.get());
	}
	{
		matrix.set(
			0.0,-1.0, 0.0, 0.0,
		    1.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
		    0.0, 0.0, 0.0, 1.0);

		pMatrixTransform = new MatrixTransform;
		pMatrixTransform->setMatrix(matrix);
		pMatrixTransform->addChild(plate2D);

		addChild(pMatrixTransform.get());
	}
	{
		matrix.set(
			1.0, 0.0, 0.0, 0.0,
			0.0, 0.0, 1.0, 0.0,
			0.0,-1.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 1.0);

		pMatrixTransform = new MatrixTransform;
		pMatrixTransform->setMatrix(matrix);
		pMatrixTransform->addChild(plate2D);

		addChild(pMatrixTransform.get());
	}
	{
		matrix.set(
			1.0, 0.0, 0.0, 0.0,
			0.0, 0.0,-1.0, 0.0,
			0.0, 1.0, 0.0, 0.0,
			0.0, 0.0, 0.0, 1.0);

		pMatrixTransform = new MatrixTransform;
		pMatrixTransform->setMatrix(matrix);
		pMatrixTransform->addChild(plate2D);

		addChild(pMatrixTransform.get());
	}
}

//--------------------------------------------------------------------------

void UntransformedPlate3D::setColor(const float aarrflColor[4])	{
	int nI;
	int nNumChildren = this->getNumChildren();
	for(nI = 0; nI < nNumChildren; nI++) {

		ref_ptr < Node > pNode = this->getChild(nI);

		MatrixTransform * pMatrixTransform = 
			dynamic_cast< MatrixTransform * > (pNode.get());

		UntransformedPlate2D * pUntransformedPlate2D =
			dynamic_cast< UntransformedPlate2D * > (pMatrixTransform->getChild(0));

		pUntransformedPlate2D->setColor(aarrflColor);
	}
}

//--------------------------------------------------------------------------

void UntransformedPlate3D::setTexture(const char * apchFileName)	{
	int nI;
	int nNumChildren = this->getNumChildren();
	for(nI = 0; nI < nNumChildren; nI++) {

		ref_ptr < Node > pNode = this->getChild(nI);

		MatrixTransform * pMatrixTransform = 
			dynamic_cast< MatrixTransform * > (pNode.get());

		UntransformedPlate2D * pUntransformedPlate2D =
			dynamic_cast< UntransformedPlate2D * > (pMatrixTransform->getChild(0));

		pUntransformedPlate2D->setTexture(apchFileName);
	}
}