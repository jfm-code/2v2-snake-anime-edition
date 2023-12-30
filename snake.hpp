#ifndef SNAKE_H
#define SNAKE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <vector>
#include <deque>
#include <forward_list>

using namespace std;

const int BOARD_WIDTH = 40;
const int BOARD_HEIGHT = 26;
const int MAX_NUM_OF_FOOD = 4; //each food = 1 point
const int MAX_NUM_OF_DRINK = 3; //each drink = 2 points
const int TILE_SIZE = 25;
const int FONT_SIZE = 25;

extern bool snake_1_die;

enum OBJECT_TYPE { TILE, SNAKE, FOOD, DRINK, WALL, NUMBER_OF_OBJECT };
enum DIRECTION { UP, DOWN, LEFT, RIGHT, NUMBER_OF_DIRECTION };

struct Coord
{
    int x;
    int y;
};
typedef struct Coord coord;

class World; //forward declaration
class Snake; //forward declaration
class Tile
{
public:
    Tile(int init_x, int init_y, World& init_world);
    virtual void display(sf::RenderWindow& window) {};
    virtual OBJECT_TYPE who() { return TILE; };
    virtual void move(DIRECTION way) {};

protected:
    coord coord;
    World& my_world;
};
class World
{
public:
    World(int input_player, int input_level);
    void display(sf::RenderWindow& window);
    vector<Tile*>& operator[](int row);
    bool simulate_game(int& who_wins, int& snake_1_score, int& snake_2_score);
    void respawn_food(int number_of_food);
    void respawn_drink(int number_of_drink);
    void delete_drink();
    void create_maze();
    void OutputInput() { cout << number_of_player << " - " << difficulty_level << endl; }
protected:
    vector<vector<Tile*>> world;
    deque<Snake*>two_snakes; //use deck because vector can't pop_front()
    int remaining_food;
    int number_of_player;
    char difficulty_level;
    vector<int>scores;
    int turn;
};
class Snake : public Tile
{
public:
    Snake(int init_x, int init_y, World& init_world);
    OBJECT_TYPE who() { return SNAKE; };
    void display(sf::RenderWindow& window);
    void move(int& num_of_food); //pass by reference to change the number of remaining food
    void body_follow_head(int x_head, int y_head);
    bool checkCollision();
    DIRECTION getCurrentWay() { return current_way; } //accessor function
    void changeCurrentWay(DIRECTION input_way) { current_way = input_way; }; //mutator function
    DIRECTION getIntendedWay() { return intended_way; }
    void changeIntendedWay(DIRECTION input_way) { intended_way = input_way; };
    int score_before_die() { return score; };
    int getCoordX() { return coord.x; }
    int getCoordY() { return coord.y; }
    void declareWhichOne(int indicator) { which_one = indicator; }
private:
    DIRECTION current_way;
    DIRECTION intended_way;
    forward_list<Snake*> snake_body;
    int score;
    int which_one;
};
class Food : public Tile
{
public:
    Food(int init_x, int init_y, World& init_world);
    OBJECT_TYPE who() { return FOOD; };
    void display(sf::RenderWindow& window);

private:

};
class Drink : public Tile
{
public:
    Drink(int init_x, int init_y, World& init_world);
    OBJECT_TYPE who() { return DRINK; };
    void display(sf::RenderWindow& window);

private:
};
class Wall : public Tile
{
public:
    Wall(int init_x, int init_y, World& init_world);
    OBJECT_TYPE who() { return WALL; };
    void display(sf::RenderWindow& window);

private:

};

bool outroGameMenu(int winner, int player1_score, int player2_score);
void introGameMenu(int& input_player, char& input_level);
bool wish_to_continue();

#endif