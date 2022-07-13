#include "Window.h"
#include <iostream>
#include "Camera.h"
#include "Math/Matrix_Transformations.h"
#include "Math/Matrix4x4.h"
#include "Helper.h"

SDL_Window* Window::window;
int Window::width;
int Window::height;
bool Window::onUI = true;
bool Window::isClose = false;

Window::Window(int width, int height)
{
	this->width = width;
	this->height = height;
	onUI = true;
	isClose = false;
};

Window::~Window()
{
	SDL_GL_DeleteContext(glcontext);

	SDL_DestroyWindow(window);

	SDL_Quit();
};

int Window::WinInit()
{
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 5);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	//SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES, 16);

	window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	glcontext = SDL_GL_CreateContext(window);

	if (window == nullptr)
	{
		std::cout << "Error! Window cannot to be created!"<< std::endl;
		return 1;
	}
	return 0;
}

void Window::evPoll(SDL_Event &event)
{
		switch (event.type)
		{
		case SDL_QUIT: isClose = true; break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_q)
			{
				isClose = true;
			}
			if (event.key.keysym.sym == SDLK_ESCAPE)
			{
				if (onUI == false)
				{
					onUI = true;
				}
				else
				{
					onUI = false;
				}
			}
			break;
		
		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_RESIZED)
			{
				SDL_GetWindowSize(window,&width,&height);
				glViewport(0, 0, width, height);
				Projection = Perspective(fov, float(width) / (height), 0.1f, 1000.0f);
				//PickFBO.Bind();

				////glGenTextures(1, &Ftexture);
				//glBindTexture(GL_TEXTURE_2D, Ftexture);
				//glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
				//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				//glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Ftexture, 0);
				//glBindTexture(GL_TEXTURE_2D, 0);

				//glBindRenderbuffer(GL_RENDERBUFFER, rbo);
				//glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
				//glBindRenderbuffer(GL_RENDERBUFFER, 0);

				//glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);
				//PickFBO.UnBind();
			}
			break; 
		}
}

void Window::SwapBuffers()
{
	SDL_GL_SwapWindow(window);
}

void Window::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}