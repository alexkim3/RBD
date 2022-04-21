//---------------------------------------------------------------------------------
/// @file NGLScene.h
/// @author Alexandra Kim Bui
/// @brief This code file sets up and initializes the Qt window application.
/// @version 3.0
/// @date 21/07/21 Updated to NCCA Coding Standard
/// Initial Version 28/12/20
//---------------------------------------------------------------------------------
#ifndef NGLSCENE_H_
#define NGLSCENE_H_
#include <memory>
#include "Ball.h"
#include "Container.h"
#include "WindowParams.h"
#include <QOpenGLWidget>
#include "Pile.h"


class NGLScene : public QOpenGLWidget
{
  Q_OBJECT
public:
  NGLScene(QWidget *_parent);
  NGLScene();
  ~NGLScene() override;
  void initializeGL() override;
  void paintGL() override;
  void resizeGL(int _w, int _h) override;

  private:
  Pile<Ball> m_ball;
  Container m_container;
  WinParams m_win;
  ngl::Mat4 m_mouseGlobalTX; //m_transform
  ngl::Mat4 m_view;
  ngl::Mat4 m_projection;
  ngl::Vec3 m_modelPos;
  /// @brief wireframe
  bool m_wireframe;
  ///@brief number of balls
  int m_numBalls;
  double m_gravity;


  void loadMatricesToShader();
  void timerEvent(QTimerEvent *event_ = nullptr) override;
  void keyPressEvent(QKeyEvent *_event) override;
  void mouseMoveEvent(QMouseEvent *_event) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse button is pressed
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void mousePressEvent(QMouseEvent *_event) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse button is released
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void mouseReleaseEvent(QMouseEvent *_event) override;
  //----------------------------------------------------------------------------------------------------------------------
  /// @brief this method is called everytime the mouse wheel is moved
  /// inherited from QObject and overridden here.
  /// @param _event the Qt Event structure
  //----------------------------------------------------------------------------------------------------------------------
  void wheelEvent(QWheelEvent *_event) override;

public slots:
  /// @brief a slot to toggle wireframe mode
  /// @param[in] _mode the mode passed from the toggle
  void toggleWireframe(
                      bool _mode
                      );
  void setGravity(double _gravity);

};


#endif
