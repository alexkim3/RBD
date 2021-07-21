#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/NGLStream.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <QGuiApplication>
#include <QMouseEvent>

NGLScene::NGLScene(QWidget *_parent) : QOpenGLWidget( _parent ), m_ball(m_container), m_container()
{
    setFocus();
    this->resize(_parent->size());

    m_wireframe = false;
    m_numBalls = 4;
    m_gravity = 0.0f;
}

NGLScene::~NGLScene()
{

}


void NGLScene::resizeGL( int _w, int _h )
{
    m_projection=ngl::perspective( 50.0f, static_cast<float>( _w ) / _h, 0.1f, 200.0f );
    m_win.width  = static_cast<int>( _w * devicePixelRatio() );
    m_win.height = static_cast<int>( _h * devicePixelRatio() );
}


void NGLScene::initializeGL()
{
    ngl::NGLInit::initialize();
    glClearColor( 0.9f, 0.9f, 0.9f, 1.0f ); // Grey Background
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_MULTISAMPLE );
    glEnable( GL_BLEND);
    glBlendFunc( GL_BLEND_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ngl::Vec3 from{ 0.0f, 30.0f, 100.0f };
    ngl::Vec3 to{ 0.0f, 0.0f, 0.0f };
    ngl::Vec3 up{ 0.0f, 1.0f, 0.0f };
    m_view=ngl::lookAt(from,to,up);
    ngl::ShaderLib::setUniform( "camPos", from );

    ngl::VAOPrimitives::createSphere("Sphere", m_ball.m_objects[0].radius,10);
    ngl::VAOPrimitives::createCylinder("Cylinder", m_container.radius, 4, 16, 0);

    startTimer(10);
}

void NGLScene::loadMatricesToShader()
{
    auto MVP = m_projection * m_view *m_mouseGlobalTX;
    ngl::ShaderLib::setUniform("MVP", MVP);
}

void NGLScene::paintGL()
{
    glViewport( 0, 0, m_win.width, m_win.height );
    // clear the screen and depth buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    ngl::ShaderLib::use(ngl::nglColourShader);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    m_mouseGlobalTX.identity();
    m_mouseGlobalTX.translate(m_container.position.m_x, m_container.position.m_y, m_container.position.m_z);
    ngl::ShaderLib::setUniform("Colour", 1.f, 0.627f, 0.478f, 1.f);
    //m_mouseGlobalTX.rotateX(90.f);
    //m_mouseGlobalTX.translate(0.f, -1.f, 0.f);
    m_mouseGlobalTX.scale(m_container.radius*2, m_container.radius*2, m_container.radius*2);
    loadMatricesToShader();
    ngl::VAOPrimitives::draw("cube");


    for (auto &&ball : m_ball.m_objects)
    {
        m_mouseGlobalTX.identity();
        m_mouseGlobalTX.translate(ball.position.m_x, ball.position.m_y, ball.position.m_z);
        if(m_wireframe == true)
        {
            glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
        }
        else
        {
            glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
        }
        ngl::ShaderLib::setUniform("Colour", 0.f, 0.f, 0.f, 1.f);
        loadMatricesToShader();
        ngl::VAOPrimitives::draw("Sphere");
    }
}


void NGLScene::timerEvent(QTimerEvent *event_)
{
    m_ball.move();
    update();
}

void NGLScene::keyPressEvent(QKeyEvent *_event)
{
  switch (_event->key())
  {
   case Qt::Key_Escape :
   {
     QGuiApplication::exit(EXIT_SUCCESS);
     break;
   }

   case Qt::Key_Space :
   {
     m_win.spinXFace=0;
     m_win.spinYFace=0;
     m_modelPos.set(ngl::Vec3::zero());
     break;
   }

   default :
   {
     break;
   }
  }
  update();

}


void NGLScene::toggleWireframe(
                              bool _mode
                              )
{
    m_wireframe=_mode;
    update();
}


void NGLScene::setGravity(double _m_gravity)
{
  m_gravity = _m_gravity;
  update();
}
