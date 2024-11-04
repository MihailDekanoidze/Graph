#include <iostream>
#include "graph.hpp"
#include <map>

int main()
{
    try
    {  
        graph2 Table;
        Table.entering_table();

        #ifdef DEBUG
        Table.print();
        #endif

        char start = 0, end = 0;
        std::cout << "Start vertex :";
        std::cin >> start;
        std::cout << "End vertex :";
        std::cin >> end;
        
        std::cout << Table.the_best_path(start, end) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Something error" << '\n';
    }
}
