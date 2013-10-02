#ifndef OSGQT_GUI_H
#define OSGQT_GUI_H

#include <QMainWindow>

#include <osg/Node>
#include <osg/Group>

#include "ui_OSGQT.h"


class OSGQT_GUI : public QMainWindow, public Ui::VRQMainWindow {
	Q_OBJECT
public:
	OSGQT_GUI();
	osg::ref_ptr<osg::Group> pScene;

	public slots:
		void addToScene();
		void removeFromScene();

private:
	void signalSlotComm();
};

#endif //OSGQT_GUI_H