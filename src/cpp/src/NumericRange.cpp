#include "NumericRange.hpp"

NumericRange::NumericRange() {
  lower = 0;
  upper = 0;
}

NumericRange::NumericRange(int _lower, int _upper) {
  lower = _lower;
  upper = _upper;
}

void NumericRange::iterate(std::function<void(int)> consumer) const {
  for (int i = lower; i <= upper; i++) {
    consumer(i);
  }
}
