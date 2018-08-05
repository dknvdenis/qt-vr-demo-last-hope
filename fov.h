#pragma once
#include "distortion.h"

class Fov
{
public:
    explicit Fov(float screenWidth, float screenHeight, float ipd,
                 float screenDistance, float lensFov);

    QMatrix4x4 projMatrix(Distortion *distorion, float zNear, float zFar, bool leftEye);

private:
    float m_screenWidth;
    float m_screenHeight;
    float m_ipd;
    float m_screenDistance;
    float m_lensFov;
};

