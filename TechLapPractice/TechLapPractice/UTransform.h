#pragma once

#include "directxtk/SimpleMath.h"

//simpleMath�� �຤�� ���
//WorldMat = ScaleMat * RotMat * TranslateMat
using namespace DirectX::SimpleMath;

class UTransform
{
public:

private:
	Vector3 Position = Vector3::Zero;
	Vector3 Scale = Vector3::One;
	Quaternion Rotation = Quaternion::Identity;

	Vector3 Right = Vector3::UnitX;
	Vector3 Up = Vector3::UnitY;
	Vector3 Forward = Vector3::UnitZ;

	Matrix WorldMat = Matrix::Identity;
public:
	Vector3 GetPosition() const
	{
		return Position;
	}
	Vector3 GetScale() const
	{
		return Scale;
	}
	Quaternion GetRotation() const
	{
		return Rotation;
	}
	Vector3 GetEuler() const
	{
		return Rotation.ToEuler();
	}
	Vector3 GetRight() const
	{
		return Right;
	}
	Vector3 GetUp() const
	{
		return Up;
	}
	Vector3 GetForward() const
	{
		return Forward;
	}
	Matrix GetWorldMat() const
	{
		return WorldMat;
	}

	void SetPosition(const Vector3& pos)
	{
		Position = pos;
		Update();
	}
	void SetScale(const Vector3& scale)
	{
		Scale = scale;
		Update();
	}
	void SetRotation(const Quaternion& quat)
	{
		Rotation = quat;
		Update();
	}
	void SetRotataion(const Vector3& eulerRadian)
	{
		//yaw = up
		//pitch = right
		//roll = forward
		Rotation = Quaternion::CreateFromYawPitchRoll(eulerRadian.y, eulerRadian.x, eulerRadian.z);
		Update();
	}
	void RotationAxis(const Vector3& axis, const float degree)
	{
		Rotation *= Quaternion::CreateFromAxisAngle(axis, degree);
		Update();
	}
	//void Look(const Vector3& lookPos)
	//{
	//	if (Position == lookPos)
	//	{
	//		return;
	//	}
	//	else
	//	{
	//		Vector3 lookDir = lookPos - Position;
	//		Quaternion::LookRotation(lookDir, Up);
	//	}
	//}
private:
	void Update() 
	{
		WorldMat = Matrix::CreateScale(Scale) * Matrix::CreateFromQuaternion(Rotation) * Matrix::CreateTranslation(Position);
		Right = WorldMat.Right();
		Up = WorldMat.Up();
		Forward = WorldMat.Forward();
	}
	
};