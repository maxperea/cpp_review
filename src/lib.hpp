// Empty lib
#include <iostream>

template <typename Iterator>
void qsort(Iterator begin, Iterator end) {
  std::cout << *begin;
  if (*begin == *end) {
   return;
  }
  auto pivot = [&end] (const auto& a) { return a < *end;};
  auto new_end = std::partition(begin, end, pivot);
  qsort(begin, new_end);
  qsort(new_end, end);
}
