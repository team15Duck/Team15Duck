#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

//각 쉽들의 어떤 속성들이 있다고 가정
class elements
{
public:
	const char* name;		//쉽의 종류(이미지이름)
	int currentHP;
	int maxHP;
	float angle;
	float accelaration;
	float maxSpeed;

	elements() {};
	~elements() {};
};



class database : public singletonBase<database>
{
private:
	typedef vector<string>			 arrElements;
	typedef vector<string>::iterator iterElements;

	typedef map<string, elements*>			 arrElement;
	typedef map<string, elements*>::iterator iterElement;

private:
	arrElement _mTotalElement;
	float _angle;		//한 눈에 보기쉬운 앵글회전으루다가

public:
	database();
	~database();

	HRESULT init();
	void release();

	//속성값으로부터 읽어들이기 위함.
	void loadDatabase(string name);

	elements* getElementData(string str) { return _mTotalElement.find(str)->second; }

	//설정자
	void setElementDataCurrentHP(string str, float ch);
	void setElementDataMaxHP(string str, float mh);
	void setElementDataAngle(string str, float a);
	void setElementDataAccel(string str, float accel);
	void setElementDataMaxSpeed(string str, float ms);

	void setAngle(float angle) { _angle = angle; }
	float getAngle() { return _angle; }

};

