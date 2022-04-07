#pragma once
#include <vector>
class Graph{
    public:
      Graph();
      Graph(int airPortSize);
      //return_type?? primsMST();
      //PNG * printRoutes();
      //vector<ListNode> bfs_traversal(string start_airport, string end_part);

    private:
        // class ListNode {
        //   public:   
        //     ListNode(){
                
        //     }
        //     ListNode(const T & ndata){ // check type of listnode (type maybe airports)
                
        //     }
        //   private:
        //     const T data;
        //     ListNode* next;
        //     ListNode* prev;
        //   };
        std::vector<std::vector<int>> route_matrix;
        std::unordered_map airport_map;

};