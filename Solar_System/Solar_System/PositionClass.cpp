#include "framework.h"
#include "PositionClass.h"


PositionClass::PositionClass()
{
}


PositionClass::PositionClass(const PositionClass& other)
{
}


PositionClass::~PositionClass()
{
}

void PositionClass::GetRotationX(float& x) {
	x = m_rotationX;
}

void PositionClass::GetPositionZ(float& z) {
	z = m_positionZ;
}

void PositionClass::TurnRightX(bool keydown) {
	if (keydown) {
		m_rotationX += 0.2f;
		if (m_rotationX > 360.0f)
		{
			m_rotationX -= 360.0f;
		}
	}
}

void PositionClass::TurnLeftX(bool keydown) {
	if (keydown) {
		m_rotationX -= 0.2f;
		if (m_rotationX < 0.0f)
		{
			m_rotationX += 360.0f;
		}
	}
}

void PositionClass::MoveFrontZ(bool keydown) {
	if (keydown) {
		m_positionZ += 0.1f;
	}
}

void PositionClass::MoveBackZ(bool keydown) {
	if (keydown) {
		m_positionZ -= 0.1f;
	}
}