#include "vtkAppendPolyData.h"
#include "vtkConeSource.h"
#include "vtkCylinderSource.h"
#include "vtkInformation.h"
#include "vtkInformationVector.h"
#include "vtkObjectFactory.h"
#include "vtkPolyData.h"
#include "vtkTransform.h"
#include "vtkTransformFilter.h"
#include "vtkMath.h"
#include "vtkMatrix4x4.h"
#include "vtkSmartPointer.h"
#include "vtkTransformPolyDataFilter.h"

#include "ArrowSourceStartEnd.h"

vtkStandardNewMacro(ArrowSourceStartEnd);

ArrowSourceStartEnd::ArrowSourceStartEnd() : vtkArrowSource()
{
  PointStart[0] = 0.0;
  PointStart[1] = 0.0;
  PointStart[2] = 0.0;

  PointEnd[0] = 1.0;
  PointEnd[1] = 0.0;
  PointEnd[2] = 0.0;

  m_pTransform = vtkSmartPointer<vtkTransform>::New();
 
  // Transform the polydata
  transformPD = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transformPD->SetTransform(m_pTransform);
  transformPD->SetInputConnection(GetOutputPort());
}

ArrowSourceStartEnd::~ArrowSourceStartEnd(){

}

void ArrowSourceStartEnd::PrintSelf(ostream& os, vtkIndent indent)
{
  vtkArrowSource::PrintSelf(os, indent);
}

void ArrowSourceStartEnd::Update()
{
  vtkArrowSource::Update();
    // Compute a basis
  double normalizedX[3];
  double normalizedY[3];
  double normalizedZ[3];
 
  // The X axis is a vector from start to end
  vtkMath::Subtract(PointEnd, PointStart, normalizedX);
  double length = vtkMath::Norm(normalizedX);
  vtkMath::Normalize(normalizedX);
 
  double arbitrary[3] = {0.0, 0.0, 0.0};
  if((fabs(normalizedX[1]) < 0.0001) && (fabs(normalizedX[2]) < 0.0001))
    {
    arbitrary[1] = 1.0;
    } else
    {
    arbitrary[0] = normalizedX[0];
    arbitrary[1] = - normalizedX[2];
    arbitrary[2] = normalizedX[1];
	}
  vtkMath::Cross(normalizedX, arbitrary, normalizedZ);
  vtkMath::Normalize(normalizedZ);
 
  // The Y axis is Z cross X
  vtkMath::Cross(normalizedZ, normalizedX, normalizedY);
  vtkSmartPointer<vtkMatrix4x4> matrix =
    vtkSmartPointer<vtkMatrix4x4>::New();
 
  // Create the direction cosine matrix
  matrix->Identity();
  for (unsigned int i = 0; i < 3; i++)
    {
    matrix->SetElement(i, 0, normalizedX[i]);
    matrix->SetElement(i, 1, normalizedY[i]);
    matrix->SetElement(i, 2, normalizedZ[i]);
    }    
 
  // Apply the transforms
  //m_pTransform = vtkSmartPointer<vtkTransform>::New();
  m_pTransform->Identity();
  m_pTransform->Translate(PointStart);
  m_pTransform->Concatenate(matrix);
  m_pTransform->Scale(length, length, length);
  transformPD->Update();
}

vtkPolyData* ArrowSourceStartEnd::GetOutput_Specific_NonVirtual()
{
  Update();
  return(transformPD->GetOutput());
}

vtkAlgorithmOutput* ArrowSourceStartEnd::GetOutputPort_Specific_NonVirtual()
{
  Update();
  return(transformPD->GetOutputPort());
}