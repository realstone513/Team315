#include "RectangleObj.h"

RectangleObj::RectangleObj(float x, float y)
{
	shape.setSize(Vector2f(x, y));
}

RectangleObj::~RectangleObj()
{
}

void RectangleObj::Draw(RenderWindow& window)
{
	window.draw(shape);
	Object::Draw(window);
}

void RectangleObj::SetTexture(Texture* tex)
{
	shape.setTexture(tex);
}

void RectangleObj::SetOrigin(Origins origin)
{
	Utils::SetOrigin(shape, origin);
}

void RectangleObj::SetPos(const Vector2f& pos)
{
	Object::SetPos(pos);
	shape.setPosition(position);
}

void RectangleObj::SetScale(float x, float y)
{
	shape.setScale(x, y);
}

void RectangleObj::SetFillColor(Color color)
{
	shape.setFillColor(color);
}

void RectangleObj::SetFillColorAlpha(int alpha)
{
	Color color = shape.getFillColor();
	color.a = alpha;

	SetFillColor(color);
}

void RectangleObj::SetOutline(Color outlColor, float outlThickness)
{
	shape.setOutlineColor(outlColor);
	shape.setOutlineThickness(outlThickness);
}

void RectangleObj::SetSize(float x, float y)
{
	shape.setSize(Vector2f(x, y));
}

void RectangleObj::SetRotate(float rotate)
{
	shape.setRotation(rotate);
}

void RectangleObj::SetTextureRect(const IntRect& rect)
{
	shape.setTextureRect(rect);
}

const IntRect& RectangleObj::GetTextureRect() const
{
	return shape.getTextureRect();
}

Vector2f RectangleObj::GetSize() const
{
	FloatRect rect = shape.getLocalBounds();

	return Vector2f(rect.width, rect.height);
}

FloatRect RectangleObj::GetGlobalBounds() const
{
	return shape.getGlobalBounds();
}

RectangleShape& RectangleObj::GetShape()
{
	return shape;
}