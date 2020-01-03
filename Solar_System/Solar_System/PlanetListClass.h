#pragma once

class PlanetListClass : public AlignedAllocationPolicy<16>
{
public:
	PlanetListClass();
	PlanetListClass(const PlanetListClass&);
	~PlanetListClass();

	void Initialize(PLANETS);
	void Frame();
	void GetObjectMatrix(XMMATRIX&);

private:
	PLANETS m_planet;

	float m_scail = 0.0f; // �༺ ũ��

	float m_distance = 0.0f; // �¾翡�� �Ÿ�

	float m_rotation = 0.0f; // �����ֱ�
	float m_rotationY = 0.0f; // ���� ��
	float m_rotationZ = 0.0f; // ������ ��

	float m_around = 0.0f; // �����ֱ�
	float m_aroundY = 0.0f ; // ���� ��
};