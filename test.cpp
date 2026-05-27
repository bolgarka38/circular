#include "test.hpp"

struct throwing_on_copy {
    int id;
    static bool should_throw;

    throwing_on_copy(int i = 0) : id(i) {}

    throwing_on_copy(const throwing_on_copy& other) {
        if (should_throw) throw std::runtime_error("Simulated copy error");
        id = other.id;
    }

    friend std::ostream& operator<<(std::ostream& os, const throwing_on_copy& t) {
        os << "Throwing{" << t.id << "}";
        return os;
    }
};

bool throwing_on_copy::should_throw = false;

void demo_basic_operations() {
    std::cout << "Тестирование circular<TestInt>\n\n";

    CircularList<TestInt> list1;
    std::cout << "list1 (empty): " << list1 << ", size=" << list1.size() << std::endl;

    TestInt a1(10), a2(20), a3(30);
    list1.insert_after(a1);
    list1.insert_after(a2);
    list1.insert_after(a3);
    std::cout << "After inserts: " << list1 << ", size=" << list1.size() << std::endl;

    list1.next(); list1.next();
    list1.insert_before(std::move(a2));
    std::cout << "After insert_before(move): " << list1 << std::endl;

    list1.delete_current();
    std::cout << "After delete_current: " << list1 << std::endl;

    if (auto* ptr = list1.get_current()) {
        std::cout << "Current element: " << *ptr << std::endl;
    }

    CircularList<TestInt> list2 = list1;
    std::cout << "list2 (copy of list1): " << list2 << std::endl;

    CircularList<TestInt> list3 = std::move(list1);
    std::cout << "list3 (move from list1): " << list3 << std::endl;
    std::cout << "list1 after move: " << list1 << " (empty)" << std::endl;

    list1 = list2;
    std::cout << "list1 after copy-assign from list2: " << list1 << std::endl;

    CircularList<TestInt> list4;
    list4 = std::move(list3);
    std::cout << "list4 after move-assign: " << list4 << std::endl;

    std::cout << "\nИсключения при навигации/удалении\n";
    CircularList<int> empty_list;
    try {
        empty_list.next();
    } catch (const list_error& e) {
        std::cout << "Caught list_error: " << e.what() << std::endl;
    }
    try {
        empty_list.delete_current();
    } catch (const list_error& e) {
        std::cout << "Caught list_error: " << e.what() << std::endl;
    }
}

void demo_list_of_lists() {
    std::cout << "\nСписок списков\n";
    std::deque<CircularList<int>> list_of_lists;

    CircularList<int> int_list1;
    int_list1.insert_after(100);
    int_list1.insert_after(200);
    int_list1.insert_after(300);

    CircularList<int> int_list2;
    int_list2.insert_after(10);
    int_list2.insert_after(20);

    list_of_lists.push_back(int_list1);
    list_of_lists.push_back(int_list2);
    list_of_lists.push_back(CircularList<int>());

    std::cout << "\nОбработка исключений при работе с коллекцией списков\n";
    for (size_t i = 0; i < list_of_lists.size(); ++i) {
        try {
            std::cout << "Список " << i << ": " << list_of_lists[i] << " , попытка delete_current() ... ";
            list_of_lists[i].delete_current();
            std::cout << "успешно, теперь: " << list_of_lists[i] << std::endl;
        } catch (const list_error& e) {
            std::cout << "Исключение: " << e.what() << " -> продолжаем работу" << std::endl;
        }
    }

    CircularList<int> int_list3;
    int_list3.insert_after(999);
    list_of_lists.push_back(int_list3);
    std::cout << "\nДобавлен новый список: " << list_of_lists.back() << std::endl;
}

void demo_throwing_during_insert() {
    std::cout << "\nИсключения при вставке (throwing_on_copy)\n";
    CircularList<throwing_on_copy> risky_list;
    throwing_on_copy::should_throw = true;
    try {
        risky_list.insert_after(throwing_on_copy(42));
    } catch (const std::runtime_error& e) {
        std::cout << "Поймано исключение при вставке: " << e.what() << std::endl;
        std::cout << "Список остался пустым: " << risky_list << std::endl;
    }
    throwing_on_copy::should_throw = false;
    risky_list.insert_after(throwing_on_copy(77));
    std::cout << "После успешной вставки: " << risky_list << std::endl;
}

void show_help() {
    std::cout << "\nУправление списками\n"
              << "  help              - показать справку\n"
              << "  list              - показать все списки (индексы)\n"
              << "  select <idx>      - выбрать текущий список (по индексу)\n"
              << "  new               - создать новый пустой список\n"
              << "  delete_list <idx> - удалить список по индексу\n"
              << "\nОперации с выбранным списком:\n"
              << "  insert_before <val> - вставить перед текущим (копия)\n"
              << "  insert_after  <val> - вставить после текущего (копия)\n"
              << "  move_before   <val> - вставить перед текущим (перемещение)\n"
              << "  move_after    <val> - вставить после текущего (перемещение)\n"
              << "  delete_current     - удалить текущий элемент\n"
              << "  next               - перейти к следующему элементу\n"
              << "  prev               - перейти к предыдущему\n"
              << "  current            - показать текущий элемент\n"
              << "  show               - показать весь выбранный список\n"
              << "  size               - размер выбранного списка\n"
              << "  quit               - выход\n"
              << std::endl;
}

void show_lists() {
    if (lists.empty()) {
        std::cout << "Нет ни одного списка.\n";
        return;
    }
    std::cout << "Список списков (индекс : содержимое):\n";
    for (size_t i = 0; i < lists.size(); ++i) {
        std::cout << "  " << i << " : " << lists[i] << " (size=" << lists[i].size() << ")\n";
    }
}
