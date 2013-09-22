#ifndef BASE_OBJECT_H
#define BASE_OBJECT_H

#include <iostream>

#include "OrientationWidgets.h"
#include "vtkSmartPointer.h"

#include "DatabaseMgr.h"
#include "RenWin.h"
#include "FunctorPathResource.h"

class QVTKWidget;

class BaseEditor	{
public:
	BaseEditor();
	~BaseEditor();

	void setQVTKWidgets(QVTKWidget * apQVTKWidget);

protected:
	DatabaseMgr *pDatabaseMgr;
	RenWin renWin;
	QVTKWidget * m_pQVTKWidget;
	
	vtkSmartPointer < OrientationWidgets > m_pOrientationWidgets;
};
#endif //BASE_OBJECT_H
