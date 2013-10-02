#ifndef VR_PRODUCT_INTERFACE_GUI_H
#define VR_PRODUCT_INTERFACE_GUI_H

#include <QFrame>

#include <osg/Node>
#include <osg/Group>

#include "ui_VRProductInterface.h"


class VRProductInterface_GUI : public QFrame, public Ui::VRProductInterface {
	Q_OBJECT
public:
	VRProductInterface_GUI();
	~VRProductInterface_GUI();
};

#endif //VR_PRODUCT_INTERFACE_GUI_H