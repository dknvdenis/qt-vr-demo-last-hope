#pragma once

#include <QVector>
#include <QVector3D>
#include <QVector2D>

struct GeometryData
{
    QVector<QVector3D> vertices;
    QVector<ushort> indices;
    QVector<QVector2D> textureCoords;
};
