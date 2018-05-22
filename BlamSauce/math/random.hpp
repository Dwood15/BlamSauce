/*
	Yelo: Open Sauce SDK
		Halo 1 (CE) Edition

	See license\OpenSauce\Halo1_CE for specific license information
*/
#pragma once

namespace Yelo::Random {
	static std::default_random_engine g_generator;

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Initializes the random number generator's seed. </summary>
	///
	/// <param name="seed">	The seed value. </param>
	void InitializeSeed(const long seed) {
		g_generator.seed(seed);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a random real within the specified bounds. </summary>
	///
	/// <param name="lower">	The lower value. </param>
	/// <param name="upper">	The upper value. </param>
	///
	/// <returns>	A random real. </returns>
	real GetReal(const real lower, const real upper) {
		std::uniform_real_distribution<real> distribution(lower, upper);

		return distribution(g_generator);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a random real within the specified bounds. </summary>
	///
	/// <param name="bounds">	The value bounds. </param>
	///
	/// <returns>	A random real. </returns>
	real GetReal(const real_bounds bounds) {
		return GetReal(bounds.lower, bounds.upper);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a random real within the specified bounds. </summary>
	///
	/// <param name="bounds">	The value bounds. </param>
	///
	/// <returns>	A random real. </returns>
	real GetReal(const real_fraction_bounds bounds) {
		return GetReal(bounds.lower, bounds.upper);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a random angle within the specified bounds. </summary>
	///
	/// <param name="bounds">	The value bounds. </param>
	///
	/// <returns>	A random angle. </returns>
	real GetReal(const angle_bounds bounds) {
		return GetReal(bounds.lower, bounds.upper);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a random uint32 within the specified bounds. </summary>
	///
	/// <param name="lower">	The lower value. </param>
	/// <param name="upper">	The upper value. </param>
	///
	/// <returns>	A random uint32. </returns>
	uint32 GetUInt32(const uint32 lower, const uint32 upper) {
		std::uniform_int_distribution<uint32> distribution(lower, upper);

		return distribution(g_generator);
	}


	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a random long within the specified bounds. </summary>
	///
	/// <param name="lower">	The lower value. </param>
	/// <param name="upper">	The upper value. </param>
	///
	/// <returns>	A random long. </returns>
	long GetInt32(const long lower, const long upper) {
		std::uniform_int_distribution<long> distribution(lower, upper);

		return distribution(g_generator);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a random unsigned short within the specified bounds. </summary>
	///
	/// <param name="lower">	The lower value. </param>
	/// <param name="upper">	The upper value. </param>
	///
	/// <returns>	A random unsigned short. </returns>
	unsigned short GetUInt16(const unsigned short lower, const unsigned short upper) {
		std::uniform_int_distribution<unsigned short> distribution(lower, upper);

		return distribution(g_generator);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a random short within the specified bounds. </summary>
	///
	/// <param name="lower">	The lower value. </param>
	/// <param name="upper">	The upper value. </param>
	///
	/// <returns>	A random short. </returns>
	short GetInt16(const short lower, const short upper) {
		std::uniform_int_distribution<short> distribution(lower, upper);

		return distribution(g_generator);
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////
	/// <summary>	Gets a random short within the specified bounds. </summary>
	///
	/// <param name="bounds">	The value bounds. </param>
	///
	/// <returns>	A random short. </returns>
	short GetInt16(const short_bounds bounds) {
		return GetInt16(bounds.lower, bounds.upper);
	}
};
