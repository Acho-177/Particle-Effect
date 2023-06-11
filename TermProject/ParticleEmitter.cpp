#include "pch.h"
#include "ParticleEmitter.h"
#include <random>

CParticleEmitter::CParticleEmitter()
{
    for (int i = 0; i < 3; i++) {
        m_EmitterPosition[i] = 0.;
        m_EmitterVelocity[i] = 0.;
        m_Color[i] = 0.;
    }
    m_Color[0] = 0.;
    m_Color[3] = 1.;

    m_MinSize = 0.;
    m_MaxSize = 1.;
    m_MinLifeSpan = 1000.;
    m_MaxLifeSpan = 2000.;
    m_SpawnRate = 1.0;
    m_SpawnTimer = 1.0;
    m_LifeSpan = 1000.0;
    m_Age = 0.;
    m_Shape = 0;
    m_pause = 0;
    m_MaxParticleNumber = 10000;
    m_SphereRadius = 10;
    m_SideLength = 10;
    

    // target shape start with forming a sphere
    for (int i = 0; i < 10000; i++) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> dist(-1.0, 1.0);
        float x, y, z, r;
        do {
            x = dist(gen);
            y = dist(gen);
            z = dist(gen);
            r = sqrt(x * x + y * y + z * z);
        } while (r > 1.0);

        x *= m_SphereRadius / r;
        y *= m_SphereRadius / r;
        z *= m_SphereRadius / r;

        CParticle* particle = new CParticle();
        particle->m_Emitter = this;
        particle->m_TargetPosition[0] = x;
        particle->m_TargetPosition[1] = y;
        particle->m_TargetPosition[2] = z;

        if (EnableColor)
        {
            particle->m_Color[0] = m_Color[0];
            particle->m_Color[1] = m_Color[1];
            particle->m_Color[2] = m_Color[2];
        }
        m_Particles.push_back(*particle);
    }
}

CParticleEmitter::~CParticleEmitter()
{
}

void CParticleEmitter::Update(float dt)
{
    if (m_pause > 0) { m_pause--; return; }
    m_Age += dt;

    if (m_Age > m_LifeSpan)
    {
        m_Age = 0.;
        m_pause = 200;
        m_Shape += 1;
        if (m_Shape > 3) {
            m_Shape = 0;
        }
    }

    // Update main thread particles
    for (int i = 0; i < m_Particles.size(); i++)
    {
        CParticle& particle = m_Particles[i];
        particle.Shape = m_Shape;
        particle.m_SphereRadius = m_SphereRadius;
        particle.m_SideLength = m_SideLength;
        float* color = particle.m_Emitter->m_Color;
        particle.Update(dt);
    }

    // Update instant generated particles
    for (int i = 0; i < m_InstantParticles.size(); i++)
    {
        CParticle& particle = m_InstantParticles[i];
        particle.Shape = m_Shape;
        particle.m_SphereRadius = m_SphereRadius;
        particle.m_SideLength = m_SideLength;
        particle.Update(dt);
    }

}

void CParticleEmitter::Render()
{
    for (int i=0; i < m_Particles.size();i++)
    {
        CParticle& particle = m_Particles[i];
        particle.Render();
    }
    for (int i = 0; i < m_InstantParticles.size(); i++)
    {
        CParticle& particle = m_InstantParticles[i];
        particle.Render();
    }
}

void CParticleEmitter::SpawnParticle()
{
    for (int i = 0; i < 100; i++) {
        CParticle* particle = new CParticle();
        particle->m_Emitter = this;
        m_InstantParticles.push_back(*particle);
    }
}

void CParticleEmitter::SpawnParticle(float x,float y,float z)
{
    for (int i = 0; i < 100; i++) {
        CParticle* particle = new CParticle();
        particle->m_Emitter = this;
        particle->m_Position[0] = x;
        particle->m_Position[0] = y;
        particle->m_Position[0] = z;
        m_InstantParticles.push_back(*particle);
    }
}

void CParticleEmitter::Reset() {
    for (int i = 0; i < m_Particles.size(); i++)
    {
        CParticle& particle = m_Particles[i];
        particle.Reset();
    }
    for (int i = 0; i < m_InstantParticles.size(); i++)
    {
        CParticle& particle = m_InstantParticles[i];
        particle.Reset();
    }
}

void CParticleEmitter::Clear() {
    m_Particles.clear();
    m_InstantParticles.clear();
}

