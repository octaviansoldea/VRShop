#include <QApplication>

#include "VRAppData.h"

#include "VREmbeddedWidgetStatics.h"

using namespace std;
using namespace VR;

EmbeddedWidgetStatics::EmbeddedWidgetStatics() {
	string strPluginsPath = AppData::getFPathDependencies();
	QApplication::addLibraryPath(strPluginsPath.c_str());
}

EmbeddedWidgetStatics::~EmbeddedWidgetStatics() {
}
