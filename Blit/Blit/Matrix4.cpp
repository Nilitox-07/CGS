#include "Matrix4.h"
#include "NxMath.h"
#include <iostream>

Matrix4::Matrix4()
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			m[row][col] = 0.0f;
		}
	}
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

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			toReturn[row][col] = m[row][col] + other.m[row][col];
		}
	}

	return toReturn;
}

Matrix4& Matrix4::operator+=(const Matrix4& other)
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			m[row][col] += other.m[row][col];
		}
	}

	return *this;
}

Matrix4 Matrix4::operator-(const Matrix4& other) const
{
	Matrix4 toReturn;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			toReturn[row][col] = m[row][col] - other.m[row][col];
		}
	}

	return toReturn;
}

Matrix4& Matrix4::operator-=(const Matrix4& other)
{
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			m[row][col] -= other.m[row][col];
		}
	}

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
	Matrix4 result;

	float det = Determinant();

	if (det == 0)
		return result;

	float cofactors[4][4];

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			float minor[3][3];

			int minorRow = 0;

			for (int r = 0; r < 4; r++)
			{
				if (r == row)
					continue;

				int minorCol = 0;

				for (int c = 0; c < 4; c++)
				{
					if (c == col)
						continue;

					minor[minorRow][minorCol] = m[r][c];
					minorCol++;
				}

				minorRow++;
			}

			float minorDet =
				minor[0][0] * (minor[1][1] * minor[2][2] - minor[1][2] * minor[2][1]) -
				minor[0][1] * (minor[1][0] * minor[2][2] - minor[1][2] * minor[2][0]) +
				minor[0][2] * (minor[1][0] * minor[2][1] - minor[1][1] * minor[2][0]);

			float sign = ((row + col) % 2 == 0) ? 1.0f : -1.0f;

			cofactors[row][col] = sign * minorDet;
		}
	}

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			result.m[row][col] = cofactors[col][row] / det;
		}
	}

	return result;
}

float Matrix4::Determinant() const
{
	float det = 0.0f;

	for (int col = 0; col < 4; col++)
	{
		float minor[3][3];
		int minorRow = 0;

		for (int row = 1; row < 4; row++)
		{
			int minorCol = 0;

			for (int currentCol = 0; currentCol < 4; currentCol++)
			{
				if (currentCol == col)
					continue;

				minor[minorRow][minorCol] = m[row][currentCol];
				minorCol++;
			}

			minorRow++;
		}

		float minorDet =
			minor[0][0] * (minor[1][1] * minor[2][2] - minor[1][2] * minor[2][1]) -
			minor[0][1] * (minor[1][0] * minor[2][2] - minor[1][2] * minor[2][0]) +
			minor[0][2] * (minor[1][0] * minor[2][1] - minor[1][1] * minor[2][0]);

		float sign = (col % 2 == 0) ? 1.0f : -1.0f;

		det += sign * m[0][col] * minorDet;
	}

	return det;
}

Vector3 Matrix4::TransformPoint(const Vector3& vec) const
{
	Vector3 result;

	result.x =
		m[0][0] * vec.x +
		m[0][1] * vec.y +
		m[0][2] * vec.z +
		m[0][3];

	result.y =
		m[1][0] * vec.x +
		m[1][1] * vec.y +
		m[1][2] * vec.z +
		m[1][3];

	result.z =
		m[2][0] * vec.x +
		m[2][1] * vec.y +
		m[2][2] * vec.z +
		m[2][3];

	return result;
}

Vector3 Matrix4::ProjectPoint(const Vector3& vec) const
{
	Vector3 result;

	float w =
		m[3][0] * vec.x +
		m[3][1] * vec.y +
		m[3][2] * vec.z +
		m[3][3];

	result.x =
		m[0][0] * vec.x +
		m[0][1] * vec.y +
		m[0][2] * vec.z +
		m[0][3];

	result.y =
		m[1][0] * vec.x +
		m[1][1] * vec.y +
		m[1][2] * vec.z +
		m[1][3];

	result.z =
		m[2][0] * vec.x +
		m[2][1] * vec.y +
		m[2][2] * vec.z +
		m[2][3];

	if (w != 0)
	{
		result.x /= w;
		result.y /= w;
		result.z /= w;
	}

	return result;
}

float Matrix4::Trace() const
{
	return m[0][0] +
		   m[1][1] +
		   m[2][2] +
		   m[3][3];
}

Vector3 Matrix4::Forward()
{
	return Vector3(m[0][2], m[1][2], m[2][2]);
}

Vector3 Matrix4::Right()
{
	return Vector3(m[0][0], m[1][0], m[2][0]);
}

Vector3 Matrix4::Up()
{
	return Vector3(m[0][1], m[1][1], m[2][1]);
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

Matrix4 Matrix4::Perspective(float fov, float aspect, float nearPlane, float farPlane)
{
	Matrix4 result;

	float YScale = 1.0f / tan(fov / 2.0f);

	result[0][0] = YScale * aspect;
	result[1][1] = YScale;

	result[2][2] = (farPlane + nearPlane) / (nearPlane - farPlane);
	result[2][3] = (2.0f * farPlane * nearPlane) / (nearPlane - farPlane);

	result[3][2] = -1.0f;
	result[3][3] = 0.0f;

	return result;
}
