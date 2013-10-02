#include "SphereWidget.h"
#include "vtkInteractorStyleTrackballCamera.h"

#include <iostream>

using namespace std;

int main( int, char *[] )
{
	vtkSmartPointer<vtkRenderer> m_pRen = 
		vtkSmartPointer<vtkRenderer>::New();
	vtkSmartPointer<vtkRenderWindow> m_pRenWin = 
		vtkSmartPointer<vtkRenderWindow>::New();
	vtkSmartPointer<vtkRenderWindowInteractor> m_pIren = 
		vtkSmartPointer<vtkRenderWindowInteractor>::New();

	// Create a sphere widget
	vtkSmartPointer<vtkSphereWidget2> sphereWidget =
		vtkSmartPointer<vtkSphereWidget2>::New();
	sphereWidget->SetInteractor(m_pIren);
	sphereWidget->CreateDefaultRepresentation();

	//This is unnecessary - already defined within the .H file
	vtkSphereRepresentation* sphereRepresentation =
		reinterpret_cast<vtkSphereRepresentation*>( sphereWidget->GetRepresentation() );
	sphereRepresentation->HandleVisibilityOn();

	// Create a callback interaction
	vtkSmartPointer<vtkSphereCallback> sphereCallback =
		vtkSmartPointer<vtkSphereCallback>::New();
	sphereWidget->AddObserver( vtkCommand::InteractionEvent, sphereCallback );

	m_pRenWin->AddRenderer(m_pRen);

	m_pRen->Render();
	m_pIren->SetRenderWindow(m_pRenWin);

	//render image
	m_pIren->Initialize();
	m_pRenWin->Render();
	sphereWidget->On();

	// Begin mouse interaction
	m_pIren->Start();

	return EXIT_SUCCESS;
}
