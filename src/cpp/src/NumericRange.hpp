#ifndef OOPPROJECT_NUMERIC_RANGE
#define OOPPROJECT_NUMERIC_RANGE

#include <functional>

//An inclusive range of numbers
class NumericRange{

private:

    int lower;
    int upper;

public:

    NumericRange();
    NumericRange(int _lower, int _upper);

    ///Apply the given function to all numbers in the range
    void iterate(std::function<void(int)> consumer) const;

};
#endif //OOPPROJECT_NUMERIC_RANGE
