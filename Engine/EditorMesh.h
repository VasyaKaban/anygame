#pragma once
#include <iostream>
#include "glew.h"
#include <vector>
#include"Math/Quaternion.h"
#include "Math/Matrix_Transformations.h"
#include "Math/EMath.h"

//GLuint EMvbo, EMvao;

//std::vector<MeshCoord> mc;

//Matrix4x4 mcModel;


//void FillEditorMesh()
//{
//	MeshCoord Helpmc;
//	for (int i = -1000; i < 1001; i++)
//	{
//		Helpmc.x = i;
//		Helpmc.y = 0.0;
//		Helpmc.z = -1000;
//		mc.push_back(Helpmc);
//
//		Helpmc.x = i;
//		Helpmc.y = 0.0;
//		Helpmc.z = 1000;
//		mc.push_back(Helpmc);
//	}
//
//	for (int k = -1000; k < 1001; k++)
//	{
//		Helpmc.x = -1000;
//		Helpmc.y = 0.0;
//		Helpmc.z = k;
//		mc.push_back(Helpmc);
//
//		Helpmc.x = 1000;
//		Helpmc.y = 0.0;
//		Helpmc.z = k;
//		mc.push_back(Helpmc);
//	}
//
//	glGenVertexArrays(1, &EMvao);
//	glGenBuffers(1, &EMvbo);
//	glBindVertexArray(EMvao);
//	glBindBuffer(GL_ARRAY_BUFFER, EMvbo);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(MeshCoord) * mc.size(), &mc.front(), GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
//	glEnableVertexAttribArray(0);
//
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//
//}

//void DrawMesh()
//{
//	glBindVertexArray(EMvao);
//	glDrawArrays(GL_LINES, 0, mc.size());
//	glBindVertexArray(0);
//}


//unsigned int count = 0;
//int tim = 0;
//unsigned int moveOnArray = 0;
//enum mode
//{
//	X = 0,
//	Y = 1,
//	Z = 2
//};
//
//enum ModelMode
//{
//	Translate = 10,
//	Rotate = 20,
//	Scale = 30
//};
//
//int mod = 0;
//int Modelmod = 10;
//
//std::string EditorTitle;
//std::string EditorActiveCoord = "";
//std::string EditorTypeOfModelTranslation;
//
//bool ButtonPressed = false;
//
//void SetTitle()
//{
//	SDL_SetWindowTitle(Window::window, EditorTitle.c_str());
//}
//
//bool intersected = false;
//
//GroupOfObjects[moveOnArray].isSelected = 1;
//if (event.type == SDL_MOUSEWHEEL)
//{
//	if (event.wheel.y > 0) // scroll up
//	{
//		if (mod == Y)
//		{
//			if (Modelmod == Translate)
//			{
//				GroupOfObjects[moveOnArray].TranslateObj(0.0, -1, 0);  //https://en.wikipedia.org/wiki/Rotation_matrix https://stackoverflow.com/questions/9901453/using-glms-unproject
//			}										//https://ravesli.com/urok-7-transformatsii-v-opengl/#toc-16
//			else if (Modelmod == Rotate)
//			{
//				GroupOfObjects[moveOnArray].aY += 0.1;
//				GroupOfObjects[moveOnArray].RotateObj(0.1, 0.0, 1, 0.0);
//			}
//			else
//			{
//				GroupOfObjects[moveOnArray].ScaleObj(1.1);
//			}
//
//		}
//		else if (mod == X)
//		{
//			if (Modelmod == Translate)
//			{
//				GroupOfObjects[moveOnArray].TranslateObj(1, 0.0, 0.0);
//			}
//			else if (Modelmod == Rotate)
//			{
//				GroupOfObjects[moveOnArray].aX += 0.1;
//				GroupOfObjects[moveOnArray].RotateObj(0.1, 1, 0.0, 0.0);
//			}
//			else
//			{
//				GroupOfObjects[moveOnArray].ScaleObj(1.1);
//			}
//
//		}
//		else
//		{
//			if (Modelmod == Translate)
//			{
//				GroupOfObjects[moveOnArray].TranslateObj(0, 0.0, -1);
//			}
//			else if (Modelmod == Rotate)
//			{
//				GroupOfObjects[moveOnArray].aZ += 0.1;
//				GroupOfObjects[moveOnArray].RotateObj(0.1, 0.0, 0.0, 1);
//			}
//			else
//			{
//				GroupOfObjects[moveOnArray].ScaleObj(1.1);
//			}
//
//		}
//
//	}
//	else if (event.wheel.y < 0) // scroll down
//	{
//		if (mod == Y)
//		{
//			if (Modelmod == Translate)
//			{
//				GroupOfObjects[moveOnArray].TranslateObj(0.0, 1, 0);
//			}
//			else if (Modelmod == Rotate)
//			{
//				GroupOfObjects[moveOnArray].aY -= 0.1;
//				GroupOfObjects[moveOnArray].RotateObj(-0.1, 0.0, 1, 0.0);//http://sporgalka.blogspot.com/2011/12/opengl.html
//			}
//			else
//			{
//				GroupOfObjects[moveOnArray].ScaleObj(-1.1);
//			}
//
//		}
//		else if (mod == X)
//		{
//			if (Modelmod == Translate)
//			{
//				GroupOfObjects[moveOnArray].TranslateObj(-1, 0.0, 0.0);
//			}
//			else if (Modelmod == Rotate)
//			{
//				GroupOfObjects[moveOnArray].aX -= 0.1;
//				GroupOfObjects[moveOnArray].RotateObj(-0.1, 1, 0.0, 0.0);
//			}
//			else
//			{
//				GroupOfObjects[moveOnArray].ScaleObj(-1.1);
//			}
//
//		}
//		else
//		{
//			if (Modelmod == Translate)
//			{
//				GroupOfObjects[moveOnArray].TranslateObj(0, 0.0, 1);
//			}
//			else if (Modelmod == Rotate)
//			{
//				GroupOfObjects[moveOnArray].aZ -= 0.1;
//				GroupOfObjects[moveOnArray].RotateObj(-0.1, 0.0, 0.0, 1);
//			}
//			else
//			{
//				GroupOfObjects[moveOnArray].ScaleObj(-1.1);
//			}
//
//		}
//	}
//}
//
//if (event.type == SDL_MOUSEBUTTONDOWN)
//{
//
//	ButtonPressed = true;
//
//}
//if (event.type == SDL_MOUSEBUTTONUP)
//{
//	ButtonPressed = false;
//}
//if (event.type == SDL_MOUSEMOTION)
//{
//	if (ButtonPressed)
//	{
//		angleXZ -= (CatchX - event.motion.x) / 16.7;
//		angleY -= (CatchY - event.motion.y) / 16.7;
//		if (angleY < -89.0) { angleY = -89.0; }
//		if (angleY > 89.0) { angleY = 89.0; }
//		if (angleXZ > 360) { angleXZ = 0; }
//		if (angleXZ < 0) { angleXZ = 360; }
//		//SDL_WarpMouseInWindow(Window::window, CatchX, CatchY);
//		FocusOn();
//		SetCamera();
//	}
//}
//
//if (event.type = SDL_KEYDOWN)
//{
//	if (event.key.keysym.sym == SDLK_m)
//	{
//		count++;
//		if (count % 2 == 1)
//		{
//			GroupOfObjects.push_back(GroupOfObjects[moveOnArray]);
//			GroupOfObjects.back().ReadObject();
//			GroupOfObjects.back().CreateTexture();
//			GroupOfObjects.back().TranslateObj(FocusX + sin(angleXZ / 180 * 3.14), FocusY, FocusZ + cos(angleXZ / 180 * 3.14));
//			GroupOfObjects.back().CreateBuffers();
//			GroupOfObjects.back().isSelected = 0;
//		}
//	}
//	if (event.key.keysym.sym == SDLK_y)
//	{
//		mod = Y;
//		EditorActiveCoord = "xYz";
//	}
//	if (event.key.keysym.sym == SDLK_x)
//	{
//		mod = X;
//		EditorActiveCoord = "Xyz";
//	}
//	if (event.key.keysym.sym == SDLK_z)
//	{
//		mod = Z;
//		EditorActiveCoord = "xyZ";
//	}
//	if (event.key.keysym.sym == SDLK_LCTRL)
//	{
//		if (event.key.keysym.sym == SDLK_c)
//		{
//
//		}
//	}
//	if (event.key.keysym.sym == SDLK_DELETE)
//	{
//		count++;
//		if (count % 2 == 1)
//		{
//			GroupOfObjects[moveOnArray].DeleteBuffers();
//			GroupOfObjects.erase(GroupOfObjects.begin() + moveOnArray);
//			if (moveOnArray > GroupOfObjects.size() - 1)
//			{
//				moveOnArray = GroupOfObjects.size() - 1;
//			}
//		}
//	}
//	if (event.key.keysym.sym == SDLK_r)
//	{
//		Modelmod = Rotate;
//		EditorTypeOfModelTranslation = "Rotate";
//	}
//	if (event.key.keysym.sym == SDLK_t)
//	{
//		Modelmod = Translate;
//		EditorTypeOfModelTranslation = "Translate";
//	}
//	if (event.key.keysym.sym == SDLK_n)
//	{
//		Modelmod = Scale;
//		EditorTypeOfModelTranslation = "Scale";
//	}
//	if (event.key.keysym.sym == SDLK_DOWN)
//	{
//		count++;
//		if (count % 2 == 1)
//		{
//			if (moveOnArray != GroupOfObjects.size() - 1)
//			{
//				GroupOfObjects[moveOnArray].isSelected = 0;
//			}
//			if (moveOnArray < GroupOfObjects.size() - 1)
//			{
//				moveOnArray++;
//				system("cls");
//				for (int i = 0; i < GroupOfObjects.size(); i++)
//				{
//					if (i == moveOnArray)
//					{
//						std::cout << GroupOfObjects[moveOnArray].GetPath() << " Selected" << std::endl;
//						GroupOfObjects[moveOnArray].isSelected = 1;
//					}
//					else
//					{
//						std::cout << GroupOfObjects[i].GetPath() << std::endl;
//					}
//				}
//				std::cout << mod << std::endl;
//			}
//		}
//
//	}
//	if (event.key.keysym.sym == SDLK_UP)
//	{
//		count++;
//		if (count % 2 == 1)
//		{
//			if (moveOnArray != 0)
//			{
//				GroupOfObjects[moveOnArray].isSelected = 0;
//			}
//			if (moveOnArray > 0)
//			{
//				moveOnArray--;
//				system("cls");
//				for (int i = 0; i < GroupOfObjects.size(); i++)
//				{
//					if (i == moveOnArray)
//					{
//						std::cout << GroupOfObjects[moveOnArray].GetPath() << " Selected" << std::endl;
//						GroupOfObjects[moveOnArray].isSelected = 1;
//					}
//					else
//					{
//						std::cout << GroupOfObjects[i].GetPath() << std::endl;
//					}
//				}
//				std::cout << mod << std::endl;
//			}
//		}
//
//	}
//}
//	}
//
//	EditorTitle = "Editor mode: " + EditorActiveCoord + "; Type: " + EditorTypeOfModelTranslation + "; Object: " + GroupOfObjects[moveOnArray].GetPath();
//	SetTitle();

