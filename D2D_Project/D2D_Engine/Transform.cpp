#include "pch.h"
#include "Transform.h"

Transform::Transform()
	:Position({ 0,0 }), Scale({ 1,1 }), Angle(0.0f)
{}

D2D_MATRIX_3X2_F Transform::GetSR()
{
	D2D_MATRIX_3X2_F resultMatix =
		D2D1::Matrix3x2F::Scale(Scale.x, Scale.y, { Position.x, Position.y })
		* D2D1::Matrix3x2F::Rotation(Angle, { Position.x, Position.y });

	return resultMatix;
}

Transform Transform::operator+(Transform& target)
{
	Transform temp;
	temp.Position = { Position.x + target.Position.x, Position.y + target.Position.y };
	temp.Angle = Angle + target.Angle;
	temp.Scale = { Scale.x * target.Scale.x, Scale.y * target.Scale.y };

	return temp;
}

Transform Transform::operator-(Transform& target)
{
	Transform temp;
	temp.Position = { target.Position.x - Position.x, target.Position.y - Position.y };
	temp.Angle = Angle + target.Angle;
	temp.Scale = { Scale.x * target.Scale.x, Scale.y * target.Scale.y };

	return temp;
}
