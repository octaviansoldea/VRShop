#include <osg/MatrixTransform>

#include "VRUntransformedPlate2D.h"
#include "VRUntransformedPlate3D.h"

using namespace osg;
using namespace VR;
using namespace std;

UntransformedPlate3D::UntransformedPlate3D() : MatrixTransform()	{
	ref_ptr<UntransformedPlate2D> plate2D
		//= new UntransformedPlate2D
		;

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
		plate2D = new UntransformedPlate2D;
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
		plate2D = new UntransformedPlate2D;
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
		plate2D = new UntransformedPlate2D;
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
		plate2D = new UntransformedPlate2D;
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
		plate2D = new UntransformedPlate2D;
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
		plate2D = new UntransformedPlate2D;
		pMatrixTransform->addChild(plate2D);

		addChild(pMatrixTransform.get());
	}
}

//--------------------------------------------------------------------------

void UntransformedPlate3D::setTextureOrColor(Surface & aSurface)	{
	bool bIsColor = aSurface.m_bIsColor;
	int nPlate = aSurface.m_PlateSide;

	if (nPlate==PlateSide::ALL)	{
		int nI;
		int nNumChildren = this->getNumChildren();

		for(nI = 0; nI < nNumChildren; nI++) {
			PlateSide & enumInt = (PlateSide&)nI;
			ref_ptr<UntransformedPlate2D> pUntransformedPlate2D = getPlate2D(enumInt);

			if (bIsColor==false)
				pUntransformedPlate2D->setTexture(aSurface.m_strFileName);
			else 
				pUntransformedPlate2D->setColor(aSurface.m_vecColor);
		}
	} else {
		ref_ptr<UntransformedPlate2D> pUntransformedPlate2D = getPlate2D(aSurface.m_PlateSide);

		if (bIsColor==false)
			pUntransformedPlate2D->setTexture(aSurface.m_strFileName);
		else 
			pUntransformedPlate2D->setColor(aSurface.m_vecColor);
	}
}

//--------------------------------------------------------------------------

UntransformedPlate2D * UntransformedPlate3D::getPlate2D(const PlateSide & anSide)	{
	ref_ptr<MatrixTransform> pMatrixTransform = static_cast<MatrixTransform *>(getChild(anSide));

	ref_ptr<UntransformedPlate2D> pUntransformedPlate2D = 
		static_cast<UntransformedPlate2D *>(pMatrixTransform->getChild(0));

	return pUntransformedPlate2D;
}

//--------------------------------------------------------------------------

void UntransformedPlate3D::setColor(std::vector<float> & avecColor, PlateSide aPlateSide)	{
	Surface aSurface;
	aSurface.m_bIsColor=true;
	aSurface.m_vecColor=avecColor;
	aSurface.m_PlateSide=aPlateSide;
	setTextureOrColor(aSurface);
}

//--------------------------------------------------------------------------

void UntransformedPlate3D::setTexture(std::string & astrFileName, PlateSide aPlateSide)	{
	Surface aSurface;
	aSurface.m_bIsColor=false;
	aSurface.m_strFileName=astrFileName;
	aSurface.m_PlateSide=aPlateSide;
	setTextureOrColor(aSurface);
}