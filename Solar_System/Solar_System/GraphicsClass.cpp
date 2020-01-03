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
	// Direct3D ��ü ����
	m_Direct3D = new D3DClass;
	if (!m_Direct3D)
	{
		return false;
	}

	// Direct3D ��ü �ʱ�ȭ
	if (!m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR))
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}

	// m_Camera ��ü ����
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// ī�޶� ������ ����
	m_Camera->SetPosition(0.0f, 0.0f, -5.0f);

	// m_Model ��ü ����
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}
	
	// m_Model ��ü �ʱ�ȭ
	if (!m_Model->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "data/sphere.txt"))
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}
	
	// m_Map ��ü ����
	m_Map = new ModelClass;
	if (!m_Map)
	{
		return false;
	}

	// m_Map ��ü �ʱ�ȭ
	if (!m_Map->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "data/map.txt"))
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// m_TextureShader ��ü ����
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// m_TextureShader ��ü �ʱ�ȭ
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
	// m_TextureShader ��ü ��ȯ
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// m_Model ��ü ��ȯ
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// m_Camera ��ü ��ȯ
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}

	// Direct3D ��ü ��ȯ
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
	
	// ī�޶� ��ġ ����
	m_Camera->SetPosition(0.0f, 2.5f, positionZ);

	// ī�޶��� ȸ���� �����մϴ�
	m_Camera->SetRotation(rotationY, 0.0f, 0.0f);

	// �׷��� ������ ó��
	return Render();
}


bool GraphicsClass::Render()
{
	// ���� �׸��� ���� ���۸� ����ϴ�
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// ī�޶��� ��ġ�� ���� �� ����� �����մϴ�
	m_Camera->Render();

	// ī�޶� �� d3d ��ü���� ����, �� �� ���� ����� �����ɴϴ�
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, modelMatrix;
	m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	m_Direct3D->GetProjectionMatrix(projectionMatrix);

	//	//XMMatrixRotationY(rotation), XMMatrixTranslation(2, 0, 0), XMMatrixScaling(0.6963, 0.6963, 0.6963), XMMatrixRotationY(rotation)

	// �¾�� �༺�� 
	for (int i = 0; i < 9; i++) {
		m_PlanetList[i].GetObjectMatrix(worldMatrix);

		// �� ���ؽ��� �ε��� ���۸� �׷��� ������ ���ο� ��ġ�Ͽ� ������� �غ��մϴ�.
		m_Model->Render(m_Direct3D->GetDeviceContext());

		// �ؽ��� ���̴��� ����Ͽ� ���� �������մϴ�.
		if (!m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture((PLANETS)i)))
		{
			return false;
		}

		m_Direct3D->GetWorldMatrix(worldMatrix);
	}

	// ��
	m_PlanetList[3].GetObjectMatrix(worldMatrix);
	m_PlanetList[9].GetObjectMatrix(worldMatrix);

	// �� ���ؽ��� �ε��� ���۸� �׷��� ������ ���ο� ��ġ�Ͽ� ������� �غ��մϴ�.
	m_Model->Render(m_Direct3D->GetDeviceContext());

	// �ؽ��� ���̴��� ����Ͽ� ���� �������մϴ�.
	if (!m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetIndexCount(), worldMatrix, viewMatrix, projectionMatrix, m_Model->GetTexture(MOON)))
	{
		return false;
	}
	
	m_Direct3D->GetWorldMatrix(worldMatrix);

	// ������ ������ ȭ�鿡 ����մϴ�
	m_Direct3D->EndScene();

	return true;
}