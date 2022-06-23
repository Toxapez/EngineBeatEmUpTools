#pragma once
#include <vector>
#include "SDLClass.h"
#include <filesystem>
#include <iostream>
#include "OpenGLClass.h"

class Animation
{
public:
	static std::vector<Animation*> animations;
	std::vector<unsigned int> frames;
	unsigned int it;
	static void Start();
	Animation();
	Animation* Set(std::string _name, Vector2 os = Vector2());
	std::vector<int> index;
	std::vector<int> repeat;
	int currentFrame;
	int frameRepeatCounter;
	int realFrames;
	std::vector<RectTwoPoint> spriteRects;
	void SetRealFrames();
	void ModifyTimeline(int* indexs , int * repeats, int n);
	Vector2 offset;
	void Load();
	void Reset();
	std::string dir;
	float counter;
	float itIncrement;
	void SetFPS(int a);
	int framesPlayed;
	bool loop;
	int GetRealFrameBeingPlayed();
	void Play(float speed);
	bool HasEnded();
	~Animation();
};
