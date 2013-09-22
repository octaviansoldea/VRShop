#ifndef SHELF_H
#define SHELF_H

#include "vtkSmartPointer.h"
#include "vtkAssembly.h"

class vtkTransform;
class PlatePipe;

class Shelf : public vtkAssembly {
public:
	static Shelf * New();

	~Shelf();
	void setSizes(double adbLenX, double adbLenY, double adbLenZ);

private:
	Shelf();
	PlatePipe * m_arrpPlatePipe[6];
};
#endif //SHELF_H