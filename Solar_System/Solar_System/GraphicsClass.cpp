#include "framework.h"
#include "d3dclass.h"
#include "cameraclass.h"
#include "modelclass.h"
#include "textureshaderclass.h"
#include "graphicsclass.h"
#include "PlanetListClass.h"


GraphicsClass::GraphicsClass()
{
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd)
{
	// Direct3D 객체 생성
	m_Direct3D = new D3DClass;
	if (!m_Direct3D)
	{
		return false;
	}

	// Direct3D 객체 초기화
	if (!m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR))
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// m_Camera 객체 생성
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// 카메라 포지션 설정
	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);

	// m_Model 객체 생성
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}
	
	// m_Model 객체 초기화
	if (!m_Model->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "data/sphere.txt"))
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	
	// m_TextureShader 객체 생성
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// m_TextureShader 객체 초기화
	if (!m_TextureShader->Initialize(m_Direct3D->GetDevice(), hwnd))
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}

	m_PlanetList = new PlanetListClass[10];
	for (int i = 0; i < 10; i++) {
		m_PlanetList[i].Initialize((PLANETS)i);
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// m_TextureShader 객체 반환
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// m_Model 객체 반환
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// m_Camera 객체 반환
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Direct3D 객체 반환
	if (m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}
}


bool GraphicsClass::Frame(float positionZ, float rotationY)
{
	for (int i = 0; i < 10; i++) {
		m_PlanetList[i].Frame();
	}
	
	// 카메라 위치 설정
	m_Camera->SetPosition(0.0f, 2.5f, positionZ);

	// 카메라의 회전을 설정합니다
	m_Camera->SetRotation(rotationY, 0.0f, 0.0f);

	// 그래픽 랜더링 처리
	return Render();
}


bool GraphicsClass::Render()
{
	// 씬을 그리기 위해 버퍼를 지웁니다
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// 카메라의 위치에 따라 뷰 행렬을 생성합니다
	m_Camera->Render();

	// 카메라 및 d3d 객체에서 월드, 뷰 및 투영 행렬을 가져옵니다
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, modelMatrix;
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	//for (int i = 0; i < 9; i++) {
	//	// 회전 할 수 있도록 회전 값으로 월드 행렬을 회전합니다.
	//	worldMatrix = XMMatrixScaling(0.6955, 0.6955, 0.6955) * XMMatrixRotationY(rotation) * XMMatrixTranslation(2*i, 0, 0);
	//	//XMMatrixRotationY(rotation), XMMatrixTranslation(2, 0, 0), XMMatrixScaling(0.6963, 0.6963, 0.6963), XMMatrixRotationY(rotation)

	//	// 모델 버텍스와 인덱스 버퍼를 그래픽 파이프 라인에 배치하여 드로잉을 준비합니다.
	//	m_Model->Render(m_Direct3D->GetDeviceContext());

	//	// 텍스쳐 쉐이더를 사용하여 모델을 렌더링합니다.
	//	if (!m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(EARTH)))
	//	{
	//		return false;
	//	}

	//	m_Direct3D->GetWorldMatrix(worldMatrix);
	//}

	// TEST
	for (int i = 0; i < 9; i++) {
		m_PlanetList[i].GetObjectMatrix(worldMatrix);

		// 모델 버텍스와 인덱스 버퍼를 그래픽 파이프 라인에 배치하여 드로잉을 준비합니다.
		m_Model->Render(m_Direct3D->GetDeviceContext());

		// 텍스쳐 쉐이더를 사용하여 모델을 렌더링합니다.
		if (!m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture((PLANETS)i)))
		{
			return false;
		}

		m_Direct3D->GetWorldMatrix(worldMatrix);
	}

	m_PlanetList[3].GetObjectMatrix(worldMatrix);
	m_PlanetList[9].GetObjectMatrix(worldMatrix);

	// 모델 버텍스와 인덱스 버퍼를 그래픽 파이프 라인에 배치하여 드로잉을 준비합니다.
	m_Model->Render(m_Direct3D->GetDeviceContext());

	// 텍스쳐 쉐이더를 사용하여 모델을 렌더링합니다.
	if (!m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(MOON)))
	{
		return false;
	}
	
	m_Direct3D->GetWorldMatrix(worldMatrix);

	// TEST

	// 버퍼의 내용을 화면에 출력합니다
	m_Direct3D->EndScene();

	return true;
}