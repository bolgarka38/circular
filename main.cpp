#include <iostream>
#include "test.hpp"

int main() {
    setlocale(LC_ALL,"Russian");
    demo_basic_operations();
    demo_list_of_lists();
    demo_throwing_during_insert();

    std::cout << "\nВсе тесты завершены.\n";
    return 0;
}
