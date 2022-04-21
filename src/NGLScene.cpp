//---------------------------------------------------------------------------------
/// @file NGLScene.cpp
/// @author Alexandra Kim Bui
/// @brief This code file sets up and initializes the Qt window application.
/// @version 3.0
/// @date 21/07/21 Updated to NCCA Coding Standard
/// Initial Version 28/12/20
//---------------------------------------------------------------------------------
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
  std::cout << "Shutting down NGL, removing VAO's and Shaders\n";
}

void NGLScene::resizeGL( int _w, int _h )
{
  m_projection=ngl::perspective( 50.0f, static_cast<float>( _w ) / _h, 0.1f, 200.0f );
  m_win.width  = static_cast<int>( _w * devicePixelRatio() );
  m_win.height = static_cast<int>( _h * devicePixelRatio() );
}

constexpr auto shaderProgram = "PBR";

void NGLScene::initializeGL()
{
  ngl::NGLInit::initialize();
  glClearColor( 0.9f, 0.9f, 0.9f, 1.0f ); // Grey Background
  glEnable( GL_DEPTH_TEST );
  glEnable( GL_MULTISAMPLE );
  glEnable( GL_BLEND);
  glBlendFunc( GL_BLEND_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  constexpr auto vertexShader  = "PBRVertex";
  constexpr auto fragShader    = "PBRFragment";
  // create the shader program
  ngl::ShaderLib::createShaderProgram( shaderProgram );
  // now we are going to create empty shaders for Frag and Vert
  ngl::ShaderLib::attachShader( vertexShader, ngl::ShaderType::VERTEX );
  ngl::ShaderLib::attachShader( fragShader, ngl::ShaderType::FRAGMENT );
  // attach the source
  ngl::ShaderLib::loadShaderSource( vertexShader, "shaders/PBRVertex.glsl" );
  ngl::ShaderLib::loadShaderSource( fragShader, "shaders/PBRFragment.glsl" );
  // compile the shaders
  ngl::ShaderLib::compileShader( vertexShader );
  ngl::ShaderLib::compileShader( fragShader );
  // add them to the program
  ngl::ShaderLib::attachShaderToProgram( shaderProgram, vertexShader );
  ngl::ShaderLib::attachShaderToProgram( shaderProgram, fragShader );
  // now we have associated that data we can link the shader
  ngl::ShaderLib::linkProgramObject( shaderProgram );
  // and make it active ready to load values
  ngl::ShaderLib::use(shaderProgram );

  ngl::Vec3 from{ 0.0f, 30.0f, 100.0f };
  ngl::Vec3 to{ 0.0f, 0.0f, 0.0f };
  ngl::Vec3 up{ 0.0f, 1.0f, 0.0f };
  m_view=ngl::lookAt(from,to,up);
  ngl::ShaderLib::setUniform( "camPos", from );

  //ngl::ShaderLib::setUniform("lightPosition",m_lightPos.toVec3());
  ngl::ShaderLib::setUniform("lightColor",400.0f,400.0f,400.0f);
  ngl::ShaderLib::setUniform("exposure",2.2f);
  ngl::ShaderLib::setUniform("albedo",0.950f, 0.71f, 0.29f);

  ngl::ShaderLib::setUniform("metallic",1.02f);
  ngl::ShaderLib::setUniform("roughness",0.38f);
  ngl::ShaderLib::setUniform("ao",0.2f);
  ngl::ShaderLib::printRegisteredUniforms(shaderProgram);

  ngl::VAOPrimitives::createSphere("Sphere", m_ball.m_objects[0].m_radius,10);
  ngl::VAOPrimitives::createCylinder("Cylinder", m_container.m_radius, 4, 16, 0);

  startTimer(10);
}

void NGLScene::loadMatricesToShader()
{
  ngl::ShaderLib::use("PBR");
  struct transform
  {
    ngl::Mat4 MVP;
    ngl::Mat4 normalMatrix;
    ngl::Mat4 M;
  };

   transform t;
   t.M=m_view*m_mouseGlobalTX;

   t.MVP=m_projection*t.M;
   t.normalMatrix=t.M;
   t.normalMatrix.inverse().transpose();
   ngl::ShaderLib::setUniformBuffer("TransformUBO",sizeof(transform),&t.MVP.m_00);
  // ngl::msg->addMessage(fmt::format("size {0}",sizeof(transform)));

}

void NGLScene::paintGL()
{
  glViewport( 0, 0, m_win.width, m_win.height );
  // clear the screen and depth buffer
  glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  ngl::ShaderLib::use(ngl::nglColourShader);
  glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);


  m_mouseGlobalTX.identity();
  m_mouseGlobalTX.translate(m_container.m_position.m_x, m_container.m_position.m_y, m_container.m_position.m_z);
  //ngl::ShaderLib::setUniform("Colour", 1.f, 1.f, 1.f, 1.f);
  m_mouseGlobalTX.scale(m_container.m_radius*2, m_container.m_radius*2, m_container.m_radius*2);

  loadMatricesToShader();

  ngl::VAOPrimitives::draw("cube");

  ngl::Mat4 MVP=m_projection*m_view*m_mouseGlobalTX;
  ngl::Mat3 normalMatrix=m_view*m_mouseGlobalTX;
  normalMatrix.inverse().transpose();
  ngl::ShaderLib::setUniform("MVP",MVP);
  ngl::ShaderLib::setUniform("normalMatrix",normalMatrix);

  for (auto &&ball : m_ball.m_objects)
  {
    m_mouseGlobalTX.identity();
    m_mouseGlobalTX.translate(ball.m_position.m_x, ball.m_position.m_y, ball.m_position.m_z);
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

void NGLScene::timerEvent(QTimerEvent *_event)
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


void NGLScene::setGravity(
                          double _m_gravity
                          )
{
  m_gravity = _m_gravity;
  update();
}
