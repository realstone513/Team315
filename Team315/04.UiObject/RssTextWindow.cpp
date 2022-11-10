#include "RssTextWindow.h"

RssTextWindow::RssTextWindow(Font& font)
	: value(0.f), valueGoal(0.f)
{
	text.setFont(font);
}

RssTextWindow::~RssTextWindow()
{
}

void RssTextWindow::Update(float dt)
{
	text.setString(to_string(value));
}

void RssTextWindow::Draw(RenderWindow& window)
{
	Object::Draw(window);
	window.draw(background);
	window.draw(text);
}

void RssTextWindow::SetPos(const Vector2f& pos)
{
	SpriteObj::SetPos(pos);
	background.setPosition(pos + backgroundLocalPos);
	text.setPosition(pos + textLocalPos);
}

void RssTextWindow::SetSize(float x, float y)
{
	background.setSize(Vector2f(x, y));
}

void RssTextWindow::SetBackgroundColor(Color color)
{
	background.setFillColor(color);
}

void RssTextWindow::SetBackgroundOutline(Color color, float thickness)
{
	background.setOutlineColor(color);
	background.setOutlineThickness(thickness);
}

void RssTextWindow::SetBackgroundLocalPos(Vector2f bgPos)
{
	backgroundLocalPos = bgPos;
}

void RssTextWindow::SetTextLocalPos(Vector2f txtPos)
{
	textLocalPos = txtPos;
}

void RssTextWindow::SetTextValue(float value)
{
	valueGoal = value;
}

void RssTextWindow::SetTextStyle(Color color, int cSize)
{
	text.setFillColor(color);
	text.setCharacterSize(cSize);
}

void RssTextWindow::SetTextOutline(Color color, float thickness)
{
	text.setOutlineColor(color);
	text.setOutlineThickness(thickness);
}