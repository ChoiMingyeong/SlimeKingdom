#pragma once

class Transform
{
public:
	Transform();

public:
	D2D_VECTOR_2F Position;
	float Angle;
	D2D_VECTOR_2F Scale;

public:
	D2D_MATRIX_3X2_F GetSR();

	Transform operator+(Transform& target);
	Transform operator-(Transform& target);
};

