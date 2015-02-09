#include <osgDB/ReadFile>

#include <QPixmap>
#include <QImageReader>
#include <QFileDialog>

#include "VRAbstractObject.h"
#include "VREditItem_GUI.h"
#include "VREditItemPrism_GUI.h"
#include "VREditItemFurniture_GUI.h"

#include "VREditItem_GUIBase.h"

using namespace VR;
using namespace osg;
using namespace std;

//----------------------------------------------------------------------

EditItem_GUIBase::EditItem_GUIBase(AbstractObject * apAbstractObject)	{
	m_pAbstractObject = apAbstractObject;
}

//----------------------------------------------------------------------

EditItem_GUIBase::~EditItem_GUIBase()	{
}

//======================================================================

EditItem_GUIBase * EditItem_GUIBase::createInstance(AbstractObject * apAbstractObject)	{
	const string & strGUIName = apAbstractObject->className();

	if (strGUIName == "Plate3D")	{
		return new EditItem_GUI(apAbstractObject);
	} else if (strGUIName == "Prism")	{
		return new EditItemPrism_GUI(apAbstractObject);
	} else if (strGUIName == "Cylinder")	{
		return new EditItemPrism_GUI(apAbstractObject);
	} else if ((strGUIName == "Container") || (strGUIName == "Cupboard")) {
		return new EditItemFurniture_GUI(apAbstractObject);
	} else {
		return new EditItem_GUI(apAbstractObject);
	}
}


//----------------------------------------------------------------------

void EditItem_GUIBase::slotInsertImage()	{
}

//----------------------------------------------------------------------

void EditItem_GUIBase::slotBrowseDirectory()	{
	QString qstrFileName = QFileDialog::getOpenFileName(this, 
		tr("Open File"),
		tr("."), "*.bmp");

	previewTexture(qstrFileName);
	m_pAbstractObject->setTexture(qstrFileName.toStdString());
}

//----------------------------------------------------------------------

void EditItem_GUIBase::accept()	{
	QDialog::accept();
}

//----------------------------------------------------------------------

vector<float> EditItem_GUIBase::getColor() const	{
	return vector<float>(0);
}

//----------------------------------------------------------------------

string EditItem_GUIBase::getTexture()	{
	return "";
}
