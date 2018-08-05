#include "distortionMaterial.h"

DistortionMaterial::DistortionMaterial(std::shared_ptr<FboRender> fbo,
                                       const DistortionKoeffs &koeffs,
                                       const QVector2D &center,
                                       float maxRadius,
                                       const QString &vertextShaderName,
                                       const QString &fragmentShaderName)
    : m_fbo(fbo),
      m_program(std::make_unique<QOpenGLShaderProgram>())
{
    initializeOpenGLFunctions();

    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertextShaderName);
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderName);
    m_program->link();

    m_program->bind();
    m_program->setUniformValue("k1", koeffs.k1);
    m_program->setUniformValue("k2", koeffs.k2);
    m_program->setUniformValue("center", center);
    m_program->setUniformValue("maxRadius", maxRadius);
    m_program->release();
}

void DistortionMaterial::bind()
{
    m_program->bind();
    glBindTexture(QOpenGLTexture::Target2D, m_fbo->texture());
}

void DistortionMaterial::release()
{
    glBindTexture(QOpenGLTexture::Target2D, 0);
    m_program->release();
}

QOpenGLShaderProgram *DistortionMaterial::program()
{
    return m_program.get();
}
