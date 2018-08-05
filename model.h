#pragma once

#include <memory>
#include "geometry.h"
#include "iMaterial.h"

class Model
{
public:
    explicit Model(std::shared_ptr<Geometry> geometry,
                   std::shared_ptr<IMaterial> material);

public:
    void setProjMatrix(const QMatrix4x4 &proj);
    void setModelMatrix(const QMatrix4x4 &model);

    void render();

private:
    std::shared_ptr<Geometry> m_geometry;
    std::shared_ptr<IMaterial> m_material;

    QMatrix4x4 m_proj;
    QMatrix4x4 m_model;
};
