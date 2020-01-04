#include "framework.h"
#include "PlanetListClass.h"

PlanetListClass::PlanetListClass()
{
}


PlanetListClass::PlanetListClass(const PlanetListClass& other)
{
}


PlanetListClass::~PlanetListClass()
{
}

void PlanetListClass::Initialize(PLANETS planet) {
	m_planet = planet;

	switch (m_planet) {
	case SUN:
		m_scail = 0.60551f; // 0.695510f 
		break;
	case MERCURY:
		m_scail = 0.044634f; // 0.002439f
		m_distance = 1.16f; // 5.8f / 5
		m_rotation = 0.01694f;
		m_rotationZ = -0.000614f;
		m_around = 0.0254772f;
		break;
	case VENUS:
		m_scail = 0.066306f;  // 0.006051f
		m_distance = 2.16f; // 10.8f / 5
		m_rotation = 0.0000411f;
		m_rotationZ = -3.096f;
		m_around = 0.0162946f;
		break;
	case EARTH:
		m_scail = 0.068226f; // 0.006371f
		m_distance = 3.0f; // 15.0f / 5
		m_rotation = 0.01f;
		m_rotationZ = -0.4091f; // 23.4
		m_around = 0.001f;//0.01f;
		break;
	case MARS:
		m_scail = 0.050334f; // 0.003389f
		m_distance = 4.56f; // 22.8f / 5
		m_rotation = 0.009746f;
		m_rotationZ = -0.4396f;
		m_around = 0.0053206f;
		break;
	case JUPITER:
		m_scail = 0.169733f; // 0.069911f * 3
		m_distance = 5.725f; // 77.8f / 8
		m_rotation = 0.0410f;
		m_rotationZ = -0.0546f;
		m_around = 0.00088667f;
		break;
	case SATURN:
		m_scail = 0.144696f; // 0.058232f * 3
		m_distance = 7.972f; // 142.7f / 11
		m_rotation = 0.0426f;
		m_rotationZ = -0.4665f;
		m_around = 0.00034482f;
		break;
	case URANUS:
		m_scail = 0.096086; // 0.025362f * 3
		m_distance = 10.4f; // 288.0f / 20
		m_rotation = 0.0718f;
		m_rotationZ = -1.7064f;
		m_around = 0.00011904f;
		break;
	case NEPTUNE:
		m_scail = 0.083866; // 0.024622f
		m_distance = 12.052f; // 451.3f / 25
		m_rotation = 0.0669f;
		m_rotationZ = -0.4943f;
		m_around = 0.0000909f;
		break;
	case MOON:
		m_scail = 0.020634f;
		m_distance = 0.1452f; // 지구에서 거리 
		m_rotation = 0.08f;
		m_rotationZ = -0.4101f;
		m_around = 0.04f;
		break;
	}
}

void PlanetListClass::Frame() {
	if (m_planet != SUN) {
		m_rotationY += (float)XM_PI * m_rotation; // 자전
		if (m_rotationY >= 360.0f) {
			m_rotationY -= 360.0f;
		}

		m_aroundY += (float)XM_PI * m_around; // 공전
		if (m_aroundY >= 360.0f) {
			m_aroundY -= 360.0f;
		}
	}
}

void PlanetListClass::GetObjectMatrix(XMMATRIX& objectMatrix)
{
	XMMATRIX m_objectMarix = XMMatrixIdentity();
	
	if (m_planet == SUN) {
		m_objectMarix = XMMatrixScaling(m_scail, m_scail, m_scail);
	}
	else if (m_planet == MOON) {
		XMFLOAT4X4 fPosition;
		XMStoreFloat4x4(&fPosition, objectMatrix);
		
		m_objectMarix = XMMatrixScaling(m_scail, m_scail, m_scail) * XMMatrixRotationY(m_rotationY) * XMMatrixRotationZ(m_rotationZ) * XMMatrixRotationY(-m_aroundY)
			* XMMatrixTranslation(m_distance, 0, 0) * XMMatrixRotationY(m_aroundY) * XMMatrixRotationZ(m_rotationZ)
			* XMMatrixTranslation(fPosition._41, fPosition._42, fPosition._43);
	}
	else {
		m_objectMarix = XMMatrixScaling(m_scail, m_scail, m_scail) * XMMatrixRotationY(m_rotationY) * XMMatrixRotationZ(m_rotationZ) * XMMatrixRotationY(-m_aroundY)
			* XMMatrixTranslation(m_distance, 0, 0) * XMMatrixRotationY(m_aroundY);
	}

	objectMatrix = m_objectMarix;
}