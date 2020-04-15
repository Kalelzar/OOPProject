#ifndef OOPPROJECT_NUMERIC_RANGE
#define OOPPROJECT_NUMERIC_RANGE

#include <functional>

class NumericRange{

private:

    int lower;
    int upper;

public:

    NumericRange();
    NumericRange(int _lower, int _upper);

    void iterate(std::function<void(int)> consumer) const;

};
#endif //OOPPROJECT_NUMERIC_RANGE
