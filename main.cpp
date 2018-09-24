#include <iostream>
#include <stdio.h>

class Labyrinth {
public:
    int size_x;
    int size_y;
    int start_x;
    int start_y;
    int end_x;
    int end_y;
    bool ** map;

    Labyrinth(){
        scanf("%d %d %d %d %d %d ", &size_x, &size_y, &start_x, &start_y,
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
};

int main() {
    Labyrinth labyrinth;
    labyrinth.PrintLabyrinth();
}