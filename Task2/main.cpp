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

        size_t mileage = 0;
        std::cout << "Enter the mileage: ";
        std::cin >> mileage;
        std::cout << "The city with lowest links in range " << mileage << " is: " << Table.cities_less_mil(mileage) << std::endl;
    }
    catch(const std::exception& e)
    {
        std::cerr << "Something error" << '\n';
    }
}
