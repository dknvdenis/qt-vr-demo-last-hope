#include "distortion.h"
#include <QVector>
#include <QtMath>

Distortion::Distortion(const DistortionKoeffs &distKoef)
    : m_koeffs(distKoef)
{
    compInvKoeffs(1, 10);
}

float Distortion::distort(float r) const
{
    return distortPriv(r, m_koeffs);
}

float Distortion::distortInv(float r) const
{
    return  distortPriv(r, m_invKoeffs);
}

DistortionKoeffs Distortion::invKoeffs() const
{
    return m_invKoeffs;
}

float Distortion::distortPriv(float r, const DistortionKoeffs &koef) const
{
    float r2 = r * r;
    return r * (1.f + koef.k1 * r2 + koef.k2 * r2 * r2);
}

void Distortion::compInvKoeffs(float maxRadius, int count)
{
    float sumR4 = 0;
    float sumR6 = 0;
    float sumR8 = 0;
    float sumR10 = 0;
    float sumR3d = 0;
    float sumR5d = 0;

    float step = maxRadius / count;
    for (int i = 0; i < count; i++)
    {
        float out = (i + 1) * step;
        float in = distort(out);

        sumR4 += qPow(in, 4);
        sumR6 += qPow(in, 6);
        sumR8 += qPow(in, 8);
        sumR10 += qPow(in, 10);

        sumR3d += qPow(in, 3) * out;
        sumR5d += qPow(in, 5) * out;
    }

    float s1 = sumR3d - sumR4;
    float s2 = sumR5d - sumR6;

    QMatrix2x2 mat;
    mat.fill(0);

    mat(0, 0) = sumR6;
    mat(0, 1) = sumR8;
    mat(1, 0) = sumR8;
    mat(1, 1) = sumR10;

    float det = matDet(mat);
    if (qFuzzyCompare(det, 0))
    {
        qDebug() << "Determinant is zero";
        m_invKoeffs = {0, 0};
        return;
    }

    QMatrix2x2 mat1 = mat;
    mat1(0, 0) = s1;
    mat1(1, 0) = s2;

    QMatrix2x2 mat2 = mat;
    mat2(0, 1) = s1;
    mat2(1, 1) = s2;

    float det1 = matDet(mat1);
    float det2 = matDet(mat2);

    float k1 = det1 / det;
    float k2 = det2 / det;

    m_invKoeffs = {k1, k2};
}

float Distortion::matDet(QMatrix2x2 &mat) const
{
    return (mat(0, 0) * mat(1, 1) - mat(0, 1) * mat(1, 0));
}
