#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <cstdio>
#include <iostream>
#include <vector>
#include <map>
#include <cmath>

class graph2
{
private:
    struct Node
    {
        char name;
        size_t longest_edge;
        bool vis;
        std::map<size_t, Node*>::iterator curr_nvis_ver;
        std::map<char, Node*>  ::iterator curr_node_map;
        Node* prev;
        std::map<char, size_t> links;           //TODO:Pointers?
        Node():links(){};
    };  

    struct Tree
    {
        Node* start_node;
    };
    


    std::map        <char, std::map<char, size_t>>              graph_table;
    std::map        <char, Node>                                relative_search_table;
    std::map        <char, std::map<char, size_t>>::iterator    main_it;
    std::map        <char, size_t>::iterator                    link_it;
    std::vector     <char>                                      short_path;
    std::multimap   <char, char>                                all_links;
    std::map        <char, char>                                short_part_edges;
    std::map        <char, char>::iterator                      pit;
    std::multimap   <size_t, Node*>                             vis_ver;
    std::multimap   <size_t, Node*>                             nvis_ver;
       
    typedef std::map<char, std::map<char, size_t>>      graph;
    typedef std::map<char, size_t>                      link;
    typedef std::map<char, std::map<char, size_t>>::    iterator it1;
    typedef std::map<char, size_t>::iterator            it2;
    typedef std::map<char, Node>::iterator              itrst;
    typedef std::map<size_t, Node*>::iterator           itnvis_ver;
    typedef std::map<char, Node*>::iterator             itnode_map;
    typedef std::pair<size_t, Node*>                    itneig;

    static const size_t INF_LEN = 0xAB0BAB0BAB0BAB0B;
    static const size_t INF_CITIES_NUMBER = 0xABABABABABABABAB;
public:
    graph2();
    void entering_table();
    size_t the_best_path(char, char);
    char cities_less_mil(size_t mileage);
    void shortest_path_task();
    void print();
    void print_search_table();
    void graph_image_ctor();
    void map_print();
    void nvis_ver_print();
    void vis_ver_print();
    ~graph2(){};
};

#endif //GRAPH_HPP