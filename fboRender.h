#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLFramebufferObject>
#include <QOpenGLShaderProgram>
#include <QOpenGLTexture>

#include "geometry.h"
#include "model.h"

class FboRender final : protected QOpenGLFunctions
{
public:
    explicit FboRender(float width, float height, float sphereRadius,
                       const QMatrix4x4 &projMatrix, const QMatrix4x4 &modelMatrix);

public:
    void setSettings(float width, float height);
    void render();
    GLuint texture() const;
    QImage toImage() const;

private:
    float m_width;
    float m_height;

    std::unique_ptr<QOpenGLFramebufferObject> m_fbo;
    std::unique_ptr<Model> m_model;

private:
    void init(float sphereRadius, const QMatrix4x4 &projMatrix,
              const QMatrix4x4 &modelMatrix);
};
