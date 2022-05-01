#define _USE_MATH_DEFINES
#include <cmath>

#include "../../../../catch2/catch.hpp"

#include "../../../../labs/lab4/shapes/headers/shapes/CCircle.h"

TEST_CASE("Circle at creation state")
{
	const CPoint basePoint{ 10.10, 20.20 };
	const double radius = 100;
	const uint32_t outlineColor = 16711680, fillColor = 65280;
	const CCircle circle{ basePoint, radius, outlineColor, fillColor };

	WHEN("Circle created")
	{
		THEN("Getters are working correctly")
		{
			REQUIRE(circle.GetRadius() == radius);
			REQUIRE(circle.GetCenter() == basePoint);
			REQUIRE(circle.GetArea() == M_PI * radius * radius);
			REQUIRE(circle.GetPerimeter() == 2 * M_PI * radius);
			REQUIRE(circle.GetFillColor() == fillColor);
			REQUIRE(circle.GetOutlineColor() == outlineColor);
		}
	}
}
