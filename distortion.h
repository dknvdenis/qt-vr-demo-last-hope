#pragma once

#include <QVector2D>
#include <QMatrix2x2>

struct DistortionKoeffs
{
    float k1;
    float k2;
};

class Distortion
{
public:
    explicit Distortion(const DistortionKoeffs &distKoeffs);

public:
    float distort(float r) const;
    float distortInv(float r) const;
    DistortionKoeffs invKoeffs() const;

private:
    DistortionKoeffs m_koeffs;
    DistortionKoeffs m_invKoeffs;

private:
    float distortPriv(float r, const DistortionKoeffs &koef) const;
    void compInvKoeffs(float maxRadius, int count);
    float matDet(QMatrix2x2 &mat) const;

};
