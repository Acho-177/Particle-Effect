#include <vector>
#include "ParticleGenerator.h"
#include "Particle.h"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"


#pragma once
class CParticleEmitter
{
//method
public:
    CParticleEmitter();
    virtual ~CParticleEmitter();

    // Update the particle system
    void Update(float deltaTime);

    // Render the particles to the screen using OpenGL
    void Render();

    void SpawnParticle();

    void SpawnParticle(float x, float y, float z);

    void Reset();

    void Clear();

//attributes
public:
    // Particle properties
    float m_EmitterPosition[3];
    float m_EmitterVelocity[3];
    float m_MinSize;
    float m_MaxSize;
    float m_MinLifeSpan;
    float m_MaxLifeSpan;
    float m_SpawnRate;
    float m_SpawnTimer;
    float m_Color[4];
    int m_Shape;
    float m_Age;
    float m_LifeSpan;
    float m_pause;
    int m_MaxParticleNumber;
    boolean EnableColor = false;

    // Collection of main thread particles
    std::vector<CParticle> m_Particles;

    // Collection of instant generated particles
    std::vector<CParticle> m_InstantParticles;
  // bool IsParticleInsideBounds(const CParticle& particle);

// shape attributes
public:
    float m_SphereRadius;
    int m_SideLength;
};

