#pragma once
#include <SFML/Graphics.hpp>
#include <list>
#include <map>

using namespace sf;
using namespace std;

enum class Axis
{
    Horizontal,
    Vertical,
};

struct AxisInfo
{
    Axis axis;
    list<Keyboard::Key> positives;
    list<Keyboard::Key> negatives;

    float sensi;
    float value;
};

class InputMgr
{
private:
    static map<Axis, AxisInfo> axisInfoMap;
    static list<int> downList;
    static list<int> ingList;
    static list<int> upList;
    static Vector2f mousePos;
    static float mouseWheelState;

public:
    static void Init();
    static void Update(float dt);
    static void ProcessInput(Event& ev);

    static bool GetKeyDown(Keyboard::Key key);
    static bool GetKey(Keyboard::Key key);
    static bool GetKeyUp(Keyboard::Key key);

    static float GetAxis(Axis axis);
    static float GetAxisRaw(Axis axis);

    static const Vector2f& GetMousePosF();
    static const Vector2i& GetMousePosI();
    static bool GetMouseDown(Mouse::Button key);
    static bool GetMouse(Mouse::Button key);
    static bool GetMouseUp(Mouse::Button key);
    static float GetMouseWheel();
};