#pragma once
#include <algorithm>
#include <iostream> 

template<typename T>
class Stats {
private:
    T current;
    T maximum;

public:
    explicit Stats(T maxVal)
      : current(maxVal), maximum(maxVal) {}

    Stats(const Stats&) = default;
    Stats(Stats&&) = default;

    Stats& operator=(const Stats&) = default;
    Stats& operator=(Stats&&) = default;

    // membra dependenta de T
    void takeDamage(T amount) {
        current = std::max<T>(0, current - amount);
    }

    void heal(T amount) {
        current = std::min<T>(maximum, current + amount);
    }
    
    T getCurrent() const { return current; }
    T getMax()     const { return maximum; }
    // membra dependenta de T, returnează procent
    float getRatio() const {
        return maximum > 0
             ? static_cast<float>(current) / static_cast<float>(maximum)
             : 0.f;
    }


};

// functie libera template
template<typename T>
inline void logStat(const Stats<T>& s, const char* name) {
    std::cout << name << ": "
              << s.getCurrent() << " / "
              << s.getMax()     << "\n";
}

template<typename T>
bool isCritical(const Stats<T>& stat, float tresholdFraction)
{
    return stat.getRatio() <= static_cast<float>(tresholdFraction);
}