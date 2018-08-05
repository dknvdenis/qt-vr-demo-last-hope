#pragma once

#include <QQuickItem>
#include <vrRenderer.h>

class VRView : public QQuickItem
{
    Q_OBJECT
    Q_PROPERTY(float scene_sphereRadius READ scene_sphereRadius WRITE setScene_sphereRadius NOTIFY scene_sphereRadiusChanged)
    Q_PROPERTY(float scene_zNear READ scene_zNear WRITE setScene_zNear NOTIFY scene_zNearChanged)
    Q_PROPERTY(float scene_zFar READ scene_zFar WRITE setScene_zFar NOTIFY scene_zFarChanged)
    Q_PROPERTY(float scene_width READ scene_width WRITE setScene_width NOTIFY scene_widthChanged)
    Q_PROPERTY(float scene_height READ scene_height WRITE setScene_height NOTIFY scene_heightChanged)
    Q_PROPERTY(float vr_k1 READ vr_k1 WRITE setVr_k1 NOTIFY vr_k1Changed)
    Q_PROPERTY(float vr_k2 READ vr_k2 WRITE setVr_k2 NOTIFY vr_k2Changed)
    Q_PROPERTY(int vr_meshRows READ vr_meshRows WRITE setVr_meshRows NOTIFY vr_meshRowsChanged)
    Q_PROPERTY(int vr_meshCols READ vr_meshCols WRITE setVr_meshCols NOTIFY vr_meshColsChanged)

public:
    explicit VRView();

    float scene_sphereRadius() const
    {
        return m_scene_sphereRadius;
    }

    float scene_zNear() const
    {
        return m_scene_zNear;
    }

    float scene_zFar() const
    {
        return m_scene_zFar;
    }

    float scene_width() const
    {
        return m_scene_width;
    }

    float scene_height() const
    {
        return m_scene_height;
    }

    float vr_k1() const
    {
        return m_vr_k1;
    }

    float vr_k2() const
    {
        return m_vr_k2;
    }

    int vr_meshRows() const
    {
        return m_vr_meshRows;
    }

    int vr_meshCols() const
    {
        return m_vr_meshCols;
    }

public slots:
    void sync();
    void cleanup();

    void setScene_sphereRadius(float scene_sphereRadius)
    {
        if (qFuzzyCompare(m_scene_sphereRadius, scene_sphereRadius))
            return;

        m_scene_sphereRadius = scene_sphereRadius;
        emit scene_sphereRadiusChanged(m_scene_sphereRadius);
    }

    void setScene_zNear(float scene_zNear)
    {
        if (qFuzzyCompare(m_scene_zNear, scene_zNear))
            return;

        m_scene_zNear = scene_zNear;
        emit scene_zNearChanged(m_scene_zNear);
    }

    void setScene_zFar(float scene_zFar)
    {
        if (qFuzzyCompare(m_scene_zFar, scene_zFar))
            return;

        m_scene_zFar = scene_zFar;
        emit scene_zFarChanged(m_scene_zFar);
    }

    void setScene_width(float scene_width)
    {
        if (qFuzzyCompare(m_scene_width, scene_width))
            return;

        m_scene_width = scene_width;
        emit scene_widthChanged(m_scene_width);
    }

    void setScene_height(float scene_height)
    {
        if (qFuzzyCompare(m_scene_height, scene_height))
            return;

        m_scene_height = scene_height;
        emit scene_heightChanged(m_scene_height);
    }

    void setVr_k1(float vr_k1)
    {
        if (qFuzzyCompare(m_vr_k1, vr_k1))
            return;

        m_vr_k1 = vr_k1;
        emit vr_k1Changed(m_vr_k1);
    }

    void setVr_k2(float vr_k2)
    {
        if (qFuzzyCompare(m_vr_k2, vr_k2))
            return;

        m_vr_k2 = vr_k2;
        emit vr_k2Changed(m_vr_k2);
    }

    void setVr_meshRows(int vr_meshRows)
    {
        if (m_vr_meshRows == vr_meshRows)
            return;

        m_vr_meshRows = vr_meshRows;
        emit vr_meshRowsChanged(m_vr_meshRows);
    }

    void setVr_meshCols(int vr_meshCols)
    {
        if (m_vr_meshCols == vr_meshCols)
            return;

        m_vr_meshCols = vr_meshCols;
        emit vr_meshColsChanged(m_vr_meshCols);
    }

private:
    VRRenderer *m_renderer;

    float m_scene_sphereRadius {0};
    float m_scene_zNear {0};
    float m_scene_zFar {0};
    float m_scene_width {0};
    float m_scene_height {0};
    float m_vr_k1 {0};
    float m_vr_k2 {0};
    int m_vr_meshRows {0};
    int m_vr_meshCols {0};

private slots:
    void handleWindowChanged(QQuickWindow *win);

signals:
    void scene_sphereRadiusChanged(float scene_sphereRadius);
    void scene_zNearChanged(float scene_zNear);
    void scene_zFarChanged(float scene_zFar);
    void scene_widthChanged(float scene_width);
    void scene_heightChanged(float scene_height);
    void vr_k1Changed(float vr_k1);
    void vr_k2Changed(float vr_k2);
    void vr_meshRowsChanged(int vr_meshRows);
    void vr_meshColsChanged(int vr_meshCols);
};
