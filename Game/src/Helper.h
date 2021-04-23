#pragma once
#include "Can.h"
namespace Can::Helper
{
#define TERRAIN_SCALE_DOWN 10.0f
#define COLOR_COUNT 5

	bool CheckBoundingBoxHit(const glm::vec3& rayStartPoint, const glm::vec3& ray, const glm::vec3& least, const glm::vec3& most);

	glm::vec2 CheckRotatedRectangleCollision(
		const glm::vec2& r1l,
		const glm::vec2& r1m,
		float rot1,
		const glm::vec2& pos1,
		const glm::vec2& r2l,
		const glm::vec2& r2m,
		float rot2,
		const glm::vec2& pos2
	);

	glm::vec3 RayPlaneIntersection(const glm::vec3& X, const glm::vec3& v, const glm::vec3& C, const glm::vec3& n);

	float DistanceBetweenLineSLineS(glm::vec2 p1, glm::vec2 p2, glm::vec2 p3, glm::vec2 p4);

	bool RayTriangleIntersection(const glm::vec3& camPos, const glm::vec3& ray, const glm::vec3& A, const glm::vec3& B, const glm::vec3& C, const glm::vec3& normal, glm::vec3& intersection);

	glm::vec2 RotateAPointAroundAPoint(const glm::vec2& p1, float angleInRadians, const glm::vec2& p2 = { 0.0f, 0.0f });

	void LevelTheTerrain(const glm::vec2& startIndex, const glm::vec2& endIndex, const glm::vec3& startCoord, const glm::vec3& endCoord, Object* terrain, float width);

	Prefab* GetPrefabForTerrain(const std::string& texturePath);

	std::vector<std::string> GetFiles(const std::string& folder, const std::string& filter, const std::string& fileType);

}