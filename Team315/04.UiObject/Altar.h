#pragma once
#include "SpriteObj.h"
#include "TextObj.h"
#include "Include.h"
#include "Animator.h"
#include "rapidcsv.h"
//#include "StringTable.h"

struct AltarStr
{
	wstring altar1;
	wstring altar2;
	wstring altar3;
	AltarStr() {}
	AltarStr(wstring str1, wstring str2, wstring str3)
		: altar1(str1), altar2(str2), altar3(str3)
	{}
};

class Altar :  public SpriteObj
{
protected:
	int m_grade;

	SpriteObj m_altarEffect;
	SpriteObj m_altarLight;

	vector<SpriteObj> numList;
	//roma
	SpriteObj m_romaNum01;
	SpriteObj m_romaNum05;
	SpriteObj m_romaNum10;
	SpriteObj m_romaNum15;
	//dot
	SpriteObj m_romaNum02;
	SpriteObj m_romaNum03;
	SpriteObj m_romaNum04;
	SpriteObj m_romaNum06;
	SpriteObj m_romaNum07;
	SpriteObj m_romaNum08;
	SpriteObj m_romaNum09;
	SpriteObj m_romaNum11;
	SpriteObj m_romaNum12;
	SpriteObj m_romaNum13;
	SpriteObj m_romaNum14;

	SpriteObj m_button1;
	SpriteObj m_button5;

	TextObj m_number;
	TextObj m_altarName;
	Vector2f altarPos;

	TextObj m_buff1;
	TextObj m_buff2;
	TextObj m_buff3;

	Sprite m_sFlame;
	Animator m_Flame;

	int m_Index;

	map<string, AltarStr> AltarStringData;

public:
	Altar(Vector2f mainPos, int index, wstring AltarName, Color color, int loadGrade);
	virtual ~Altar() {};

	virtual void Update(float dt) override;
	virtual void Draw(RenderWindow& window) override;

	virtual void Enter();
	
	void MoveSetPos(Vector2f movepos);
	int GetIndex() { return m_Index; };
	int GetGrade() { return m_grade; };
	void SetGrade(int grade) {m_grade = grade;};

	void SetAltarString();
	void SetRomaNumber(Vector2f mainPos, int index);
	void SetBuffString(Vector2f mainpos);

	int GetButtonCall(Vector2f nowMousePos, int count);

	void ResetCount();

	void ChangeAltarNum(int Num);
	void ChangeObjAlhpa(int num);
};