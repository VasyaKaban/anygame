#include "Window.h"
#include "Camera.h"
#include "glew.h"
#include <iostream>
#include "Math/EMath.h"
#include "Timer.h"
#include "Math/Matrix_Transformations.h"
#include "Helper.h"
#include <vector>
#include "Math/Quaternion.h"
#include "Math/EMath.h"

#include "EditorStuff.h"
#include <thread>

const Uint8* KeyState = SDL_GetKeyboardState(NULL);

Camera::Camera(Vector3 Pos)
{
	this->Pos = Pos;
	Projection = Perspective(fov, float(Window::width) / (Window::height), 2.1f, 1000.0f);
	SetCamera();
	FocusOn();
};

Quaternion q, q1;

void Camera::SetCamera()
{
	View = QuatLook(q * q1, Pos, Orient, SideOrient);
}

void Camera::CameraPoll(SDL_Event &event)
{
	Focus = Pos;
	Focus = Focus + Orient;
	if (Window::onUI == false)
	{
		SDL_ShowCursor(false);
		if (event.type == SDL_MOUSEMOTION)
		{
			angleXZ -= float((CatchX - event.motion.x)) / 16.7;
			angleY -= float((CatchY - event.motion.y)) / 16.7;
			//if (angleY < -89.0) { angleY = -89.0; }
			//if (angleY > 89.0) { angleY = 89.0; }
			/*if (angleY > 360.0)
			{
				angleY = 0;
			}
			if (angleY < 0.0)
			{
				angleY = 360;
			}*/
			if (angleXZ > 360) { angleXZ = 0; }
			if (angleXZ < 0) { angleXZ = 360; }
			SDL_WarpMouseInWindow(Window::window, CatchX, CatchY);
			FocusOn();
			SetCamera();
		}
	}
	else
	{
		if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			float pix[4];
			glReadBuffer(GL_COLOR_ATTACHMENT0);
			glReadPixels(event.motion.x, Window::height - event.motion.y, 1, 1, GL_RGBA, GL_FLOAT, &pix);
			glReadBuffer(GL_NONE);
			Vector3 vpix;
			vpix.x = round(pix[0] * 10000) / 10000;
			vpix.y = round(pix[1] * 10000) / 10000;
			vpix.z = round(pix[2] * 10000) / 10000;
			for (std::unique_ptr<Object> &obj : GroupOfObjects)
			{
				if ((*obj).RGBid == vpix)
				{
					std::cout << (*obj).GetName()<< std::endl;
					(*obj).isPicked = true;
					continue;
				}
				(*obj).isPicked = false;
				
			}
			std::cout << vpix.x<<"\t"<<vpix.y<<"\t"<<vpix.z<<"\t"<<pix[3]<< std::endl;
		}
		SDL_ShowCursor(true);
		SDL_GetMouseState(&CatchX, &CatchY);
	}
}



// Frames = k / t
//k = Frames * t
//k = 999
//пусть идеал это 60 fps
//тогда узнаём во сколько раз таргет фпс больше 60
//на это число и будем умножать/делить

void Camera::Move()
{
	Vector3 Or = Orient;
	Or = Or / MainTimer.GetFramesRatio() / 10;
	Vector3 Sor = SideOrient;
	Sor = Sor / MainTimer.GetFramesRatio() / 10;
	if (KeyState[SDL_SCANCODE_W])
	{
		/*x -= -sin(angleXZ / 180 * 3.14) / MainTimer.GetFramesRatio() / speed;
		z += cos(angleXZ / 180 * 3.14) / MainTimer.GetFramesRatio() / speed;
		y += sin(angleY / 180 * 3.14) / MainTimer.GetFramesRatio() / speed;*/
		Pos += Or / 5;
	}
	if (KeyState[SDL_SCANCODE_S])
	{
		/*x += -sin(angleXZ / 180 * 3.14) / MainTimer.GetFramesRatio() / speed;
		z -= cos(angleXZ / 180 * 3.14) / MainTimer.GetFramesRatio() / speed;
		y -= sin(angleY / 180 * 3.14) / MainTimer.GetFramesRatio() / speed;*/
		Pos -= Or / 5;
	}
	
	if (KeyState[SDL_SCANCODE_A])
	{
		//x += -sin((angleXZ - 90) / 180 * 3.14) / MainTimer.GetFramesRatio() / speed;
		//z -= cos((angleXZ - 90) / 180 * 3.14) / MainTimer.GetFramesRatio() / speed;
		Pos += Sor / 5;
	}
	if (KeyState[SDL_SCANCODE_D])
	{
		//x += -sin((angleXZ + 90) / 180 * 3.14) / MainTimer.GetFramesRatio() / speed
		//z -= cos((angleXZ + 90) / 180 * 3.14) / MainTimer.GetFramesRatio() / speed;
		Pos -= Sor / 5;
	}
	if (KeyState[SDL_SCANCODE_LSHIFT])
	{
		//y -= 0.05 / MainTimer.GetFramesRatio();
		Pos.y -= 0.1 / MainTimer.GetFramesRatio();
	}
	if (KeyState[SDL_SCANCODE_LCTRL])
	{
		//y += 0.05 / MainTimer.GetFramesRatio();
		Pos.y += 0.1 / MainTimer.GetFramesRatio();
	}
	if (KeyState[SDL_SCANCODE_M])
	{
		for (std::unique_ptr<Object> &obj : GroupOfObjects)
		{
			if ((*obj).isPicked == true)
			{
				(*obj).Rotate = (*obj).Rotate * FromQuatToMat(Quaternion(RotateYawPitchRoll(Vector3(0, 0, 0.01 * MainTimer.GetDeltaT()))));
				(*obj).ModelCreate();
				(*obj).objAABB.Recompute((*obj).Model, (*obj).Vertexes);
				(*obj).objOBB.Recompute((*obj).Model);
			}
		}
	}

	if (KeyState[SDL_SCANCODE_R])
	{
		for (std::unique_ptr<Object> &obj : GroupOfObjects)
		{
			if ((*obj).isPicked == true)
			{
				(*obj).Rotate = (*obj).Rotate * FromQuatToMat(Quaternion(RotateYawPitchRoll(Vector3(0, 0.01 * MainTimer.GetDeltaT(), 0))));
				(*obj).ModelCreate();
				(*obj).objAABB.Recompute((*obj).Model, (*obj).Vertexes);
				(*obj).objOBB.Recompute((*obj).Model);
			}
		}
	}

	if (KeyState[SDL_SCANCODE_L])
	{
		for (std::unique_ptr<Object> &obj : GroupOfObjects)
		{
			if ((*obj).isPicked == true)
			{
				(*obj).Trans(3, 0) += 0.01 * MainTimer.GetDeltaT();
				(*obj).ModelCreate();
				(*obj).objAABB.Recompute((*obj).Model, (*obj).Vertexes);
				(*obj).objOBB.Recompute((*obj).Model);
			}

		}
	}

	if (KeyState[SDL_SCANCODE_U])
	{
		for (std::unique_ptr<Object> &obj : GroupOfObjects)
		{
			if ((*obj).isPicked == true)
			{
				(*obj).Trans(3, 1) += 0.01 * MainTimer.GetDeltaT();
				(*obj).ModelCreate();
				(*obj).objAABB.Recompute((*obj).Model, (*obj).Vertexes);
				(*obj).objOBB.Recompute((*obj).Model);
			}

		}
	}

	if (KeyState[SDL_SCANCODE_Z])
	{
		for (std::unique_ptr<Object> &obj : GroupOfObjects)
		{
			if ((*obj).isPicked == true)
			{
				(*obj).Trans(3, 2) -= 0.01 * MainTimer.GetDeltaT();
				(*obj).ModelCreate();
				(*obj).objAABB.Recompute((*obj).Model, (*obj).Vertexes);
				(*obj).objOBB.Recompute((*obj).Model);
			}

		}
	}

	/*for (std::unique_ptr<Object> &obj : GroupOfObjects)
	{
		if ((*obj).isPicked == true)
		{
			if (Pos.x > (*obj).objAABB.min.x && Pos.y > (*obj).objAABB.min.y && Pos.z > (*obj).objAABB.min.z && Pos.x < (*obj).objAABB.max.x && Pos.y < (*obj).objAABB.max.y && Pos.z < (*obj).objAABB.max.z) std::cout << "collide!" << std::endl;
		}

	}*/

	FocusOn();
	SetCamera();
}

void Camera::FocusOn()
{
	//FocusX = x + sin(angleXZ / 180 * 3.14);//Update Camera angle every iterations to avoid invisible world objects
	//FocusY = y + tan(angleY / 180 * 3.14);  //if you dont use mousemotion
	//FocusZ = z + cos(angleXZ / 180 * 3.14);

	q = RotateYawPitchRoll(Vector3(angleY, 0, 0));
	q1 = RotateYawPitchRoll(Vector3(0, angleXZ, 0));
}