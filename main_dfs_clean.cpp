//Daniel Blanck Kahan A01022794
//Salomon Levy Becherano A01023530
//Axel Zuchovicki Zaritsky A01022875

#include <iostream>
#include <stdio.h>
#include <set>
#include <queue>
#include <string>
#include <tuple>
#include <chrono>
#include <stack>
#include <unordered_map>
#include <bits/stdc++.h>


using std::string;
using std::pair;

class Node{
public:
    short int pos_x;
    short int pos_y;
    int direction_id;
    Node(const short int y, const short int x, const int d): pos_y(y), pos_x(x), direction_id(d){}
};

class Labyrinth {
public:
    short int size_y;
    short int size_x;
    short int start_y;
    short int start_x;
    short int end_x;
    short int end_y;
    int current_id;
    bool** map;
    string upside_down_result;
    pair<char, int>*  directions;
    bool ** visited;
    std::stack<Node> node_queue;

    Labyrinth(){
        scanf("%hd %hd %hd %hd %hd %hd ", &size_x, &size_y, &start_x, &start_y,
              &end_x, &end_y);
        map = new bool* [size_y];
        visited = new bool* [size_y];
        int size = size_y*(size_x+1);
        char* all_chars = new char [size];
        fread(all_chars, 1, size, stdin);
        char* iterating = all_chars;
        for (int i = size_y - 1; i >= 0; --i) {
            map[i] = new bool [size_x];
            visited[i] = new bool [size_x];
            for (int j = 0; j < size_x; ++j) {
                if(*(iterating++) == '1') map[i][j] = true;
                else map[i][j] = false;
                visited[i][j] = false;
            }
            ++iterating;
        }
        current_id = 0;
        if(!map[start_y][start_x]) {
            node_queue.emplace(start_y, start_x, current_id);
            visited[start_y][start_x] = true;
        }
        directions = new pair<char, int> [(size_x*size_y)/2];
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
            if(current.pos_y == end_y && current.pos_x == end_x){
                return GetSteps(current.direction_id);
            }
            AddNeighborsToQueue(current);
        }
        upside_down_result = "-";
    }

    void GetSteps(const int id) {
        upside_down_result = "";
        upside_down_result.reserve(current_id);
        int traverse = id;
        while (traverse != 0) {
            upside_down_result += directions[traverse].first;
            traverse = directions[traverse].second;
        }
    }

    void PrintResult(){
        //t1 = std::chrono::high_resolution_clock::now();
        for(int i = upside_down_result.size() - 1; i >= 0; --i){
            printf("%c", upside_down_result[i]);
        }
        printf("\n");
        /*std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
        std::cout << "Printing time is: " << duration << "us" << "\n";*/
    }

    void AddNeighborsToQueue(const Node& node){
        if(node.pos_y > 0){
            short int new_y_down = node.pos_y;
            --new_y_down;
            if(!map[new_y_down][node.pos_x]) {
                if (!visited[new_y_down][node.pos_x]) {
                    visited[new_y_down][node.pos_x] = true;
                    node_queue.emplace(new_y_down, node.pos_x, ++current_id);
                    directions[current_id] = {'D', node.direction_id};
                }
            }
        }
        short int new_y_up = node.pos_y;
        ++new_y_up;
        if(new_y_up < size_y) {
            if(!map[new_y_up][node.pos_x]) {
                if (!visited[new_y_up][node.pos_x]) {
                    visited[new_y_up][node.pos_x] = true;
                    node_queue.emplace(new_y_up, node.pos_x, ++current_id);
                    directions[current_id] = {'U', node.direction_id};
                }
            }
        }
        if(node.pos_x > 0){
            short int new_x_left = node.pos_x;
            --new_x_left;
            if(!map[node.pos_y][new_x_left]) {
                if (!visited[node.pos_y][new_x_left]) {
                    visited[node.pos_y][new_x_left] = true;
                    node_queue.emplace(node.pos_y, new_x_left, ++current_id);
                    directions[current_id] = {'L', node.direction_id};
                }
            }
        }
        short int new_x_right = node.pos_x;
        ++new_x_right;
        if(new_x_right < size_x){
            if(!map[node.pos_y][new_x_right]) {
                if (!visited[node.pos_y][new_x_right]) {
                    visited[node.pos_y][new_x_right] = true;
                    node_queue.emplace(node.pos_y, new_x_right, ++current_id);
                    directions[current_id] = {'R', node.direction_id};
                }
            }
        }
    }

};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    Labyrinth labyrinth;
    //labyrinth.PrintLabyrinth();
    labyrinth.Solve();
    labyrinth.PrintResult();
    std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
    std::cout << "Time is: " << duration << "us" << "\n";
}
