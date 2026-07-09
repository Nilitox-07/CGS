#include "Matrix4.h"
#include "NxMath.h"

Matrix4::Matrix4()
{
	
}

Matrix4::Matrix4(const Matrix4& other)
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			m[row][col] = other[row][col];
		}
	}
}

Matrix4::Matrix4(const float(&values)[16])
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			m[row][col] = values[row * 4 + col];
		}
	}
}

Matrix4::Matrix4(float m00, float m01, float m02, float m03, float m10, float m11, float m12, float m13, float m20, float m21, float m22, float m23, float m30, float m31, float m32, float m33)
{
	m[0][0] = m00;
	m[0][1] = m01;
	m[0][2] = m02;
	m[0][3] = m03;

	m[1][0] = m10;
	m[1][1] = m11;
	m[1][2] = m12;
	m[1][3] = m13;

	m[2][0] = m20;
	m[2][1] = m21;
	m[2][2] = m22;
	m[2][3] = m23;

	m[3][0] = m30;
	m[3][1] = m31;
	m[3][2] = m32;
	m[3][3] = m33;
}

Matrix4& Matrix4::operator=(const Matrix4 & other)
{
	if (this != &other)
	{
		for (int row = 0; row < 4; row++)
		{
			for (int col = 0; col < 4; col++)
			{
				m[row][col] = other.m[row][col];
			}
		}
	}
	return *this;
}

Matrix4 Matrix4::operator+(const Matrix4& other) const
{
	Matrix4 toReturn;

	toReturn.m[0][0] = m[0][0] + other.m[0][0];
	toReturn.m[0][1] = m[0][1] + other.m[0][1];
	toReturn.m[0][2] = m[0][2] + other.m[0][2];
	toReturn.m[0][3] = m[0][3] + other.m[0][3];
	toReturn.m[1][0] = m[1][0] + other.m[1][0];
	toReturn.m[1][1] = m[1][1] + other.m[1][1];
	toReturn.m[1][2] = m[1][2] + other.m[1][2];
	toReturn.m[1][3] = m[1][3] + other.m[1][3];
	toReturn.m[2][0] = m[2][0] + other.m[2][0];
	toReturn.m[2][1] = m[2][1] + other.m[2][1];
	toReturn.m[2][2] = m[2][2] + other.m[2][2];
	toReturn.m[2][3] = m[2][3] + other.m[2][3];
	toReturn.m[3][0] = m[3][0] + other.m[3][0];
	toReturn.m[3][1] = m[3][1] + other.m[3][1];
	toReturn.m[3][2] = m[3][2] + other.m[3][2];
	toReturn.m[3][3] = m[3][3] + other.m[3][3];

	return toReturn;
}

Matrix4& Matrix4::operator+=(const Matrix4& other)
{
	m[0][0] += other.m[0][0];
	m[0][1] += other.m[0][1];
	m[0][2] += other.m[0][2];
	m[0][3] += other.m[0][3];
	m[1][0] += other.m[1][0];
	m[1][1] += other.m[1][1];
	m[1][2] += other.m[1][2];
	m[1][3] += other.m[1][3];
	m[2][0] += other.m[2][0];
	m[2][1] += other.m[2][1];
	m[2][2] += other.m[2][2];
	m[2][3] += other.m[2][3];
	m[3][0] += other.m[3][0];
	m[3][1] += other.m[3][1];
	m[3][2] += other.m[3][2];
	m[3][3] += other.m[3][3];

	return *this;
}

Matrix4 Matrix4::operator-(const Matrix4& other) const
{
	Matrix4 toReturn;

	toReturn.m[0][0] = m[0][0] - other.m[0][0];
	toReturn.m[0][1] = m[0][1] - other.m[0][1];
	toReturn.m[0][2] = m[0][2] - other.m[0][2];
	toReturn.m[0][3] = m[0][3] - other.m[0][3];
	toReturn.m[1][0] = m[1][0] - other.m[1][0];
	toReturn.m[1][1] = m[1][1] - other.m[1][1];
	toReturn.m[1][2] = m[1][2] - other.m[1][2];
	toReturn.m[1][3] = m[1][3] - other.m[1][3];
	toReturn.m[2][0] = m[2][0] - other.m[2][0];
	toReturn.m[2][1] = m[2][1] - other.m[2][1];
	toReturn.m[2][2] = m[2][2] - other.m[2][2];
	toReturn.m[2][3] = m[2][3] - other.m[2][3];
	toReturn.m[3][0] = m[3][0] - other.m[3][0];
	toReturn.m[3][1] = m[3][1] - other.m[3][1];
	toReturn.m[3][2] = m[3][2] - other.m[3][2];
	toReturn.m[3][3] = m[3][3] - other.m[3][3];

	return toReturn;
}

Matrix4& Matrix4::operator-=(const Matrix4& other)
{
	m[0][0] -= other.m[0][0];
	m[0][1] -= other.m[0][1];
	m[0][2] -= other.m[0][2];
	m[0][3] -= other.m[0][3];
	m[1][0] -= other.m[1][0];
	m[1][1] -= other.m[1][1];
	m[1][2] -= other.m[1][2];
	m[1][3] -= other.m[1][3];
	m[2][0] -= other.m[2][0];
	m[2][1] -= other.m[2][1];
	m[2][2] -= other.m[2][2];
	m[2][3] -= other.m[2][3];
	m[3][0] -= other.m[3][0];
	m[3][1] -= other.m[3][1];
	m[3][2] -= other.m[3][2];
	m[3][3] -= other.m[3][3];

	return *this;
}

Matrix4 Matrix4::operator*(const Matrix4& other) const
{
	Matrix4 result;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			result.m[row][col] =
				m[row][0] * other.m[0][col] +
				m[row][1] * other.m[1][col] +
				m[row][2] * other.m[2][col] +
				m[row][3] * other.m[3][col];
		}
	}

	return result;
}

Matrix4& Matrix4::operator*=(const Matrix4& other)
{
	*this = *this * other;

	return *this;
}

bool Matrix4::operator==(const Matrix4& other) const
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (m[row][col] != other[row][col])
				return false;
		}
	}
	return true;
}

bool Matrix4::operator!=(const Matrix4& other) const
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			if (m[row][col] == other[row][col])
				return false;
		}
	}
	return true;
}

float& Matrix4::operator()(int row, int col)
{
	return m[row][col];
}

const float& Matrix4::operator()(int row, int col) const
{
	return m[row][col];
}

float* Matrix4::operator[](int row)
{
	return m[row];
}

const float* Matrix4::operator[](int row) const
{
	return m[row];
}

Matrix4 Matrix4::Transposed() const
{
	Matrix4 result;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			result[row][col] = m[col][row];
		}
	}

	return result;
}

void Matrix4::Transpose()
{
	Matrix4 temp = Transposed();

	*this = temp;
}

Matrix4 Matrix4::Inverse() const
{
	
}

float Matrix4::Determinant() const
{
	float det = 0.0f;

	det += m[0][0] * (
		m[1][1] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
		m[1][2] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) +
		m[1][3] * (m[2][1] * m[3][2] - m[2][2] * m[3][1])
		);

	det -= m[0][1] * (
		m[1][0] * (m[2][2] * m[3][3] - m[2][3] * m[3][2]) -
		m[1][2] * (m[2][0] * m[3][3] - m[2][3] * m[3][0]) +
		m[1][3] * (m[2][0] * m[3][2] - m[2][2] * m[3][0])
		);

	det += m[0][2] * (
		m[1][0] * (m[2][1] * m[3][3] - m[2][3] * m[3][1]) -
		m[1][1] * (m[2][0] * m[3][3] - m[2][3] * m[3][0]) +
		m[1][3] * (m[2][0] * m[3][1] - m[2][1] * m[3][0])
		);

	det -= m[0][3] * (
		m[1][0] * (m[2][1] * m[3][2] - m[2][2] * m[3][1]) -
		m[1][1] * (m[2][0] * m[3][2] - m[2][2] * m[3][0]) +
		m[1][2] * (m[2][0] * m[3][1] - m[2][1] * m[3][0])
		);

	return det;
}

float Matrix4::Trace() const
{
	return m[0][0] +
		   m[1][1] +
		   m[2][2] +
		   m[3][3];
}

Matrix4 Matrix4::Indentity()
{
	return Matrix4(
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}

Matrix4 Matrix4::Translation(Vector3 position)
{
	return Matrix4(
		1, 0, 0, position.x,
		0, 1, 0, position.y,
		0, 0, 1, position.z,
		0, 0, 0, 1
	);
}

Matrix4 Matrix4::Scale(Vector3 scale)
{
	return Matrix4(
		scale.x, 0, 0, 0,
		0, scale.y, 0, 0,
		0, 0, scale.z, 0,
		0, 0, 0, 1
	);
}

Matrix4 Matrix4::RotationX(float radians)
{
	float c = cos(radians);
	float s = sin(radians);

	return Matrix4(
		1, 0, 0, 0,
		0, c, -s, 0,
		0, s, c, 0,
		0, 0, 0, 1
	);
}

Matrix4 Matrix4::RotationY(float radians)
{
	float c = cos(radians);
	float s = sin(radians);

	return Matrix4(
		c, 0, s, 0,
		0, 1, 0, 0,
		-s, 0, c, 0,
		0, 0, 0, 1
	);
}

Matrix4 Matrix4::RotationZ(float radians)
{
	float c = cos(radians);
	float s = sin(radians);

	return Matrix4(
		c, -s, 0, 0,
		s, c, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	);
}
