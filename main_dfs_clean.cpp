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
//#include "timing.h"
//#include <opencv2/opencv.hpp>

using std::string;
using std::pair;

/*DECLARE_TIMING(o1);
DECLARE_TIMING(o2);
DECLARE_TIMING(o3);
DECLARE_TIMING(o4);
DECLARE_TIMING(o5);
DECLARE_TIMING(o6);
DECLARE_TIMING(o7);
DECLARE_TIMING(o8);
DECLARE_TIMING(o9);
DECLARE_TIMING(o10);
DECLARE_TIMING(o11);
DECLARE_TIMING(o12);
DECLARE_TIMING(o13);
DECLARE_TIMING(o14);
DECLARE_TIMING(o15);*/

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
    pair<char, int>*  directions;
    bool ** visited;
    std::stack<Node> node_queue;

    Labyrinth(){
        //START_TIMING(o1);
        //t1 = std::chrono::high_resolution_clock::now();
        scanf("%d %d %d %d %d %d ", &size_x, &size_y, &start_x, &start_y,
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
            std::pair<int,int> start(start_y,start_x);
            node_queue.emplace(start, current_id);
            visited[start_y][start_x] = true;
        }
        directions = new pair<char, int> [(size_x*size_y)/2];
        //std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
        //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
        //std::cout << "Initialization time is: " << duration << "us" << "\n";
        //t1 = std::chrono::high_resolution_clock::now();
        //STOP_TIMING(o1);
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
            //START_TIMING(o2);
            Node current = node_queue.top();
            node_queue.pop();
            //STOP_TIMING(o2);
            //START_TIMING(o3);
            if(current.pos.first == end_y && current.pos.second == end_x){
                return GetSteps(current.direction_id);
            }
            //STOP_TIMING(o3);
            //START_TIMING(o5);
            AddNeighborsToQueue(current);
            //STOP_TIMING(o5);
        }
        upside_down_result = "-";
    }

    void GetSteps(const int id) {
        //START_TIMING(o4);
        upside_down_result = "";
        upside_down_result.reserve(current_id);
        int traverse = id;
        while (traverse != 0) {
            upside_down_result += directions[traverse].first;
            traverse = directions[traverse].second;
        }
        //STOP_TIMING(o4);
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
        //START_TIMING(o6);
        if(node.pos.first > 0){
            // START_TIMING(o10);
            std::pair<int,int> down_position(node.pos.first - 1, node.pos.second);
            // STOP_TIMING(o10);
            //START_TIMING(o11);
            if(!map[down_position.first][down_position.second]) {
                //  STOP_TIMING(o11);
                //START_TIMING(o12);
                if (!visited[down_position.first][down_position.second]) {
                    // STOP_TIMING(o12);
                    // START_TIMING(o13);
                    visited[down_position.first][down_position.second] = true;
                    //  STOP_TIMING(o13);
                    //START_TIMING(o14);
                    node_queue.emplace(down_position, ++current_id); //TODO(semylevy) improve this.
                    //STOP_TIMING(o14);
                    //START_TIMING(o15);
                    directions[current_id] = {'D', node.direction_id};
                    //STOP_TIMING(o15);
                } //else STOP_TIMING(o12);
            } //else STOP_TIMING(o11);
        }
        //STOP_TIMING(o6);
        //START_TIMING(o7);
        if(node.pos.first + 1 < size_y) {
            // START_TIMING(o10);
            std::pair<int,int> up_position(node.pos.first + 1, node.pos.second);
            //STOP_TIMING(o10);
            //START_TIMING(o11);
            if(!map[up_position.first][up_position.second]) {
                //   STOP_TIMING(o11);
                //  START_TIMING(o12);
                if (!visited[up_position.first][up_position.second]) {
                    //    STOP_TIMING(o12);
                    //  START_TIMING(o13);
                    visited[up_position.first][up_position.second] = true;
                    // STOP_TIMING(o13);
                    //START_TIMING(o14);
                    node_queue.emplace(up_position, ++current_id); //TODO(semylevy) improve this.
                    //STOP_TIMING(o14);
                    //START_TIMING(o15);
                    directions[current_id] = {'U', node.direction_id};
                    //STOP_TIMING(o15);
                } //else STOP_TIMING(o12);
            } //else STOP_TIMING(o11);
        }
        //STOP_TIMING(o7);
        //START_TIMING(o8);
        if(node.pos.second > 0){
            //  START_TIMING(o10);
            std::pair<int,int> left_position(node.pos.first, node.pos.second - 1);
            //STOP_TIMING(o10);
            //START_TIMING(o11);
            if(!map[left_position.first][left_position.second]) {
                //  STOP_TIMING(o11);
                // START_TIMING(o12);
                if (!visited[left_position.first][left_position.second]) {
                    //   STOP_TIMING(o12);
                    //  START_TIMING(o13);
                    visited[left_position.first][left_position.second] = true;
                    //STOP_TIMING(o13);
                    //START_TIMING(o14);
                    node_queue.emplace(left_position, ++current_id); //TODO(semylevy) improve this.
                    //STOP_TIMING(o14);
                    //START_TIMING(o15);
                    directions[current_id] = {'L', node.direction_id};
                    //STOP_TIMING(o15);
                } //else STOP_TIMING(o12);
            } //else STOP_TIMING(o11);
        }
        //STOP_TIMING(o8);
        //START_TIMING(o9);
        if(node.pos.second + 1 < size_x){
            // START_TIMING(o10);
            std::pair<int,int> right_position(node.pos.first, node.pos.second + 1);
            //STOP_TIMING(o10);
            //START_TIMING(o11);
            if(!map[right_position.first][right_position.second]) {
                //STOP_TIMING(o11);
                //START_TIMING(o12);
                if (!visited[right_position.first][right_position.second]) {
                    //  STOP_TIMING(o12);
                    // START_TIMING(o13);
                    visited[right_position.first][right_position.second] = true;
                    //STOP_TIMING(o13);
                    //START_TIMING(o14);
                    node_queue.emplace(right_position, ++current_id); //TODO(semylevy) improve this.
                    //STOP_TIMING(o14);
                    //START_TIMING(o15);
                    directions[current_id] = {'R', node.direction_id};
                    //STOP_TIMING(o15);
                } //else STOP_TIMING(o12);
            } //else STOP_TIMING(o11);
        }
        //STOP_TIMING(o9);
    }

};

int main() {
    //std::chrono::high_resolution_clock::time_point t1 = std::chrono::high_resolution_clock::now();
    Labyrinth labyrinth;
    //labyrinth.PrintLabyrinth();
    labyrinth.Solve();
    labyrinth.PrintResult();
    //std::chrono::high_resolution_clock::time_point t2 = std::chrono::high_resolution_clock::now();
   // auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2-t1).count();
    //std::cout << "Time is: " << duration << "us" << "\n";
    /*SHOW_TIMING(o1, "o1:");
    SHOW_TIMING(o2, "o2:");
    SHOW_TIMING(o3, "o3:");
    SHOW_TIMING(o4, "o4:");
    SHOW_TIMING(o5, "o5:");
    SHOW_TIMING(o6, "o6:");
    SHOW_TIMING(o7, "o7:");
    SHOW_TIMING(o8, "o8:");
    SHOW_TIMING(o9, "o9:");
    SHOW_TIMING(o10, "o10:");
    SHOW_TIMING(o11, "o11:");
    SHOW_TIMING(o12, "o12:");
    SHOW_TIMING(o13, "o13:");
    SHOW_TIMING(o14, "o14:");
    SHOW_TIMING(o15, "o15:");*/
}
