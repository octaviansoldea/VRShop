#include <iostream>
#include <QApplication>
#include <string>
#include <QString>
#include <vector>


#include "VRProduct.h"

using namespace VR;

int main(int argc, char * argv[])	{
	QApplication app(argc, argv);

	Product product;
	product.createProductDB();

	return(0);
}