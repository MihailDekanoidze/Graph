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
        size_t len;
        bool vis;
        std::map<char, size_t> links;           //TODO:Pointers?
        Node(): links(){};
    };  
    
    std::map        <char, std::map<char, size_t>>              graph_table;
    std::map        <char, Node>                                relative_search_table;
    std::map        <char, std::map<char, size_t>>::iterator    main_it;
    std::map        <char, size_t>::iterator                    link_it;
    std::vector     <char>                                      short_path;
    std::multimap   <char, char>                                all_links;
    std::map        <char, char>                                short_part_edges;
    std::map        <char, char>::iterator                      pit;
       
    typedef std::map<char, std::map<char, size_t>> graph;
    typedef std::map<char, size_t> link;
    typedef std::map<char, std::map<char, size_t>>::iterator it1;
    typedef std::map<char, size_t>::iterator it2;
    typedef std::map<char, Node>::iterator itrst;

    static const size_t INF_LEN = 0xAB0BAB0BAB0BAB0B;
    static const size_t INF_CITIES_NUMBER = 0xABABABABABABABAB;
public:
    graph2();
    void entering_table();
    size_t short_path_len(char, char);
    char cities_less_mil(size_t mileage);
    void shortest_path_task();
    void print();
    void print_search_table();
    void graph_image_ctor();
    void map_print();
    ~graph2(){};
};

#endif //GRAPH_HPP