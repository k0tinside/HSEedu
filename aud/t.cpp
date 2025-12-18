#include <stdexcept>

class Range {
private:
    int low;
    int high;

public:

    Range(int low, int high) : low(low), high(high) {
        if (low >= high) {
            throw std::invalid_argument("Неыерный диапазон: low >= high");
        }
    }

    int low() const {   return low; }
    int high() const {   return high; }
    bool contains(int x) const {
        return (low <= x) && (x <= high);
    }
};
