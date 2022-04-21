//---------------------------------------------------------------------------------
/// @file main.cpp
/// @author Alexandra Kim Bui
/// @brief This code file sets up and initializes the Qt window application.
/// @version 3.0
/// @date 21/07/21 Updated to NCCA Coding Standard
/// Initial Version 28/12/20
//---------------------------------------------------------------------------------

#include <QApplication>
#include <QSurfaceFormat>
#include "MainWindow.h"

int main(int argc, char **argv)
{

  QSurfaceFormat format;
  format.setSamples(4);

#if defined( __APPLE__)
  format.setMajorVersion(4);
  format.setMinorVersion(2);
#else
  format.setMajorVersion(4);
  format.setMinorVersion(3);
#endif
  format.setProfile(QSurfaceFormat::CoreProfile);
  format.setDepthBufferSize(24);
  QSurfaceFormat::setDefaultFormat(format);
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
