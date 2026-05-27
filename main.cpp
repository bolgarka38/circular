#include <iostream>
#include <string>
#include <sstream>
#include "test.hpp"

int main() {
    setlocale(LC_ALL,"Russian");
    demo_basic_operations();
    demo_list_of_lists();
    demo_throwing_during_insert();

    std::cout << "\nВсе тесты завершены.\n";

    int current_idx = -1;  // индекс выбранного списка
    show_help();

    std::string line;
    while (true) {
        std::cout << "\n> ";
        std::getline(std::cin, line);
        if (line.empty()) continue;

        std::istringstream iss(line);
        std::string cmd;
        iss >> cmd;

        if (cmd == "quit" || cmd == "exit") {
            break;
        }
        else if (cmd == "help") {
            show_help();
        }
        else if (cmd == "list") {
            show_lists();
        }
        else if (cmd == "new") {
            lists.push_back(CircularList<int>());
            std::cout << "Создан новый пустой список с индексом " << lists.size() - 1 << std::endl;
        }
        else if (cmd == "delete_list") {
            int idx;
            if (!(iss >> idx)) {
                std::cout << "Ошибка: укажите индекс списка для удаления.\n";
                continue;
            }
            if (idx < 0 || idx >= (int)lists.size()) {
                std::cout << "Неверный индекс.\n";
                continue;
            }
            if (current_idx == idx) {
                current_idx = -1;
            }
            lists.erase(lists.begin() + idx);
            std::cout << "Список удалён.\n";
        }
        else if (cmd == "select") {
            int idx;
            if (!(iss >> idx)) {
                std::cout << "Ошибка: укажите индекс списка.\n";
                continue;
            }
            if (idx < 0 || idx >= (int)lists.size()) {
                std::cout << "Неверный индекс. Используйте 'list' для просмотра.\n";
            } else {
                current_idx = idx;
                std::cout << "Выбран список " << current_idx << ": " << lists[current_idx] << std::endl;
            }
        }
        else {
            // Все остальные команды требуют выбранного списка
            if (current_idx == -1) {
                std::cout << "Сначала выберите список командой 'select <idx>'\n";
                continue;
            }
            auto& lst = lists[current_idx];

            try {
                if (cmd == "insert_before") {
                    int val;
                    if (!(iss >> val)) throw std::runtime_error("не указано значение");
                    lst.insert_before(val);
                    std::cout << "Вставлено " << val << " перед текущим. Список: " << lst << std::endl;
                }
                else if (cmd == "insert_after") {
                    int val;
                    if (!(iss >> val)) throw std::runtime_error("не указано значение");
                    lst.insert_after(val);
                    std::cout << "Вставлено " << val << " после текущего. Список: " << lst << std::endl;
                }
                else if (cmd == "move_before") {
                    int val;
                    if (!(iss >> val)) throw std::runtime_error("не указано значение");
                    int tmp = val;  // демонстрация перемещения: создаём временный объект
                    lst.insert_before(std::move(tmp));
                    std::cout << "Вставлено перемещением " << val << " перед текущим. Список: " << lst << std::endl;
                }
                else if (cmd == "move_after") {
                    int val;
                    if (!(iss >> val)) throw std::runtime_error("не указано значение");
                    int tmp = val;
                    lst.insert_after(std::move(tmp));
                    std::cout << "Вставлено перемещением " << val << " после текущего. Список: " << lst << std::endl;
                }
                else if (cmd == "delete_current") {
                    lst.delete_current();
                    std::cout << "Текущий элемент удалён. Список: " << lst << std::endl;
                }
                else if (cmd == "next") {
                    lst.next();
                    auto* cur = lst.get_current();
                    if (cur) std::cout << "Переход к следующему. Текущий элемент: " << *cur << std::endl;
                    else std::cout << "Список стал пустым.\n";
                }
                else if (cmd == "prev") {
                    lst.prev();
                    auto* cur = lst.get_current();
                    if (cur) std::cout << "Переход к предыдущему. Текущий элемент: " << *cur << std::endl;
                    else std::cout << "Список стал пустым.\n";
                }
                else if (cmd == "current") {
                    auto* cur = lst.get_current();
                    if (cur) std::cout << "Текущий элемент: " << *cur << std::endl;
                    else std::cout << "Список пуст, нет текущего элемента.\n";
                }
                else if (cmd == "show") {
                    std::cout << "Список " << current_idx << ": " << lst << std::endl;
                }
                else if (cmd == "size") {
                    std::cout << "Размер списка: " << lst.size() << std::endl;
                }
                else {
                    std::cout << "Неизвестная команда. Введите 'help'.\n";
                }
            } catch (const list_error& e) {
                std::cout << "Ошибка списка: " << e.what() << " (операция пропущена, продолжаем работу)\n";
            } catch (const std::exception& e) {
                std::cout << "Ошибка: " << e.what() << std::endl;
            }
            return 0;
        }
    }
    return 0;
}

