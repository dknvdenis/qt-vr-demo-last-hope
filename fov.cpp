#include "fov.h"
#include <QtMath>
#include <QMatrix4x4>

Fov::Fov(float screenWidth, float screenHeight, float ipd,
         float screenDistance, float lensFov)
    : m_screenWidth(screenWidth),
      m_screenHeight(screenHeight),
      m_ipd(ipd),
      m_screenDistance(screenDistance),
      m_lensFov(lensFov)
{

}

QMatrix4x4 Fov::projMatrix(Distortion *distorion, float zNear, float zFar, bool leftEye)
{
    Q_ASSERT(distorion);

    float lenseTan = qTan(qDegreesToRadians(m_lensFov));

    float halfW = m_screenWidth / 2.f;
    float halfH = m_screenHeight / 2.f;
    float halfIpd = m_ipd / 2.f;

    float l;
    float r;
    if (leftEye)
    {
        l = halfIpd - halfW;
        r = halfIpd;
    }
    else
    {
        l = -halfIpd;
        r = halfW - halfIpd;
    }

    float t = halfH;
    float b = -halfH;

    float screenLeftTan = l / m_screenDistance;
    float screenRightTan = r / m_screenDistance;
    float screenTopTan = t / m_screenDistance;
    float screenBottomTan = b / m_screenDistance;

    screenLeftTan = distorion->distort(screenLeftTan);
    screenRightTan = distorion->distort(screenRightTan);
    screenTopTan = distorion->distort(screenTopTan);
    screenBottomTan = distorion->distort(screenBottomTan);

    QMatrix4x4 proj;
    proj.setToIdentity();

    proj.frustum(qMax(-lenseTan, screenLeftTan),   // left
                 qMin(lenseTan, screenRightTan),   // rigth
                 qMax(-lenseTan, screenBottomTan), // bottom
                 qMin(lenseTan, screenTopTan),     // top
                 zNear, zFar);

    return proj;
}
