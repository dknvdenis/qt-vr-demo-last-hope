#pragma once

#include <QOpenGLFunctions>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

#include "geometryData.h"

class Geometry final : protected QOpenGLFunctions
{
    Geometry();

public:
    ~Geometry();

    void render(QOpenGLShaderProgram *program);
    QVector2D center() const;

public:
    static Geometry *createSphere(float radius, int slices, int stacks);
    static Geometry *createPlane(float width, float height, int rows, int cols);

private:
    QOpenGLBuffer m_verticesBuf;
    QOpenGLBuffer m_indicesBuf;
    QOpenGLBuffer m_textCoordBuf;

    GLenum m_drawMode;
    int m_indicesCount;
    QVector2D m_center;

private:
    void initBuffers(const GeometryData &data);
};
