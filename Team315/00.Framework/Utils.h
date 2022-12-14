#pragma once
#include "SFML/Graphics.hpp"
#include <random>
#include <vector>

using namespace sf;
using namespace std;

enum class Origins
{
	TL, TC, TR,
	ML, MC, MR,
	BL, BC, BR,
};

class Utils
{
private:
	static std::random_device rd;
	static std::mt19937 gen;

public:
	static void SetOrigin(Text& obj, Origins origin);
	static void SetOrigin(Sprite& obj, Origins origin);
	static void SetOrigin(Shape& obj, Origins origin);
	static void SetOrigin(Transformable& obj, Origins origin, FloatRect rect);
	static float Clamp(float v, float min, float max);

	static int RandomRange(int min, int maxExclude);
	static float RandomRange(float min, float maxInclude);
	static float RandomZeroToOne();
	static Vector2f RandomInCirclePoint();
	static Vector2f RandomOutCirclePoint();

	// Vector2f
	static float SqrMagnitude(const Vector2f& vec);
	static float Magnitude(const Vector2f& vec);
	static Vector2f Normalize(const Vector2f& vec);
	static float Distance(const Vector2f& vec1, const Vector2f& vec2);
	static float Dot(const Vector2f& a, const Vector2f& b);
	static Vector2f GetNormal(const Vector2f& vec);

	// Vector2i
	static float SqrMagnitude(const Vector2i& vec);
	static float Magnitude(const Vector2i& vec);
	static float Distance(const Vector2i& vec1, const Vector2i& vec2);

	static bool EqualFloat(float a, float b, float epsilon = numeric_limits<float>::epsilon());
	static float GetMinScaleRatioFromFloatRect(float sizeX, float sizeY, FloatRect fr);

	//Use Korean Set
	static wstring s2w(const std::string& var);
	static wstring ReplaceNewLine(wstring str);
};