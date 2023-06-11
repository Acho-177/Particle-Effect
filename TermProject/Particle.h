#include "graphics/OpenGLWnd.h"
#include "graphics/GrTexture.h"
class CParticleEmitter;
#pragma once
class CParticle
{
public:
    CParticle();
    virtual ~CParticle();

    virtual void Update(float dt);
    virtual void Render();
    virtual void Reset();

public:
    float m_Position[3];
    float m_StartPosition[3];
    float m_TargetPosition[3];
    float m_Velocity[3];
    float m_Color[4];
    float m_Size = 1.;
    float m_LifeSpan = 1000.;
    float m_Age = 0.;
    int Shape = 0;
    float m_SphereRadius = 10;
    int m_SideLength = 10;
    CParticleEmitter* m_Emitter;
};

