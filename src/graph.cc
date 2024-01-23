/*****************************************************************
 * Description
 * Email huxiaoheigame@gmail.com
 * Created on 2024/01/19
 * Copyright (c) 2023 虎小黑
 ****************************************************************/

#ifndef DEADLOCK_GRAPH_H_
#define DEADLOCK_GRAPH_H_

#include "graph.h"

Graph::Graph()
{
}

Graph::~Graph()
{
}

void Graph::add_vertex(pthread_t thread_id)
{
    if (vertexs.find(thread_id) == vertexs.end())
    {
        vertex_ptr v = std::make_shared<vertex_t>(thread_id);
        vertexs.insert(std::make_pair(thread_id, v));
    }
}

void Graph::add_vertex(vertex_ptr v)
{
    if (vertexs.find(v->id) == vertexs.end())
    {
        vertexs.insert(std::make_pair(v->id, v));
    }
}

void Graph::remove_vertex(vertex_ptr v)
{
    remove_vertex(v->id);
}

void Graph::remove_vertex(pthread_t id)
{
    if (vertexs.find(id) == vertexs.end())
    {
        return;
    }
    for (auto it = vertexs.begin(); it != vertexs.end(); it++)
    {
        it->second->nexts.erase(id);
    }
    vertexs.erase(id);
}

void Graph::add_edge(vertex_ptr src, vertex_ptr dst)
{
    add_vertex(src);
    add_vertex(dst);
    vertexs[src->id]->nexts.insert(dst->id);
}

void Graph::add_edge(pthread_t src, pthread_t dst)
{
    add_vertex(src);
    add_vertex(dst);
    vertexs[src]->nexts.insert(dst);
}

void Graph::remove_edge(vertex_ptr src, vertex_ptr dst)
{
    if (vertexs.find(src->id) != vertexs.end())
    {
        src->nexts.erase(dst->id);
    }
}

void Graph::remove_edge(pthread_t src, pthread_t dst)
{
    if (vertexs.find(src) != vertexs.end())
    {
        vertexs[src]->nexts.erase(dst);
    }
}

Graph::vertex_ptr Graph::get_vertex(pthread_t id)
{
    add_vertex(id);
    return vertexs[id];
}

bool Graph::dfs(pthread_t id, std::unordered_set<uint64_t> &visited, std::list<uint64_t> &path)
{
    if (visited.find(id) != visited.end())
    {
        path.push_back(id);
        return true;
    }
    visited.insert(id);
    path.push_back(id);

    for (auto it = vertexs[id]->nexts.begin(); it != vertexs[id]->nexts.end(); it++)
    {
        if (dfs(*it, visited, path))
        {
            return true;
        }
    }
    path.pop_back();
    visited.erase(id);
    return false;
}

void Graph::search_for_cycle(std::list<uint64_t> &path)
{
    std::unordered_set<uint64_t> visited;
    for (auto it : vertexs)
    {
        visited.clear();
        path.clear();
        if (!dfs(it.first, visited, path))
        {
            continue;
        }
        else
        {
            std::cout << "cycle found [";
            for (auto it2 = path.begin(); it2 != path.end(); it2++)
            {
                std::cout << *it2 << " ";
            }
            std::cout << "]" << std::endl;
            break;
        }
    }
}

void Graph::print_graph()
{
    for (auto &it : vertexs)
    {
        std::cout << it.first << " -> ";
        for (auto it2 : it.second->nexts)
        {
            std::cout << it2 << " ";
        }
        std::cout << std::endl;
    }
}

#endif // DEADLOCK_GRAPH_H_
