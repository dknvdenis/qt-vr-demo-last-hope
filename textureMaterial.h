#pragma once

#include <memory>
#include <QString>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include "iMaterial.h"

class TextureMaterial : public IMaterial
{
public:
    explicit TextureMaterial(const QString &vertexShaderName,
                      const QString &fragmentShaderName,
                      const QString &textureName,
                      bool flipHorizontally = false,
                      bool flipVertically = false);

public:
    void bind() override;
    void release() override;
    QOpenGLShaderProgram *program() override;

    template<typename T>
    void setUniformValue(const char *name, T &&value)
    {
        m_program->setUniformValue(name, std::forward<T>(value));
    }

private:
    std::unique_ptr<QOpenGLShaderProgram> m_program;
    std::unique_ptr<QOpenGLTexture> m_texture;
};
