#pragma once

class PositionClass
{
public:
	PositionClass();
	PositionClass(const PositionClass&);
	~PositionClass();

	void GetRotationX(float&);
	void GetPositionZ(float&);

	void TurnRightX(bool); // up
	void TurnLeftX(bool); // down
	void MoveFrontZ(bool); // right
	void MoveBackZ(bool); // left

private:
	float m_rotationX = 0.0f;
	float m_positionZ = -10.0f;
};