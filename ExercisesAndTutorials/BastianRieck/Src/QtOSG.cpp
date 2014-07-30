#include "MainWindow.h"

#include <QApplication>

#ifndef GL_DOUBLE
    #define GL_DOUBLE 0x140A
    typedef double GLdouble;
#endif

int main( int argc, char** argv )
{
  QApplication application( argc, argv );

  MainWindow mainWindow;
  mainWindow.show();

  return( application.exec() );
}
