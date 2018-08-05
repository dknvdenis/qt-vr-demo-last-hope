#include "geometry.h"
#include <QtMath>

namespace {
GeometryData genSphere(float radius, int slices, int stacks)
{
    GeometryData data;

    for(int i = 0; i <= stacks; i++)
    {
        // V texture coordinate.
        float V = i / (float)stacks;
        float phi = V * M_PI;

        for ( int j = 0; j <= slices; j++)
        {
            // U texture coordinate.
            float U = j / (float)slices;
            float theta = U * 2 * M_PI;

            float X = cos(theta) * sin(phi);
            float Y = cos(phi);
            float Z = sin(theta) * sin(phi);

            data.vertices.push_back(QVector3D(X, Y, Z) * radius);
            data.textureCoords.push_back(QVector2D(U, V));
        }
    }

    for(int i = 0; i < slices * stacks + slices; i++)
    {
//        data.indices.push_back(i);
//        data.indices.push_back(i + slices + 1);
//        data.indices.push_back(i + slices);

//        data.indices.push_back(i + slices + 1);
//        data.indices.push_back(i);
//        data.indices.push_back(i + 1);

        data.indices.push_back(i + slices);
        data.indices.push_back(i + slices + 1);
        data.indices.push_back(i);

        data.indices.push_back(i + 1);
        data.indices.push_back(i);
        data.indices.push_back(i + slices + 1);
    }

    return data;
}

GeometryData genPlane(float width, float height, int rows, int cols)
{
    GeometryData data;
    int indicesCount = 2 * cols * (rows - 1) + 2 * (rows - 2);

    data.vertices.reserve(rows * cols);
    data.textureCoords.reserve(rows * cols);
    data.indices.reserve(indicesCount);

    float wStep = width / (cols - 1);
    float hStep = height / (rows - 1);

    for (int r = 0; r < rows; r++)
    {
        // add a degenerate triangle
        if (r > 0 && r < rows - 1)
        {
            data.indices.push_back(data.indices.last());
            data.indices.push_back(r * cols + cols);
        }

        for (int c = 0; c < cols; c++)
        {
            float x = c * wStep;
            float y = r * hStep;
            data.vertices.push_back(QVector3D(x, y, 0.f));
            data.textureCoords.push_back(QVector2D(x / width, y / height));

            if (r < rows - 1)
            {
                ushort i = r * cols + c;
                data.indices.push_back(i + cols);
                data.indices.push_back(i);
            }
        }
    }

    return data;
}
}

Geometry::Geometry()
    : m_indicesBuf(QOpenGLBuffer::IndexBuffer)
{
    initializeOpenGLFunctions();

    m_verticesBuf.create();
    m_indicesBuf.create();
    m_textCoordBuf.create();
}

Geometry::~Geometry()
{
    m_verticesBuf.destroy();
    m_indicesBuf.destroy();
    m_textCoordBuf.destroy();
}

void Geometry::render(QOpenGLShaderProgram *program)
{
    m_verticesBuf.bind();
    m_indicesBuf.bind();

    int vertexLocation = program->attributeLocation("a_position");
    program->enableAttributeArray(vertexLocation);
    program->setAttributeBuffer(vertexLocation, GL_FLOAT, 0, 3);

    m_textCoordBuf.bind();
    int texcoordLocation = program->attributeLocation("a_texcoord");
    program->enableAttributeArray(texcoordLocation);
    program->setAttributeBuffer(texcoordLocation, GL_FLOAT, 0, 2);

    glDrawElements(m_drawMode, m_indicesCount, GL_UNSIGNED_SHORT, 0);

    program->disableAttributeArray(vertexLocation);
    program->disableAttributeArray(texcoordLocation);

    QOpenGLBuffer::release(QOpenGLBuffer::VertexBuffer);
    QOpenGLBuffer::release(QOpenGLBuffer::IndexBuffer);
}

QVector2D Geometry::center() const
{
    return m_center;
}

void Geometry::initBuffers(const GeometryData &data)
{
    m_verticesBuf.bind();
    m_verticesBuf.allocate(data.vertices.constData(),
                           data.vertices.size() * sizeof(QVector3D));

    m_indicesBuf.bind();
    m_indicesBuf.allocate(data.indices.constData(),
                          data.indices.size() * sizeof(GLushort));

    m_textCoordBuf.bind();
    m_textCoordBuf.allocate(data.textureCoords.constData(),
                            data.textureCoords.size() * sizeof(QVector2D));

    QOpenGLBuffer::release(QOpenGLBuffer::VertexBuffer);
    QOpenGLBuffer::release(QOpenGLBuffer::IndexBuffer);
}

Geometry *Geometry::createSphere(float radius, int slices, int stacks)
{
    auto model = new Geometry();
    auto data = genSphere(radius, slices, stacks);

    model->m_drawMode = GL_TRIANGLES;
    model->m_indicesCount = data.indices.size();
    model->m_center = QVector2D(0.f, 0.f);
    model->initBuffers(data);

    return model;
}

Geometry *Geometry::createPlane(float width, float height, int rows, int cols)
{
    auto model = new Geometry();
    auto data = genPlane(width, height, rows, cols);

    model->m_drawMode = GL_TRIANGLE_STRIP;
    model->m_indicesCount = data.indices.size();
    model->m_center = QVector2D(width / 2.f, height / 2.f);
    model->initBuffers(data);

    return model;
}
