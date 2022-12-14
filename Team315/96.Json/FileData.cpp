#include "FileData.h"

void ns::to_json(json& j, const BackInfo& b)
{
    j = json{ {"path", b.path}, {"speed", b.speed} };
}

void ns::from_json(const json& j, BackInfo& b)
{
    j.at("path").get_to(b.path);
    j.at("speed").get_to(b.speed);
}

void sf::to_json(json& j, const Vector2f& p)
{
    j = json{ {"x", p.x}, {"y", p.y} };
}

void sf::from_json(const json& j, Vector2f& p)
{
    j.at("x").get_to(p.x);
    j.at("y").get_to(p.y);
}

void sf::to_json(json& j, const Vector2i& p)
{
    j = json{ {"x", p.x}, {"y", p.y} };
}

void sf::from_json(const json& j, Vector2i& p)
{
    j.at("x").get_to(p.x);
    j.at("y").get_to(p.y);
}

void ns::to_json(json& j, const CircleInfo& c)
{
    j = json{ {"rad", c.rad}, {"pos", c.pos} };
}

void ns::from_json(const json& j, CircleInfo& c)
{
    j.at("rad").get_to(c.rad);
    j.at("pos").get_to(c.pos);
}

void ns::to_json(json& j, const RectangleInfo& c)
{
    j = json{ {"size", c.size}, {"pos", c.pos} };
}

void ns::from_json(const json& j, RectangleInfo& c)
{
    j.at("size").get_to(c.size);
    j.at("pos").get_to(c.pos);
}

void ns::to_json(json& j, const ConvexInfo& c)
{
    j = json{ {"points", c.points}, {"pos", c.pos} };
}

void ns::from_json(const json& j, ConvexInfo& c)
{
    j.at("points").get_to(c.points);
    j.at("pos").get_to(c.pos);
}

//sf::Vector2i arrIndex;
//
//int TileTypes;
//int ThemeTypes;
//int pathIndex;

void ns::to_json(json& j, const TileData& b)
{
	j = json
	{
		{"arrIndex", b.arrIndex},
		{"TileTypes", b.TileTypes},
		{"ThemeTypes", b.ThemeTypes},
		{"pathIndex", b.pathIndex},
	    {"grade", b.grade}
	};
}

void ns::from_json(const json& j, TileData& b)
{
    j.at("arrIndex").get_to(b.arrIndex);
    j.at("TileTypes").get_to(b.TileTypes);
    j.at("ThemeTypes").get_to(b.ThemeTypes);
    j.at("pathIndex").get_to(b.pathIndex);
    j.at("grade").get_to(b.grade);
}

void ns::to_json(json& j, const BackGroundData& b)
{
    j = json
    {
        {"arrIndex", b.arrIndex},
        {"TileTypes", b.TileTypes},
        {"ThemeTypes", b.ThemeTypes},
        {"pathIndex", b.pathIndex},
    };
}

void ns::from_json(const json& j, BackGroundData& b)
{
    j.at("arrIndex").get_to(b.arrIndex);
    j.at("TileTypes").get_to(b.TileTypes);
    j.at("ThemeTypes").get_to(b.ThemeTypes);
    j.at("pathIndex").get_to(b.pathIndex);
}
