#include "../graph.hpp"
#include <map>
#include <iostream>
#include <cstdlib>
#include <fstream>

//#define DEBUG

graph2::graph2(): graph_table(), relative_search_table(), main_it(), link_it(), short_path(), all_links(){}

void graph2::entering_table()
{
    std::cout << "Enter links number: ";
    size_t links_number = 0;
    std::cin >> links_number;

    for (size_t i = 0; i < links_number; i++)
    {
        static char city_1 = 0, city_2 = 0;
        static size_t length = 0;
        std::cin >> city_1 >> city_2 >> length;
        
        graph_table[city_1][city_2] = graph_table[city_2][city_1] = length;
        graph_table[city_1][city_1] = graph_table[city_2][city_2] = 0;
    }
}

void graph2::shortest_path_task()
{
    std::cout << "Enter start vertex: ";
    char start = 0;
    std::cin >> start;
    std::cout << "Enter end vertex: ";
    char end = 0;
    std::cin >> end;

    size_t len = short_path_len(start, end);
    if (len == INF_LEN) 
    {
        std::cout << "The root was not defined\n";  
        return;
    }
    std::cout << "Shortest len is " << len << std::endl;             
    return;
}

size_t graph2::short_path_len(char start, char end)
{   
    #define SHORT_PATH
    it1 curr = graph_table.find(start);

    if(!relative_search_table.empty())
    {
        for (itrst ver = relative_search_table.begin(); ver != relative_search_table.end(); ver++) 
        {
            ver->second.vis = 0;
            ver->second.len = INF_LEN;
        }
    }
    else 
    {
        for (main_it = graph_table.begin(); main_it != graph_table.end(); main_it++) 
        {
            Node* new_node = new Node;
            new_node->len = INF_LEN;
            new_node->links = main_it->second;
            new_node->vis = false;
            relative_search_table[main_it->first] = *new_node;
            delete new_node;
        }    
    }

    relative_search_table.find(curr->first)->second.len = 0;

    bool is_continue = true;
    
    #ifdef DEBUG
    print_search_table(); 
    #endif

    std::map<char, char> edges = {std::make_pair(start, start)};

    while (is_continue)
    {          
        is_continue = false;
        itrst curr_ver = relative_search_table.begin();

        #ifdef DEBUG
        std::cout << "In while circle\n"; 
        #endif

        for (itrst search_it = relative_search_table.begin(); search_it != relative_search_table.end(); search_it++)
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

        for (itrst search_it = relative_search_table.begin(); search_it != relative_search_table.end(); search_it++)
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

        for (it2 neighbour = curr_ver->second.links.begin(); neighbour != curr_ver->second.links.end(); neighbour++)
        {
            itrst curr_neig = relative_search_table.find(neighbour->first);    
            #ifdef DEBUG
            std::cout << "Curr ver is " << curr_ver->first << " curr_neig " << curr_neig->first << std::endl;
            #endif
            if (!curr_neig->second.vis) 
            {
                if (curr_ver->second.len != INF_LEN) 
                {
                    size_t new_len = neighbour->second + curr_ver->second.len;
                    if (curr_neig->second.len > new_len)
                    {
                        #ifdef DEBUG
                        std::cout << "Chaged curr ver is " << curr_ver->first << " curr_neig " << curr_neig->first << std::endl;
                        #endif
                        curr_neig->second.len = new_len;

                        pit = edges.find(curr_neig->first);

                        #ifdef DEBUG
                        std::cout<<"Curr pit is" << pit->first << std::endl;
                        #endif

                        if(pit->first == curr_neig->first) pit->second = curr_ver->first;
                        else edges.insert(std::make_pair(curr_neig->first, curr_ver->first));
                    }
                }
                #ifdef DEBUG
                std::cout << "\nEdges\n";
                for (pit = edges.begin(); pit != edges.end(); pit++)
                    std::cout << "Key is " << pit->first << " val is " << pit->second << std::endl;
                std::cout << std::endl;
                #endif
            }
        }

        curr_ver->second.vis = true;

        #ifdef DEBUG
        print_search_table();
        #endif
    }

    size_t searched_len = relative_search_table.find(end)->second.len;
    char path_vex = end; 

    while (path_vex != start)
    {
        pit  = edges.find(path_vex);
        short_part_edges.insert(*pit);
        path_vex = pit->second;
    }

    #ifdef DEBUG
    std::cout << "\nShort_path_edges\n";
    for (pit = short_part_edges.begin(); pit != short_part_edges.end(); pit++)
        std::cout << "Key is " << pit->first << " val is " << pit->second << std::endl;
    std::cout << std::endl;
    #endif

    return searched_len;
}

void graph2::print_search_table()
{
    std::cout << std::endl << "Search table list: " << std::endl;

    for (itrst search_it = relative_search_table.begin(); search_it != relative_search_table.end(); search_it++)
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

void graph2::graph_image_ctor()
{
    std::ofstream graph_info;

    graph_info.open("graph_info.dot");
    graph_info << "digraph G\n" << "{\n" << "rankdir=TB;\n" << "node[color=\"red\"shape=\"rectangle\",style=\"rounded\"];\n";
    for (it1 ver = graph_table.begin(); ver != graph_table.end(); ver++)
    {
        for (it2 link_ver = ver->second.begin(); link_ver != ver->second.end(); link_ver++)
        {
            #ifdef DEBUG
            std::cout << "Ver is " << ver->first << " and link_ver is " << link_ver->first << std::endl;
              
            #endif
            if (link_ver->first != ver->first) 
            {
                bool link_already_exists = false;
                for (auto it1 = all_links.begin(); it1 != all_links.end(); it1++)
                {
                    if (((it1->first == ver->first)      && (it1->second == link_ver->first)) 
                    ||  ((it1->first == link_ver->first) && (it1->second == ver->first))) 
                    {
                        link_already_exists = true;
                    }
                }
                if(!link_already_exists)
                {
                    graph_info << ver->first << " -> " << link_ver->first << "[dir = both][label = \" " << link_ver->second << " \"];" << std::endl; 
                    all_links.insert(std::make_pair(ver->first, link_ver->first));
                }
            }
            #ifdef DEBUG
            map_print();
            std::cout << std::endl;
            #endif
        }
    }
    graph_info << "}" << '\0';
    graph_info.close();
    system("dot graph_info.dot -T png -o graph.png");
}

void graph2::map_print()
{
    for (auto it1 = all_links.begin(); it1 != all_links.end(); it1++)
        std::cout << "Key = " << it1->first << " value " << it1->second << std::endl;
}

char graph2::cities_less_mil(size_t mileage)
{
    size_t lowest_cities_in_range = INF_CITIES_NUMBER;
    char found_city = 0;
    for (it1 ver = graph_table.begin(); ver != graph_table.end(); ver++)
    {
        size_t curr_cities_in_range = 0;
        short_path_len(ver->first, ver->first);
        for (itrst curr_city = relative_search_table.begin(); curr_city != relative_search_table.end(); curr_city++)
        {
            if (curr_city->second.len <= mileage) curr_cities_in_range++;
        }
        if (lowest_cities_in_range >= curr_cities_in_range)
        {
            lowest_cities_in_range = curr_cities_in_range;
            found_city = ver->first;
        }
    }

    return found_city;
}
