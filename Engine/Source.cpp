#include <iostream>
#include "Window.h"
#include "Camera.h"
#include "Object.h"
#include "Shader.h"
#include "Timer.h"
#include <vector>
#include "Math/Vector3.h"
#include "Helper.h"
#include <chrono>
#include "EditorStuff.h"
#include "Texture.h"
#include "FrameBuffer.h"

//std::vector<Object*> GroupOfObjects;
std::vector<std::unique_ptr<Object>> GroupOfObjects;
Timer MainTimer;
Shader ObjectShader("gamedata/shaders/Vs.vs", "gamedata/shaders/Fs.fs");
Shader PickShader("gamedata/shaders/Pick.vs", "gamedata/shaders/Pick.fs");
Shader ArrowShader("gamedata/shaders/Arrow.vs", "gamedata/shaders/Arrow.fs");
Shader BBShader("gamedata/shaders/BB.vs", "gamedata/shaders/BB.fs");
Matrix4x4 Projection;
float fov = 45.0f;

bool InitSDL()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		std::cout << "Error! SDL cannot be initialized!" << std::endl;
		return 1;
	}
	return 0;
}

bool InitSDLIMG()
{
	if (!IMG_Init(IMG_INIT_PNG))
	{
		std::cout << "Error! SDLIMG cannot be initialized!" << std::endl;
		return 1;
	}
	return 0;
}

bool InitGLEW()
{
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Error! Glew cannot be initialized!" << std::endl;
		return 1;
	}
	return 0;
}

void PollEvents(Window &window,Camera &camera)
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		window.evPoll(event);
		camera.CameraPoll(event);
	}
}

int main(int argc, char* argv[])
{
	InitSDL();
	InitSDLIMG();
	std::cout << __DATE__ << "\t" << __TIME__ << std::endl;
	Window Win(800, 600);
	Win.WinInit();
	InitGLEW();
	//glEnable(GL_CULL_FACE);
	//GroupOfObjects.push_back(std::make_unique<Object>("gamedata/objects/art.txt", "gamedata/textures/PIG.jpg"));
	//GroupOfObjects.push_back(std::make_unique<Object>("gamedata/objects/TriangledTorus.txt", "gamedata/textures/PIG.jpg"));
	//GroupOfObjects.push_back(std::make_unique<Object>("gamedata/objects/neptune.txt", "gamedata/textures/PIG.jpg"));
	GroupOfObjects.push_back(std::make_unique<Object>("gamedata/objects/vtn.txt", "gamedata/textures/PIG.jpg"));
	GroupOfObjects.push_back(std::make_unique<Object>("gamedata/objects/airplane.txt", "gamedata/textures/newlist.bmp"));

	//(*GroupOfObjects[0]).Rotate = (*GroupOfObjects[0]).Rotate * FromQuatToMat(Quaternion(RotateYawPitchRoll(Vector3(0, 50, 0))));
	(*GroupOfObjects[1]).Rotate = (*GroupOfObjects[1]).Rotate * FromQuatToMat(Quaternion(RotateYawPitchRoll(Vector3(0, 0, 50))));
	(*GroupOfObjects[1]).Trans(3, 0) += 2;
	
	

	for (std::unique_ptr<Object> &obj : GroupOfObjects)
	{
		(*obj).ReadObject();
		(*obj).CreateTexture();
		(*obj).CreateBuffers();
		(*obj).ModelCreate();
		(*obj).objAABB.Recompute((*obj).Model, (*obj).Vertexes);
		(*obj).objOBB.Recompute((*obj).Model);
	}
	
	Camera cam(Vector3(0.0, 0.0, 2.0 ));

	FrameBuffer PickFBO;
	unsigned int rbo;

	//FrameBuffer PickFBO;
	PickFBO.Bind();

	//unsigned int Ftexture;

	/*glGenTextures(1, &Ftexture);
	glBindTexture(GL_TEXTURE_2D, Ftexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 800, 600, 0, GL_RGB, GL_UNSIGNED_BYTE, 0);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, Ftexture, 0);
	glBindTexture(GL_TEXTURE_2D, 0);*/

	Texture PickTexture(800, 600, GL_RGB);
	PickTexture.Bind();
		PickTexture.Create(0);
		PickTexture.SetParameter(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		PickTexture.SetParameter(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, PickTexture.GetTextureUnit(), 0);
	PickTexture.UnBind();
	
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, 800, 600);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) == GL_FRAMEBUFFER_COMPLETE)
	{
		std::cout << "Framebuffer has been created!" << std::endl;
	}

	PickFBO.UnBind();

	Matrix4x4 ModelArrow;

	std::vector<Vector3> ArrowVec{
		Vector3(0, 0, 0),
		Vector3(10, 0, 0),
		Vector3(0, 0, 0),
		Vector3(0, 10, 0),
		Vector3(0, 0, 0),
		Vector3(0, 0, 10) };

	std::vector<Vector3> ArrowCol{
		Vector3(0, 1.0, 0),
		Vector3(0, 1.0, 0),
		Vector3(1.0, 0, 0),
		Vector3(1.0, 0, 0),
		Vector3(0, 0, 1.0),
		Vector3(0, 0, 1.0)
	};


	VAO ArrowVAO;
	BufferObject ArrowVBO(GL_ARRAY_BUFFER);
	BufferObject ArrowColVBO(GL_ARRAY_BUFFER);
	ArrowVAO.Bind();
	ArrowVBO.Bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * ArrowVec.size(), &ArrowVec.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), nullptr);
	glEnableVertexAttribArray(0);
	ArrowVBO.UnBind();
	ArrowColVBO.Bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * ArrowCol.size(), &ArrowCol.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), nullptr);
	glEnableVertexAttribArray(2);
	ArrowColVBO.UnBind();
	ArrowVAO.UnBind();
	

	Matrix4x4 BBmodel;

	unsigned int BBIndexes[36]{0, 3, 5,   0, 5, 6,   0, 2, 3,   0, 1, 2,   1, 7, 2,   2, 4, 7,   7, 5, 6,   4, 5, 7,  0, 6, 7,   7, 1, 0,   4, 2, 3,   3, 5, 4};

	VAO BBvao;
	BufferObject BBvbo(GL_ARRAY_BUFFER);
	BufferObject BBebo(GL_ELEMENT_ARRAY_BUFFER);
	BBvao.Bind();

	BBvbo.Bind();
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * 8, 0, GL_STREAM_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3), nullptr);
	glEnableVertexAttribArray(0);
	BBvbo.UnBind();

	BBebo.Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 36, BBIndexes, GL_STATIC_DRAW);
	BBebo.UnBind();

	BBvao.UnBind();
	/*BufferObject Fvbo(GL_ARRAY_BUFFER);
	Fvao.Bind();
	Fvbo.Bind();
	float Fdata[]
	{
		-1.0f, 1.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f,
			1.0f, -1.0f, 1.0f, 0.0f,

			-1.0f, 1.0f, 0.0f, 1.0f,
			1.0f, -1.0f, 1.0f, 0.0f,
			1.0f, 1.0f, 1.0f, 1.0f
	};
	glBufferData(GL_ARRAY_BUFFER, sizeof(Fdata), &Fdata, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
	Fvbo.UnBind();
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	
	Fvao.UnBind();*/




	ObjectShader.CreateVertexShader();
	ObjectShader.CreateFragmentShader();
	ObjectShader.CreateShaderProgram();

	PickShader.CreateVertexShader();
	PickShader.CreateFragmentShader();
	PickShader.CreateShaderProgram();

	ArrowShader.CreateVertexShader();
	ArrowShader.CreateFragmentShader();
	ArrowShader.CreateShaderProgram();

	BBShader.CreateVertexShader();
	BBShader.CreateFragmentShader();
	BBShader.CreateShaderProgram();

	//glEnable(GL_DEPTH_TEST);
	//glClearColor(0.0, 0.0, 0.5, 1.0);
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glDepthFunc(GL_ALWAYS);
	//glLoadIdentity();
	//glBegin(GL_TRIANGLES);
	//glColor3f(1, 0, 0);
	//glVertex3f(1, 0.5, 0);
	//glVertex3f(-1, 0.5, 0);
	//glVertex3f(0, 0.49, 1);
	//glEnd();
	//glFlush();
	////Win.SwapBuffers();
	///*glLoadIdentity();
	//glBegin(GL_TRIANGLES);
	//glColor3f(0, 1, 0);
	//glVertex3f(-1, -1, 0);
	//glVertex3f(-1, 0.5, 0);
	//glVertex3f(1, 0.5, 0);
	//glEnd();
	//glFlush();*/
	//Win.SwapBuffers();
	//float d;
	//glReadPixels(400, 449, 1, 1, GL_DEPTH_COMPONENT, GL_FLOAT, &d);
	//std::cout << d << std::endl;
	//system("pause");

	//glEnable(GL_CULL_FACE);

	GLint mem = 0;
	glGetIntegerv(GL_GPU_MEMORY_INFO_CURRENT_AVAILABLE_VIDMEM_NVX, &mem);
	std::cout << mem / 1024 << std::endl;

	while (!Win.isClose)
	{
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		//glCullFace(GL_BACK);
		/*MainTimer.TimerStart();

		Win.Clear();
		PollEvents(Win, cam);
		cam.Move();
		ObjectShader.UseShader();
		ObjectShader.SetMat4("view", &Camera::View(0, 0));
		ObjectShader.SetMat4("projection", &Projection(0, 0));
		for (std::unique_ptr<Object> &obj : GroupOfObjects)
		{
			ObjectShader.SetMat4("model", &(*obj).Model(0, 0));
			(*obj).Draw();
		}
		Win.SwapBuffers();
		MainTimer.TimerEnd();*/
		MainTimer.TimerStart();
		PickFBO.Draw();
		glEnable(GL_DEPTH_TEST);
		glClearColor(1.0, 1.0, 1.0, 1.0);
		Win.Clear();
		PickShader.UseShader();
		PickShader.SetMat4("view", &cam.View(0, 0));
		PickShader.SetMat4("projection", &Projection(0, 0));
		for (std::unique_ptr<Object> &obj : GroupOfObjects)
		{
			PickShader.SetMat4("model", &(*obj).Model(0, 0));
			PickShader.SetVec3("RGBid", (*obj).RGBid);
			(*obj).Draw();
		}
		glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		glClearColor(0.0, 0.0, 0.5, 1.0);
		Win.Clear();
		ObjectShader.UseShader();
		ObjectShader.SetMat4("view", &cam.View(0, 0));
		ObjectShader.SetMat4("projection", &Projection(0, 0));
		for (std::unique_ptr<Object> &obj : GroupOfObjects)
		{
			ObjectShader.SetMat4("model", &(*obj).Model(0, 0));
			ObjectShader.SetBool("isPicked", (*obj).isPicked);
			(*obj).Draw();
			if ((*obj).isPicked == true)
			{
				glDisable(GL_DEPTH_TEST);
				ModelArrow = (*obj).Model;
				ArrowShader.UseShader();
				ArrowShader.SetMat4("view", &cam.View(0, 0));
				ArrowShader.SetMat4("projection", &Projection(0, 0));
				ArrowShader.SetMat4("model", &ModelArrow(0, 0));
				ArrowVAO.Bind();

				glDrawArrays(GL_LINES, 0, ArrowVec.size());

				ArrowVAO.UnBind();

				glEnable(GL_DEPTH_TEST);

				BBShader.UseShader();
				BBShader.SetMat4("view", &cam.View(0, 0));
				BBShader.SetMat4("projection", &Projection(0, 0));
				ArrowShader.SetMat4("model", &BBmodel(0, 0));
				BBvao.Bind();
				BBvbo.Bind();
				/*std::vector<Vector3> BBvec{ (*obj).min, Vector3((*obj).min.x, (*obj).min.y, (*obj).max.z), Vector3((*obj).min.x, (*obj).max.y, (*obj).max.z),
					Vector3((*obj).min.x, (*obj).max.y, (*obj).max.z), Vector3((*obj).min.x, (*obj).max.y, (*obj).min.z), (*obj).min,
					Vector3((*obj).min.x, (*obj).max.y, (*obj).min.z), Vector3((*obj).min.x, (*obj).max.y, (*obj).max.z),Vector3((*obj).max.x, (*obj).max.y, (*obj).min.z),
					Vector3((*obj).max.x, (*obj).max.y, (*obj).min.z), Vector3((*obj).min.x, (*obj).max.y, (*obj).max.z), (*obj).max,
					(*obj).max, Vector3((*obj).max.x, (*obj).min.y, (*obj).max.z), Vector3((*obj).min.x, (*obj).min.y, (*obj).max.z),
					Vector3((*obj).min.x, (*obj).min.y, (*obj).max.z), Vector3((*obj).min.x, (*obj).max.y, (*obj).max.z), (*obj).max,
				
				
					(*obj).max, Vector3((*obj).max.x, (*obj).max.y, (*obj).min.z), Vector3((*obj).max.x, (*obj).min.y, (*obj).min.z),
					Vector3((*obj).max.x, (*obj).min.y, (*obj).min.z), Vector3((*obj).max.x, (*obj).min.y, (*obj).max.z), (*obj).max,
					Vector3((*obj).max.x, (*obj).min.y, (*obj).max.z), Vector3((*obj).max.x, (*obj).min.y, (*obj).min.z), Vector3((*obj).min.x, (*obj).min.y, (*obj).max.z),
					Vector3((*obj).min.x, (*obj).min.y, (*obj).max.z), Vector3((*obj).max.x, (*obj).min.y, (*obj).min.z), (*obj).min,
					(*obj).min, Vector3((*obj).min.x, (*obj).max.y, (*obj).min.z), Vector3((*obj).max.x, (*obj).max.y, (*obj).min.z),
					Vector3((*obj).max.x, (*obj).max.y, (*obj).min.z), Vector3((*obj).max.x, (*obj).min.y, (*obj).min.z), (*obj).min };*/

				/*std::vector<Vector3> BBvec{ (*obj).objAABB.min,
					Vector3((*obj).objAABB.max.x, (*obj).objAABB.min.y, (*obj).objAABB.min.z),
					Vector3((*obj).objAABB.max.x, (*obj).objAABB.max.y, (*obj).objAABB.min.z),
					Vector3((*obj).objAABB.min.x, (*obj).objAABB.max.y, (*obj).objAABB.min.z),
				
					(*obj).objAABB.max,
					Vector3((*obj).objAABB.min.x, (*obj).objAABB.max.y, (*obj).objAABB.max.z),
					Vector3((*obj).objAABB.min.x, (*obj).objAABB.min.y, (*obj).objAABB.max.z),
					Vector3((*obj).objAABB.max.x, (*obj).objAABB.min.y, (*obj).objAABB.max.z) };*/

				BBmodel = (*obj).Model;

				/*std::vector<Vector3> BBvec{ (*obj).objOBB.RecVertexes[0],
					Vector3((*obj).objOBB.RecVertexes[4].x, (*obj).objOBB.RecVertexes[0].y, (*obj).objOBB.RecVertexes[0].z),
					Vector3((*obj).objOBB.RecVertexes[4].x, (*obj).objOBB.RecVertexes[4].y, (*obj).objOBB.RecVertexes[0].z),
					Vector3((*obj).objOBB.RecVertexes[0].x, (*obj).objOBB.RecVertexes[4].y, (*obj).objOBB.RecVertexes[0].z),

					(*obj).objOBB.RecVertexes[4],
					Vector3((*obj).objOBB.RecVertexes[0].x, (*obj).objOBB.RecVertexes[4].y, (*obj).objOBB.RecVertexes[4].z),
					Vector3((*obj).objOBB.RecVertexes[0].x, (*obj).objOBB.RecVertexes[0].y, (*obj).objOBB.RecVertexes[4].z),
					Vector3((*obj).objOBB.RecVertexes[4].x, (*obj).objOBB.RecVertexes[0].y, (*obj).objOBB.RecVertexes[4].z) };*/

				std::vector<Vector3> BBvec{ (*obj).objOBB.Vertexes[0],
					Vector3((*obj).objOBB.Vertexes[4].x, (*obj).objOBB.Vertexes[0].y, (*obj).objOBB.Vertexes[0].z),
					Vector3((*obj).objOBB.Vertexes[4].x, (*obj).objOBB.Vertexes[4].y, (*obj).objOBB.Vertexes[0].z),
					Vector3((*obj).objOBB.Vertexes[0].x, (*obj).objOBB.Vertexes[4].y, (*obj).objOBB.Vertexes[0].z),

					(*obj).objOBB.Vertexes[4],
					Vector3((*obj).objOBB.Vertexes[0].x, (*obj).objOBB.Vertexes[4].y, (*obj).objOBB.Vertexes[4].z),
					Vector3((*obj).objOBB.Vertexes[0].x, (*obj).objOBB.Vertexes[0].y, (*obj).objOBB.Vertexes[4].z),
					Vector3((*obj).objOBB.Vertexes[4].x, (*obj).objOBB.Vertexes[0].y, (*obj).objOBB.Vertexes[4].z) };

				glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Vector3) * BBvec.size(), &BBvec.front());
				BBvbo.UnBind();
				glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
				//glDrawArrays(GL_TRIANGLES, 0, 36);
				glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_INT, BBIndexes);
				
				glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
				BBvao.UnBind();

				ObjectShader.UseShader();
			}
		}
		PickFBO.Read();
		PollEvents(Win, cam);
		if (SATtest((*GroupOfObjects[0]).objOBB, (*GroupOfObjects[1]).objOBB)) std::cout << "Objects separate!"<< std::endl;
		PickFBO.UnBind();
		cam.Move();

		/*glDisable(GL_DEPTH_TEST);
		glClearColor(1.0, 1.0, 1.0, 1.0);
		glClear(GL_COLOR_BUFFER_BIT);


		ScreenShader.UseShader();
		Fvao.Bind();
			glBindTexture(GL_TEXTURE_2D, Ftexture);
			glDrawArrays(GL_TRIANGLES, 0, 6);
		Fvao.UnBind();*/

		Win.SwapBuffers();
		MainTimer.TimerEnd();
	}
	//https://stackoverflow.com/questions/10123601/opengl-read-pixels-from-framebuffer-for-picking-rounded-up-to-255-0xff
	//https://triplepointfive.github.io/ogltutor/tutorials/tutorial29.html
	

	return 0;
}