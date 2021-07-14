#include "NGLScene.h"
#include <ngl/NGLInit.h>
#include <ngl/NGLStream.h>
#include <ngl/ShaderLib.h>
#include <ngl/VAOPrimitives.h>
#include <QGuiApplication>
#include <QMouseEvent>

NGLScene::NGLScene() : /*m_pileofballs(), */m_container()
{
    setTitle( "Rigid body dynamics" );
}


NGLScene::~NGLScene()
{
    std::cout << "Shutting down NGL, removing VAO's and Shaders\n";
}

void NGLScene::resizeGL( int _w, int _h )
{
    m_projection=ngl::perspective( 45.0f, static_cast<float>( _w ) / _h, 0.1f, 200.0f );

    //m_win.width  = static_cast<int>( _w * devicePixelRatio() );
    //m_win.height = static_cast<int>( _h * devicePixelRatio() );
}


void NGLScene::initializeGL()
{
    ngl::NGLInit::initialize();
    glClearColor( 0.9f, 0.9f, 0.9f, 1.0f ); // Grey Background
    glEnable( GL_DEPTH_TEST );
    glEnable( GL_MULTISAMPLE );
    glEnable( GL_BLEND);
    glBlendFunc( GL_BLEND_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    ngl::Vec3 from{ 1.0f, 2.0f, 4.0f };
    ngl::Vec3 to{ 0.0f, 0.0f, 0.0f };
    ngl::Vec3 up{ 0.0f, 1.0f, 0.0f };
    m_view=ngl::lookAt(from,to,up);
    ngl::VAOPrimitives::createSphere("Sphere", m_ball[0].radius,20);
    ngl::VAOPrimitives::createSphere("Sphere", m_ball[1].radius,20);
    ngl::VAOPrimitives::createCylinder("Cylinder", m_container.radius, 3, 16, 0);

    startTimer(10);

}


void NGLScene::loadMatricesToShader()
{
    auto MVP = m_projection * m_view *m_mouseGlobalTX;
    ngl::ShaderLib::setUniform("MVP", MVP);
}

void NGLScene::paintGL()
{
    glViewport( 0, 0, width(), height() );
    // clear the screen and depth buffer
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    ngl::ShaderLib::use(ngl::nglColourShader);
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);

    m_mouseGlobalTX.identity();
    m_mouseGlobalTX.translate(m_container.position.m_x, m_container.position.m_y, m_container.position.m_z);
    ngl::ShaderLib::setUniform("Colour", 1.f, 0.627f, 0.478f, 1.f);
    m_mouseGlobalTX.rotateX(90.f);
    m_mouseGlobalTX.translate(0.f, -1.f, 0.f);
    loadMatricesToShader();


    ngl::VAOPrimitives::draw("Cylinder");

    m_mouseGlobalTX.identity();
    m_mouseGlobalTX.translate(m_ball[0].position.m_x, m_ball[0].position.m_y, m_ball[0].position.m_z);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    ngl::ShaderLib::setUniform("Colour", 0.f, 0.f, 0.f, 1.f);
    loadMatricesToShader();
    ngl::VAOPrimitives::draw("Sphere");

    m_mouseGlobalTX.identity();
    m_mouseGlobalTX.translate(m_ball[0].position.m_x, m_ball[0].position.m_y+1, m_ball[0].position.m_z);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    ngl::ShaderLib::setUniform("Colour", 0.f, 0.f, 0.f, 1.f);
    loadMatricesToShader();
    ngl::VAOPrimitives::draw("Sphere");

}

void NGLScene::timerEvent(QTimerEvent *event_)
{
    m_ball[0].fall();
    update();
}

