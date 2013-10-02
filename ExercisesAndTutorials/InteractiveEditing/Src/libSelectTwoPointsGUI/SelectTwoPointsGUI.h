#ifndef SELECT_TWO_POINTS_GUI_H
#define SELECT_TWO_POINTS_GUI_H

#include <QMainWindow>
#include <string>

#include "ui_SelectTwoPointsGUI.h"

#include "SelectTwoPoints.h"

class vtkRenderer;
class vtkEventQtSlotConnect;
class vtkObject;
class vtkCommand;

//===========================================================================
/*!
    \file   SelectTwoPointsGUI.h
	\class	SelectTwoPointsGUI
	\brief	The class SelectTwoPointsGUI implements the GUI interface required at the initialization step, 
	        when an initial point onto the artery has to be choosen. 
*/
//===========================================================================

class SelectTwoPointsGUI : public QMainWindow, public Ui::MainWindow_SelectTwoPoints
{

  std::string m_strArteryFileName; /**< The variable keeps the name of the artery file */
  bool m_bArtery;  /**< The variable indicates if the artery is loaded or not */
  
  QString SelectTwoPointsGUI::openDialog(const char * apchSuffix); /**< Open the dialog that will allow to choose the artery file */
  QString SelectTwoPointsGUI::saveDialog(const char * apchSuffix); /**< Open the dialog that will allow to save the iniFile.txt file */

  Q_OBJECT

public:

  SelectTwoPoints m_SelectTwoPoints; /**< Constructor of SelectTwoPointsGUI */
  SelectTwoPointsGUI(); /**<Destructor of SelectTwoPointsGUI */
  ~SelectTwoPointsGUI();

  bool getStatusArtery(); /**< Get the status of the artery. If the artery is loaded in the window, this function returns true, otherwise returns false. */
  void setStatusArtery(bool abArtery); /**< Set the status of the artery. The parameter m_bArtery is set to true if the artery is loaded in the window and false if it is not loaded. */

public slots:

  void slotLoadFile(); /**< Set the slot that load the artery file */
  void slotSaveFile(); /**< Set the slot that save the file iniFile.txt */

  void slotUpdatePts(double adbDummy); /**< Set the slot that update the points from the SpinBoxes, on the right part of the GUI  */
};

#endif //SELECT_TWO_POINTS_GUI_H