#ifndef ABSTRACT_ORIENTATION_WIDGET_H
#define ABSTRACT_ORIENTATION_WIDGET_H

#include "vtkObject.h"

class AbstractOrientationWidget : public vtkObject{
public:

	virtual void VisibilityOn() = 0;
	virtual void VisibilityOff() = 0;
	virtual int GetVisibility() = 0;
	virtual void SetVisibility(int anVisible) = 0;

	virtual ~AbstractOrientationWidget() = 0;
	//virtual void Delete() = 0;
private:

};

#endif //ABSTRACT_ORIENTATION_WIDGET_H