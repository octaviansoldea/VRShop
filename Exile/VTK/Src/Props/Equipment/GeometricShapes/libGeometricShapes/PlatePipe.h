#ifndef PLATE_PIPE_H
#define PLATE_PIPE_H

#include <string>

#include "vtkSmartPointer.h"

#include "GenericPlate.h"

class vtkPolyData;
class vtkActor;
class vtkTexture;
class vtkObject;

class PlatePipe : public vtkObject {
public:
	static PlatePipe * New();

	~PlatePipe();

	vtkSmartPointer < vtkPolyData > getPoly();
	vtkSmartPointer < vtkActor > getActor();

	std::string getSQLData() const {};
	void initFromSQLData(const std::string & astrSQLData) {};

	void plateTransformation(vtkSmartPointer<vtkTransform> &apVTKTransform);

private:
	PlatePipe();

	GenericPlate * m_pGenericPlate;

	vtkSmartPointer<vtkActor> m_pVTKActor;
	vtkSmartPointer< vtkTexture > m_pVTKTexture;
};
#endif //PLATE_PIPE_H