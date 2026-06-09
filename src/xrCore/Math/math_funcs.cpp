#include "Common/Platform.hpp"
#include "xrCore/Math/bitwise.hpp"
#include "xrCore/Math/constants.hpp"
#include "xrCore/Math/math_funcs_inline.hpp"

#include "math_funcs.hpp"

// normalize angle (0..2PI)
float angle_normalize_always(float a)
{
	float div = a / PI_MUL_2;
	int rnd = (div > 0) ? iFloor(div) : iCeil(div);
	float frac = div - rnd;
	if (frac < 0) frac += 1.f;
	return frac * PI_MUL_2;
}

// normalize angle (0..2PI)
float angle_normalize(float a)
{
	if (a >= 0 && a <= PI_MUL_2) return a;
	return angle_normalize_always(a);
}

// -PI .. +PI
float angle_normalize_signed(float a)
{
	if (a >= (-PI) && a <= PI) return a;
	float angle = angle_normalize_always(a);
	if (angle > PI) angle -= PI_MUL_2;
	return angle;
}

float angle_difference_signed(float a, float b)
{
	float diff = angle_normalize_signed(a) - angle_normalize_signed(b);
	if (diff > 0)
	{
		if (diff > PI)
			diff -= PI_MUL_2;
	}
	else
	{
		if (diff < -PI)
			diff += PI_MUL_2;
	}
	return diff;
}

// 0..PI
float angle_difference(float a, float b)
{
	return _abs(angle_difference_signed(a, b));
}

bool are_ordered(float const value0, float const value1, float const value2)
{
	if ((value1 >= value0) && (value1 <= value2))
		return true;

	if ((value1 <= value0) && (value1 >= value2))
		return true;

	return false;
}

bool is_between(float const value, float const left, float const right)
{
	return are_ordered(left, value, right);
}

// c=current, t=target, s=speed, dt=dt
bool angle_lerp(float& c, float t, float s, float dt)
{
	float const before = c;
	float diff = t - c;
	if (diff > 0)
	{
		if (diff > PI)
			diff -= PI_MUL_2;
	}
	else
	{
		if (diff < -PI)
			diff += PI_MUL_2;
	}
	float diff_a = _abs(diff);

	if (diff_a < EPS_S)
		return true;

	float mot = s*dt;
	if (mot > diff_a) mot = diff_a;
	c += (diff / diff_a)*mot;

	if (is_between(c, before, t))
		return false;

	if (c < 0)
		c += PI_MUL_2;
	else if (c > PI_MUL_2)
		c -= PI_MUL_2;

	return false;
}

// Just lerp :) expects normalized angles in range [0..2PI)
float angle_lerp(float A, float B, float f)
{
	float diff = B - A;
	if (diff > PI) diff -= PI_MUL_2;
	else if (diff < -PI) diff += PI_MUL_2;

	return A + diff*f;
}

float angle_inertion(float src, float tgt, float speed, float clmp, float dt)
{
	float a = angle_normalize_signed(tgt);
	angle_lerp(src, a, speed, dt);
	src = angle_normalize_signed(src);
	float dH = angle_difference_signed(src, a);
	float dCH = clampr(dH, -clmp, clmp);
	src -= dH - dCH;
	return src;
}

float angle_inertion_var(float src, float tgt, float min_speed, float max_speed, float clmp, float dt)
{
	tgt = angle_normalize_signed(tgt);
	src = angle_normalize_signed(src);
	float speed = _abs((max_speed - min_speed)*angle_difference(tgt, src) / clmp) + min_speed;
	angle_lerp(src, tgt, speed, dt);
	src = angle_normalize_signed(src);
	float dH = angle_difference_signed(src, tgt);
	float dCH = clampr(dH, -clmp, clmp);
	src -= dH - dCH;
	return src;
}

double rsqrt(double v) noexcept { return 1.0 / _sqrt(v); }

bool exact_normalize(float* a)
{
	double sqr_magnitude = a[0] * a[0] + a[1] * a[1] + a[2] * a[2];
	double epsilon = 1.192092896e-05F;
	if (sqr_magnitude > epsilon)
	{
		double l = rsqrt(sqr_magnitude);
		a[0] *= l;
		a[1] *= l;
		a[2] *= l;
		return true;
	}
	double a0, a1, a2, aa0, aa1, aa2, l;
	a0 = a[0];
	a1 = a[1];
	a2 = a[2];
	aa0 = _abs(a0);
	aa1 = _abs(a1);
	aa2 = _abs(a2);
	if (aa1 > aa0)
	{
		if (aa2 > aa1)
		{
			goto aa2_largest;
		}
		else // aa1 is largest
		{
			a0 /= aa1;
			a2 /= aa1;
			l = rsqrt(a0*a0 + a2*a2 + 1);
			a[0] = a0*l;
			a[1] = (double)_copysign(l, a1);
			a[2] = a2*l;
		}
	}
	else
	{
		if (aa2 > aa0)
		{
		aa2_largest: // aa2 is largest
			a0 /= aa2;
			a1 /= aa2;
			l = rsqrt(a0*a0 + a1*a1 + 1);
			a[0] = a0*l;
			a[1] = a1*l;
			a[2] = (double)_copysign(l, a2);
		}
		else // aa0 is largest
		{
			if (aa0 <= 0)
			{
				// dDEBUGMSG ("vector has zero size"); ... this message is annoying
				a[0] = 0; // if all a's are zero, this is where we'll end up.
				a[1] = 1; // return a default unit length vector.
				a[2] = 0;
				return false;
			}
			a1 /= aa0;
			a2 /= aa0;
			l = rsqrt(a1*a1 + a2*a2 + 1);
			a[0] = (double)_copysign(l, a0);
			a[1] = a1*l;
			a[2] = a2*l;
		}
	}
	return true;
}
