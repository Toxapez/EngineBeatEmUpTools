#pragma once
#include "GameObject.h"
#include "RectTwoPoint.h"
#include "Meth.h"
#include "CameraBounds.h"
class Cam: public GameObject
{
	bool zoomAnimation;
	float zoomAnimationTarget;
	float zoomAnimationCounter;
	float zoomAnimationTime;
	float zoomAnimationQuantity;
public:

	float speed;
	void SetCamMovible(Vector2 pos, float s, CameraBounds* cb = nullptr);
	void Update() override;
	void Draw() override;
	void Clamp();
	bool move = false;
	CameraBounds* cameraBounds;

	static Cam* currentCam;
	double zoom;
	double rotation;
	double realWorldZoom = 1;
	double worldZoom = 1;
	Cam();
	Cam(Vector2 pos);

	void StartSimpleZoomAnimation(float target, float time);
	void StopZoomAnimation();

	float vibrationCounter;
	Vector2 vibration;
	float vibrationForce;
	bool decreasingVibration;
	float decreasingVibrationFactor;

	void StartSimpleVibration(float time, float force);
	void StartDecreasingVibration(float d, float force);
	void StopVibration();
};

