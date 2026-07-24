#pragma once
#include "NxMath.h"

class Vector3;

class Matrix4
{
public:
	Matrix4();
    Matrix4(const Matrix4& other);
    Matrix4(const float(&values)[16]);
	Matrix4(float m00, float m01, float m02, float m03,
            float m10, float m11, float m12, float m13,
            float m20, float m21, float m22, float m23,
            float m30, float m31, float m32, float m33);

    Matrix4& operator=(const Matrix4& other);
    Matrix4 operator+(const Matrix4& other) const;
    Matrix4& operator+=(const Matrix4& other);
    Matrix4 operator-(const Matrix4& other) const;
    Matrix4& operator-=(const Matrix4& other);
    Matrix4 operator*(const Matrix4& other) const;
    Matrix4& operator*=(const Matrix4& other);
    bool operator==(const Matrix4& other) const;
    bool operator!=(const Matrix4& other) const;

    float& operator()(int row, int col);
    const float& operator()(int row, int col) const;

    float* operator[](int row);
    const float* operator[](int row) const;


    Matrix4 Transposed() const;
    void Transpose();

    Matrix4 Inverse() const;
    float Determinant() const;
    Vector3 TransformPoint(const Vector3& vec) const;
    Vector3 ProjectPoint(const Vector3& vec) const;
    float Trace() const;
    Vector3 Forward();
    Vector3 Right();
    Vector3 Up();

    static Matrix4 Indentity();
    static Matrix4 Translation(Vector3 position);
    static Matrix4 Scale(Vector3 scale);
    static Matrix4 RotationX(float radians);
    static Matrix4 RotationY(float radians);
    static Matrix4 RotationZ(float radians);
    static Matrix4 Perspective(float fov, float aspect, float nearPlane, float farPlane);

private:

    float m[4][4] = 
    {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0} 
    };

};

