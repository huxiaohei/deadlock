/*****************************************************************
 * Description
 * Email huxiaoheigame@gmail.com
 * Created on 2024/01/19
 * Copyright (c) 2023 虎小黑
 ****************************************************************/

#include "graph.h"
#include <iostream>

int main()
{
    std::cout << "Hello, World!" << std::endl;

    auto graph = std::make_shared<Graph>();
    graph->add_vertex(1);
    graph->add_vertex(2);
    graph->add_vertex(3);
    graph->add_vertex(4);
    graph->add_vertex(5);
    graph->add_vertex(6);

    graph->add_edge(1, 2);
    graph->add_edge(1, 3);
    graph->add_edge(2, 3);
    graph->add_edge(3, 4);
    graph->add_edge(4, 5);
    graph->add_edge(4, 6);
    graph->add_edge(5, 6);
    graph->add_edge(4, 1);

    graph->print_graph();

    std::list<uint64_t> path;
    graph->search_for_cycle(path);

    graph->remove_edge(3, 4);
    graph->print_graph();
    path.clear();
    graph->search_for_cycle(path);
    return 0;
}