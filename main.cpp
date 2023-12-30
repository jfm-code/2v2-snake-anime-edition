#include "snake.hpp"
#include <iostream>
#include <vector>
#include <deque>
#include <forward_list>

using namespace std;

int main()
{
    //setting the sound
    sf::SoundBuffer gameBuffer;
    if (!gameBuffer.loadFromFile("C:\\Users\\User\\source\\repos\\Snake Game\\Snake Game\\Sakura-Girl-Daisy-chosic.com_.wav")) {
        cout << "error opening file";
        exit(1);
    }
    sf::Sound gameSound;
    gameSound.setBuffer(gameBuffer);

    sf::SoundBuffer dieBuffer;
    if (!dieBuffer.loadFromFile("C:\\Users\\User\\source\\repos\\Snake Game\\Snake Game\\game_over.wav")) {
        cout << "error opening file";
        exit(1);
    }
    sf::Sound dieSound;
    dieSound.setBuffer(dieBuffer);

    bool play_again = false;
    do
    {
        int num_player = 0;
        char level = 0;
        introGameMenu(num_player, level); //get the number of player and level through menu

        sf::RenderWindow windowGame(sf::VideoMode(1020, 670), "Snake Game!");
        World world(num_player, level);
        snake_1_die = false;
        play_again = true;
        gameSound.play();

        //pass these three variables in the simulate function to get values updated for outro
        int who_wins = -1;
        int snake_1_score = -1;
        int snake_2_score = -1;
        
        while (windowGame.isOpen())
        {
            sf::Event event;
            while (windowGame.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    windowGame.close();
            }
            windowGame.clear();
            bool is_game_over = world.simulate_game(who_wins,snake_1_score,snake_2_score);
            world.display(windowGame);
            windowGame.display();
            sf::sleep(sf::milliseconds(200));

            if (is_game_over)
            {
                gameSound.stop();
                dieSound.play();
                play_again = outroGameMenu(who_wins, snake_1_score, snake_2_score);
                break;
            }
        }
    } while (play_again);

    return 0;
}