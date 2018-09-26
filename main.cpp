#include <iostream>
#include <stdio.h>
#include <set>
#include <queue>
#include <string>
#include <tuple>
#include <chrono>
#include <unordered_map>

using std::string;
using std::pair;


class Node {
public:
    std::pair<int, int> pos;
    int weight;
    char direction;
    Node* parent;

    Node(const int y, const int x, const int w, Node* dad, const char dir) : pos(std::make_pair(y, x)), weight(w), parent(dad),
                                                                             direction(dir) {}

    Node(const pair<int, int> p, const int w, Node* dad, const char dir) : pos(p), weight(w), parent(dad),
                                                                           direction(dir) {}

    ~Node() {}
};

struct OrderByWeight {
    bool operator()(const Node &a, const Node &b) { return a.weight < b.weight; }
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
    bool **map;
    int current_id;
    string upside_down_result;
    std::unordered_map<int, pair<char, int> > directions;
    std::set<std::pair<int, int> > visited;
    NodeQueue node_queue;

    Labyrinth() {
        scanf("%d %d %d %d %d %d ", &size_x, &size_y, &start_x, &start_y,
              &end_x, &end_y);
        map = new bool *[size_y];
        for (int i = size_y - 1; i >= 0; --i) {
            map[i] = new bool[size_x];
            for (int j = 0; j < size_x; ++j) {
                char cell_char;
                scanf("%c ", &cell_char);
                if (cell_char == '1') map[i][j] = true;
                else map[i][j] = false;
            }
        }
        current_id = 0;
        if (!map[start_y][start_x]) {
            std::pair<int, int> start(start_y, start_x);
            node_queue.emplace(start, GetDistance(start_y, start_x), nullptr, 'X');
            visited.emplace(start);
        }
    }

    int GetDistance(int &y, int &x) {
        return (y < end_y ? end_y - y : y - end_y) + (x < end_x ? end_x - x : x - end_x);
    }

    bool IsCloserToFinish(int prev_pos, int new_pos, int end_pos) {
        if (new_pos > prev_pos) {
            return new_pos <= end_pos;
        } else {
            return new_pos >= end_pos;
        }
    }

    void PrintLabyrinth() {
        for (int i = size_y - 1; i >= 0; --i) {
            for (int j = 0; j < size_x; ++j) {
                char c = map[i][j] ? '1' : '0';
                printf("%c ", c);
            }
            printf("\n");
        }
    }

    void Solve() {
        while (!node_queue.empty()) {
            Node current = node_queue.top();
            node_queue.pop();
            if (current.weight == 0) return GetSteps(&current);
            AddNeighborsToQueue(current);
        }
        upside_down_result = "-";
    }

    void GetSteps(Node* start) {
        upside_down_result = "";
        Node* traverse = start;
        while (traverse->parent != nullptr) {
            upside_down_result += traverse->direction;
            traverse = traverse->parent;
        }
    }

    void PrintResult(){
        for(int i = upside_down_result.size() - 1; i >= 0; --i){
            printf("%c", upside_down_result[i]);
        }
        printf("\n");
    }

    void AddNeighborsToQueue(Node &node) {
        if (node.pos.first > 0) {
            Node* new_node;
            std::pair<int, int> down_position(node.pos.first - 1, node.pos.second);
            if (!map[down_position.first][down_position.second]) {
                if (visited.find(down_position) == visited.end()) {
                    visited.emplace(down_position);
                    int new_weight = node.weight;
                    new_node = new Node(down_position,
                                  IsCloserToFinish(node.pos.first, down_position.first, end_y) ? --new_weight
                                                                                               : ++new_weight,
                                  &node, 'D'); //TODO(semylevy) improve this.
                                  node_queue.push(*new_node);
                }
            }
        }
        if (node.pos.first + 1 < size_y) {
            std::pair<int, int> up_position(node.pos.first + 1, node.pos.second);
            if (!map[up_position.first][up_position.second]) {
                if (visited.find(up_position) == visited.end()) {
                    visited.emplace(up_position);
                    int new_weight = node.weight;
                    Node* new_node;
                    new_node = new Node(up_position,
                                  IsCloserToFinish(node.pos.first, up_position.first, end_y) ? --new_weight
                                                                                             : ++new_weight,
                                  &node, 'U'); //TODO(semylevy) improve this.
                    node_queue.push(*new_node);

                }
            }
        }
        if (node.pos.second > 0) {
            std::pair<int, int> left_position(node.pos.first, node.pos.second - 1);
            if (!map[left_position.first][left_position.second]) {
                if (visited.find(left_position) == visited.end()) {
                    visited.emplace(left_position);
                    int new_weight = node.weight;
                    Node* new_node;
                    new_node = new Node(left_position,
                                  IsCloserToFinish(node.pos.second, left_position.second, end_x) ? --new_weight
                                                                                                 : ++new_weight,
                                  &node, 'L'); //TODO(semylevy) improve this.
                    node_queue.push(*new_node);
                }
            }
        }
        if (node.pos.second + 1 < size_x) {
            std::pair<int, int> right_position(node.pos.first, node.pos.second + 1);
            if (!map[right_position.first][right_position.second]) {
                if (visited.find(right_position) == visited.end()) {
                    visited.emplace(right_position);
                    int new_weight = node.weight;
                    Node* new_node;
                    new_node = new Node(right_position,
                                  IsCloserToFinish(node.pos.second, right_position.second, end_x) ? --new_weight
                                                                                                  : ++new_weight,
                                  &node, 'R'); //TODO(semylevy) improve this.
                    node_queue.push(*new_node);
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
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "Time is: " << duration << "us" << "\n";
}

