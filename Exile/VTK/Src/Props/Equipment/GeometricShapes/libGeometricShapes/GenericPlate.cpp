#include "vtkPoints.h"
#include "vtkPolygon.h"
#include "vtkCellArray.h"

#include "GenericPlate.h"

GenericPlate::GenericPlate()	{	
	vtkSmartPointer<vtkPoints> m_pVTKPoints = vtkSmartPointer<vtkPoints>::New();
	double m_dbXLen = 1;
	double m_dbYLen = 1;

	//Set 4 points that define a polygon
	m_pVTKPoints->InsertPoint(0, - m_dbXLen / 2.0, - m_dbYLen / 2.0, 0.0);
	m_pVTKPoints->InsertPoint(1, - m_dbXLen / 2.0,   m_dbYLen / 2.0, 0.0);
	m_pVTKPoints->InsertPoint(2,   m_dbXLen / 2.0,   m_dbYLen / 2.0, 0.0);
	m_pVTKPoints->InsertPoint(3,   m_dbXLen / 2.0, - m_dbYLen / 2.0, 0.0);
	m_pVTKPoints->Modified();

	//Create polygons
	vtkSmartPointer<vtkPolygon> m_pVTKPolygon = vtkSmartPointer<vtkPolygon>::New();
	vtkSmartPointer<vtkCellArray> m_pVTKCellArray = vtkSmartPointer<vtkCellArray>::New();

	m_pVTKPolygon->GetPointIds()->SetNumberOfIds(4);
	m_pVTKPolygon->GetPointIds()->SetId(0,0);
	m_pVTKPolygon->GetPointIds()->SetId(1,1);
	m_pVTKPolygon->GetPointIds()->SetId(2,2);
	m_pVTKPolygon->GetPointIds()->SetId(3,3);

	m_pVTKCellArray->InsertNextCell(m_pVTKPolygon);

	//Create a polydata
	m_PolyData = vtkSmartPointer<vtkPolyData>::New();
	m_PolyData->SetPoints(m_pVTKPoints);
	m_PolyData->SetPolys(m_pVTKCellArray);
}

//--------------------------------------------------------------

vtkSmartPointer < vtkPolyData > GenericPlate::getPoly()	{
	return m_PolyData;
}
