#include "vrRenderer.h"
#include <memory>
#include <QtMath>
#include <QDebug>

#include "distortion.h"
#include <fov.h>
#include <distortionMaterial.h>
#include "textureMaterial.h"

namespace {
const float metersPerInch = 0.0254f;
}

VRRenderer::VRRenderer()
    : m_vX(0),
      m_vY(0),
      m_vWidth(1),
      m_vHeight(1)
{

}

void VRRenderer::setQmlViewportSize(const QSize &size)
{
    m_qmlViewportSize = size;
}

void VRRenderer::setWindow(QQuickWindow *window)
{
    m_window = window;
}

void VRRenderer::paint()
{
    if (!m_leftPlane)
    {
        initializeOpenGLFunctions();

        DistortionKoeffs koeffs {m_vr_k1, m_vr_k2};
        auto distortion = std::make_unique<Distortion>(koeffs);

        initFbo(distortion.get());
        initPlanes(distortion.get());
    }

    glClearColor(0, 0, 0, 1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    m_leftEyeFbo->render();
    m_rightEyeFbo->render();

    glViewport(0, 0, m_qmlViewportSize.width(), m_qmlViewportSize.height());
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_leftPlane->render();
    m_rigthPlane->render();

    m_window->resetOpenGLState();
}

void VRRenderer::setVr_meshCols(int vr_meshCols)
{
    m_vr_meshCols = vr_meshCols;
}

void VRRenderer::setVr_meshRows(int vr_meshRows)
{
    m_vr_meshRows = vr_meshRows;
}

void VRRenderer::setVr_k2(float vr_k2)
{
    m_vr_k2 = vr_k2;
}

void VRRenderer::setVr_k1(float vr_k1)
{
    m_vr_k1 = vr_k1;
}

void VRRenderer::setScene_height(float scene_height)
{
    m_scene_height = scene_height;
}

void VRRenderer::setScene_width(float scene_width)
{
    m_scene_width = scene_width;
}

void VRRenderer::setScene_zFar(float scene_zFar)
{
    m_scene_zFar = scene_zFar;
}

void VRRenderer::setScene_zNear(float scene_zNear)
{
    m_scene_zNear = scene_zNear;
}

void VRRenderer::setScene_sphereRadius(float scene_sphereRadius)
{
    m_scene_sphereRadius = scene_sphereRadius;
}

QMatrix4x4 VRRenderer::orthoProj(float left, float right, float bottom, float top)
{
    QMatrix4x4 proj;

    proj.setToIdentity();
    proj.ortho(left, right, bottom, top, 10.f, -10.f);

    return proj;
}

void VRRenderer::initPlanes(Distortion *distortion)
{
    float ppi = qSqrt(m_scene_width * m_scene_width + m_scene_height * m_scene_height) / m_diag;
    float ipdInPx = m_ipd / metersPerInch * ppi;

    auto projMatrix = orthoProj(0, m_scene_width, 0, m_scene_height);
    auto koeffs = distortion->invKoeffs();
    float halfWidth = m_scene_width / 2.f;
    float halfHeight = m_scene_height / 2.f;

    float maxRadius = QVector2D(halfWidth / 2.f, halfHeight).length();
    float scaleX = 1.f / distortion->distort(halfWidth / 2.f / maxRadius);
    float scaleY = 1.f / distortion->distort(halfHeight / maxRadius);

    auto plane = Geometry::createPlane(halfWidth * scaleX,
                                       m_scene_height * scaleY,
                                       m_vr_meshRows, m_vr_meshCols);
    auto geometry = std::shared_ptr<Geometry>(plane);

//  Left eye ---------------------------------------------------------------------------

    QVector2D center(halfWidth - ipdInPx / 2.f, halfHeight);
    QMatrix4x4 modelMatrix;
    modelMatrix.setToIdentity();
    modelMatrix.translate((m_scene_width / 2.f - 2.f * geometry->center().x()) / 2.f,
                          (m_scene_height - 2.f * geometry->center().y()) / 2.f, 0);

    auto leftMaterial = std::make_shared<DistortionMaterial>(m_leftEyeFbo, koeffs,
                                                             center, maxRadius);

    m_leftPlane = std::make_unique<Model>(geometry, leftMaterial);

    m_leftPlane->setProjMatrix(projMatrix);
    m_leftPlane->setModelMatrix(modelMatrix);

//  Right eye ---------------------------------------------------------------------------

    center += QVector2D(ipdInPx, 0.f);
    modelMatrix.translate(halfWidth, 0.f, 0.f);

    auto rightMaterial = std::make_shared<DistortionMaterial>(m_rightEyeFbo, koeffs,
                                                              center, maxRadius);
    m_rigthPlane = std::make_unique<Model>(geometry, rightMaterial);

    m_rigthPlane->setProjMatrix(projMatrix);
    m_rigthPlane->setModelMatrix(modelMatrix);
}

void VRRenderer::initFbo(Distortion *distortion)
{
    float ppi = qSqrt(m_scene_width * m_scene_width + m_scene_height * m_scene_height) / m_diag;
    float shift = (m_ipd / metersPerInch * ppi) / 2.f;
    auto fov = std::make_unique<Fov>(m_screenWidth, m_screenHeight, m_ipd,
                                     m_screenDistance, m_lensFov);

    QMatrix4x4 leftMatrix;
    leftMatrix.setToIdentity();
    leftMatrix.rotate(-90.f, 0.f, 1.f, 0.f);
    leftMatrix.translate(0, 0, shift);

    QMatrix4x4 rightMatrix;
    rightMatrix.setToIdentity();
    rightMatrix.rotate(-90.f, 0.f, 1.f, 0.f);
    rightMatrix.translate(0.f, 0.f, -shift);

    float fboW = m_scene_width;
    float fboH = m_scene_height;

    auto leftEyeProj = fov->projMatrix(distortion, m_scene_zNear, m_scene_zFar, true);
    auto rightEyeProj = fov->projMatrix(distortion, m_scene_zNear, m_scene_zFar, false);

    m_leftEyeFbo = std::make_shared<FboRender>(fboW, fboH, m_scene_sphereRadius,
                                               leftEyeProj, leftMatrix);

    m_rightEyeFbo = std::make_shared<FboRender>(fboW, fboH, m_scene_sphereRadius,
                                                rightEyeProj, rightMatrix);
}
