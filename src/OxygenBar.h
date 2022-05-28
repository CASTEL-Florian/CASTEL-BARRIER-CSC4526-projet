#pragma once

class OxygenBar
{
public:
	explicit OxygenBar(float x, float y, float timeMax);
	void update();
	void display();
private:
	const float timeMax;
	float time;
	float x;
	float y;

};

