#include "ObjectParser.h"
#include <string>
#include <fstream>
#include <iostream>

void ObjectParserCenter(std::string path)
{
	std::string inpath = "input/";
	txtpath = path;
	CompletedPath = path;
	path = inpath + path;
	fs.open(path);
	if (!fs.is_open())
	{
		std::cout << path << " has not exsist!" << std::endl;
	}
	else
	{
		while (!fs.eof())
		{
			fs >> Type;
			if (Type == "v")
			{
				ObjectVertexParser();
			}
			if (Type == "vt")
			{
				ObjectVertexTextureParser();
			}
			if (Type == "vn")
			{
				ObjectVertexNormalsParser();
			}
			if (Type == "f")
			{
				ObjectSurfacesParser();
			}
		}
		fs.close();

		VertexAndNormalsCoord VertexHelp;
		for (int i = 0; i < VertexIndexes.size(); i++)
		{
			VertexHelp.x = vc[VertexIndexes[i]].x;
			VertexHelp.y = vc[VertexIndexes[i]].y;
			VertexHelp.z = vc[VertexIndexes[i]].z;
			VertexCompleted.push_back(VertexHelp);
		}

		TextureCoord TextureHelp;
		for (int i = 0; i < TextureIndexes.size(); i++)
		{
			TextureHelp.x = vt[TextureIndexes[i]].x;
			TextureHelp.y = vt[TextureIndexes[i]].y;
			TextureCompleted.push_back(TextureHelp);
		}

		VertexAndNormalsCoord NormalsHelp;
		for (int i = 0; i < NormalsIndexes.size(); i++)
		{
			NormalsHelp.x = vn[NormalsIndexes[i]].x;
			NormalsHelp.y = vn[NormalsIndexes[i]].y;
			NormalsHelp.z = vn[NormalsIndexes[i]].z;
			NormalsCompleted.push_back(NormalsHelp);
		}

		CompletedCoord vtnhelp;
		for (int i = 0; i < VertexIndexes.size(); i++)
		{
			vtnhelp.vx = VertexCompleted[i].x;
			vtnhelp.vy = VertexCompleted[i].y;
			vtnhelp.vz = VertexCompleted[i].z;

			vtnhelp.tx = TextureCompleted[i].x;
			vtnhelp.ty = TextureCompleted[i].y;

			vtnhelp.nx = NormalsCompleted[i].x;
			vtnhelp.ny = NormalsCompleted[i].y;
			vtnhelp.nz = NormalsCompleted[i].z;

			Completed.push_back(vtnhelp);
		}
		vc.clear();
		vt.clear();
		vn.clear();
		VertexCompleted.clear();
		TextureCompleted.clear();
		NormalsCompleted.clear();
		VertexIndexes.clear();
		TextureIndexes.clear();
		NormalsIndexes.clear();
		/*VertexHelp.x = VertexHelp.y = VertexHelp.z = 0;
		TextureHelp.x = TextureHelp.y = 0;
		NormalsHelp.x = NormalsHelp.y = NormalsHelp.z = 0;
		vtnhelp.vx = vtnhelp.vy = vtnhelp.vz = vtnhelp.tx = vtnhelp.ty = vtnhelp.nx = vtnhelp.ny = vtnhelp.nz = 0;*/
		CreateTXT();
	}

}

void ObjectVertexParser()
{
	VertexAndNormalsCoord vcc;
	fs >> vcc.x >> vcc.y >> vcc.z;
	vc.push_back(vcc);
}

void ObjectVertexTextureParser()
{
	TextureCoord vtt;
	fs >> vtt.x >> vtt.y;
	vt.push_back(vtt);
}

void ObjectVertexNormalsParser()
{
	VertexAndNormalsCoord vnn;
	fs >> vnn.x >> vnn.y >> vnn.z;
	vn.push_back(vnn);
}

void ObjectSurfacesParser()
{
	std::string VertexSur;
	std::string TexturesSur;
	std::string NormalsSur;
	for (int i = 0; i < 3; i++)
	{
		fs >> Type;
		VertexSur = TexturesSur = NormalsSur = Type;

		for (int v = 0; v < VertexSur.size(); v++)
		{
			if (VertexSur[v] == '/')
			{
				VertexSur.erase(v, VertexSur.size() - v);
				break;
			}
		}
		VertexIndexes.push_back(stof(VertexSur) - 1);

		for (int tex = 0; tex < TexturesSur.size(); tex++)
		{
			if (TexturesSur[tex] == '/')
			{
				TexturesSur.erase(0, tex + 1);
				for (int k = 0; k < TexturesSur.size(); k++)
				{
					if (TexturesSur[k] == '/')
					{
						TexturesSur.erase(k, TexturesSur.size() - k);
						break;
					}
				}
				break;
			}
		}
		TextureIndexes.push_back(stof(TexturesSur) - 1);

		for (int n = NormalsSur.size() - 1; n < NormalsSur.size(); n--)
		{
			if (NormalsSur[n] == '/')
			{
				NormalsSur.erase(0, n + 1);
				break;
			}
		}
		NormalsIndexes.push_back(stof(NormalsSur) - 1);
	}
	//VertexSur = TexturesSur = NormalsSur = "";
}

void CreateTXT()
{
	for (int i = txtpath.size() - 1; i < txtpath.size(); i--)
	{
		if (txtpath[i] == 'j' || txtpath[i - 1] == 'b' || txtpath[i - 2] == 'o' || txtpath[i - 3] == '.')
		{
			txtpath.erase(i - 2, 3);
		}
	}
	std::string otxt = "txt";
	std::string outpath = "output/";
	txtpath =  outpath + txtpath + otxt;
	of.open(txtpath);
	for (int i = 0; i < Completed.size(); i++)
	{
		of <<"vtn "<<Completed[i].vx<< " "<< Completed[i].vy<<" "<< Completed[i].vz<<" "<< Completed[i].tx<<" "<<Completed[i].ty<<" "<<
			Completed[i].nx<<" "<< Completed[i].ny<<" "<<Completed[i].nz<< std::endl;
	}
	of.close();
	Completed.clear();
	std::cout << CompletedPath<<" Completed!"<< std::endl;
}