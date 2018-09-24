#include <iostream>
#include <stdio.h>
#include <set>
#include <queue>
#include <math.h>
#include <string>
#include <tuple>
#include <chrono>

#define MAX_SIZE 1500

using std::string;
using std::pair;

class Node{
public:
    std::pair<int,int> pos;
    int weight;
    string route;
    Node(const int y, const int x, const int w, string d): pos(std::make_pair(y,x)), weight(w), route(d){}
    Node(const pair<int,int> p, const int w, string d): pos(p), weight(w), route(d){}
};

struct OrderByWeight{
    bool operator() (const Node& a, const Node& b) { return a.weight < b.weight; }
};

typedef std::priority_queue<Node, std::vector<Node>, OrderByWeight> NodeQueue;


class Labyrinth {
public:
    int size_y;
    int size_x;
    int start_y;
    int start_x;
    int end_x;
    int end_y;
    bool map[MAX_SIZE][MAX_SIZE]; // Space allocated in compile time to save time in run time.
    std::set<std::pair<int,int> > visited;
    NodeQueue node_queue;


    Labyrinth(){
        scanf("%d %d %d %d %d %d ", &size_x, &size_y, &start_x, &start_y,
              &end_x, &end_y);
        for (int i = size_y - 1; i >= 0; --i) {
            for (int j = 0; j < size_x; ++j) {
                char cell_char;
                scanf("%c ", &cell_char);
                if(cell_char == '1') map[i][j] = true;
                else map[i][j] = false;
            }
        }
        if(!map[start_y][start_x]) {
            std::pair<int,int> start(start_y,start_x);
            node_queue.emplace(start, GetDistance(start_y, start_x), "");
            visited.emplace(start);
        }
    }

    int GetDistance(int& y, int& x){
        return abs(y - end_y) + abs(x - end_x);
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
            if(current.weight == 0) return current.route;
            AddNeighborsToQueue(current);
        }
        return "-";
    }

    void AddNeighborsToQueue(const Node& node){
        if(node.pos.first > 0){
            std::pair<int,int> down_position(node.pos.first - 1, node.pos.second);
            AddNodeIfPossible(down_position, node.route, "D");
        }
        if(node.pos.first + 1 < size_y){
            std::pair<int,int> up_position(node.pos.first + 1, node.pos.second);
            AddNodeIfPossible(up_position, node.route, "U");
        }
        if(node.pos.second > 0){
            std::pair<int,int> left_position(node.pos.first, node.pos.second - 1);
            AddNodeIfPossible(left_position, node.route, "L");
        }
        if(node.pos.second + 1 < size_x){
            std::pair<int,int> right_position(node.pos.first, node.pos.second + 1);
            AddNodeIfPossible(right_position, node.route, "R");
        }
    }

    void AddNodeIfPossible(pair<int,int> pos, const string& route, string new_letter){
        if(!map[pos.first][pos.second]) {
            if (visited.find(pos) == visited.end()) {
                visited.emplace(pos);
                node_queue.emplace(pos, GetDistance(pos.first, pos.second), route + new_letter); //TODO(semylevy) improve this.
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
    std::cout << "Time is: " << duration << "ms" << "\n";
}