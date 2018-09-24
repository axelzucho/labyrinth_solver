#include <iostream>
#include <stdio.h>
#include <unordered_set>
#include <queue>
#include <math.h>
#include <string>
#include <pair>

using std::string;

class Node{
    std::pair<int,int> pos;
    int weight;
    string direction;

    Node(const int y, const int x, const int w, string d): pos(std::pair(y,x)), weight(w), direction(d){}
};

struct OrderByWeight{
    bool operator(Node const& a, Node const& b) { return a.weight < b.weight; }
};

typedef std::priority_queue<Node, std::vector<Node> OrderByWeight> NodeQueue;


class Labyrinth {
public:
    int size_y;
    int size_x;
    int start_y;
    int start_x;
    int end_x;
    int end_y;
    bool ** map;
    std::unordered_set<std::pair<int,int>> visited;
    NodeQueue node_queue;


    Labyrinth(){
        scanf("%d %d %d %d %d %d ", &size_y, &size_x, &start_y, &start_x,
              &end_x, &end_y);
        map = new bool *[size_y];
        map[0] = new bool[size_y * size_x];
        for (int i = 1; i < size_x; ++i) {
            map[i] = map[0] + i * size_y;
        }
        for (int i = 0; i < size_y; ++i) {
            for (int j = 0; j < size_x; ++j) {
                scanf("%c ", &map[i][j]);
            }
        }

        node_queue.emplace(start_y, start_x, GetDistance(start_y, start_x), "");
    }

    int GetDistance(int& y, int& x){
        return abs(y - end_y) + abs(x - end_x);
    }

    void PrintLabyrinth(){
        for(int i = 0; i < size_y; ++i){
            for(int j = 0; j < size_x; ++j){
                printf("%c ", map[i][j]);
            }
            printf("\n");
        }
    }

    ~Labyrinth(){
        delete(map[0]);
        delete[] (map);
    }

    string Solve(){
        while (!node_queue.empty()){
            Node current = node_queue.top();
            node_queue.pop();
            if(current.weight == 0) return current.direction;
            if(visited.find(current.pos) != visited.end()) continue;
            visited.emplace(current.pos);
        }
        return "-";
    }

    void AddNeighborsToQueue(const Node& node){
        if(node.pos.first != 0){

            if(!map[node.pos.first-1][pos.second]) {
                if (!visited[]) {
                    visited.emplace(pos);
                    node_queue.emplace(pos);
                }
            }
        }
    }

    void AddNode(const pair<int,int>& pos, string& route, string& new_letter){
        if(!map[pos.first][pos.second]) {
            if (!visited[pos]) {
                visited.emplace(pos);
                node_queue.emplace(pos, GetDistance(pos.first, pos.second), route + new_letter); //TODO(semylevy) improve this.
            }
        }
    }
};

int main() {
    Labyrinth labyrinth;
    labyrinth.PrintLabyrinth();
}