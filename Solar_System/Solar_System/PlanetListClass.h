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

	float m_scail = 0.0f; // 행성 크기

	float m_distance = 0.0f; // 태양에서 거리

	float m_rotation = 0.0f; // 자전주기
	float m_rotationY = 0.0f; // 자전 각
	float m_rotationZ = 0.0f; // 자전축 각

	float m_around = 0.0f; // 공전주기
	float m_aroundY = 0.0f ; // 공전 각
};