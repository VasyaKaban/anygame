#pragma once

#include "SDL.h"
#include "Math/Matrix4x4.h"
#include "Math/Vector3.h"


class Camera
{
public:

	Camera(Vector3 Pos);

	void CameraPoll(SDL_Event &event);
	
	void Move();

	void FocusOn();

	Matrix4x4 View;



private:
	void SetCamera();
	Vector3 Pos;
	Vector3 Focus;
	float angleXZ = 0;
	float angleY = 0;
	int CatchX, CatchY;
	Vector3 Orient, SideOrient;
};