#include <iostream>
#include <vector>


template <typename T>
void print_vec(std::vector<T> &vect) {
  for (auto element : vect) {
    std::cout << element << " ";
  }
  std::cout << "\n";
}

template <typename T>
void quick_sort(std::vector<T> &vector) {
  return;
}

int main(int argc, char **argv) {

  std::vector<int> vect{ 30, 10, 20 };

  print_vec(vect);
  quick_sort(vect);
  print_vec(vect);

  return 0;
}
