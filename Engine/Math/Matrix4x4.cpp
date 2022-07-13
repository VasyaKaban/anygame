#include "Matrix4x4.h"

Matrix4x4::Matrix4x4()
{
	Identity();
}

Matrix4x4::Matrix4x4(float m0, float m1, float m2, float m3,
	float m4, float m5, float m6, float m7,
	float m8, float m9, float m10, float m11,
	float m12, float m13, float m14, float m15)
{
	m[0][0] = m0;
	m[0][1] = m1;
	m[0][2] = m2;
	m[0][3] = m3;

	m[1][0] = m4;
	m[1][1] = m5;
	m[1][2] = m6;
	m[1][3] = m7;

	m[2][0] = m8;
	m[2][1] = m9;
	m[2][2] = m10;
	m[2][3] = m11;

	m[3][0] = m12;
	m[3][1] = m13;
	m[3][2] = m14;
	m[3][3] = m15;
};

Matrix4x4::Matrix4x4(float data[4][4])
{
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			this->m[i][k] = data[i][k];
		}
	}
}

Matrix4x4::~Matrix4x4()
{
}

Matrix4x4 Matrix4x4::operator+(const Matrix4x4& other)
{
	return Matrix4x4(this->m[0][0] + other.m[0][0], this->m[0][1] + other.m[0][1], this->m[0][2] + other.m[0][2], this->m[0][3] + other.m[0][3],
		this->m[1][0] + other.m[1][0], this->m[1][1] + other.m[1][1], this->m[1][2] + other.m[1][2], this->m[1][3] + other.m[1][3], 
		this->m[2][0] + other.m[2][0], this->m[2][1] + other.m[2][1], this->m[2][2] + other.m[2][2], this->m[2][3] + other.m[2][3], 
		this->m[3][0] + other.m[3][0], this->m[3][1] + other.m[3][1], this->m[3][2] + other.m[3][2], this->m[3][3] + other.m[3][3]);
}

Matrix4x4 Matrix4x4::operator-(const Matrix4x4& other)
{
	return Matrix4x4(this->m[0][0] - other.m[0][0], this->m[0][1] - other.m[0][1], this->m[0][2] - other.m[0][2], this->m[0][3] - other.m[0][3],
		this->m[1][0] - other.m[1][0], this->m[1][1] - other.m[1][1], this->m[1][2] - other.m[1][2], this->m[1][3] - other.m[1][3],
		this->m[2][0] - other.m[2][0], this->m[2][1] - other.m[2][1], this->m[2][2] - other.m[2][2], this->m[2][3] - other.m[2][3],
		this->m[3][0] - other.m[3][0], this->m[3][1] - other.m[3][1], this->m[3][2] - other.m[3][2], this->m[3][3] - other.m[3][3]);
}

Matrix4x4 Matrix4x4::operator*(const Matrix4x4& other)
{
	Matrix4x4 HelpMat = *this;

	HelpMat.m[0][0] = m[0][0] * other.m[0][0] + m[0][1] * other.m[1][0] + m[0][2] * other.m[2][0] + m[0][3] * other.m[3][0];
	HelpMat.m[0][1] = m[0][0] * other.m[0][1] + m[0][1] * other.m[1][1] + m[0][2] * other.m[2][1] + m[0][3] * other.m[3][1];
	HelpMat.m[0][2] = m[0][0] * other.m[0][2] + m[0][1] * other.m[1][2] + m[0][2] * other.m[2][2] + m[0][3] * other.m[3][2];
	HelpMat.m[0][3] = m[0][0] * other.m[0][3] + m[0][1] * other.m[1][3] + m[0][2] * other.m[2][3] + m[0][3] * other.m[3][3];

	HelpMat.m[1][0] = m[1][0] * other.m[0][0] + m[1][1] * other.m[1][0] + m[1][2] * other.m[2][0] + m[1][3] * other.m[3][0];
	HelpMat.m[1][1] = m[1][0] * other.m[0][1] + m[1][1] * other.m[1][1] + m[1][2] * other.m[2][1] + m[1][3] * other.m[3][1];
	HelpMat.m[1][2] = m[1][0] * other.m[0][2] + m[1][1] * other.m[1][2] + m[1][2] * other.m[2][2] + m[1][3] * other.m[3][2];
	HelpMat.m[1][3] = m[1][0] * other.m[0][3] + m[1][1] * other.m[1][3] + m[1][2] * other.m[2][3] + m[1][3] * other.m[3][3];

	HelpMat.m[2][0] = m[2][0] * other.m[0][0] + m[2][1] * other.m[1][0] + m[2][2] * other.m[2][0] + m[2][3] * other.m[3][0];
	HelpMat.m[2][1] = m[2][0] * other.m[0][1] + m[2][1] * other.m[1][1] + m[2][2] * other.m[2][1] + m[2][3] * other.m[3][1];
	HelpMat.m[2][2] = m[2][0] * other.m[0][2] + m[2][1] * other.m[1][2] + m[2][2] * other.m[2][2] + m[2][3] * other.m[3][2];
	HelpMat.m[2][3] = m[2][0] * other.m[0][3] + m[2][1] * other.m[1][3] + m[2][2] * other.m[2][3] + m[2][3] * other.m[3][3];

	HelpMat.m[3][0] = m[3][0] * other.m[0][0] + m[3][1] * other.m[1][0] + m[3][2] * other.m[2][0] + m[3][3] * other.m[3][0];
	HelpMat.m[3][1] = m[3][0] * other.m[0][1] + m[3][1] * other.m[1][1] + m[3][2] * other.m[2][1] + m[3][3] * other.m[3][1];
	HelpMat.m[3][2] = m[3][0] * other.m[0][2] + m[3][1] * other.m[1][2] + m[3][2] * other.m[2][2] + m[3][3] * other.m[3][2];
	HelpMat.m[3][3] = m[4][0] * other.m[0][3] + m[3][1] * other.m[1][3] + m[3][2] * other.m[2][3] + m[3][3] * other.m[3][3];

	return HelpMat;
}

Matrix4x4& Matrix4x4::operator=(const Matrix4x4& other)
{
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			m[i][k] = other.m[i][k];
		}
	}

	return *this;
}

Matrix4x4 Matrix4x4::operator+(const float value)
{
	return Matrix4x4(this->m[0][0] + value, this->m[0][1] + value, this->m[0][2] + value, this->m[0][3] + value,
		this->m[1][0] + value, this->m[1][1] + value, this->m[1][2] + value, this->m[1][3] + value,
		this->m[2][0] + value, this->m[2][1] + value, this->m[2][2] + value, this->m[2][3] + value,
		this->m[3][0] + value, this->m[3][1] + value, this->m[3][2] + value, this->m[3][3] + value);
}

Matrix4x4 Matrix4x4::operator-(const float value)
{
	return Matrix4x4(this->m[0][0] - value, this->m[0][1] - value, this->m[0][2] - value, this->m[0][3] - value,
		this->m[1][0] - value, this->m[1][1] - value, this->m[1][2] - value, this->m[1][3] - value,
		this->m[2][0] - value, this->m[2][1] - value, this->m[2][2] - value, this->m[2][3] - value,
		this->m[3][0] - value, this->m[3][1] - value, this->m[3][2] - value, this->m[3][3] - value);
}

Matrix4x4 Matrix4x4::operator*(const float value)
{
	return Matrix4x4(this->m[0][0] * value, this->m[0][1] * value, this->m[0][2] * value, this->m[0][3] * value,
		this->m[1][0] * value, this->m[1][1] * value, this->m[1][2] * value, this->m[1][3] * value,
		this->m[2][0] * value, this->m[2][1] * value, this->m[2][2] * value, this->m[2][3] * value,
		this->m[3][0] * value, this->m[3][1] * value, this->m[3][2] * value, this->m[3][3] * value);
}

float& Matrix4x4::operator()(int ind1, int ind2)
{
	return m[ind1][ind2];
}

void Matrix4x4::Identity()
{
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			if (k == i)
			{
				m[i][k] = 1;
			}
			else
			{
				m[i][k] = 0;
			}
		}
	}
}

void Matrix4x4::PrintMat()
{
	for (int i = 0; i < 4; i++)
	{
		for (int k = 0; k < 4; k++)
		{
			std::cout << m[i][k] << " ";
		}
		std::cout << "\n";
	}
}

void Matrix4x4::Invert()
{
	Matrix4x4 hm = *this;

	this->m[0][1] = hm.m[1][0];
	this->m[0][2] = hm.m[2][0];
	this->m[0][3] = hm.m[3][0];
	this->m[1][0] = hm.m[0][1];
	this->m[1][2] = hm.m[2][1];
	this->m[1][3] = hm.m[3][1];
	this->m[2][0] = hm.m[0][2];
	this->m[2][1] = hm.m[1][2];
	this->m[2][3] = hm.m[3][2];
	this->m[3][0] = hm.m[0][3];
	this->m[3][1] = hm.m[1][3];
	this->m[3][2] = hm.m[2][3];
}


