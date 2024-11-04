#include "../graph.hpp"
#include <map>
#include <vector>
#include <iostream>
#include <cstdlib>
#include <fstream>

//#define DEBUG

graph2::graph2(): graph_table(), relative_search_table(), main_it(), link_it(), short_path(), all_links(), nvis_ver(){}

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

    size_t len = the_best_path(start, end);
    if (len == INF_LEN) 
    {
        std::cout << "The root was not defined\n";  
        return;
    }
    std::cout << "Shortest len is " << len << std::endl;             
    return;
}

size_t graph2::the_best_path(char start, char end)
{   
    #define SHORT_PATH
    
    #ifdef DEBUG
    print_search_table(); 
    #endif

    std::map<char, Node*> nodes_map = {};
    for (it1 ver = graph_table.begin(); ver != graph_table.end(); ver++)
    {
        Node* node1 = new Node;
        node1->name = ver->first;
        node1->links = ver->second;
        node1->vis = false;
        node1->longest_edge = INF_LEN + ver->first;
        nodes_map.insert(std::make_pair(ver->first, node1));
    }
    #ifdef DEBUG
    std::cout << "Size nodes_map = " << nodes_map.size() << std::endl;
    for (auto it = nodes_map.begin(); it != nodes_map.end(); it++)
        std::cout << "Key is " << it->first << " longest_edge is " << it->second->longest_edge << std::endl;
    #endif
    Node* first_node = nodes_map.find(start)->second;
    first_node->longest_edge = 0;
    first_node->prev = first_node;

    for (itnode_map ver = nodes_map.begin(); ver != nodes_map.end(); ver++)
    {
        #ifdef DEBUG
        std::cout << "Ver is " << ver->first << " the longest edge is " << ver->second->longest_edge << std::endl;
        #endif
        nvis_ver.insert(std::make_pair(ver->second->longest_edge, ver->second));
    }

    for (itnode_map ver = nodes_map.begin(); ver != nodes_map.end(); ver++) ver->second->curr_node_map = ver;
    for (itnvis_ver ver = nvis_ver.begin(); ver != nvis_ver.end(); ver++)   ver->second->curr_nvis_ver = ver;

    #ifdef DEBUG
    for (auto it = nodes_map.begin(); it != nodes_map.end(); it++)
        std::cout << "Key is " << it->first << " longest_edge is " << it->second->longest_edge << std::endl;
    nvis_ver_print(); 
    vis_ver_print();
    std::cout << "nvis is empty = " <<  nvis_ver.empty() << std::endl;
    #endif
    while (!nvis_ver.empty())
    {
        itnvis_ver curr_ver = nvis_ver.begin();

        #ifdef DEBUG
        std::cout << "///////////////////////////////////////\n" << "In while circle begin\n"; 
        nvis_ver_print(); 
        vis_ver_print();
        std::cout << "After firts print\n"; 
        #endif

        char neighbour_path = 0; 
        size_t min_narrow_place = curr_ver->second->longest_edge;
        for (it2 neighbour = curr_ver->second->links.begin(); neighbour != curr_ver->second->links.end(); neighbour++)
        {
            Node* curr_neig_node = nodes_map.find(neighbour->first)->second; 
            #ifdef DEBUG
            std::cout << "Curr_ver is " << curr_ver->second->name << " Curr neighbour is " << curr_neig_node->name << std::endl;
            #endif
            if (curr_neig_node->vis == false)
            {
                itnvis_ver curr_neig = curr_neig_node->curr_nvis_ver;
                #ifdef DEBUG
                std::cout << "neighbour is not vis " << "Curr_ver is " << curr_ver->second->name << " neighbour is " << neighbour->first <<std::endl;
                #endif
                if (curr_ver->second->name != neighbour->first)
                {
                    #ifdef DEBUG
                    std::cout << "Curr_ver_le is " << curr_ver->second->longest_edge << " neighbour_le is " << curr_neig->second->longest_edge  << std::endl;
                    #endif

                    size_t new_narrow_len = (curr_ver->second->longest_edge > neighbour->second) ? curr_ver->second->longest_edge : neighbour->second;

                    #ifdef DEBUG
                    std::cout << "New_narrow_len " << new_narrow_len << std::endl;
                    #endif
                    if (curr_neig->second->longest_edge > new_narrow_len)
                    {
                        #ifdef DEBUG
                        std::cout << "Before changes\n";
                        nvis_ver_print();
                        #endif

                        Node* new_node = new Node;
                        *new_node = *curr_neig->second; 

                        #ifdef DEBUG
                        printf("New node address: %p\n", new_node);
                        printf("New pair: (key %zu, value %c)\n", new_narrow_len, new_node->name);
                        printf("Old node address: %p\n", new_node);
                        printf("Old pair: (key %zu, value %c)\n", curr_neig->first, curr_neig->second->name);
                        #endif

                        itnvis_ver new_it = nvis_ver.insert(std::make_pair(new_narrow_len, curr_neig->second));
                        new_it->second->curr_nvis_ver = new_it;
                        new_it->second->prev = curr_ver->second;
                        new_it->second->longest_edge = new_narrow_len;
                        #ifdef DEBUG
                        std::cout << "I am insert a new ver: name is " << new_it->second->name << " le: " << new_it->second->longest_edge << std::endl;
                        std::cout << "After insert\n";
                        nvis_ver_print();
                        #endif
                        nvis_ver.erase(curr_neig);
                        #ifdef DEBUG
                        std::cout << "After erase\n";
                        nvis_ver_print();
                        std::cout << "New ver " << new_it->second->name << " has iterator " << new_it->second->curr_nvis_ver->second->name << std::endl;
                        std::cout << "New ver has le " << new_narrow_len << std::endl;
                        #endif
                    }
                    else
                    {
                        #ifdef DEBUG
                        std::cout << "Without changes\n";
                        #endif
                    }
                }
                else
                {
                    #ifdef DEBUG
                    std::cout << "Neighbour is " << neighbour->first << " and curr_ver is " << curr_ver->second->name << " too\n";
                    #endif
                }
                #ifdef DEBUG
                nvis_ver_print();
                #endif
            }
            else 
            {
                #ifdef DEBUG
                std::cout << "Neighbour " << curr_neig_node->name << " is already visited\n";
                #endif
            }
        }
        vis_ver.insert(std::make_pair(curr_ver->second->longest_edge, curr_ver->second));
        curr_ver->second->vis = true;
        nvis_ver.erase(curr_ver);

        #ifdef DEBUG
        std::cout << "Before second print\n"; 
        nvis_ver_print(); 
        vis_ver_print();   
        std::cout << "After second print\n"; 
        std::cout << "**********************************" << std::endl;
        #endif
    }
    #ifdef DEBUG
    std::cout << "The end\'s name is : " << nodes_map.find(end)->second->name << 
    " and the prev is : " <<  nodes_map.find(end)->second->prev->name << std::endl;
    #endif

    auto it = nodes_map.find(end)->second;
    std::vector<char> path[nodes_map.size()];
    path->push_back(end);
    do
    {
        it = it->prev;
        path->push_back(it->name);
    } while (it->name != start);

    #ifdef DEBUG
    std::cout << "Path source:\n";
    size_t iterator = 0;
    for (auto it = path->begin(); it != path->end(); it++, iterator++) std::cout << "Path[" << iterator << "] = " << *it << std:: endl;
    #endif
    std::cout << "Path :\n" << start; 
    for (auto it = path->rbegin() + 1; it != path->rend(); it++) std::cout << " -> " << *it;
    std::cout << std::endl; 

    return nodes_map.find(end)->second->longest_edge;
}

void graph2::print_search_table()
{
    std::cout << std::endl << "Search table list: " << std::endl;

    for (itrst search_it = relative_search_table.begin(); search_it != relative_search_table.end(); search_it++)
        std::cout << search_it->first << " has len " << search_it->second.longest_edge << " and vis " << search_it->second.vis << std::endl;
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

void graph2::nvis_ver_print()
{
    std::cout << "Nvis_ver printing" << std::endl;
    size_t iterator = 0;
    for (auto it = nvis_ver.begin(); it != nvis_ver.end(); it++, iterator++)
    {
        //std::cout << "Iterator " << iterator << std::endl;
        std::cout << "Key is " << it->first << " city is " << it->second->name << std::endl;
    }
    std::cout << std::endl;
}

void graph2::vis_ver_print()
{
    std::cout << "Vis_ver printing" << std::endl;
    for (auto it = vis_ver.begin(); it != vis_ver.end(); it++)
    {
        std::cout << "Key is " << it->first << " city is " << it->second->name << std::endl;
    }
    std::cout << std::endl;
}