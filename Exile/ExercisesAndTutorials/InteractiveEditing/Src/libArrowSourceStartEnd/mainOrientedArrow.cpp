#define USER_MATRIX
#include <vtkArrowSource.h>
#include <vtkPolyData.h>
#include <vtkSmartPointer.h>
#include <vtkPolyDataMapper.h>
#include <vtkActor.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkMath.h>
#include <vtkSphereSource.h>
#include <vtkProperty.h>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>
#include <vtkAxesActor.h>
#include <time.h>
 
int main(int, char *[])
{
  //Create an arrow.
  vtkSmartPointer<vtkArrowSource> arrowSource =
    vtkSmartPointer<vtkArrowSource>::New();
 
  // Generate a random start and end point
//  double startPoint[3], endPoint[3];
//#ifndef main
//  vtkMath::RandomSeed(time(NULL));
//#else
//  vtkMath::RandomSeed(8775070);
//#endif
//  startPoint[0] = vtkMath::Random(-10,10);
//  startPoint[1] = vtkMath::Random(-10,10);
//  startPoint[2] = vtkMath::Random(-10,10);
//  endPoint[0] = vtkMath::Random(-10,10);
//  endPoint[1] = vtkMath::Random(-10,10);
//  endPoint[2] = vtkMath::Random(-10,10);

  double startPoint[3] = {1.0, 0.0, 0.0}, endPoint[3] = {2.0, 2.0, 0.0};

  // Compute a basis
  double normalizedX[3];
  double normalizedY[3];
  double normalizedZ[3];
 
  // The X axis is a vector from start to end
  vtkMath::Subtract(endPoint, startPoint, normalizedX);
  double length = vtkMath::Norm(normalizedX);
  vtkMath::Normalize(normalizedX);
 
  double arbitrary[3] = {0.0, 0.0, 0.0};
  if((fabs(startPoint[1]) < 0.0001) && (fabs(startPoint[2]) < 0.0001))
  {
    arbitrary[1] = 1.0;
  }
  arbitrary[0] = normalizedX[0];
  arbitrary[1] = - normalizedX[2];
  arbitrary[2] = normalizedX[1];
  vtkMath::Cross(normalizedX, arbitrary, normalizedZ);
  vtkMath::Normalize(normalizedZ);
 
  // The Y axis is Z cross X
  vtkMath::Cross(normalizedZ, normalizedX, normalizedY);
  vtkSmartPointer<vtkMatrix4x4> matrix =
    vtkSmartPointer<vtkMatrix4x4>::New();
 
  // Create the direction cosine matrix
  matrix->Identity();
  for (unsigned int i = 0; i < 3; i++)
    {
    matrix->SetElement(i, 0, normalizedX[i]);
    matrix->SetElement(i, 1, normalizedY[i]);
    matrix->SetElement(i, 2, normalizedZ[i]);
    }    
 
  // Apply the transforms
  vtkSmartPointer<vtkTransform> transform = 
    vtkSmartPointer<vtkTransform>::New();
  transform->Translate(startPoint);
  transform->Concatenate(matrix);
  transform->Scale(length, length, length);
 
  // Transform the polydata
  vtkSmartPointer<vtkTransformPolyDataFilter> transformPD = 
    vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  transformPD->SetTransform(transform);
  transformPD->SetInputConnection(arrowSource->GetOutputPort());
 
  //Create a mapper and actor for the arrow
  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
#ifdef USER_MATRIX
  mapper->SetInputConnection(arrowSource->GetOutputPort());
  actor->SetUserMatrix(transform->GetMatrix());
#else
  mapper->SetInputConnection(transformPD->GetOutputPort());
#endif
  actor->SetMapper(mapper);
 
  // Create spheres for start and end point
  vtkSmartPointer<vtkSphereSource> sphereStartSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereStartSource->SetCenter(startPoint);
  sphereStartSource->SetRadius(0.125);
  vtkSmartPointer<vtkPolyDataMapper> sphereStartMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereStartMapper->SetInputConnection(sphereStartSource->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereStart =
    vtkSmartPointer<vtkActor>::New();
  sphereStart->SetMapper(sphereStartMapper);
  sphereStart->GetProperty()->SetColor(1.0, 1.0, .3);
 
  vtkSmartPointer<vtkSphereSource> sphereEndSource =
    vtkSmartPointer<vtkSphereSource>::New();
  sphereEndSource->SetCenter(endPoint);
  sphereEndSource->SetRadius(0.125);
  vtkSmartPointer<vtkPolyDataMapper> sphereEndMapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  sphereEndMapper->SetInputConnection(sphereEndSource->GetOutputPort());
  vtkSmartPointer<vtkActor> sphereEnd =
    vtkSmartPointer<vtkActor>::New();
  sphereEnd->SetMapper(sphereEndMapper);
  sphereEnd->GetProperty()->SetColor(1.0, .3, .3);
 
  //Create a renderer, render window, and interactor
  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  renderWindowInteractor->SetRenderWindow(renderWindow);
 
  vtkSmartPointer < vtkAxesActor > pvtkAxesActor =
	  vtkSmartPointer < vtkAxesActor >::New();
  pvtkAxesActor->SetXAxisLabelText( "x" );
  pvtkAxesActor->SetYAxisLabelText( "y" );
  pvtkAxesActor->SetZAxisLabelText( "z" );

  //Add the actor to the scene
  renderer->AddActor(actor);
  renderer->AddActor(sphereStart);
  renderer->AddActor(sphereEnd);
  renderer->AddActor(pvtkAxesActor);

  renderer->SetBackground(.1, .2, .3); // Background color dark blue
 
 
  //Render and interact
  renderWindow->Render();
  renderWindowInteractor->Start();
 
  return EXIT_SUCCESS;
}