#include "SplineWidget.h"
#include "vtkAxesActor.h"

#include <iostream>

using namespace std;

int main1()
{
	// Define and initialize basic elements
	vtkSmartPointer<vtkRenderer> m_pRen = 
		vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> m_pRenWin = 
		vtkSmartPointer<vtkRenderWindow>::New();
	m_pRenWin->AddRenderer(m_pRen);
	vtkSmartPointer<vtkRenderWindowInteractor> m_pIren = 
		vtkSmartPointer<vtkRenderWindowInteractor>::New();
	m_pIren->SetRenderWindow(m_pRenWin);

	// Define Plane source and send an actor to the scene
	vtkPlaneSource* planeSource = vtkPlaneSource::New();
	planeSource->Update();
	vtkPolyDataMapper* planeSourceMapper = vtkPolyDataMapper::New();
	planeSourceMapper->SetInput(planeSource->GetOutput());
	vtkActor* planeSourceActor = vtkActor::New();
	planeSourceActor->SetMapper(planeSourceMapper);
	planeSourceActor->GetProperty()->SetColor(0.1,0.4,0.7);
	m_pRen->AddActor(planeSourceActor);

	//Define a spline widget
	vtkSplineWidget* spline = vtkSplineWidget::New();
	spline->SetInteractor(m_pIren);
	spline->SetInput(planeSource->GetOutput());
	spline->PlaceWidget();

	//Initialize polydata to be then sent to the "callback" as an external input
	vtkPolyData* poly = vtkPolyData::New();
	spline->GetPolyData(poly);

	// Set a widget callback
	vtkSplineWidgetCallback* swcb = vtkSplineWidgetCallback::New();
	swcb->Poly = poly;

	spline->AddObserver(vtkCommand::InteractionEvent,swcb);
	spline->On();

	// Invoke axes for the sake of orientation
	vtkSmartPointer<vtkAxesActor> axes = vtkSmartPointer<vtkAxesActor>::New();
	axes->SetPosition(0,0,0);
	m_pRen->AddActor(axes);

	//Define background
	m_pRen->SetBackground( 0.1, 0.2, 0.4);

	m_pRenWin->SetSize(600, 300);
	m_pRenWin->Render();


	// Set up a viewpoint
	vtkCamera* camera = m_pRen->GetActiveCamera();

	// Render the image
	m_pIren->Initialize();
	m_pRenWin->Render();

	m_pIren->Start();

	//Delete
	camera->Delete();
	swcb->Delete();
	poly->Delete();
	spline->Delete();
	planeSource->Delete();
	planeSourceMapper->Delete();
	planeSourceActor->Delete();


	return EXIT_SUCCESS;
}

int main()	{
	main1();

	return(0);
}