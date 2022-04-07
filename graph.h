#pragma once
#include <vector>
class Graph{
    public:
      Graph();
      Graph(int airPortSize);
      return_type?? primsMST();
      PNG * printRoutes();
      
    private:
        std::vector<std::vector<int>> route_matrix;
        std::unordered_map airport_map;

};