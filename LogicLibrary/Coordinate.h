#pragma once
namespace LogicLibrary
{
	template <typename T>
	class Coordinate
	{
	public:
		Coordinate();
		Coordinate(T, T);
		T X() const;
		T Y() const;
	private:
		T x;
		T y;
	};

	template <>
	class Coordinate<int>
	{
	public:
		Coordinate();
		Coordinate(Coordinate<double>);
		Coordinate(int, int);
		int X() const;
		int Y() const;
	private:
		int x;
		int y;
	};

	inline Coordinate<int>::Coordinate()
	{
		x = 0;
		y = 0;
	}

	inline Coordinate<int>::Coordinate(Coordinate<double> cd)
	{
		x = static_cast<int>(cd.X());
		y = static_cast<int>(cd.Y());
	}

	inline Coordinate<int>::Coordinate(int xi, int yi)
	{
		x = xi;
		y = yi;
	}

	inline int Coordinate<int>::X() const
	{
		return x;
	}

	inline int Coordinate<int>::Y() const
	{
		return y;
	}

	template<typename T>
	inline Coordinate<T>::Coordinate()
	{
		x = 0;
		y = 0;
	}

	template <typename T>
	inline Coordinate<T>::Coordinate(T xi, T yi)
	{
		x = xi;
		y = yi;
	}

	template<typename T>
	inline T Coordinate<T>::X() const
	{
		return x;
	}

	template<typename T>
	inline T Coordinate<T>::Y() const
	{
		return y;
	}

	template class Coordinate<double>;
	template class Coordinate<int>;
}