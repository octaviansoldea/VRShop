#ifndef REN_WIN_H
#define REN_WIN_H

#include "vtkSmartPointer.h"

class vtkRenderer;
class vtkRenderWindow;
class vtkRenderWindowInteractor;
class vtkCamera;

class RenWin	{
public:
	RenWin();
	~RenWin();

	vtkSmartPointer< vtkRenderer > m_pRenderer3D;
	vtkSmartPointer< vtkRenderWindow > m_pRenWin3D;
	vtkRenderWindowInteractor * m_pIren3D;

	vtkCamera * m_pCamera;
};
#endif //REN_WIN_H