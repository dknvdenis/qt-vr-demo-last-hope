#pragma once

#include <memory>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>

#include "fboRender.h"
#include "iMaterial.h"
#include "distortion.h"

class DistortionMaterial : public IMaterial, protected QOpenGLFunctions
{
public:
    explicit DistortionMaterial(std::shared_ptr<FboRender> fbo,
                                const DistortionKoeffs &koeffs,
                                const QVector2D &center,
                                float maxRadius,
                                const QString &vertextShaderName = ":/vshader_distortion.glsl",
                                const QString &fragmentShaderName = ":/fshader.glsl");

public:
    void bind() override;
    void release() override;
    QOpenGLShaderProgram *program() override;

private:
    std::shared_ptr<FboRender> m_fbo;
    std::unique_ptr<QOpenGLShaderProgram> m_program;
};
