#pragma once

#include "stdafx.h"

using namespace System;

namespace FbxWrapper
{
	public value struct Colour
	{
	public:
		Colour(double r, double g, double b, double a)
		{
			R = r;
			G = g;
			B = b;
			A = a;
		}

		property double R;
		property double G;
		property double B;
		property double A;

		inline operator FbxVector4() { return FbxVector4(R, G, B, A); }
		inline operator FbxDouble4() { return FbxDouble4(R, G, B, A); }
		inline operator FbxColor() { return FbxColor(R, G, B, A); }

		virtual String ^ToString() override
		{
			return String::Format("{0}, {1}, {2}, {3}", Math::Round(R, 3), Math::Round(G, 3), Math::Round(B, 3), Math::Round(A, 3));
		}

	internal:
		Colour(FbxColor fbxColour)
		{
			R = fbxColour.mRed;
			G = fbxColour.mGreen;
			B = fbxColour.mBlue;
			A = fbxColour.mAlpha;
		}


	};

	public value struct Vector3
	{
	public:
		Vector3(double x, double y, double z)
		{
			X = x;
			Y = y;
			Z = z;
		}

		property double X;
		property double Y;
		property double Z;

		inline operator FbxDouble3() { return FbxDouble3(X, Y, Z); }
		inline operator FbxVector4() { return FbxVector4(X, Y, Z, 0); }


		virtual String ^ToString() override
		{
			return String::Format("{0}, {1}, {2}", Math::Round(X, 3), Math::Round(Y, 3), Math::Round(Z, 3));
		}

		static Vector3 operator *(Vector3 self, float value)
		{
			self.X *= value;
			self.Y *= value;
			self.Z *= value;
			return self;
		}

	internal:
		Vector3(FbxDouble3 fbxDouble)
		{
			X = fbxDouble[0];
			Y = fbxDouble[1];
			Z = fbxDouble[2];
		}
	};

	public value struct Vector2
	{
		Vector2(double x, double y)
		{
			X = x;
			Y = y;
		}
		inline operator FbxVector2() { return FbxVector2(X, Y); }
		inline operator FbxDouble2() { return FbxDouble2(X, Y); }

		virtual String ^ToString() override
		{
			return String::Format("{0}, {1}", Math::Round(X, 3), Math::Round(Y, 3));
		}

		property double X;
		property double Y;

	internal:
		Vector2(FbxVector2 vector)
		{
			X = vector[0];
			Y = vector[1];
		}
	};

	public value struct Vector4
	{
	internal:
		Vector4(FbxVector4 vector)
		{
			X = vector.mData[0];
			Y = vector.mData[1];
			Z = vector.mData[2];
			W = vector.mData[3];
		}
	public:
		Vector4(double x, double y, double z, double w)
		{
			W = w;
			X = x;
			Y = y;
			Z = z;
		}

		inline operator FbxVector4() { return FbxVector4(X, Y, Z, W); }
		inline operator FbxDouble4() { return FbxDouble4(X, Y, Z, W); }
		

		virtual String ^ToString() override
		{
			return String::Format("{0}, {1}, {2}, {3}", Math::Round(X, 3), Math::Round(Y, 3), Math::Round(Z, 3), Math::Round(W, 3));
		}
		property double X;
		property double Y;
		property double Z;
		property double W;
	};
}
