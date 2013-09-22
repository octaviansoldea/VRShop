#include "vtkActor.h"
#include "vtkRenderer.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkInteractorStyleTrackballCamera.h"

#include "RenWin.h"
#include "OrientationWidgets.h"

#include "Shelf.h"
#include "Cupboard.h"

int main1(int argc, char *argv[])	{
	RenWin *pRenWin = new RenWin;	
	pRenWin->m_pRenWin3D->Render();

	//Define interactor
	pRenWin->m_pIren3D = vtkRenderWindowInteractor::New();
	vtkInteractorStyleTrackballCamera *pStyle = 
		vtkInteractorStyleTrackballCamera::New();
	pRenWin->m_pIren3D->SetInteractorStyle(pStyle);
	pRenWin->m_pIren3D->SetRenderWindow( pRenWin->m_pRenWin3D );

	OrientationWidgets * pOrientationWidgets = OrientationWidgets::New();
	pOrientationWidgets->SetRenderingPipeline(pRenWin->m_pIren3D);

	//Add an actor to the renderer and render in the render window
	Shelf * pShelf = Shelf::New();
	pShelf->setSizes(10.2,0.1,2.0);
	pRenWin->m_pRenderer3D->AddActor(pShelf);

	pRenWin->m_pIren3D->Initialize();
	pRenWin->m_pIren3D->Start();

	//Delete dynamic objects
	pStyle->Delete();
	pShelf->Delete();
	delete pRenWin;

	return(0);
}


//---------------------------------------------------------------------------

int main2(int argc, char *argv[])	{
	RenWin *pRenWin = new RenWin;	
	pRenWin->m_pRenWin3D->Render();

	//Define interactor
	pRenWin->m_pIren3D = vtkRenderWindowInteractor::New();
	vtkInteractorStyleTrackballCamera *pStyle = 
		vtkInteractorStyleTrackballCamera::New();
	pRenWin->m_pIren3D->SetInteractorStyle(pStyle);
	pRenWin->m_pIren3D->SetRenderWindow( pRenWin->m_pRenWin3D );

	OrientationWidgets * pOrientationWidgets = OrientationWidgets::New();
	pOrientationWidgets->SetRenderingPipeline(pRenWin->m_pIren3D);

	//Add an actor to the renderer and render in the render window
	Cupboard * pCupboard = Cupboard::New();
	pCupboard->initCupboard();
	pRenWin->m_pRenderer3D->AddActor(pCupboard);

	pRenWin->m_pIren3D->Initialize();
	pRenWin->m_pIren3D->Start();

	//Delete dynamic objects
	pStyle->Delete();
	pCupboard->Delete();
	delete pRenWin;

	return(0);
}

//=====================================================================================

int main(int argc, char *argv[])	{
//	main1(argc, argv);
	main2(argc, argv);

	return 0;
}