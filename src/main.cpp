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

// template<typename T, typename Unused = typename std::enable_if<std::is_base_of<PrintableD, T>::value>::type>
// void printSomething(T* c) {
//   c->print_dynamic();
// }

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


#include <algorithm>

template <typename Iterator>
void quicksort_aux(Iterator begin, Iterator end) {
  if (begin == end) {
   return;
  }
  auto lower = [&end] (const auto& a) { return a < *end;};
  auto higher = [&end] (const auto& a) { return a > *end;};

  auto new_end = std::partition(begin, end, lower);
  auto new_begin = std::partition(new_end, end, higher);

  quicksort_aux(begin, new_end);
  quicksort_aux(new_begin, end);
}

int main(int argc, char **argv) {

  SmallDog first_small_dog;
  printSomething(first_small_dog);

  SmallCat first_small_cat;
  printSomething(first_small_cat);

  auto first_cat = std::make_unique<Cat>();
  auto first_dog = std::make_unique<Dog>();

  std::vector<std::unique_ptr<AbstractPrintableT>> stat_arr = {};
  stat_arr.push_back(std::move(first_dog));
  stat_arr.push_back(std::move(first_cat));

  for (auto &elem : stat_arr) {
    elem->print_static();
  }

  auto second_dog = std::make_unique<Dog>();
  std::vector<std::unique_ptr<PrintableD>> dyn_arr = {};

  dyn_arr.push_back(std::move(second_dog));

  for (auto &elem : dyn_arr) {
    elem->print_dynamic();
  }

  std::vector<int> test_array = {1,5,2,4,5,3};
  quicksort_aux(test_array.begin(), test_array.end());
  print_vector(test_array);
}
