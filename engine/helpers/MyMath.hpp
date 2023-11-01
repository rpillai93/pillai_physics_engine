#pragma once
namespace mymath {
	template<typename T>
	constexpr const T& clamp(const T& v, const T& lo, const T& hi) {
		if (v > hi) {

			return hi;
		}
		if (v < lo) {

			return lo;
		}

		return v;
	}

	template<typename T>
	constexpr const T& min(const T& v1, const T& v2) {
		return v1 > v2 ? v2 : v1;
	}

	template<typename T>
	constexpr const T& max(const T& v1, const T& v2) {
		return v1 >= v2 ? v1 : v2;
	}

	template<typename T>
	constexpr const double sqrt(const T& v) {
		double tol = 0.001;
		// Assuming the sqrt of n as n only
		double x = static_cast<double>(v);

		// The closed guess will be stored in the root
		double root;

		// To count the number of iterations
		int count = 0;

		while (1) {
			count++;

			// Calculate more closed x
			root = 0.5 * (x + (v / x));

			// Check for closeness
			if (abs(root - x) < tol)
				break;

			// Update root
			x = root;
		}

		return root;
	}

	namespace vector2 {




		template<typename T>
		constexpr const T& getDistSq(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2)
		{
			return (v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y);
		}


		template<typename T>
		constexpr const T& getDist(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2)
		{
			return sqrt((v1.x - v2.x) * (v1.x - v2.x) + (v1.y - v2.y) * (v1.y - v2.y));
		}

		template<typename T>
		constexpr const T& magnitudeSq(const sf::Vector2<T>& v)
		{
			return v.x * v.x + v.y * v.y;
		}

		template<typename T>
		constexpr const T& magnitude(const sf::Vector2<T>& v)
		{
			return sqrt(v.x * v.x + v.y * v.y);
		}

		template<typename T>
		constexpr sf::Vector2<T>& normalize(sf::Vector2<T>& v)
		{
			v.x /= magnitude(v);
			v.y /= magnitude(v);
			return v;
		}

		template<typename T>
		constexpr const T& dotProduct(const sf::Vector2<T>& v1, const sf::Vector2<T>& v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}


	}

}