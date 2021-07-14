#ifndef NGLSCENE_H_
#define NGLSCENE_H_
#include <ngl/Vec3.h>
#include <ngl/Mat4.h>
#include <array>
#include <QOpenGLWindow>
#include "Ball.h"
#include "Container.h"
//#include "WindowParams.h"

class NGLScene : public QOpenGLWindow
{
    Q_OBJECT
public:
    NGLScene();
    ~NGLScene() override;
    void initializeGL() override;
    void paintGL() override;
    void resizeGL(int _w, int _h) override;

    private:
    //WinParams m_win;
    ngl::Mat4 m_mouseGlobalTX; //m_transform
    ngl::Mat4 m_view;
    ngl::Mat4 m_projection;
    std::array<Ball,2> m_ball;
    Container m_container;

    void loadMatricesToShader();
    void timerEvent(QTimerEvent *event_ = nullptr) override;
};


#endif
