#pragma once
class CParticleGenerator
{
public:
    CParticleGenerator();
    virtual ~CParticleGenerator();

    virtual void Update(float dt);
    virtual void Render();

    float m_Position[3];
    float m_EmitRate;
    float m_EmitRadius;
    float m_MinVelocity[3];
    float m_MaxVelocity[3];
    float m_MinColor[4];
    float m_MaxColor[4];
    float m_MinSize;
    float m_MaxSize;
    float m_MinLifeSpan;
    float m_MaxLifeSpan;
};

