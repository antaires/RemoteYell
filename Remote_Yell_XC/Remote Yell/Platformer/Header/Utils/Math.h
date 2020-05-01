#pragma once

namespace Platformer
{

namespace Utils
{

struct Math
{
	template <typename T>
	static int Sign(T val);
	
};

template <typename T>
int Math::Sign(T val)
{
	return (T(0) < val) - (val < T(0));
}

} // Utils

} // Platformer
