// Empty lib
#include <vector>
#include <algorithm>
#include <iostream>

template <typename Iterator>
void quicksort_aux(Iterator begin, Iterator end) {
  std::cout << *begin;
  if (*begin == *end) {
   return;
  }
  auto pivot = [&end] (const auto& a) { return a < *end;};
  auto new_end = std::partition(begin, end, pivot);
  quicksort_aux(begin, new_end);
  quicksort_aux(new_end, end);
}
