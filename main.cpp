#include <iostream>
#include <stdio.h>
#include <set>
#include <queue>
#include <string>
#include <tuple>
#include <chrono>
#include <bitset>

#define MAX_SIZE 50
#define DOWN_POS 0
#define UP_POS 1
#define RIGHT_POS 2
#define LEFT_POS 3

char letters[4] = {'D', 'U', 'R', 'L'};

using std::string;
using std::pair;
using std::bitset;

typedef std::priority_queue<Node, std::vector<Node>, OrderByWeight> NodeQueue;
typedef std::vector<bitset<MAX_SIZE>> bitset_vector;
j
class Node{
public:
    std::pair<int,int> pos;
    int weight;
    int step_number;
    int current_index;
    bitset_vector route;
    Node(const int y, const int x, const int w, bitset_vector d, const int steps, const int index): pos(std::make_pair(y,x)), weight(w), route(d), step_number(steps), current_index(index){}
    Node(const pair<int,int> p, const int w, bitset_vector d, const int steps, const int index): pos(p), weight(w), route(d), step_number(steps), current_index(index){}
};

struct OrderByWeight{
    bool operator() (const Node& a, const Node& b) { return a.weight < b.weight; }
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
    NodeQueue node_queue;

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
            bitset<MAX_SIZE> any;
            bitset_vector bv;
            bv.push_back(any);
            node_queue.emplace(start, GetDistance(start_y, start_x), bv, 0);
            visited.emplace(start);
        }
    }

    int GetDistance(int& y, int& x){
        return (y < end_y ? end_y - y : y - end_y) + (x < end_x ? end_x - x : x - end_x);
    }

    bool IsCloserToFinish(int prev_pos, int new_pos, int end_pos) {
      if (new_pos > prev_pos) {
        return new_pos <= end_pos;
      } else {
        return new_pos >= end_pos;
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
            Node current = node_queue.top();
            node_queue.pop();
            if(current.weight == 0) return DecodeRoute(current);
            AddNeighborsToQueue(current);
        }
        return "-";
    }

    string DecodeRoute(const Node& node){
        string result = "";
        for(int i = node.step_number*2 - 1; i >= 0; i-=2){
            result += letters[node.route[i]*2 + node.route[i-1]];
        }
        return result;
    }

    void AddNeighborsToQueue(const Node& node){
        if(node.pos.first > 0){
            std::pair<int,int> down_position(node.pos.first - 1, node.pos.second);
            if(!map[down_position.first][down_position.second]) {
                if (visited.find(down_position) == visited.end()) {
                    visited.emplace(down_position);
                    int new_weight = node.weight;
                    int new_index = node.current_index;
                    bitset_vector new_route(node.route);
                    int steps = node.step_number;
                    if(steps > MAX_SIZE){
                        bitset<MAX_SIZE> new_bitset;
                        ++new_index;
                        new_route.push_back(new_bitset);
                        steps = 0;
                    }
                    else{
                        ++steps;
                    }
                    new_route[new_index] <<= 2;
                    new_route[new_index] |= DOWN_POS;
                    node_queue.emplace(down_position,
                        IsCloserToFinish(node.pos.first, down_position.first, end_y) ? --new_weight : ++new_weight,
                        new_route, steps, new_index); //TODO(semylevy) improve this.
                }
            }
        }
        if(node.pos.first + 1 < size_y) {
            std::pair<int,int> up_position(node.pos.first + 1, node.pos.second);
            if(!map[up_position.first][up_position.second]) {
                if (visited.find(up_position) == visited.end()) {
                    visited.emplace(up_position);
                    int new_weight = node.weight;
                    int steps = node.step_number;
                    bitset<MAX_SIZE> new_route = node.route;
                    new_route <<= 2;
                    new_route |= UP_POS;
                    node_queue.emplace(up_position,
                        IsCloserToFinish(node.pos.first, up_position.first, end_y) ? --new_weight : ++new_weight,
                        new_route, ++steps); //TODO(semylevy) improve this.
                }
            }
        }
        if(node.pos.second > 0){
            std::pair<int,int> left_position(node.pos.first, node.pos.second - 1);
            if(!map[left_position.first][left_position.second]) {
                if (visited.find(left_position) == visited.end()) {
                    visited.emplace(left_position);
                    int new_weight = node.weight;
                    bitset<MAX_SIZE> new_route = node.route;
                    new_route <<= 2;
                    new_route |= LEFT_POS;
                    int steps = node.step_number;
                    node_queue.emplace(left_position,
                        IsCloserToFinish(node.pos.second, left_position.second, end_x) ? --new_weight : ++new_weight,
                        new_route, ++steps); //TODO(semylevy) improve this.
                }
            }
        }
        if(node.pos.second + 1 < size_x){
          std::pair<int,int> right_position(node.pos.first, node.pos.second + 1);
          if(!map[right_position.first][right_position.second]) {
              if (visited.find(right_position) == visited.end()) {
                  visited.emplace(right_position);
                  int new_weight = node.weight;
                  bitset<MAX_SIZE> new_route = node.route;
                  int steps = node.step_number;
                  new_route <<= 2;
                  new_route |= RIGHT_POS;
                  node_queue.emplace(right_position,
                      IsCloserToFinish(node.pos.second, right_position.second, end_x) ? --new_weight : ++new_weight,
                      new_route, steps++); //TODO(semylevy) improve this.
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
