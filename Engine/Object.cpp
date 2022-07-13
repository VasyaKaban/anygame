#include "Object.h"
#include "SDL_image.h"

unsigned int Object::PickID = 0x0;

Object::Object(std::string path, std::string Tpath)
{
	this->path = path;
	this->Tpath = Tpath;
	vbo.SetType(GL_ARRAY_BUFFER);
	tbo.SetType(GL_ARRAY_BUFFER);
	nbo.SetType(GL_ARRAY_BUFFER);
	PickID++;
	RGBid.x = ((PickID >> 16) & 0xFF) / 255.0f;//r
	RGBid.x = round(RGBid.x * 10000) / 10000;
	RGBid.y = ((PickID >> 8) & 0xFF) / 255.0f;//g
	RGBid.y = round(RGBid.y * 10000) / 10000;
	RGBid.z = ((PickID) & 0xFF) / 255.0f;//b
	RGBid.z = round(RGBid.z * 10000) / 10000;
	isPicked = false;
}

Object::~Object()
{
}

void Object::ReadObject()
{
	std::ifstream ifs;
	ifs.open(path);
	if (!ifs.is_open())
	{
		std::cout <<path<<" has not exist" << std::endl;
	}
	else
	{
		while (!ifs.eof())
		{
			std::string line;
			line = "";
			ifs >> line;
			if (line == "vtn")
			{
				Vector3 v;
				Vector3 n;
				Vec2 t;
				ifs >> v.x >> v.y >> v.z >> t.u >> t.v >> n.x >> n.y >> n.z;
				Vertexes.push_back(v);
				Textures.push_back(t);
				Normals.push_back(n);
			}
		}
	}
	ifs.close();

	objAABB.min = objAABB.max = Vertexes[0];

	for (size_t i = 0; i < Vertexes.size(); i++)
	{
		if (objAABB.min.x > Vertexes[i].x) objAABB.min.x = Vertexes[i].x;
		if (objAABB.min.y > Vertexes[i].y) objAABB.min.y = Vertexes[i].y;
		if (objAABB.min.z > Vertexes[i].z) objAABB.min.z = Vertexes[i].z;

		if (objAABB.max.x < Vertexes[i].x) objAABB.max.x = Vertexes[i].x;
		if (objAABB.max.y < Vertexes[i].y) objAABB.max.y = Vertexes[i].y;
		if (objAABB.max.z < Vertexes[i].z) objAABB.max.z = Vertexes[i].z;
	}

	objOBB.Compute(objAABB.min, objAABB.max);
}

void Object::CreateTexture()
{
	ObjectTexture.Bind();
		ObjectTexture.SetParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		ObjectTexture.SetParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		ObjectTexture.SetParameter(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		ObjectTexture.SetParameter(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		ObjectTexture.LoadImage(Tpath.c_str());
		ObjectTexture.SetFormat(GL_RGBA);
		ObjectTexture.CreateFromImage();
		ObjectTexture.GenMipMap();
	ObjectTexture.UnBind();
	/*glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);

	SDL_Surface* Tp = IMG_Load(Tpath.c_str());
	SDL_Surface* Tn = SDL_ConvertSurfaceFormat(Tp, SDL_PIXELFORMAT_RGBA32, NULL);

	if (Tn)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Tn->w, Tn->h, 0, GL_RGBA, GL_UNSIGNED_BYTE, Tn->pixels);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Error! " << Tpath << " has not exist!" << std::endl;
	}
	glBindTexture(GL_TEXTURE_2D, 0);*/
}

void Object::CreateBuffers()
{
	vao.Bind();
		vbo.Bind();
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * Vertexes.size(), &Vertexes.front(), GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);	//vertex

		
		vbo.UnBind();

		tbo.Bind();
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2) * Textures.size(), &Textures.front(), GL_STATIC_DRAW);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);	//textures
		tbo.UnBind();

		nbo.Bind();
		glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3) * Normals.size(), &Normals.front(), GL_STATIC_DRAW);
		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);	//textures
		nbo.UnBind();

		//glBindBuffer(GL_ARRAY_BUFFER, tbo);
		//glBufferData(GL_ARRAY_BUFFER, sizeof(Vec2) * Textures.size(), &Textures.front(), GL_STATIC_DRAW);
		//glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), nullptr);	//textures
		//glBindBuffer(GL_ARRAY_BUFFER, 0);

		//glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (GLvoid*)(5 * sizeof(float)));	//normals
	
		//glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);
	vao.UnBind();
}

void Object::Draw()
{


	glBindTexture(GL_TEXTURE_2D, ObjectTexture.GetTextureUnit());
	vao.Bind();

	glDrawArrays(GL_TRIANGLES, 0, Vertexes.size());
	
	vao.UnBind();
}

std::string Object::GetName()
{
	return path;
}

void Object::ModelCreate()
{
	Model = Rotate * Trans;
}
