#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"
#include "vtkAssembly.h"
#include "vtkPolyData.h"
#include "vtkTransform.h"
#include "vtkMatrix4x4.h"

#include "vtkCamera.h"

#include "RenWin.h"

#include "PlatePipe.h"

//------------------------------------------------------------------------

int main1(int argc, char *argv[])	{
	RenWin *pRenWin = new RenWin;

	PlatePipe * plate = PlatePipe::New();
	vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();
	transform->Scale(2,2,0);
	plate->plateTransformation(transform);

	//Add an actor to the renderer and render in the render window
	pRenWin->m_pRenderer3D->AddActor(plate->getActor());	
	pRenWin->m_pRenWin3D->Render();

	//Define interactor
	pRenWin->m_pIren3D = vtkRenderWindowInteractor::New();
	vtkInteractorStyleTrackballCamera *pStyle = 
		vtkInteractorStyleTrackballCamera::New();
	pRenWin->m_pIren3D->SetInteractorStyle(pStyle);
	pRenWin->m_pIren3D->SetRenderWindow( pRenWin->m_pRenWin3D );

	pRenWin->m_pIren3D->Initialize();
	pRenWin->m_pIren3D->Start();

	//Delete dynamic objects
	pStyle->Delete();
	delete pRenWin;
	delete plate;

	return(0);
}

//------------------------------------------------------------------------

int main2(int argc, char *argv[])	{
	RenWin renWin;

	PlatePipe * plate = PlatePipe::New();
	vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();

	double matrix[16] = {3, 0, 0, 0, 
						 0, 5, 0, 0,
						 0, 0, 1, 0,
						 0, 0, 0, 1};

	transform->SetMatrix(matrix);

	plate->plateTransformation(transform);

	//Add an actor to the renderer and render in the render window
	renWin.m_pRenderer3D->AddActor(plate->getActor());	
	renWin.m_pRenWin3D->Render();

	//Define interactor
	renWin.m_pIren3D = vtkRenderWindowInteractor::New();
	vtkInteractorStyleTrackballCamera *pStyle = 
		vtkInteractorStyleTrackballCamera::New();
	renWin.m_pIren3D->SetInteractorStyle(pStyle);
	renWin.m_pIren3D->SetRenderWindow( renWin.m_pRenWin3D );

	renWin.m_pIren3D->Initialize();
	renWin.m_pIren3D->Start();

	//Delete dynamic objects
	pStyle->Delete();
	delete plate;

	return(0);
}

//=======================================================================

int main(int argc, char *argv[])	{
//	main1(argc, argv);
	main2(argc, argv);

	return 0;
}