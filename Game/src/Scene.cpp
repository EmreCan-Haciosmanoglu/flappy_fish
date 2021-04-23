#include "canpch.h"
#include "Scene.h"
#include "GameLayer.h"

Scene::Scene(float width, float heigth, GameLayer* gameLayer)
	: m_ObstacleCount(8)
	, m_Width(width)
	, m_Height(heigth)
	, m_MovementSpeed(3.0f)
	, m_ObstacleWidth(1.4f)
	, m_MinObstacleHeight(2.5f)
	, m_MaxObstacleHeight(4.5f)
	, m_MinSpaceHeight(1.5f)
	, m_MaxSpaceHeight(2.5f)
	, m_MinSpaceWidth(2.5f)
	, m_MaxSpaceWidth(4.0f)
	, m_GameLayer(gameLayer)
{
	for (int i = 0; i < m_ObstacleCount; i++)
	{
		AddObstacle();
	}
	m_ObstacleTexture = Can::Texture2D::Create("assets/textures/Stalactite.png");
}

Scene::~Scene()
{
	m_Obstacles.clear();
}

void Scene::Update(float ts)
{
	float offset = ts * m_MovementSpeed;
	for (int i = 0; i < m_ObstacleCount; i++)
	{
		m_Obstacles.at(i).x1 -= offset;
		m_Obstacles.at(i).x2 -= offset;
		if (m_Obstacles.at(i).x1 < ((-m_Width) / 2.0f) + 1.5f)
		{
			m_GameLayer->AddPoint();
			m_Obstacles.erase(m_Obstacles.begin());
			AddObstacle();
			i--;
		}
	}
}

void Scene::Draw()
{
	auto params = Can::DrawQuadParameters();

	params.Position = { 0.0f, 0.0f, -0.111f };
	params.Size = { 38.0f,24.0f };
	params.texture = m_GameLayer->m_BackgroundImage;
	Can::Renderer2D::DrawQuad(params);

	params.Position = { 0.0f, 0.0f, -0.11f };
	params.Size = { m_Width + 0.5f, m_Height + 0.5f };
	params.texture = nullptr;
	params.TintColor = { 0.1f, 0.1f, 0.1f, 1.0f };
	Can::Renderer2D::DrawQuad(params);

	params.Position = { 0.0f, 0.0f, -0.1f };
	params.Size = { m_Width, m_Height };
	params.texture = m_GameLayer->m_WaterImage;
	params.TintColor =glm::vec4(1.0f);
	Can::Renderer2D::DrawQuad(params);

	params.texture = m_GameLayer->m_StalactiteImage;
	for (int i = 0; i < m_ObstacleCount; i++)
	{
		Obstacle ob = m_Obstacles.at(i);
		if (ob.x1 < m_Width / 2 - m_ObstacleWidth)
		{
			params.Position = { ob.x1 + m_ObstacleWidth / 2 , ob.y1 - m_Height / 2.0f, 0.0f };
			params.Size = { ob.w * 1.4f, ob.h1 };
			params.RotationInRadians = 0.0f;
			Can::Renderer2D::DrawQuad(params);

			params.Position = { ob.x2 + m_ObstacleWidth / 2 , ob.y2 - m_Height / 2.0f, 0.0f };
			params.Size = { ob.w * 1.4f, ob.h2 };
			params.RotationInRadians = glm::radians(180.0f);
			Can::Renderer2D::DrawQuad(params);
		}
	}
}

void Scene::AddObstacle()
{
	float x = m_Obstacles.size() > 0 ? m_Obstacles.back().x1 : -9.0f;

	float spacew = Can::Utility::Random::Float(m_MinSpaceWidth, m_MaxSpaceWidth);
	float height = Can::Utility::Random::Float(m_MinObstacleHeight, m_MaxObstacleHeight);
	float spaceh = Can::Utility::Random::Float(m_MinSpaceHeight, m_MaxSpaceHeight);
	float y1 = height / 2;
	float h2 = m_Height - (height + spaceh);
	float y2 = m_Height - (h2 / 2);
	x += spacew + m_ObstacleWidth;

	m_Obstacles.push_back(Obstacle(x, x, y1, y2, height, h2, m_ObstacleWidth, spacew));
}
