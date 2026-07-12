#pragma once

class GameClientRandomVariable {
public:
    enum DistributionType {
        CONSTANT = 0,
        UNIFORM,
        GAUSSIAN,
        TRIANGULAR,
        LOW_BIAS,
        HIGH_BIAS,
    };

    GameClientRandomVariable()
    {
        distribution = CONSTANT;
        minimum = 0.0f;
        maximum = 0.0f;
    }

    GameClientRandomVariable &operator=(const GameClientRandomVariable &that);

    DistributionType getDistributionType() const;
    float getValue() const;
    float getMinimumValue() const;
    float getMaximumValue() const;
    void setRange(float minimum, float maximum, DistributionType distribution);

    DistributionType distribution;
    float minimum;
    float maximum;
};

bool operator==(const GameClientRandomVariable &left, const GameClientRandomVariable &right);
bool operator!=(const GameClientRandomVariable &left, const GameClientRandomVariable &right);
