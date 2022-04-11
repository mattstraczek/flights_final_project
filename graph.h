#pragma once
#include <vector>
#include <unordered_map>
#include <string>
#include "routes.h"

class Graph{
    public:
      Graph();
      Graph(int airPortSize,  std::unordered_map<std::string, int> map_, std::vector<Routes> route_airports);
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
        std::vector<std::vector<int> > route_matrix;
        std::unordered_map<std::string, int> route_map; //route_map key == departure string + destination string
                                                        //eg. "ORDLAX"
};