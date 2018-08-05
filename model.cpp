#include "model.h"

Model::Model(std::shared_ptr<Geometry> geometry, std::shared_ptr<IMaterial> material)
    : m_geometry(geometry),
      m_material(material)
{
    m_proj.setToIdentity();
    m_model.setToIdentity();
}

void Model::setProjMatrix(const QMatrix4x4 &proj)
{
    m_proj = proj;
}

void Model::setModelMatrix(const QMatrix4x4 &model)
{
    m_model = model;
}

void Model::render()
{
    if (!m_geometry || !m_material)
        return;

    m_material->bind();

    auto program = m_material->program();
    program->setUniformValue("p_matrix", m_proj);
    program->setUniformValue("m_matrix", m_model);
    m_geometry->render(program);

    m_material->release();
}
