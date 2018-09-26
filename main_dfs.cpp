#include <iostream>
#include <stdio.h>
#include <set>
#include <queue>
#include <string>
#include <tuple>
#include <chrono>
#include <stack>
#include <unordered_map>

using std::string;
using std::pair;

class Node{
public:
    std::pair<int,int> pos;
    int direction_id;
    Node(const pair<int,int> p, const int d): pos(p), direction_id(d){}
};

class Labyrinth {
public:
    int size_y;
    int size_x;
    int start_y;
    int start_x;
    int end_x;
    int end_y;
    int current_id;
    bool** map;
    string upside_down_result;
    std::unordered_map<int, pair<char, int> > directions;
    std::set<std::pair<int,int> > visited;
    std::stack<Node> node_queue;

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
        current_id = 0;
        if(!map[start_y][start_x]) {
            std::pair<int,int> start(start_y,start_x);
            node_queue.emplace(start, current_id);
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

    void Solve(){
        while (!node_queue.empty()){
            Node current = node_queue.top();
            node_queue.pop();
            if(current.pos.first == end_y && current.pos.second == end_x) return GetSteps(current.direction_id);
            AddNeighborsToQueue(current);
        }
        upside_down_result = "-";
    }

    void GetSteps(const int id) {
        upside_down_result = "";
        upside_down_result.reserve(current_id);
        int traverse = id;
        while (traverse != 0) {
            upside_down_result += (*directions.find(traverse)).second.first;
            traverse = (*directions.find(traverse)).second.second;
        }
    }

    void PrintResult(){
        for(int i = upside_down_result.size() - 1; i >= 0; --i){
            printf("%c", upside_down_result[i]);
        }
        printf("\n");
    }

    void AddNeighborsToQueue(const Node& node){
        if(node.pos.first > 0){
            std::pair<int,int> down_position(node.pos.first - 1, node.pos.second);
            if(!map[down_position.first][down_position.second]) {
                if (visited.find(down_position) == visited.end()) {
                    visited.emplace(down_position);
                    node_queue.emplace(down_position, ++current_id); //TODO(semylevy) improve this.
                    directions.insert({current_id, {'D', node.direction_id}});
                }
            }
        }
        if(node.pos.first + 1 < size_y) {
            std::pair<int,int> up_position(node.pos.first + 1, node.pos.second);
            if(!map[up_position.first][up_position.second]) {
                if (visited.find(up_position) == visited.end()) {
                    visited.emplace(up_position);
                    node_queue.emplace(up_position, ++current_id); //TODO(semylevy) improve this.
                    directions.insert({current_id, {'U', node.direction_id}});
                }
            }
        }
        if(node.pos.second > 0){
            std::pair<int,int> left_position(node.pos.first, node.pos.second - 1);
            if(!map[left_position.first][left_position.second]) {
                if (visited.find(left_position) == visited.end()) {
                    visited.emplace(left_position);
                    node_queue.emplace(left_position, ++current_id); //TODO(semylevy) improve this.
                    directions.insert({current_id, {'L', node.direction_id}});
                }
            }
        }
        if(node.pos.second + 1 < size_x){
          std::pair<int,int> right_position(node.pos.first, node.pos.second + 1);
          if(!map[right_position.first][right_position.second]) {
              if (visited.find(right_position) == visited.end()) {
                  visited.emplace(right_position);
                  node_queue.emplace(right_position, ++current_id); //TODO(semylevy) improve this.
                  directions.insert({current_id, {'R', node.direction_id}});
              }
          }
        }
    }

};

int main() {
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    Labyrinth labyrinth;
    //labyrinth.PrintLabyrinth();
    labyrinth.Solve();
    labyrinth.PrintResult();
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
    std::cout << "Time is: " << duration << "us" << "\n";
}
