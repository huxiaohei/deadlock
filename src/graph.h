/*****************************************************************
 * Description
 * Email huxiaoheigame@gmail.com
 * Created on 2024/01/19
 * Copyright (c) 2023 虎小黑
 ****************************************************************/

#include <iostream>
#include <list>
#include <memory>
#include <pthread.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>

class Graph
{
  public:
    typedef struct vertex
    {
        vertex(pthread_t thread_id) : id(thread_id){};
        pthread_t id;
        uint64_t wait_lock = 0;
        std::unordered_set<uint64_t> locks;
        std::unordered_set<pthread_t> nexts;
    } vertex_t;

    typedef std::shared_ptr<vertex_t> vertex_ptr;

  public:
    Graph();
    ~Graph();

  public:
    void add_vertex(pthread_t id);
    void add_vertex(vertex_ptr v);
    void remove_vertex(vertex_ptr v);
    void remove_vertex(pthread_t id);
    void add_edge(vertex_ptr src, vertex_ptr dst);
    void add_edge(pthread_t src, pthread_t dst);
    void remove_edge(vertex_ptr src, vertex_ptr dst);
    void remove_edge(pthread_t src, pthread_t dst);
    vertex_ptr get_vertex(pthread_t id);
    void search_for_cycle(std::list<uint64_t> &path);
    void print_graph();

  public:
    std::unordered_map<pthread_t, vertex_ptr> vertexs;

  private:
    bool dfs(pthread_t id, std::unordered_set<uint64_t> &visited, std::list<uint64_t> &path);
};