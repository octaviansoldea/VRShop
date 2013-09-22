#include "vtkTransform.h"
#include "vtkActor.h"
#include "vtkObjectFactory.h"
#include "PlatePipe.h"

#include "Shelf.h"

vtkStandardNewMacro(Shelf);

Shelf::~Shelf()	{

	int nI;
	for (nI=0;nI<6;nI++)	{
		m_arrpPlatePipe[nI]->Delete();
	}
}

//-----------------------------------------------------------

Shelf::Shelf()	{
}

//--------------------------------------------------------------------------------------------------

void Shelf::setSizes(double adbLenX, double adbLenY, double adbLenZ)	{
	double m_dbXLen = adbLenX;
	double m_dbYLen = adbLenY;
	double m_dbZLen = adbLenZ;

	int nI;
	vtkSmartPointer < vtkMatrix4x4 > arrpMatrix[6];	
	for (nI=0;nI<6;nI++)	{
		m_arrpPlatePipe[nI] = PlatePipe::New();
		arrpMatrix[nI] = vtkSmartPointer < vtkMatrix4x4 >::New();
		arrpMatrix[nI]->Identity();
	}

	vtkSmartPointer < vtkMatrix4x4 > pMatrixScale = vtkSmartPointer < vtkMatrix4x4 >::New();
	vtkSmartPointer < vtkMatrix4x4 > pMatrixTmp = vtkSmartPointer < vtkMatrix4x4 >::New();

	{
		vtkSmartPointer < vtkMatrix4x4 > pMatrix0 = arrpMatrix[0];
		(*pMatrix0)[0][3] = m_dbXLen / 2.0;

		(*pMatrix0)[0][0] = 0.0;	(*pMatrix0)[0][1] = 0.0;	(*pMatrix0)[0][2] = 1.0;
		(*pMatrix0)[1][0] = 0.0;	(*pMatrix0)[1][1] = 1.0;	(*pMatrix0)[1][2] = 0.0;
		(*pMatrix0)[2][0] = -1.0;	(*pMatrix0)[2][1] = 0.0;	(*pMatrix0)[2][2] = 0.0;

		
		pMatrixScale->Identity();
		(*pMatrixScale)[1][1] = m_dbYLen;
		(*pMatrixScale)[0][0] = m_dbZLen;
		
		vtkMatrix4x4::Multiply4x4(pMatrix0, pMatrixScale, pMatrixTmp);
		pMatrix0->DeepCopy(pMatrixTmp);
	}
	{
		vtkSmartPointer < vtkMatrix4x4 > pMatrix1 = arrpMatrix[1];
		(*pMatrix1)[0][3] = - m_dbXLen / 2.0;

		(*pMatrix1)[0][0] = 0.0;	(*pMatrix1)[0][1] = 0.0;	(*pMatrix1)[0][2] = -1.0;
		(*pMatrix1)[1][0] = 0.0;	(*pMatrix1)[1][1] = 1.0;	(*pMatrix1)[1][2] = 0.0;
		(*pMatrix1)[2][0] = 1.0;	(*pMatrix1)[2][1] = 0.0;	(*pMatrix1)[2][2] = 0.0;

		pMatrixScale->Identity();
		(*pMatrixScale)[1][1] = m_dbYLen;
		(*pMatrixScale)[0][0] = m_dbZLen;
		vtkMatrix4x4::Multiply4x4(pMatrix1, pMatrixScale, pMatrixTmp);
		pMatrix1->DeepCopy(pMatrixTmp);

	}
	{
		vtkSmartPointer < vtkMatrix4x4 > pMatrix2 = arrpMatrix[2];
		(*pMatrix2)[1][3] = m_dbYLen / 2.0;

		(*pMatrix2)[0][0] = 1.0;	(*pMatrix2)[0][1] = 0.0;	(*pMatrix2)[0][2] = 0.0;
		(*pMatrix2)[1][0] = 0.0;	(*pMatrix2)[1][1] = 0.0;	(*pMatrix2)[1][2] = 1.0;
		(*pMatrix2)[2][0] = 0.0;	(*pMatrix2)[2][1] = -1.0;	(*pMatrix2)[2][2] = 0.0;

		pMatrixScale->Identity();
		(*pMatrixScale)[0][0] = m_dbXLen;
		(*pMatrixScale)[1][1] = m_dbZLen;
		vtkMatrix4x4::Multiply4x4(pMatrix2, pMatrixScale, pMatrixTmp);
		pMatrix2->DeepCopy(pMatrixTmp);
	}
	{
		vtkSmartPointer < vtkMatrix4x4 > pMatrix3 = arrpMatrix[3];
		(*pMatrix3)[1][3] = - m_dbYLen / 2.0;

		(*pMatrix3)[0][0] = 1.0;	(*pMatrix3)[0][1] = 0.0;	(*pMatrix3)[0][2] = 0.0;
		(*pMatrix3)[1][0] = 0.0;	(*pMatrix3)[1][1] = 0.0;	(*pMatrix3)[1][2] = -1.0;
		(*pMatrix3)[2][0] = 0.0;	(*pMatrix3)[2][1] = 1.0;	(*pMatrix3)[2][2] = 0.0;

		pMatrixScale->Identity();
		(*pMatrixScale)[0][0] = m_dbXLen;
		(*pMatrixScale)[1][1] = m_dbZLen;
		vtkMatrix4x4::Multiply4x4(pMatrix3, pMatrixScale, pMatrixTmp);
		pMatrix3->DeepCopy(pMatrixTmp);
	}

	{
		vtkSmartPointer < vtkMatrix4x4 > pMatrix4 = arrpMatrix[4];
		(*pMatrix4)[2][3] = m_dbZLen / 2.0;

		pMatrixScale->Identity();
		(*pMatrixScale)[0][0] = m_dbXLen;
		(*pMatrixScale)[1][1] = m_dbYLen;
		vtkMatrix4x4::Multiply4x4(pMatrix4, pMatrixScale, pMatrixTmp);
		pMatrix4->DeepCopy(pMatrixTmp);
	}
	{
		vtkSmartPointer < vtkMatrix4x4 > pMatrix5 = arrpMatrix[5];
		(*pMatrix5)[2][3] = - m_dbZLen / 2.0;

		pMatrixScale->Identity();
		(*pMatrixScale)[0][0] = m_dbXLen;
		(*pMatrixScale)[1][1] = m_dbYLen;
		vtkMatrix4x4::Multiply4x4(pMatrix5, pMatrixScale, pMatrixTmp);
		pMatrix5->DeepCopy(pMatrixTmp);
	}

	for (nI=0;nI<6;nI++)	{
		vtkSmartPointer <vtkTransform> pTransform = vtkSmartPointer <vtkTransform>::New();
		pTransform->PostMultiply();
		pTransform->SetMatrix(arrpMatrix[nI]);
		m_arrpPlatePipe[nI]->plateTransformation(pTransform);
		this->AddPart(m_arrpPlatePipe[nI]->getActor());
	}

}

//--------------------------------------------------------------------------------