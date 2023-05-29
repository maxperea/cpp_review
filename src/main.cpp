#include <algorithm>
#include <iostream>
#include <vector>

struct AbstractPrintableT {
  virtual ~AbstractPrintableT() = default;
  virtual void print_static() = 0;
};

template <typename T>
concept Printable = requires(T t) {
  t.print_static();
};

template <typename T>
struct PrintableT : AbstractPrintableT {
  void print_static() override {
    static_cast<T*>(this)->print_implementation();
  }
};

struct PrintableD {
  virtual ~PrintableD() = default;
  virtual void print_dynamic() = 0;
};


struct Cat : PrintableT<Cat> {
  void print_implementation() {
    std::cout << "Static hello from Cat\n";
  }
};

struct Dog : PrintableT<Dog> , PrintableD {
  void print_implementation() {
    std::cout << "Static hello from Dog\n";
  }

  void print_dynamic() override {
    std::cout << "Dynamic hello from Dog\n";
  }
};

struct SmallDog {
  void print_static() {
    std::cout << "WOOF!\n";
  }
};

struct SmallCat {
  void print_static() {
    std::cout << "MIAO";
  }
};

int add (int a, int b) {
  return a + b;
}

int say_hello(int i) {
  return i + i;
}

template<Printable T>
void printSomething(T& c) {
  c.print_static();
};

template <typename T>
void print_vector(std::vector<T> vec) {
  for (auto& elem : vec) {
    std::cout << elem << '\n';
  }
}

template <typename Iter>
void qsort(Iter begin, Iter end) {
  if (end - begin <= 1) return;

  auto pivot = end - 1;
  auto compare = [pivot](const auto& a) { return a < *pivot;};
  auto mid = std::partition(begin, end, compare);
  std::swap(*mid, *pivot);

  qsort(begin, mid);
  qsort(mid + 1, end);
}

int main(int argc, char **argv) {
  std::vector<int> test_array = {1,5,2,4,5,3};
  qsort(test_array.begin(), test_array.end());
  print_vector(test_array);
  std::sort(test_array.begin(), test_array.end());
}
