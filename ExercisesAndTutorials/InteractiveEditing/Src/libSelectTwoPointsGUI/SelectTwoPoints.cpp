#include <string>

#include "qvtkwidget.h"

#include "vtkCamera.h"
#include "vtkRenderWindow.h"
#include "vtkRenderWindowInteractor.h"
#include "vtkRenderer.h"
#include "vtkWindowToImageFilter.h"
#include "vtkBMPWriter.h"
#include "vtkTextProperty.h"
#include "vtkCubeAxesActor2D.h"
#include "vtkProperty.h"
#include "vtkVRMLImporter.h"
#include "vtkPolyDataMapper.h"

//#include "CIniWriter.h"
//#include "Singleton.h"
//#include "DynamicFilesManager.h"

#include "SelectTwoPoints.h"
#include "ArrowSourceStartEnd.h"


TargetClosest & TargetClosest::operator=(const TargetClosest & aTargetClosest) {
	m_nID = aTargetClosest.m_nID;
	int nI;
	for(nI = 0; nI < 3; nI++)
		m_arrdbPt[nI] = aTargetClosest.m_arrdbPt[nI];
	return(*this);
}

SelectTwoPoints::SelectTwoPoints() {

	for(int nI=0; nI<3; nI++)
		m_arrdbMinVals[nI]=0.0;
	m_pRenderer = vtkSmartPointer < vtkRenderer >::New();
	m_pRenWin = vtkSmartPointer < vtkRenderWindow >::New();
	m_pRenWin->SetSize(200, 500);
	m_pRenWin->AddRenderer(m_pRenderer);

	m_pAxesWidget = vtkSmartPointer < AxesWidget >::New();
	m_pAxesWidget->SetLengths(5.0);

	m_pRenderer->AddActor(m_pAxesWidget->GetAxesActor());

	//////////////////////////////////////
	//   
	// Create sphere widget 1
	//
	/////////////////////////////////
	 m_pSphereWidget1 = vtkSmartPointer<vtkSphereWidget2>::New();
	 //m_pSphereWidget->SetInteractor(m_pIren);
	 m_pSphereWidget1->CreateDefaultRepresentation();

	 m_pSphereRepresentation1 = vtkSphereRepresentation::SafeDownCast( m_pSphereWidget1->GetRepresentation() );
	 m_pSphereRepresentation1->SetRadius(1.5);
	 m_pSphereRepresentation1->SetCenter(0.0,2.5,0.0);
	 m_pSphereRepresentation1->HandleTextOff();
	 m_pSphereRepresentation1->RadialLineOff();
	 m_pSphereCallback1 = vtkSmartPointer<vtkSphereCallback>::New();

	//////////////////////////////////////
	//   
	// Create sphere widget 2
	//
	/////////////////////////////////
	 m_pSphereWidget2 = vtkSmartPointer<vtkSphereWidget2>::New();
	 m_pSphereWidget2->CreateDefaultRepresentation();

	 m_pSphereRepresentation2 = vtkSphereRepresentation::SafeDownCast( m_pSphereWidget2->GetRepresentation() );
	 m_pSphereRepresentation2->SetRadius(1.5);
	 m_pSphereRepresentation2->SetCenter(0.0,0.0,5.0);
	 m_pSphereRepresentation2->HandleTextOff();
	 m_pSphereRepresentation2->RadialLineOff();
	 m_pSphereCallback2 = vtkSmartPointer<vtkSphereCallback>::New();

	//  Create an arrow

	  //Create a mapper and actor for the arrow
	m_pMapperArrow = vtkSmartPointer<vtkPolyDataMapper>::New();
	m_pActorArrow =	vtkSmartPointer<vtkActor>::New();

	m_pArrowSourceStartEnd =
		  vtkSmartPointer < ArrowSourceStartEnd> ::New();
	m_pArrowSourceStartEnd->SetPointStart(m_pSphereRepresentation1->GetCenter());
	m_pArrowSourceStartEnd->SetPointEnd(m_pSphereRepresentation2->GetCenter());

	m_pMapperArrow->SetInputConnection(m_pArrowSourceStartEnd->GetOutputPort_Specific_NonVirtual());
	m_pActorArrow->SetMapper(m_pMapperArrow);


	/////////////////////////////////////////////////////////////

	m_pPolyDataArtery = vtkSmartPointer < vtkPolyData >::New();
	m_pMapperArtery = vtkSmartPointer < vtkPolyDataMapper >::New();
	m_pActorArtery = vtkSmartPointer < vtkActor >::New();
	m_pMapperArtery->SetInput(m_pPolyDataArtery);
	m_pActorArtery->SetMapper(m_pMapperArtery);
	m_pRenderer->AddActor(m_pActorArtery);
	m_pRenderer->AddActor(m_pActorArrow);

}

SelectTwoPoints::~SelectTwoPoints() {
	//VTK_DELETE_NULL(m_pRenderer);
	//VTK_DELETE_NULL(m_pRenWin);
}

void SelectTwoPoints::setInteractor(vtkRenderWindowInteractor * apIren) {
	m_pIren = apIren;

	m_pSphereWidget1->SetInteractor(m_pIren);
	m_pSphereWidget1->AddObserver( vtkCommand::InteractionEvent, m_pSphereCallback1 );
	m_pSphereWidget1->On();

	m_pSphereWidget2->SetInteractor(m_pIren);
	m_pSphereWidget2->AddObserver( vtkCommand::InteractionEvent, m_pSphereCallback2 );
	m_pSphereWidget2->On();
}

void SelectTwoPoints::updateRenderer() {

	m_pRenderer->ResetCamera();
	m_pRenWin->Render();

}

vtkRenderer * SelectTwoPoints::GetRenderer() {
	return(m_pRenderer);
}

vtkRenderWindow * SelectTwoPoints::GetRenderWindow() {
	return(m_pRenWin);
}

void SelectTwoPoints::UpdatePts(double aarrdbPt1[3], 
								double aarrdbPt2[3], 
								double adbRadiuses,
								bool abArtery) {
	m_pSphereRepresentation1->SetCenter(aarrdbPt1);
	m_pSphereRepresentation2->SetCenter(aarrdbPt2);
	m_pSphereRepresentation1->SetRadius(adbRadiuses);
	m_pSphereRepresentation2->SetRadius(adbRadiuses);

	m_pArrowSourceStartEnd->SetPointStart(m_pSphereRepresentation1->GetCenter());
	m_pArrowSourceStartEnd->SetPointEnd(m_pSphereRepresentation2->GetCenter());
	m_pArrowSourceStartEnd->Update();

	if(abArtery == true) {
		TargetClosest tc = compClosest(m_pPolyDataArtery, m_pSphereRepresentation1->GetCenter());
		int nI;
		for(nI = 0; nI < 3; nI++)
			m_arrdbMinVals[nI]= tc.m_arrdbPt[nI];
		m_nMinIndx = tc.m_nID;
	
	}

	m_pRenWin->Render();
}

void SelectTwoPoints::readVRML2PolyData(vtkSmartPointer < vtkPolyData > apPolyData,
	const std::string & astrFileName) {

		vtkSmartPointer < vtkVRMLImporter > pvtkVRMLImporter =
			vtkSmartPointer < vtkVRMLImporter >::New();
		pvtkVRMLImporter->SetFileName(astrFileName.c_str());
		pvtkVRMLImporter->Read();
		pvtkVRMLImporter->Update();
		pvtkVRMLImporter->useNode("ANY");

		pvtkVRMLImporter->GetRenderer()->GetActors()->InitTraversal();
		vtkActor * pActor = pvtkVRMLImporter->GetRenderer()->GetActors()->GetLastActor();
		vtkMapper * pMapper = pActor->GetMapper();
		vtkDataSet * pDataSetSrc = pMapper->GetInput();
		vtkPolyData * pPDSrc = dynamic_cast< vtkPolyData * > (pDataSetSrc);

		apPolyData->DeepCopy(pPDSrc);

}

void SelectTwoPoints::LoadArtery(const std::string & astrFileName) {
	readVRML2PolyData(m_pPolyDataArtery, astrFileName);
	m_pRenderer->ResetCamera();
	m_pRenWin->Render();
}

void SelectTwoPoints::setArteryFileName(const std::string & astrFileName)
{
	m_strArteryFileName = astrFileName;
}


TargetClosest SelectTwoPoints::compClosest(vtkPolyData * apvtkPolyData, double * apdbStartPoint)
{
	double _arrdbMinVals[3];
	int _nMinIndx;
	

	TargetClosest tc;

	double *pdbStartPoint = apdbStartPoint;//m_pArrowSourceStartEnd->GetPointStart();
	
    double dbFixX = pdbStartPoint[0];
	double dbFixY = pdbStartPoint[1];
	double dbFixZ = pdbStartPoint[2];


	/*pdbStartPoint[0] = 55;
	pdbStartPoint[1] = -39;
	pdbStartPoint[2] = 22;
	pdbEndPoint[0] = 54;
	pdbEndPoint[1] = -36.9;
	pdbEndPoint[2] = 23.9;*/
	// 55 -39 22
	// 54 -36.9 23.9
	//54.3031 -40.604 21.6494


	vtkPoints * pPoints = apvtkPolyData->GetPoints();
	int nPointsNr = pPoints->GetNumberOfPoints();
	if(nPointsNr == 0) {
		cerr << "Error: zero points detected"<< endl;
		exit(-1);
	}
	double dbDist, dbMinDist;
	double * pdbVals;
	_nMinIndx = 0;
	pdbVals = pPoints->GetPoint(0);
	_arrdbMinVals[0] = pdbVals[0];
	_arrdbMinVals[1] = pdbVals[1];
	_arrdbMinVals[2] = pdbVals[2];
	double dbFocusX = pdbVals[0];
	double dbFocusY = pdbVals[1];
	double dbFocusZ = pdbVals[2];
	dbMinDist = sqrt((dbFixX-dbFocusX)*(dbFixX-dbFocusX)+
						 (dbFixY-dbFocusY)*(dbFixY-dbFocusY)+
						 (dbFixZ-dbFocusZ)*(dbFixZ-dbFocusZ)); 
	int nI;
	for(nI = 1; nI < nPointsNr; nI++) {
		pdbVals = pPoints->GetPoint(nI);
		dbFocusX = pdbVals[0];
		dbFocusY = pdbVals[1];
		dbFocusZ = pdbVals[2];

		dbDist = sqrt((dbFixX-dbFocusX)*(dbFixX-dbFocusX)+
						 (dbFixY-dbFocusY)*(dbFixY-dbFocusY)+
						 (dbFixZ-dbFocusZ)*(dbFixZ-dbFocusZ)); 
		if(dbDist < dbMinDist){
			dbMinDist = dbDist;
			_nMinIndx = nI;
			_arrdbMinVals[0] = pdbVals[0];
			_arrdbMinVals[1] = pdbVals[1];
			_arrdbMinVals[2] = pdbVals[2];
		}
	}
	printf("pdbStartPoint[0]= %f, pdbStartPoint[1]= %f, pdbStartPoint[2]= %f\n",pdbStartPoint[0], pdbStartPoint[1], pdbStartPoint[2]);
	printf("pdbMinVals[0]= %f, pdbMinVals[1]= %f, pdbMinVals[2]= %f\n",_arrdbMinVals[0], _arrdbMinVals[1], _arrdbMinVals[2]);
	printf("nMinIndx= %d, dbMinDist= %f\n",_nMinIndx, dbMinDist);
	printf("======================\n");
	tc.m_nID = _nMinIndx;
	for(nI = 0; nI < 3; nI++)
		tc.m_arrdbPt[nI] = _arrdbMinVals[nI];
	return(tc);
}


void SelectTwoPoints::savePointAndIdxToFile(const char * achFileName) {
//
//	CIniWriter * pCIniWriter = Singleton< CIniWriter > ::instance();
//	pCIniWriter->SetFileName(achFileName);
//
//	std::string strSection1 = m_strArteryFileName.c_str();
//	std::string strKey1X = "ClosestPointToInitialPointX";
//		pCIniWriter->WriteDouble(strSection1.c_str(), strKey1X.c_str(), m_arrdbMinVals[0]);
//	std::string strKey1Y = "ClosestPointToInitialPointY";
//		pCIniWriter->WriteDouble(strSection1.c_str(), strKey1Y.c_str(), m_arrdbMinVals[1]);
//	std::string strKey1Z = "ClosestPointToInitialPointZ";
//		pCIniWriter->WriteDouble(strSection1.c_str(), strKey1Z.c_str(), m_arrdbMinVals[2]);
//	std::string strKey1 = "ClosestPointIndex";
//		pCIniWriter->WriteDouble(strSection1.c_str(), strKey1.c_str(), m_nMinIndx);
}