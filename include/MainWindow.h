//---------------------------------------------------------------------------------
/// @file MainWindow.h
/// @author Alexandra Kim Bui
/// @brief This code file sets up and initializes the Qt window application.
/// @version 3.0
/// @date 21/07/21 Updated to NCCA Coding Standard
/// Initial Version 28/12/20
//---------------------------------------------------------------------------------
#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include "NGLScene.h"

namespace Ui
{
  class MainWindow;
}

class MainWindow : public QMainWindow
{
  Q_OBJECT
public:
  explicit MainWindow(QWidget *parent = nullptr);
  ~MainWindow();

private:
  Ui::MainWindow *m_ui;
  NGLScene *m_gl;

  static int const EXIT_CODE_REBOOT;
};

#endif // MAINWINDOW_H
