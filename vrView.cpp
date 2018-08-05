#include "vrView.h"
#include <QQuickWindow>

VRView::VRView()
    : m_renderer(nullptr)
{
    connect(this, &QQuickItem::windowChanged,
            this, &VRView::handleWindowChanged);
}

void VRView::sync()
{
    if (!m_renderer)
    {
        m_renderer = new VRRenderer();
        connect(window(), &QQuickWindow::beforeRendering,
                m_renderer, &VRRenderer::paint, Qt::DirectConnection);
    }

    m_renderer->setScene_sphereRadius(m_scene_sphereRadius);
    m_renderer->setScene_zNear(m_scene_zNear);
    m_renderer->setScene_zFar(m_scene_zFar);
    m_renderer->setScene_width(m_scene_width);
    m_renderer->setScene_height(m_scene_height);

    m_renderer->setVr_k1(m_vr_k1);
    m_renderer->setVr_k2(m_vr_k2);
    m_renderer->setVr_meshRows(m_vr_meshRows);
    m_renderer->setVr_meshCols(m_vr_meshCols);

    if (!window())
        return;
    m_renderer->setQmlViewportSize(window()->size() * window()->devicePixelRatio());
    m_renderer->setWindow(window());
}

void VRView::cleanup()
{
    if (m_renderer)
    {
        delete m_renderer;
        m_renderer = nullptr;
    }
}

void VRView::handleWindowChanged(QQuickWindow *win)
{
    if (win)
    {
        connect(win, &QQuickWindow::beforeSynchronizing,
                this, &VRView::sync, Qt::DirectConnection);
        connect(win, &QQuickWindow::sceneGraphInvalidated,
                this, &VRView::cleanup, Qt::DirectConnection);

        win->setClearBeforeRendering(false);
    }
}
