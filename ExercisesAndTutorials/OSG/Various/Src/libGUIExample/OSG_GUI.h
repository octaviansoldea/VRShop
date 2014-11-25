#ifndef OSGQT_GUI_H
#define OSGQT_GUI_H

#include <QDialog>
#include <QMainWindow>

#include <osg/Node>
#include <osg/Group>

#include "Model3D.h"

#include "ui_GUI-MainWindow.h"

class OSGQT_GUI : public QMainWindow, public Ui::MainWindow	{
	Q_OBJECT
public:
	OSGQT_GUI();
	osg::ref_ptr<osg::Group> pScene;

	public slots:
		void addToScene();
		void changeColor();

private:
	void signalSlotComm();
};

#endif //OSGQT_GUI_H