#include "vtkPolygon.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkTransform.h"
#include "vtkTransformPolyDataFilter.h"
#include "vtkObjectFactory.h"

#include "PlatePipe.h"

vtkStandardNewMacro(PlatePipe);

//-----------------------------------------------------------------------

PlatePipe::~PlatePipe()	{
	delete m_pGenericPlate;
}

//-----------------------------------------------------------------------

vtkSmartPointer <vtkPolyData> PlatePipe::getPoly()	{
	return m_pGenericPlate->getPoly();
}

//-----------------------------------------------------------------------

void PlatePipe::plateTransformation(vtkSmartPointer<vtkTransform> & apVTKTransform)	{
	//Transform generic plate
	vtkSmartPointer <vtkPolyData> poly = getPoly();

	vtkSmartPointer <vtkTransformPolyDataFilter> transformedPoly = vtkSmartPointer <vtkTransformPolyDataFilter>::New();
	transformedPoly->SetInput(poly);
	transformedPoly->SetTransform(apVTKTransform);
	transformedPoly->Update();

	vtkSmartPointer<vtkPolyDataMapper> m_pVTKPolyDataMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
	m_pVTKPolyDataMapper->SetInputConnection(transformedPoly->GetOutputPort());

	m_pVTKActor = vtkSmartPointer<vtkActor>::New();
	m_pVTKActor->SetMapper(m_pVTKPolyDataMapper);
}

//-----------------------------------------------------------------------

vtkSmartPointer <vtkActor> PlatePipe::getActor()	{
	return m_pVTKActor;
}

//-----------------------------------------------------------------------

PlatePipe::PlatePipe()	{
	m_pGenericPlate = new GenericPlate;
}
