#include "textureMaterial.h"

TextureMaterial::TextureMaterial(const QString &vertexShaderName,
                   const QString &fragmentShaderName,
                   const QString &textureName,
                   bool flipHorizontally,
                   bool flipVertically)
{
    m_program = std::make_unique<QOpenGLShaderProgram>();
    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vertexShaderName);
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, fragmentShaderName);
    m_program->link();

    auto img =  QImage(textureName).mirrored(flipHorizontally, flipVertically);
    m_texture = std::make_unique<QOpenGLTexture>(img);
    m_texture->setMinificationFilter(QOpenGLTexture::LinearMipMapLinear);
    m_texture->setMagnificationFilter(QOpenGLTexture::LinearMipMapLinear);
    m_texture->generateMipMaps();
    m_texture->release();
}

void TextureMaterial::bind()
{
    m_program->bind();
    m_texture->bind();
}

void TextureMaterial::release()
{
    m_texture->release();
    m_program->release();
}

QOpenGLShaderProgram *TextureMaterial::program()
{
    return  m_program.get();
}
