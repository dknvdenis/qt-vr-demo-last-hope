#include "fboRender.h"
#include <memory>
#include <assert.h>
#include <QtMath>
#include "fov.h"
#include "distortion.h"
#include "textureMaterial.h"

FboRender::FboRender(float width, float height, float sphereRadius,
                     const QMatrix4x4 &projMatrix, const QMatrix4x4 &modelMatrix)
{
    initializeOpenGLFunctions();
    init(sphereRadius, projMatrix, modelMatrix);
    setSettings(width, height);
}

void FboRender::setSettings(float width, float height)
{
    assert(width > 0);
    assert(height > 0);

    m_width = width;
    m_height = height;

    m_fbo = std::make_unique<QOpenGLFramebufferObject>(width, height);
}

void FboRender::render()
{
    m_fbo->bind();

    glViewport(0, 0, m_width, m_height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_model->render();

    m_fbo->bindDefault();
}

GLuint FboRender::texture() const
{
    return m_fbo->texture();
}

QImage FboRender::toImage() const
{
    return m_fbo->toImage();
}

void FboRender::init(float sphereRadius, const QMatrix4x4 &projMatrix,
                     const QMatrix4x4 &modelMatrix)
{
    auto geometry = std::unique_ptr<Geometry>(Geometry::createSphere(sphereRadius, 50, 50));
    auto material = std::make_unique<TextureMaterial>(":/vshader.glsl", ":/fshader.glsl",
                                                      ":/Equirectangular-projection.jpg");

    m_model = std::make_unique<Model>(std::move(geometry), std::move(material));
    m_model->setProjMatrix(projMatrix);
    m_model->setModelMatrix(modelMatrix);
}
