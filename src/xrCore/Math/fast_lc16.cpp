#include <random>

#include "fast_lc16.hpp"

static std::random_device s_random_device;

fast_lc16::fast_lc16()
{
    seed(s_random_device());
}

void fast_lc16::seed()
{
    seed(s_random_device());
}
