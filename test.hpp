#ifndef TEST_HPP_INCLUDED
#define TEST_HPP_INCLUDED

#include <iostream>
#include <deque>
#include "circular.hpp"
#include "test_int.hpp"

static std::deque<CircularList<int>> lists;

void demo_basic_operations();
void demo_list_of_lists();
void demo_throwing_during_insert();

void show_help();
void show_lists();

#endif // TEST_HPP_INCLUDED
