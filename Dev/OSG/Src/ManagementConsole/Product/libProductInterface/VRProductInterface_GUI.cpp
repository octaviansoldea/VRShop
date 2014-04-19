#include "VRProduct.h"

#include <osg/Group>

#include "VRProductInterface_GUI.h"

using namespace VR;
using namespace osg;
using namespace Ui;

//----------------------------------------------------------------------

ProductInterface_GUI::ProductInterface_GUI() :
m_pProduct(0)	{
	setupUi(this);

}

ProductInterface_GUI::ProductInterface_GUI(QWidget * parent, Product * apProduct) : 
QFrame(parent),m_pProduct(apProduct)	{
	setupUi(this);
}

//----------------------------------------------------------------------

ProductInterface_GUI::~ProductInterface_GUI()	{
	delete m_pProduct;
}