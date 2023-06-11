
// ChildView.cpp : implementation of the CChildView class
//

#include "pch.h"
#include "framework.h"
#include "TermProject.h"
#include "ChildView.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CChildView

CChildView::CChildView()
{
    m_camera.Set(30, 20, 50, 0, 0, 0, 0, 1, 0);
    m_ParticleEmitter = CParticleEmitter();
}

CChildView::~CChildView()
{
}


BEGIN_MESSAGE_MAP(CChildView, COpenGLWnd)
	ON_WM_PAINT()
    ON_WM_MOUSEMOVE()
    ON_WM_LBUTTONDOWN()
    ON_WM_RBUTTONDOWN()
    ON_COMMAND(ID_TRANSFORM_, &CChildView::OnTransformSphere)
    ON_COMMAND(ID_TRANSFORM_32773, &CChildView::OnTransformCube)
    ON_COMMAND(ID_TRANSFORM_RAY, &CChildView::OnTransformRay)
    ON_COMMAND(ID_TRANSFORM_TROPHY, &CChildView::OnTransformTrophy)
    ON_COMMAND(ID_SPHERERADIUS_INCREAES, &CChildView::OnSphereradiusIncreaes)
    ON_COMMAND(ID_SPHERERADIUS_DECREASE, &CChildView::OnSphereradiusDecrease)
    ON_COMMAND(ID_CUBE_INCRESELENGTH, &CChildView::OnCubeIncreselength)
    ON_COMMAND(ID_CUBE_DECREASE, &CChildView::OnCubeDecrease)
    ON_COMMAND(ID_SPIN_STOP, &CChildView::OnSpinStop)
    ON_COMMAND(ID_SPIN_ACCELERATE, &CChildView::OnSpinAccelerate)
    ON_COMMAND(ID_SPIN_DECELERATE, &CChildView::OnSpinDecelerate)
    ON_COMMAND(ID_MODE_CLEAR, &CChildView::OnModeClear)
    ON_COMMAND(ID_MODE_RESPAWN, &CChildView::OnModeRespawn)
    ON_COMMAND(ID_PARTICLE_COLOR32795, &CChildView::OnParticleColor32795)
END_MESSAGE_MAP()



// CChildView message handlers

BOOL CChildView::PreCreateWindow(CREATESTRUCT& cs) 
{
	if (!COpenGLWnd::PreCreateWindow(cs))
		return FALSE;

	cs.dwExStyle |= WS_EX_CLIENTEDGE;
	cs.style &= ~WS_BORDER;
	cs.lpszClass = AfxRegisterWndClass(CS_HREDRAW|CS_VREDRAW|CS_DBLCLKS, 
		::LoadCursor(nullptr, IDC_ARROW), reinterpret_cast<HBRUSH>(COLOR_WINDOW+1), nullptr);

	return TRUE;
}

void CChildView::OnGLDraw(CDC* pDC)
{
    glClearColor(0.05f, 0.05f, 0.05f, 0.f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    //
    // Set up the camera
    //

    int width, height;
    GetSize(width, height);
    m_camera.Apply(width, height);

    //
    // Some standard parameters
    //

    // Enable depth test
    glEnable(GL_DEPTH_TEST);

    // Cull backfacing polygons
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);

    // Enable lighting
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    GLfloat lightpos[] = { 0.5, 2.0, 1.0, 0. };
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    glRotated(m_spinAngle, 0.5, 1., 1.);
    // Spin
    if (spin) {
        m_spinAngle += spinspeed;
    }
    
    // 
    // INSERT DRAWING CODE HERE
    //
    m_ParticleEmitter.Update(1);
    m_ParticleEmitter.Render();
    Invalidate();
}


void CChildView::OnLButtonDown(UINT nFlags, CPoint point)
{
    
    m_ParticleEmitter.SpawnParticle();

    m_camera.MouseDown(point.x, point.y);
    
    COpenGLWnd::OnLButtonDown(nFlags, point);
}


void CChildView::OnMouseMove(UINT nFlags, CPoint point)
{
    if (m_camera.MouseMove(point.x, point.y, nFlags))
        Invalidate();

    COpenGLWnd::OnMouseMove(nFlags, point);
}


void CChildView::OnRButtonDown(UINT nFlags, CPoint point)
{
    m_camera.MouseDown(point.x, point.y, 2);

    COpenGLWnd::OnRButtonDown(nFlags, point);
}

void CChildView::OnTransformCube()
{
    m_ParticleEmitter.m_Shape = 0;
    Invalidate();
}


void CChildView::OnTransformRay()
{
    m_ParticleEmitter.m_Shape = 1;
    Invalidate();
}

void CChildView::OnTransformTrophy()
{
    m_ParticleEmitter.m_Shape = 2;
    Invalidate();
}

void CChildView::OnTransformSphere()
{
    m_ParticleEmitter.m_Shape = 3;
    Invalidate();
}

void CChildView::OnSphereradiusIncreaes()
{
    m_ParticleEmitter.m_SphereRadius += 3;
    Invalidate();
}


void CChildView::OnSphereradiusDecrease()
{
    m_ParticleEmitter.m_SphereRadius = max(m_ParticleEmitter.m_SphereRadius - 3,1);
    Invalidate();
}



void CChildView::OnCubeIncreselength()
{
    m_ParticleEmitter.m_SideLength += 3;
    Invalidate();
}


void CChildView::OnCubeDecrease()
{
    m_ParticleEmitter.m_SideLength = max(m_ParticleEmitter.m_SideLength - 3, 1);
    Invalidate();
}


void CChildView::OnSpinStop()
{
    spin = !spin;
}


void CChildView::OnSpinAccelerate()
{
    spinspeed += 0.1;
}


void CChildView::OnSpinDecelerate()
{
    spinspeed = max(spinspeed - 0.1,0);
}


void CChildView::OnModeClear()
{
    m_ParticleEmitter.Clear();
}


void CChildView::OnModeRespawn()
{
    m_ParticleEmitter = CParticleEmitter();
}


void CChildView::OnParticleColor32795()
{
    
}
