#pragma once

#include <QObject>
#include <QtGui/QOpenGLFunctions>
#include <QQuickWindow>

#include "fboRender.h"
#include "geometry.h"
#include "model.h"
#include "distortion.h"

class VRRenderer : public QObject, protected QOpenGLFunctions
{
    Q_OBJECT
public:
    explicit VRRenderer();

public:
    void setQmlViewportSize(const QSize &size);
    void setWindow(QQuickWindow *window);

    void setScene_sphereRadius(float scene_sphereRadius);
    void setScene_zNear(float scene_zNear);
    void setScene_zFar(float scene_zFar);
    void setScene_width(float scene_width);
    void setScene_height(float scene_height);

    void setVr_k1(float vr_k1);
    void setVr_k2(float vr_k2);

    void setVr_meshRows(int vr_meshRows);
    void setVr_meshCols(int vr_meshCols);

public slots:
    void paint();

private:
    QSize m_qmlViewportSize;
    QQuickWindow *m_window;

    float m_scene_sphereRadius;
    float m_scene_zNear;
    float m_scene_zFar;
    float m_scene_width;
    float m_scene_height;

    float m_vr_k1;
    float m_vr_k2;
    int m_vr_meshRows;
    int m_vr_meshCols;

    int m_vX;
    int m_vY;
    int m_vWidth;
    int m_vHeight;

    // Samsung S8
    // 5.8 inch
    //   *-------*
    //   |       | h
    //   *-------*
    //       w
    // diag = 0.147 m
    // h = 0.064 m
    // w = 0.132 m
    const float m_diag {5.8f}; // inch
    const float m_screenWidth {0.132f};
    const float m_screenHeight {0.064f};
    const float m_ipd {0.06300000101327896f};
    const float m_screenDistance {0.04089849814772606f};
    const float m_lensFov {48.85536575317383f}; // From VR headset param

    std::unique_ptr<Distortion> m_distortion;

    std::shared_ptr<FboRender> m_leftEyeFbo;
    std::shared_ptr<FboRender> m_rightEyeFbo;

    std::unique_ptr<Model> m_leftPlane;
    std::unique_ptr<Model> m_rigthPlane;

private:
    QMatrix4x4 orthoProj(float left, float right, float bottom, float top);
    void initPlanes(Distortion *distortion);
    void initFbo(Distortion *distortion);
};
