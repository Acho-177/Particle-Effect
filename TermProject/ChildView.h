
// ChildView.h : interface of the CChildView class
//

#include "graphics/OpenGLWnd.h"
#include "graphics/GrCamera.h"
#include "ParticleEmitter.h"
#include "Particle.h"
#include <afxdlgs.h>
#include <afxcolordialog.h>
#pragma once


// CChildView window

class CChildView : public COpenGLWnd
{
// Construction
public:
	CChildView();

// Attributes
public:
	CGrCamera m_camera;
	CParticleEmitter m_ParticleEmitter;
	float m_spinAngle;
	boolean spin = true;
	float spinspeed = 0.2;
// Operations
public:

// Overrides
	protected:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	virtual ~CChildView();

	// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

public:
	void CChildView::OnGLDraw(CDC* pDC);

	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnTransformSphere();
	afx_msg void OnTransformCube();
	afx_msg void OnTransformRay();
	afx_msg void OnTransformTrophy();
	afx_msg void OnSphereradiusIncreaes();
	afx_msg void OnSphereradiusDecrease();
	afx_msg void OnCubeIncreselength();
	afx_msg void OnCubeDecrease();
	afx_msg void OnSpinStop();
	afx_msg void OnSpinAccelerate();
	afx_msg void OnSpinDecelerate();
	afx_msg void OnModeClear();
	afx_msg void OnModeRespawn();
	afx_msg void OnParticleColor32795();
};

