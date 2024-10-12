#include <iostream>
#include "graph.hpp"
#include <map>

int main()
{
    std::cout << "Enter links number: ";
    size_t links_number = 0;
    std::cin >> links_number;

    try
    {
        graph2 Table;
        for (size_t i = 0; i < links_number; i++)
        {
            static char city_1 = 0, city_2 = 0;
            static size_t length = 0;

            std::cin >> city_1 >> city_2 >> length;
            Table.add_link(city_1, city_2, length);
        }
        #ifdef DEBUG
        Table.print();
        #endif
        Table.shortest_path_task();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
}
