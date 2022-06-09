#include "myRandom.h"

/**
 * Random draw of an integer between 1 and nbMax.
 *
 * @param nbMax maximum integer that can be generated.
 * @return the numer generated.
 */
int random_1_to_n(int const nbMax)
{
    static std::random_device rd;
    static std::default_random_engine engine(rd());
    std::uniform_int_distribution<> distribution(1, nbMax);
    return distribution(engine);
}