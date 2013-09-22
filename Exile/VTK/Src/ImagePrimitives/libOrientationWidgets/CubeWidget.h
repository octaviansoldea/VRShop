#ifndef CUBE_WIDGET_H
#define CUBE_WIDGET_H

#include "vtkOrientationMarkerWidget.h"
#include "vtkAnnotatedCubeActor.h"
#include "vtkSmartPointer.h"

#include "AbstractOrientationWidget.h"

class CubeWidget : public AbstractOrientationWidget {

	//static CubeWidget *New();
	CubeWidget();	
	//virtual ~CubeWidget();
	//virtual void Delete();
public:
	virtual void VisibilityOn();
	virtual void VisibilityOff();
	virtual int GetVisibility();
	virtual void SetVisibility(int anVisible);

	
	static CubeWidget *New();
	

	
	vtkOrientationMarkerWidget * GetOrientationMarkerWidget();

protected:
	vtkSmartPointer < vtkAnnotatedCubeActor > m_pvtkAnnotatedCubeActor;
	vtkSmartPointer < vtkOrientationMarkerWidget > m_pvtkOrientationMarkerWidget;
};

#endif //CUBE_WIDGET_H