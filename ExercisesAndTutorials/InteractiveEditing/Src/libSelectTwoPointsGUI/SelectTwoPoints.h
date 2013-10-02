#ifndef SELECT_TWO_POINTS_H
#define SELECT_TWO_POINTS_H

#include "vtkSphereSource.h"
#include "vtkSmartPointer.h"
#include "vtkPolyDataMapper.h"
#include "vtkActor.h"
#include "vtkSphereWidget2.h"

#include "AxesWidget.h"
#include "SphereWidget.h"
#include "ArrowSourceStartEnd.h"

struct TargetClosest {
	int m_nID;
	double m_arrdbPt[3];

	TargetClosest & operator=(const TargetClosest & aTargetClosest);
};


//===========================================================================
/*!
    \file   SelectTwoPoints.h
	\class	SelectTwoPoints
	\brief	The class SelectTwoPoints implements the functions required at the initialization step, 
	        when an initial point onto the artery has to be choosen. 
*/
//===========================================================================


class SelectTwoPoints {

	std::string m_strArteryFileName;  /**< The variable keeps the name of the artery file */
	double m_arrdbMinVals[3];  /**< The variable keeps the values of the initial point chosen onto the artery */
	int m_nMinIndx; /**< The variable keeps the index of the initial point chosen onto the artery  */

public:

	vtkSmartPointer < vtkRenderer > m_pRenderer;  /**< The variable keeps the renderer*/
    vtkSmartPointer < vtkRenderWindow > m_pRenWin;  /**< The variable keeps the render window*/
	vtkRenderWindowInteractor * m_pIren; /**< The variable keeps the render window interactor*/

	vtkSmartPointer < AxesWidget > m_pAxesWidget; /**< The variable keeps the axes widget*/

	vtkSmartPointer<vtkSphereWidget2> m_pSphereWidget1;  /**< The variable keeps the first sphere widget*/
	vtkSmartPointer <vtkSphereRepresentation> m_pSphereRepresentation1; /**< The variable keeps the first sphere representation*/
	vtkSmartPointer<vtkSphereCallback> m_pSphereCallback1;  /**< The variable keeps the first sphere callback*/
	
	vtkSmartPointer<vtkSphereWidget2> m_pSphereWidget2;  /**< The variable keeps the second sphere widget*/
	vtkSmartPointer <vtkSphereRepresentation> m_pSphereRepresentation2; /**< The variable keeps the second sphere representation*/
	vtkSmartPointer<vtkSphereCallback> m_pSphereCallback2;  /**< The variable keeps the second sphere callback*/

	vtkSmartPointer < vtkPolyData > m_pPolyDataArtery;  /**< The variable keeps the poly data object of the artery*/
	vtkSmartPointer < vtkPolyDataMapper > m_pMapperArtery; /**< The variable keeps the mapper of the artery*/
	vtkSmartPointer < vtkActor > m_pActorArtery; /**< The variable keeps the actor of the artery*/

    vtkSmartPointer < ArrowSourceStartEnd> m_pArrowSourceStartEnd; /**< The variable keeps the object of the type ArrowSourceStartEnd*/
	vtkSmartPointer<vtkPolyDataMapper> m_pMapperArrow; /**< The variable keeps the mapper of the arrow*/
	vtkSmartPointer<vtkActor> m_pActorArrow;  /**< The variable keeps the actor of the arrow*/



	SelectTwoPoints();  /**< Constructor of the SelectTwoPoints class*/
	~SelectTwoPoints(); /**<Destructor of the SelectTwoPoints class*/

	void updateRenderer();  /**< Update the the render window */

	void setInteractor(vtkRenderWindowInteractor * apIren); /**< Set the render window interactor*/
	
	vtkRenderer * GetRenderer();  /**< Get the render */
	vtkRenderWindow * GetRenderWindow(); /**< Get the render window*/
	
	void UpdatePts(double aarrdbPt1[3], double aarrdbPt2[3], double adbRadiuses, bool abArtery);  /**< Update the centers of the spheres  */

	void readVRML2PolyData(vtkSmartPointer < vtkPolyData > apPolyData, const std::string & astrFileName); /**< Read the artery from a VRML file and save it to a vtkPolyData object  */
	void LoadArtery(const std::string & astrFileName);  /**< Load the artery file */
	void setArteryFileName(const std::string & astrFileName);  /**< Set the artery file name*/

	static TargetClosest compClosest(vtkPolyData * apvtkPolyData, double * apdbStartPoint);  /**< Compute the closest point to the artery*/
	void savePointAndIdxToFile(const char * achFileName); /**< Save the closest point to initial point to iniFile.txt*/
};


#endif //SELECT_TWO_POINTS_H