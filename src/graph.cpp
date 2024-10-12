#include "../graph.hpp"
#include <map>
#include <iostream>
#include <cstdlib>


graph2::graph2(): graph_table(), search_table(), main_it(), link_it(){}

void graph2::add_link(char city_1, char city_2, size_t length)
{
    //std::cout << "city_1 = " << city_a << std::endl;
    //std::cout << "city_2 = " << city_b << std::endl;

    graph_table[city_1][city_2] = graph_table[city_2][city_1] = length;
    graph_table[city_1][city_1] = graph_table[city_2][city_2] = 0;
}

void graph2::shortest_path_task()
{
    std::cout << "Enter start vertex: ";
    char start = 0;
    std::cin >> start;
    std::cout << "Enter end vertex: ";
    char end = 0;
    std::cin >> end;

    size_t len = short_path(start, end);
    if (len == INF_LEN) 
    {
        std::cout << "The root was not defined\n";  
        return;
    }
    std::cout << "Shortest len is " << len << std::endl;             
    return;
}

size_t graph2::short_path(char start, char end)
{   
    graph graph_copy = graph_table;
    it1 curr = graph_copy.find(start);

    for (main_it = graph_copy.begin(); main_it != graph_copy.end(); main_it++) 
    {
        Node* new_node = new Node;
        new_node->len = INF_LEN;
        new_node->links = main_it->second;
        new_node->vis = false;
        search_table[main_it->first] = *new_node;
        delete new_node;
    }    
    search_table.find(curr->first)->second.len = 0;

    bool is_continue = true;
    
    #ifdef DEBUG
    print_search_table(); 
    #endif

    while (is_continue)
    {          
        is_continue = false;
        its curr_ver = search_table.begin();

        #ifdef DEBUG
        std::cout << "In while circle\n"; 
        #endif

        for (its search_it = search_table.begin(); search_it != search_table.end(); search_it++)
        {
            if (search_it->second.vis == false)
            {
                is_continue = true;
                curr_ver = search_it;
                
                #ifdef DEBUG
                std:: cout<< "The " << search_it->first << " len: " << search_it->second.len << " and vis " << search_it->second.vis << std::endl; 
                #endif
            }
        }
        if (!is_continue) break;

        for (its search_it = search_table.begin(); search_it != search_table.end(); search_it++)
        {
            if (search_it->second.vis == false)
            {
                is_continue = true;
                curr_ver = (curr_ver->second.len > search_it->second.len) ? search_it : curr_ver;

                #ifdef DEBUG
                std:: cout<< "The " << search_it->first << " len: " << search_it->second.len << " and vis " << search_it->second.vis << std::endl; 
                #endif
            }
        }

        #ifdef DEBUG
        std::cout << "Curr ver is " << curr_ver->first << std::endl;
        #endif

        for (it2 neighbour = curr_ver->second.links.begin(); neighbour != curr_ver->second.links.end(); neighbour++)
        {
            its curr_neig = search_table.find(neighbour->first);
            if (!curr_neig->second.vis) 
            {
                if (curr_ver->second.len != INF_LEN) 
                {
                    size_t new_len = neighbour->second + curr_ver->second.len;
                    curr_neig->second.len = (curr_neig->second.len > new_len) ? new_len : curr_neig->second.len;
                }
            }
        } 

        curr_ver->second.vis = true;

        #ifdef DEBUG
        print_search_table();
        #endif
    }
    return search_table.find(end)->second.len;
}

void graph2::print_search_table()
{
    std::cout << std::endl << "Search table list: " << std::endl;

    for (its search_it = search_table.begin(); search_it != search_table.end(); search_it++)
        std::cout << search_it->first << " has len " << search_it->second.len << " and vis " << search_it->second.vis << std::endl;
    std::cout << std::endl;
}

void graph2::print()
{   
    for (main_it = graph_table.begin(); main_it != graph_table.end(); main_it++)
    {
        for (link_it = main_it->second.begin(); link_it != main_it->second.end(); link_it++)
        {
            std::cout << "Link between " << main_it->first << " and " << link_it->first 
            << " is " << link_it->second << std::endl;
        }
    }
    std::cout << " ";
    for (main_it = graph_table.begin(); main_it != graph_table.end(); main_it++) std::cout << " " << main_it->first;
    std::cout << std::endl;
    for (main_it = graph_table.begin(); main_it != graph_table.end(); main_it++)
    {
        std::cout << main_it->first;
        for (link_it = (main_it->second).begin(); link_it != (main_it->second).end(); link_it++) std::cout << " " << link_it->second;
        std::cout << std::endl;
    }
}

