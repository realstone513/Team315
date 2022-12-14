#pragma once
#include <vector>
#include <map>
#include <string>
#include <nlohmann/json.hpp> //아니 nlohmann 이거 설치하라고 이;거"
#include <SFML/System/Vector2.hpp>
#include <String>

using json = nlohmann::json;
using namespace std;	

enum class FileTypes
{
	EpisodeInfo,
	HitBoxInfo,
	CookieHitBox,
};

namespace sf {
	void to_json(json& j, const Vector2f& p);
	void from_json(const json& j, Vector2f& p);
	void to_json(json& j, const Vector2i& p);
	void from_json(const json& j, Vector2i& p);
}

namespace ns {
	struct CircleInfo
	{
		float rad;
		sf::Vector2f pos;
	};
	void to_json(json& j, const CircleInfo& c);
	void from_json(const json& j, CircleInfo& c);
}

namespace ns {
	struct RectangleInfo
	{
		sf::Vector2f size;
		sf::Vector2f pos;
	};
	void to_json(json& j, const RectangleInfo& c);
	void from_json(const json& j, RectangleInfo& c);
}

namespace ns {
	struct ConvexInfo
	{
		vector<sf::Vector2f> points;
		sf::Vector2f pos;
	};
	void to_json(json& j, const ConvexInfo& c);
	void from_json(const json& j, ConvexInfo& c);
}

namespace ns {
	struct BackInfo
	{
		string path;
		float speed;
	};
	void to_json(json& j, const BackInfo& b);
	void from_json(const json& j, BackInfo& b);
}

namespace ns {
	struct TileData
	{
		sf::Vector2i arrIndex;

		int TileTypes;
		int ThemeTypes;
		int pathIndex;
		int grade;
	};
	void to_json(json& j, const TileData& b);
	void from_json(const json& j, TileData& b);
}

namespace ns {
	struct BackGroundData
	{
		sf::Vector2i arrIndex;

		int TileTypes;
		int ThemeTypes;
		int pathIndex;
	};

	void to_json(json& j, const BackGroundData& b);
	void from_json(const json& j, BackGroundData& b);
}

//namespace ns {
//	struct AltarStringData
//	{
//		string mana;
//		string silver;
//		string physical;
//		string enforce;
//	};
//
//	void to_json(json& j, const AltarStringData& b);
//	void from_json(const json& j, AltarStringData& b);
//}

struct Chapters
{
	vector<vector< vector<vector<ns::TileData>>>> data;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(Chapters, data);
};
struct MapData
{
	vector<ns::BackInfo> backInfo; // background path
	string bottomPath;		//bottom block path
	vector<int> bottomPos;	//bottom block draw position
	map<string, vector<sf::Vector2f>> obstacles; //obstacles draw path, draw position
	map<string, vector<sf::Vector2f>> jellys; //obstacles draw path, draw position
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(MapData, backInfo, bottomPath, bottomPos, obstacles, jellys)
};
struct BackGrounds
{
	vector<ns::BackGroundData> data;
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(BackGrounds, data);
};
struct HitBoxInfo
{
	vector<ns::CircleInfo> circles;    // rad, pos
	vector<ns::RectangleInfo> rectangls;  //  size , pos
	vector <ns::ConvexInfo> points; //point
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(HitBoxInfo, circles, rectangls, points)
};

struct CookieHitBox
{
	string type;
	HitBoxInfo hitBox;
	ns::RectangleInfo bottom;
		
	NLOHMANN_DEFINE_TYPE_INTRUSIVE(CookieHitBox, type, hitBox, bottom)
};



