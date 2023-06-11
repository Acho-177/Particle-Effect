#include "pch.h"
#include "Particle.h"
#include <random>
#include "ParticleEmitter.h"
CParticle::CParticle()
{
    //Initialize with randomly distributed in a rectangle
    for (int i = 0; i < 3; i++) {
        int random_num = std::rand() % 151 - 75;
        float random_float = static_cast<float>(random_num / 10);
        m_StartPosition[i] = random_float;
        m_Position[i] = random_float;
        m_Velocity[i] = 0.0f;
        random_float = static_cast<float>((random_num + 75) / 150);
        m_TargetPosition[i] = 0.;
    }

    m_Emitter = nullptr;
    m_Color[3] = 1.;
}

CParticle::~CParticle()
{
}

void CParticle::Update(float dt)
{
    for (int i = 0; i < 3; i++) {
        // Update velocity based on age 
        m_Velocity[i] = (m_TargetPosition[i] - m_Position[i]) / (m_LifeSpan - m_Age + 1);

        // Update position based on velocity and time
        m_Position[i] += m_Velocity[i] * dt;

        // Update color based on position if no preset color
        
        m_Color[i] = m_Position[i];
            
        // Update velocity based on external forces
        //m_Velocity[i] += m_ExternalForce[i] * dt;
    }

    if (m_Color[0] < 0 && m_Color[1] < 0 && m_Color[2] < 0) m_Color[2] = abs(m_Color[2]);

    // Increase age based on time
    m_Age += dt;
    if (m_Age > m_LifeSpan)
        Reset();
}

void CParticle::Render()
{
    GLfloat color[] = { m_Color[0],
                        m_Color[1],
                        m_Color[2],
                        m_Color[3] };

    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, color);

    // Enable blending and set blending function
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Set particle size and color
    glPointSize(m_Size);

    // Render particle as point sprite
    glBegin(GL_POINTS);
    glVertex3fv(m_Position);
    glEnd();
}

void CParticle::Reset()
{
    m_Age = 0.;

    //rectangle
    if (Shape == 1) {
        for (int i = 0; i < 3; i++) {
            int random_num = std::rand() % (200*m_SideLength+1) - (100*m_SideLength);
            double random_double = static_cast<double>(random_num) / 100.0;
            m_StartPosition[i] = m_TargetPosition[i];
            m_TargetPosition[i] = static_cast<float>(min(random_double + 3, m_SideLength));
        }
    }
    //
    else if (Shape == 2) {
        float infor[3] = {100,0.5,0.5};
        for (int i = 0; i < 3; i++) {
            int random_num = std::rand() % 2001 - 1000;
            double random_double = static_cast<double>(random_num) / 1000.0;
            m_StartPosition[i] = m_TargetPosition[i];
            m_TargetPosition[i] = static_cast<float>(random_double * infor[i]);
        }
    }
    //
    else if (Shape == 3) {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);

        // Define the cone parameters
        double crown_radius = 2.0;
        double crown_height = 4.0;
        double crown_slope = crown_height / crown_radius;

        // Define the trunk parameters
        double trunk_radius = 0.5;
        double trunk_height = 2.0;

        // Generate three random numbers
        double u1 = dis(gen);
        double u2 = dis(gen);
        double u3 = dis(gen);

        // Compute the x and y coordinates
        double phi = 2.0 * 3.1415926 * u1;
        double r = crown_radius * sqrt(u2);
        double x = r * cos(phi);
        double y = r * sin(phi);

        // Compute the z coordinate
        double z = (crown_height + trunk_height) * u3 - trunk_height;

        // Adjust the z coordinate for the crown or the trunk
        if (z < 0) {
            // Adjust for the trunk
            z *= (trunk_radius / trunk_height);
        }
        else {
            // Adjust for the crown
            z -= trunk_height;
            z = crown_slope * sqrt(x * x + y * y + z * z);
        }

        m_StartPosition[0] = m_TargetPosition[0];
        m_StartPosition[1] = m_TargetPosition[1];
        m_StartPosition[2] = m_TargetPosition[2];

        m_TargetPosition[0] = static_cast<float>(x * 2);
        m_TargetPosition[1] = static_cast<float>(y * 2);
        m_TargetPosition[2] = static_cast<float>(z * 2);
    }
    //sphere
    else {
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

        m_StartPosition[0] = m_TargetPosition[0];
        m_StartPosition[1] = m_TargetPosition[1];
        m_StartPosition[2] = m_TargetPosition[2];

        m_TargetPosition[0] = x;
        m_TargetPosition[1] = y;
        m_TargetPosition[2] = z;
    }
}
