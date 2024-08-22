#include "gppch.h"
#include "Random.h"

namespace Grape {

	std::mt19937 Random::s_randomEngine;
	std::uniform_int_distribution<std::mt19937::result_type> Random::s_distribution;

}