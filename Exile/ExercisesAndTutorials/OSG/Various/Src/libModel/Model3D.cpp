#include "Model3D.h"

#include <osg/MatrixTransform>

#include "Model2D.h"

using namespace osg;

Model3D::Model3D()	{
	ref_ptr<Model2D> plate2D = new Model2D;
	
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

void Model3D::setColor(Vec4 aVec4)	{

	int nI;
	int nNumChildren = this->getNumChildren();
	for(nI = 0; nI < nNumChildren; nI++) {

		ref_ptr < Node > pNode = this->getChild(nI);

		MatrixTransform * pMatrixTransform = 
			dynamic_cast< MatrixTransform * > (pNode.get());

		Model2D * pModel2D =
			dynamic_cast< Model2D * > (pMatrixTransform->getChild(0));

		pModel2D->setColor(aVec4);
	}
}

//--------------------------------------------------------------------------

void Model3D::setTexture(const char * apchFileName)	{
	int nI;
	int nNumChildren = this->getNumChildren();
	for(nI = 0; nI < nNumChildren; nI++) {

		ref_ptr < Node > pNode = this->getChild(nI);

		MatrixTransform * pMatrixTransform = 
			dynamic_cast< MatrixTransform * > (pNode.get());

		Model2D * pModel2D =
			dynamic_cast< Model2D * > (pMatrixTransform->getChild(0));

		pModel2D->setTexture(apchFileName);
	}
}
