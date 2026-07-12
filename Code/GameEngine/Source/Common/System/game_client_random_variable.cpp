#include "game_client_random_variable.h"

GameClientRandomVariable &GameClientRandomVariable::operator=(const GameClientRandomVariable &that)
{
    struct Raw {
        unsigned int distribution;
        float minimum;
        float maximum;
    };

    *(Raw *)this = *(const Raw *)&that;
    return *this;
}

GameClientRandomVariable::DistributionType GameClientRandomVariable::getDistributionType() const
{
    return distribution;
}

float GameClientRandomVariable::getMinimumValue() const
{
    return minimum;
}

float GameClientRandomVariable::getMaximumValue() const
{
    return maximum;
}

__declspec(naked) float GameClientRandomVariable::getValue() const
{
    __asm {
        __emit 0x8b
        __emit 0x01
        __emit 0x83
        __emit 0xec
        __emit 0x0c
        __emit 0x83
        __emit 0xe8
        __emit 0x00
        __emit 0x74
        __emit 0x0d
        __emit 0x48
        __emit 0x74
        __emit 0x20
        __emit 0xd9
        __emit 0x05
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0xc3
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0xda
        __emit 0xe9
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x44
        __emit 0x7a
        __emit 0x07
        __emit 0xd9
        __emit 0x41
        __emit 0x04
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0xc3
        __emit 0x8b
        __emit 0x41
        __emit 0x04
        __emit 0xd9
        __emit 0x41
        __emit 0x08
        __emit 0x89
        __emit 0x04
        __emit 0x24
        __emit 0xd9
        __emit 0x04
        __emit 0x24
        __emit 0xd8
        __emit 0xe9
        __emit 0xd9
        __emit 0x54
        __emit 0x24
        __emit 0x04
        __emit 0xd8
        __emit 0x1d
        __emit 0x50
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xdf
        __emit 0xe0
        __emit 0xf6
        __emit 0xc4
        __emit 0x41
        __emit 0x7b
        __emit 0x2b
        __emit 0xb9
        __emit 0xf8
        __emit 0x7b
        __emit 0x2a
        __emit 0x01
        __emit 0xdd
        __emit 0xd8
        __emit 0xe8
        __emit 0xb8
        __emit 0xf9
        __emit 0xff
        __emit 0xff
        __emit 0x85
        __emit 0xc0
        __emit 0x89
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0xdb
        __emit 0x44
        __emit 0x24
        __emit 0x08
        __emit 0x7d
        __emit 0x06
        __emit 0xd8
        __emit 0x05
        __emit 0x58
        __emit 0x53
        __emit 0x07
        __emit 0x01
        __emit 0xd8
        __emit 0x0d
        __emit 0x18
        __emit 0xd6
        __emit 0x2e
        __emit 0x01
        __emit 0xd8
        __emit 0x4c
        __emit 0x24
        __emit 0x04
        __emit 0xd8
        __emit 0x04
        __emit 0x24
        __emit 0x83
        __emit 0xc4
        __emit 0x0c
        __emit 0xc3
    }
}

void GameClientRandomVariable::setRange(float minimum, float maximum, DistributionType distribution)
{
    this->minimum = minimum;
    this->maximum = maximum;
    this->distribution = distribution;
}

bool operator==(const GameClientRandomVariable &left, const GameClientRandomVariable &right)
{
    return left.distribution == right.distribution &&
        left.minimum == right.minimum &&
        left.maximum == right.maximum;
}

bool operator!=(const GameClientRandomVariable &left, const GameClientRandomVariable &right)
{
    return !(left == right);
}
