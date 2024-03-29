#include <iostream>
#include <stdio.h>
#include <set>
#include <queue>
#include <string>
#include <tuple>
#include <chrono>

using std::string;
using std::pair;

class Node{
public:
    std::pair<int,int> pos;
    string route;
    Node(const pair<int,int> p, string d): pos(p), route(d){}
};

class Labyrinth {
public:
    int size_y;
    int size_x;
    int start_y;
    int start_x;
    int end_x;
    int end_y;
    bool** map;
    std::set<std::pair<int,int> > visited;
    std::queue<Node> node_queue;

    Labyrinth(){
        scanf("%d %d %d %d %d %d ", &size_x, &size_y, &start_x, &start_y,
              &end_x, &end_y);
        map = new bool* [size_y];
        for (int i = size_y - 1; i >= 0; --i) {
          map[i] = new bool [size_x];
            for (int j = 0; j < size_x; ++j) {
                char cell_char;
                scanf("%c ", &cell_char);
                if(cell_char == '1') map[i][j] = true;
                else map[i][j] = false;
            }
        }
        if(!map[start_y][start_x]) {
            std::pair<int,int> start(start_y,start_x);
            node_queue.emplace(start, "");
            visited.emplace(start);
        }
    }

    void PrintLabyrinth(){
        for(int i = size_y - 1; i >= 0; --i){
            for(int j = 0; j < size_x; ++j){
                char c = map[i][j] ? '1' : '0';
                printf("%c ", c);
            }
            printf("\n");
        }
    }

    string Solve(){
        while (!node_queue.empty()){
            Node current = node_queue.front();
            node_queue.pop();
            if(current.pos.first == end_y && current.pos.second == end_x) return current.route;
            AddNeighborsToQueue(current);
        }
        return "-";
    }

    void AddNeighborsToQueue(const Node& node){
        if(node.pos.first > 0){
            std::pair<int,int> down_position(node.pos.first - 1, node.pos.second);
            if(!map[down_position.first][down_position.second]) {
                if (visited.find(down_position) == visited.end()) {
                    visited.emplace(down_position);
                    node_queue.emplace(down_position, node.route + "D"); //TODO(semylevy) improve this.
                }
            }
        }
        if(node.pos.first + 1 < size_y) {
            std::pair<int,int> up_position(node.pos.first + 1, node.pos.second);
            if(!map[up_position.first][up_position.second]) {
                if (visited.find(up_position) == visited.end()) {
                    visited.emplace(up_position);
                    node_queue.emplace(up_position, node.route + "U"); //TODO(semylevy) improve this.
                }
            }
        }
        if(node.pos.second > 0){
            std::pair<int,int> left_position(node.pos.first, node.pos.second - 1);
            if(!map[left_position.first][left_position.second]) {
                if (visited.find(left_position) == visited.end()) {
                    visited.emplace(left_position);
                    node_queue.emplace(left_position, node.route + "L"); //TODO(semylevy) improve this.
                }
            }
        }
        if(node.pos.second + 1 < size_x){
          std::pair<int,int> right_position(node.pos.first, node.pos.second + 1);
          if(!map[right_position.first][right_position.second]) {
              if (visited.find(right_position) == visited.end()) {
                  visited.emplace(right_position);
                  node_queue.emplace(right_position, node.route + "R"); //TODO(semylevy) improve this.
              }
          }
        }
    }

};

int main() {
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    Labyrinth labyrinth;
    //labyrinth.PrintLabyrinth();
    string solution = labyrinth.Solve();
    std::cout << solution << "\n";
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
    std::cout << "Time is: " << duration << "us" << "\n";
}
