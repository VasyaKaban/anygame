#include "EditorStuff.h"

Matrix4x4 CSModel;

MeshCoord::MeshCoord(float x, float y, float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void CreateCS()
{
	CSa = { MeshCoord(0.0, 0.0, 0.0), MeshCoord(1.0, 0.0, 0.0),
		MeshCoord(0.0, 2.0, 0.0), MeshCoord(1.0, 0.0, 0.0),
		MeshCoord(0.0, 0.0, 0.0), MeshCoord(0.0, 1.0, 0.0),
		MeshCoord(2.0, 0.0, 0.0), MeshCoord(0.0, 1.0, 0.0),
		MeshCoord(0.0, 0.0, 0.0), MeshCoord(0.0, 0.0, 1.0),
		MeshCoord(0.0, 0.0, 2.0), MeshCoord(0.0, 0.0, 1.0) };


	glGenVertexArrays(1, &CSvao);
	glGenBuffers(1, &CSvbo);
	glBindVertexArray(CSvao);
	glBindBuffer(GL_ARRAY_BUFFER, CSvbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(MeshCoord) * CSa.size(), &CSa.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), nullptr);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void DrawCS()
{
	glBindVertexArray(CSvao);
	glDrawArrays(GL_LINES, 0, CSa.size());
	glBindVertexArray(0);

}