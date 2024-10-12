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
        Node():len(), vis(), links(){};
    };  
    
    std::map<char, std::map<char, size_t>> graph_table;
    std::map<char, Node> search_table;
    std::map<char, std::map<char, size_t>>::iterator main_it;
    std::map<char, size_t>::iterator link_it;

    typedef std::map<char, std::map<char, size_t>> graph;
    typedef std::map<char, size_t> link;
    typedef std::map<char, std::map<char, size_t>>::iterator it1;
    typedef std::map<char, size_t>::iterator it2;
    typedef std::map<char, Node>::iterator its;

    static const size_t INF_LEN = 0xAB0BAB0BAB0BAB0B;
public:
    graph2();
    void add_link(char, char, size_t);
    size_t short_path(char, char);
    void shortest_path_task();
    void print();
    void print_search_table();
    ~graph2(){};
};

#endif //GRAPH_HPP