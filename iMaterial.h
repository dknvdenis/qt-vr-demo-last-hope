#pragma once

#include <QOpenGLShaderProgram>

class IMaterial
{
public:
    virtual ~IMaterial() = default;

public:
    virtual void bind() = 0;
    virtual void release() = 0;
    virtual QOpenGLShaderProgram *program() = 0;
};
