#include "snake.hpp"

bool snake_1_die = false;

//OTHER FUNCTIONS
bool wish_to_continue()
{
    cout << "Do you want to play again? (y/n): ";
    char c;
    cin >> c;
    if (c == 'y') return true;
    else if (c == 'n') return false;
}
void introGameMenu(int& input_player, char& input_level)
{
    sf::RenderWindow windowMenu(sf::VideoMode(600, 400), "Main Menu");
    sf::Texture background;
    if (background.loadFromFile("C:\\Users\\User\\source\\repos\\Snake Game\\Snake Game\\Background images\\intro.png"))
    {
        sf::Vector2u windowSize = windowMenu.getSize();
        sf::Sprite backgroundSprite(background);
        backgroundSprite.setScale(
            static_cast<float>(windowSize.x) / background.getSize().x,
            static_cast<float>(windowSize.y) / background.getSize().y
        );


        sf::RectangleShape TwoPlayerButton(sf::Vector2f(200, 60));
        TwoPlayerButton.setPosition(80, 100); //setPosition(x,y) on the window
        TwoPlayerButton.setFillColor(sf::Color(150, 123, 182));

        sf::RectangleShape OnePlayerButton(sf::Vector2f(190, 60));
        OnePlayerButton.setPosition(330, 100);
        OnePlayerButton.setFillColor(sf::Color(150, 123, 182));

        sf::Font font;
        if (!font.loadFromFile("C:\\Users\\User\\source\\repos\\Snake Game\\Snake Game\\RedGlass-BWx23.ttf"))
        {
            cout << "Error opening font file" << endl;
            exit(1);
        }

        sf::Text gameTitle("Welcome to SnakeLand !", font, FONT_SIZE + 10);
        gameTitle.setPosition(60, 20);
        gameTitle.setFillColor(sf::Color(128, 0, 128));

        sf::Text twoPlayerText("Two Players", font, FONT_SIZE);
        twoPlayerText.setPosition(95, 116);
        twoPlayerText.setFillColor(sf::Color::White);

        sf::Text onePlayerText("One Player", font, FONT_SIZE);
        onePlayerText.setPosition(350, 116);
        onePlayerText.setFillColor(sf::Color::White);

        sf::Text levelEasyText("easy", font, FONT_SIZE);
        levelEasyText.setPosition(270, 190);
        levelEasyText.setFillColor(sf::Color(128, 0, 128));

        sf::Text levelMediumText("medium", font, FONT_SIZE);
        levelMediumText.setPosition(250, 250);
        levelMediumText.setFillColor(sf::Color(128, 0, 128));

        sf::Text levelHardText("hard", font, FONT_SIZE);
        levelHardText.setPosition(270, 310);
        levelHardText.setFillColor(sf::Color(128, 0, 128));

        while (windowMenu.isOpen())
        {
            sf::Event eventMenu;
            while (windowMenu.pollEvent(eventMenu))
            {
                if (eventMenu.type == sf::Event::Closed)
                    windowMenu.close();
                if (eventMenu.type == sf::Event::MouseButtonPressed)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(windowMenu);
                    if (OnePlayerButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                        input_player = 1;
                    if (TwoPlayerButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                        input_player = 2;

                    sf::FloatRect textEasyBound = levelEasyText.getGlobalBounds();
                    if (textEasyBound.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                    {
                        levelEasyText.setFillColor(sf::Color::Blue);
                        input_level = 'e';
                        windowMenu.close();
                    }
                    sf::FloatRect textMediumBound = levelMediumText.getGlobalBounds();
                    if (textMediumBound.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                    {
                        levelMediumText.setFillColor(sf::Color::Blue);
                        input_level = 'm';
                        windowMenu.close();
                    }
                    sf::FloatRect textHardBound = levelHardText.getGlobalBounds();
                    if (textHardBound.contains(static_cast<float>(mousePos.x), static_cast<float>(mousePos.y)))
                    {
                        levelHardText.setFillColor(sf::Color::Blue);
                        input_level = 'h';
                        windowMenu.close();
                    }
                }
            }
            windowMenu.clear();

            windowMenu.draw(backgroundSprite);
            windowMenu.draw(OnePlayerButton);
            windowMenu.draw(TwoPlayerButton);

            windowMenu.draw(gameTitle);
            windowMenu.draw(onePlayerText);
            windowMenu.draw(twoPlayerText);
            windowMenu.draw(levelEasyText);
            windowMenu.draw(levelMediumText);
            windowMenu.draw(levelHardText);

            windowMenu.display();
        }
    }
    /*cout << "Choose number of player: ";
    cin >> input_player;
    cout << "Choose level (easy/medium/hard): ";
    cin >> input_level;*/
}
bool outroGameMenu(int winner, int player1_score, int player2_score)
{
    sf::RenderWindow windowMenu(sf::VideoMode(600, 400), "Wanna play again?");
    sf::Texture background;
    bool play_again = false;
    if (background.loadFromFile("C:\\Users\\User\\source\\repos\\Snake Game\\Snake Game\\Background images\\outro.png"))
    {
        sf::Vector2u windowSize = windowMenu.getSize();
        sf::Sprite backgroundSprite(background);
        backgroundSprite.setScale(
            static_cast<float>(windowSize.x) / background.getSize().x,
            static_cast<float>(windowSize.y) / background.getSize().y
        );

        sf::RectangleShape YesButton(sf::Vector2f(80, 60));
        YesButton.setPosition(80, 220); //setPosition(x,y) on the window
        YesButton.setFillColor(sf::Color(150, 123, 182));

        sf::RectangleShape NoButton(sf::Vector2f(80, 60));
        NoButton.setPosition(200, 220);
        NoButton.setFillColor(sf::Color(150, 123, 182));

        sf::Font font;
        if (!font.loadFromFile("C:\\Users\\User\\source\\repos\\Snake Game\\Snake Game\\RedGlass-BWx23.ttf"))
        {
            cout << "Error opening font file" << endl;
            exit(1);
        }

        sf::Text gameTitle("Play again?", font, FONT_SIZE + 10);
        gameTitle.setPosition(70, 160);
        gameTitle.setFillColor(sf::Color(128, 0, 128));

        sf::Text yesText("Yes", font, FONT_SIZE);
        yesText.setPosition(95, 235);
        yesText.setFillColor(sf::Color::White);

        sf::Text noText("No", font, FONT_SIZE);
        noText.setPosition(220, 235);
        noText.setFillColor(sf::Color::White);

        //display winners & scores
        sf::Text winner1Text("Player one wins!", font, FONT_SIZE + 10);
        winner1Text.setPosition(40, 80);
        winner1Text.setFillColor(sf::Color(128, 0, 128));

        sf::Text winner2Text("Player two wins!", font, FONT_SIZE + 10);
        winner2Text.setPosition(40, 80);
        winner2Text.setFillColor(sf::Color(128, 0, 128));

        sf::Text lostText("Sorry you lost!", font, FONT_SIZE + 10);
        lostText.setPosition(40, 80);
        lostText.setFillColor(sf::Color(128, 0, 128));

        //receive instruction from user to play again
        while (windowMenu.isOpen())
        {
            sf::Event eventMenu;
            while (windowMenu.pollEvent(eventMenu))
            {
                if (eventMenu.type == sf::Event::Closed)
                    windowMenu.close();
                if (eventMenu.type == sf::Event::MouseButtonPressed)
                {
                    sf::Vector2i mousePos = sf::Mouse::getPosition(windowMenu);
                    if (YesButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        play_again = true;
                        windowMenu.close();
                    }
                    if (NoButton.getGlobalBounds().contains(mousePos.x, mousePos.y))
                    {
                        play_again = false;
                        windowMenu.close();
                    }
                }

            }
            windowMenu.clear();
            windowMenu.draw(backgroundSprite);
            windowMenu.draw(YesButton);
            windowMenu.draw(NoButton);
            windowMenu.draw(gameTitle);
            windowMenu.draw(yesText);
            windowMenu.draw(noText);
            if (winner == 1)
                windowMenu.draw(winner1Text);
            else if (winner == 2)
                windowMenu.draw(winner2Text);
            else
                windowMenu.draw(lostText);
            windowMenu.display();
        }
        return play_again;
    }
}

//CONSTRUCTORS
Tile::Tile(int init_x, int init_y, World& init_world) : coord({ init_x,init_y }), my_world(init_world) {}
Snake::Snake(int init_x, int init_y, World& init_world) : Tile(init_x, init_y, init_world)
{
    current_way = RIGHT;
    intended_way = RIGHT;
    score = 0;
    which_one = 0;
}
Food::Food(int init_x, int init_y, World& init_world) : Tile(init_x, init_y, init_world) {}
Drink::Drink(int init_x, int init_y, World& init_world) : Tile(init_x, init_y, init_world) {}
Wall::Wall(int init_x, int init_y, World& init_world) : Tile(init_x, init_y, init_world) {}
World::World(int input_player, int input_level)
{
    number_of_player = input_player;
    difficulty_level = input_level;
    int number_of_snake = number_of_player;
    turn = 0;

    //resize the number of rows and columns in world vector
    world.resize(BOARD_HEIGHT);
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        world[y].resize(BOARD_WIDTH);
    }

    //fill the initial world with tiles 
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            world[y][x] = new Tile(y, x, *this);
        }
    }

    //Set up the wall (aka create the maze)
    create_maze();

    // Place randomly the food & drink
    respawn_food(MAX_NUM_OF_FOOD);
    respawn_drink(MAX_NUM_OF_DRINK);

    // Place randomly the head of the snake
    for (int i = 0; i < number_of_snake; i++)
    {
        int snake_x, snake_y;
        do
        {
            snake_x = rand() % BOARD_WIDTH;
            snake_y = rand() % BOARD_HEIGHT;
        } while (world[snake_y][snake_x]->who() != TILE);

        delete world[snake_y][snake_x];
        Snake* snake_object = new Snake(snake_x, snake_y, *this);
        world[snake_y][snake_x] = snake_object;
        two_snakes.push_back(snake_object);
    }
}

//OVERLOAD OPERATOR
vector<Tile*>& World::operator[](int row)
{
    if (row < 0 || row >= BOARD_HEIGHT)
    {
        cout << "Out of bounds number of row" << endl;
        exit(1);
    }
    else
        return world[row];
}

//DISPLAY FUNCTIONS
void World::display(sf::RenderWindow& window)
{
    sf::Texture backgroundTexture;
    if (backgroundTexture.loadFromFile("C:\\Users\\User\\source\\repos\\Snake Game\\Snake Game\\background.png"))
    {
        // Get the size of the window
        sf::Vector2u windowSize = window.getSize();

        // Create a sprite and set its texture to the loaded background
        sf::Sprite backgroundSprite(backgroundTexture);

        // Scale the background sprite to fit the window
        backgroundSprite.setScale(
            static_cast<float>(windowSize.x) / backgroundTexture.getSize().x,
            static_cast<float>(windowSize.y) / backgroundTexture.getSize().y
        );

        // Draw the scaled background sprite
        window.draw(backgroundSprite);
    }

    //Display tiles and 
    for (int y = 0; y < BOARD_HEIGHT; y++)
    {
        for (int x = 0; x < BOARD_WIDTH; x++)
        {
            world[y][x]->display(window);
        }
    }

    // Draw each snake in the vector containing 2 snakes
    for (Snake* snake : two_snakes)
    {
        //cout << "displaying snakes, size is " << two_snakes.size() << endl;
        snake->display(window);
    }
}
void Snake::display(sf::RenderWindow& window)
{
    sf::Texture snakeTexture1;
    if (!snakeTexture1.loadFromFile("C:\\Users\\User\\source\\repos\\Snake Game\\Snake Game\\pink_snake_skin.png"))
    {
        cout << "cannot open file" << endl;
        exit(1);
    }
    sf::Texture snakeTexture2;
    if (!snakeTexture2.loadFromFile("C:\\Users\\User\\source\\repos\\Snake Game\\Snake Game\\blue_snake_skin.png"))
    {
        cout << "cannot open file" << endl;
        exit(1);
    }

    sf::RectangleShape shape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    if (which_one == 1)
        shape.setTexture(&snakeTexture1);
    else if (which_one == 2)
        shape.setTexture(&snakeTexture2);

    //adjust the position so that it wont be default at (0,0)
    sf::Vector2f display_position;
    display_position.x = coord.x * TILE_SIZE + 10;
    display_position.y = coord.y * TILE_SIZE + 10;
    shape.setPosition(display_position);

    window.draw(shape);
}
void Food::display(sf::RenderWindow& window)
{
    sf::Texture foodTexture;
    if (!foodTexture.loadFromFile("C:\\Users\\User\\source\\repos\\Snake Game\\Snake Game\\bunch-of-grapes.png"))
    {
        cout << "cannot open file" << endl;
        exit(1);
    }

    sf::RectangleShape shape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    shape.setTexture(&foodTexture);

    //adjust the position so that it wont be default at (0,0)
    sf::Vector2f display_position;
    display_position.x = coord.x * TILE_SIZE + 10;
    display_position.y = coord.y * TILE_SIZE + 10;
    shape.setPosition(display_position);

    window.draw(shape);
}
void Drink::display(sf::RenderWindow& window)
{
    sf::Texture drinkTexture;
    if (!drinkTexture.loadFromFile("C:\\Users\\User\\source\\repos\\Snake Game\\Snake Game\\glass-of-water.png"))
    {
        cout << "cannot open file" << endl;
        exit(1);
    }

    sf::RectangleShape shape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    shape.setTexture(&drinkTexture);

    //adjust the position so that it wont be default at (0,0)
    sf::Vector2f display_position;
    display_position.x = coord.x * TILE_SIZE + 10;
    display_position.y = coord.y * TILE_SIZE + 10;
    shape.setPosition(display_position);

    window.draw(shape);
}
void Wall::display(sf::RenderWindow& window)
{
    sf::Texture wallTexture;
    if (!wallTexture.loadFromFile("C:\\Users\\User\\source\\repos\\Snake Game\\Snake Game\\wall.png"))
    {
        cout << "cannot open file" << endl;
        exit(1);
    }

    sf::RectangleShape shape(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    shape.setTexture(&wallTexture);

    //adjust the position so that it wont be default at (0,0)
    sf::Vector2f display_position;
    display_position.x = coord.x * TILE_SIZE + 10;
    display_position.y = coord.y * TILE_SIZE + 10;
    shape.setPosition(display_position);

    window.draw(shape);
}

//SIMULATE GAME FUNCTION
bool World::simulate_game(int& who_wins, int& snake_1_score, int& snake_2_score)
{
    //step 1 - listen instruction for each snake
    if (snake_1_die)
    {
        Snake* snake_2 = two_snakes[0];
        snake_2->declareWhichOne(2);
        snake_2->changeIntendedWay(snake_2->getCurrentWay());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            snake_2->changeIntendedWay(LEFT);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            snake_2->changeIntendedWay(RIGHT);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            snake_2->changeIntendedWay(UP);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            snake_2->changeIntendedWay(DOWN);
    }
    else
    {
        Snake* snake_1 = two_snakes[0];
        snake_1->declareWhichOne(1);
        snake_1->changeIntendedWay(snake_1->getCurrentWay());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
            snake_1->changeIntendedWay(LEFT);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
            snake_1->changeIntendedWay(RIGHT);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
            snake_1->changeIntendedWay(UP);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
            snake_1->changeIntendedWay(DOWN);
    }
    if (number_of_player == 2 && two_snakes.size() == 2)
    {
        Snake* snake_2 = two_snakes[1];
        snake_2->declareWhichOne(2);
        snake_2->changeIntendedWay(snake_2->getCurrentWay());
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
            snake_2->changeIntendedWay(LEFT);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
            snake_2->changeIntendedWay(RIGHT);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
            snake_2->changeIntendedWay(UP);
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
            snake_2->changeIntendedWay(DOWN);
    }

    //step 2 - update the snake (check if the intended direction is appropriate, if not then current direction remain)
    bool can_I_go_that_way = true;
    for (Snake* snake_object : two_snakes)
    {
        if (snake_object->getCurrentWay() == RIGHT && snake_object->getIntendedWay() == LEFT)
            can_I_go_that_way = false;
        //cout << "Cant turn over the snake right to left" << endl;
        else if (snake_object->getCurrentWay() == LEFT && snake_object->getIntendedWay() == RIGHT)
            can_I_go_that_way = false;
        //cout << "Cant turn over the snake left to right" << endl;
        else if (snake_object->getCurrentWay() == UP && snake_object->getIntendedWay() == DOWN)
            can_I_go_that_way = false;
        //cout << "Cant turn over the snake up to down" << endl;
        else if (snake_object->getCurrentWay() == DOWN && snake_object->getIntendedWay() == UP)
            can_I_go_that_way = false;
        //cout << "Cant turn over the snake down to up" << endl;
        else if (snake_object->getCurrentWay() == snake_object->getIntendedWay())
            can_I_go_that_way = true;
        //cout << "Same way, no need to change" << endl;
        else
            snake_object->changeCurrentWay(snake_object->getIntendedWay()); //current way is updated with inteded way from user
    }

    // step 3 - call the move function for the snake 
    int score_1 = 0, score_2 = 0;
    bool snake_2_die = false;
    for (Snake* snake_object : two_snakes)
    {
        if (number_of_player == 1)
            score_1 = snake_object->score_before_die();
        else if (number_of_player == 2)
        {
            if (two_snakes.size() == 1) //2 player but 1 lose
            {
                if (snake_1_die) //if snake_1 died then snake_object is snake 2
                    score_2 = snake_object->score_before_die();
                else
                    score_1 = snake_object->score_before_die();
            }
            else if (two_snakes.size() == 2)
            {
                score_1 = two_snakes[0]->score_before_die();
                score_2 = two_snakes[1]->score_before_die();
            }
        }
        //check if hit the wall or hit other snake
        if (snake_object->checkCollision())
        {
            if (snake_object == two_snakes[0])
            {
                two_snakes.pop_front();
                snake_1_die = true;
            }
            else if (snake_object == two_snakes[1])
            {
                two_snakes.pop_back();
                snake_2_die = true;
            }

            //after delete the die snake, if all snakes die then exit
            if (two_snakes.size() == 0)
            {
                if (number_of_player == 1)
                {
                    //cout << "Score of snake is " << score_1 << endl;
                    snake_1_score = score_1;
                }
                else if (number_of_player == 2)
                {
                    //cout << "Score of snake number 1 is " << score_1 << endl;
                    //cout << "Score of snake number 2 is " << score_2 << endl;
                    snake_1_score = score_1;
                    snake_2_score = score_2;

                    //decide who will win
                    if (score_1 > score_2)
                        who_wins = 1;
                    //cout << "Snake number 1 wins :)" << endl;
                    else if (score_1 < score_2)
                        who_wins = 2;
                    //cout << "Snake number 2 wins :)" << endl;
                    else
                        who_wins = 0;
                    //cout << "Draw, nobody wins :|" << endl;
                }
                //cout << turn << endl;
                return true; //it is true that game is over
            }
        }
        else
        {
            snake_object->move(remaining_food);
            turn++;
        }
    }

    //respawn if needed
    if (remaining_food == 0)
        respawn_food(MAX_NUM_OF_FOOD);
    if (turn % 20 == 0) //every 20 turns, if (turn == 20) then if turn == 40 it wont spawn
        respawn_food(1);
    if (turn % 40 == 0)
        respawn_drink(1);
    if (turn % 30 == 0)
        delete_drink();

    return false; //it is false that game is over
}
void World::respawn_food(int number_of_food)
{
    // Place randomly the food
    if (remaining_food == 0)
        remaining_food = MAX_NUM_OF_FOOD;
    else if (remaining_food != 0)
        remaining_food += number_of_food;
    for (int i = 0; i < number_of_food; i++)
    {
        int food_x, food_y;
        do
        {
            food_x = rand() % (BOARD_WIDTH - 1); //minus 1 to make the food not near the corner, easier to eat
            food_y = rand() % (BOARD_HEIGHT - 1);
        } while (world[food_y][food_x]->who() != TILE);

        delete world[food_y][food_x];
        world[food_y][food_x] = new Food(food_x, food_y, *this);
    }
}
void World::respawn_drink(int number_of_drink)
{
    // Place randomly the food
    for (int i = 0; i < number_of_drink; i++)
    {
        int drink_x, drink_y;
        do
        {
            drink_x = rand() % (BOARD_WIDTH - 1); //minus 1 to make the food not near the corner, easier to eat
            drink_y = rand() % (BOARD_HEIGHT - 1);
        } while (world[drink_y][drink_x]->who() != TILE);

        delete world[drink_y][drink_x];
        world[drink_y][drink_x] = new Drink(drink_x, drink_y, *this);
    }
}
void World::delete_drink()
{
    int drink_x, drink_y;
    do
    {
        drink_x = rand() % (BOARD_WIDTH - 1); //minus 1 to make the food not near the corner, easier to eat
        drink_y = rand() % (BOARD_HEIGHT - 1);
    } while (world[drink_y][drink_x]->who() != DRINK);

    delete world[drink_y][drink_x];
    world[drink_y][drink_x] = new Tile(drink_x, drink_y, *this);
}
void World::create_maze()
{
    //default wall for every level
    for (int x = 0; x < BOARD_WIDTH; x++) //up wall
    {
        int y = 0;
        delete world[y][x];
        world[y][x] = new Wall(x, y, *this);
    }
    for (int y = 1; y < BOARD_HEIGHT; y++) //left wall
    {
        int x = 0;
        delete world[y][x];
        world[y][x] = new Wall(x, y, *this);
    }
    for (int x = 1; x < BOARD_WIDTH; x++) //down wall
    {
        int y = BOARD_HEIGHT - 1;
        delete world[y][x];
        world[y][x] = new Wall(x, y, *this);
    }
    for (int y = 1; y < BOARD_HEIGHT; y++) //right wall
    {
        int x = BOARD_WIDTH - 1;
        delete world[y][x];
        world[y][x] = new Wall(x, y, *this);
    }

    difficulty_level = tolower(difficulty_level);
    if (difficulty_level == 'm' || difficulty_level == 'h')
    {
        for (int y = 4; y < BOARD_HEIGHT / 3; y++)
        {
            int x = 22;
            delete world[y][x];
            world[y][x] = new Wall(x, y, *this);
        }
        for (int y = BOARD_HEIGHT - 2; y > (BOARD_HEIGHT - 10); y--)
        {
            int x = 15;
            delete world[y][x];
            world[y][x] = new Wall(x, y, *this);
        }
        for (int x = 14; x > 11; x--)
        {
            int y = BOARD_HEIGHT - 9;
            delete world[y][x];
            world[y][x] = new Wall(x, y, *this);
        }
        for (int x = 0; x < 7; x++)
        {
            int y = 5;
            delete world[y][x];
            world[y][x] = new Wall(x, y, *this);
        }
        for (int x = BOARD_WIDTH / 2 + 10; x < BOARD_WIDTH; x++)
        {
            int y = BOARD_HEIGHT - 14;
            delete world[y][x];
            world[y][x] = new Wall(x, y, *this);
        }
    }
    if (difficulty_level == 'h')
    {
        for (int x = 6; x < 10; x++)
        {
            int y = BOARD_HEIGHT / 2 - 3;
            delete world[y][x];
            world[y][x] = new Wall(x, y, *this);
        }
        for (int y = BOARD_HEIGHT / 2 - 3; y < BOARD_HEIGHT / 2; y++)
        {
            int x = 6;
            delete world[y][x];
            world[y][x] = new Wall(x, y, *this);
        }
        /*for (int y = 12; y < 19; y++)
        {
            int x = 7;
            delete world[y][x];
            world[y][x] = new Wall(x, y, *this);
        }*/
        for (int y = 21; y < 25; y++)
        {
            int x = 27;
            delete world[y][x];
            world[y][x] = new Wall(x, y, *this);
        }
        for (int x = 27; x < 30; x++)
        {
            int y = 25;
            delete world[y][x];
            world[y][x] = new Wall(x, y, *this);
        }
    }
}

//MOVING FUNCTIONS
void Snake::move(int& num_of_food)
{
    //cout << "call move() function" << endl;
    int previous_coordX;
    int previous_coordY;
    switch (current_way)
    {
    case UP:
        if (my_world[coord.y - 1][coord.x]->who() == TILE)
        {
            //move the head
            previous_coordX = coord.x; //save the old coord of the head
            previous_coordY = coord.y;
            swap(my_world[coord.y - 1][coord.x], my_world[coord.y][coord.x]);
            coord.y--;

            //move the current body part into the position of previous body part
            body_follow_head(previous_coordX, previous_coordY);
        }
        else if (my_world[coord.y - 1][coord.x]->who() == FOOD) //if meet a food then grow
        {
            //the body tile created must follow color of the head
            Snake* snake_head = static_cast<Snake*>(my_world[coord.y][coord.x]);

            //swap food and old head
            swap(my_world[coord.y - 1][coord.x], my_world[coord.y][coord.x]);
            coord.y--;

            //delete food and replace with a new body snake tile
            delete my_world[coord.y + 1][coord.x];
            my_world[coord.y + 1][coord.x] = new Snake(coord.x, coord.y + 1, my_world);

            //new body snake tile is pushed in the list
            Snake* new_body_part = static_cast<Snake*>(my_world[coord.y + 1][coord.x]); //cast to the known type
            if (snake_head->which_one == 1)
                new_body_part->declareWhichOne(1);
            else if (snake_head->which_one == 2)
                new_body_part->declareWhichOne(2);
            snake_body.push_front(new_body_part);

            //update score & remaining food
            score++;
            num_of_food--;
        }
        else if (my_world[coord.y - 1][coord.x]->who() == DRINK) //if meet a food then grow
        {
            Snake* snake_head = static_cast<Snake*>(my_world[coord.y][coord.x]);
            swap(my_world[coord.y - 1][coord.x], my_world[coord.y][coord.x]);
            coord.y--;

            //delete food and replace with a new body snake tile
            delete my_world[coord.y + 1][coord.x];
            my_world[coord.y + 1][coord.x] = new Snake(coord.x, coord.y + 1, my_world);

            //new body snake tile is pushed in the list
            Snake* new_body_part = static_cast<Snake*>(my_world[coord.y + 1][coord.x]); //cast to the known type
            if (snake_head->which_one == 1)
                new_body_part->declareWhichOne(1);
            else if (snake_head->which_one == 2)
                new_body_part->declareWhichOne(2);
            snake_body.push_front(new_body_part);

            //update score & remaining food
            score += 2;
        }
        break;
    case DOWN:
        if (my_world[coord.y + 1][coord.x]->who() == TILE)
        {
            //move the head
            previous_coordX = coord.x;
            previous_coordY = coord.y;
            swap(my_world[coord.y + 1][coord.x], my_world[coord.y][coord.x]);
            coord.y++;

            //move the current body part into the position of previous body part
            body_follow_head(previous_coordX, previous_coordY);
        }
        else if (my_world[coord.y + 1][coord.x]->who() == FOOD) //if meet a food then grow
        {
            Snake* snake_head = static_cast<Snake*>(my_world[coord.y][coord.x]);

            //swap food and old head
            swap(my_world[coord.y + 1][coord.x], my_world[coord.y][coord.x]);
            coord.y++;

            //delete food and replace with a new body snake tile
            delete my_world[coord.y - 1][coord.x];
            my_world[coord.y - 1][coord.x] = new Snake(coord.x, coord.y - 1, my_world);

            //new body snake tile is pushed in the list
            Snake* new_body_part = static_cast<Snake*>(my_world[coord.y - 1][coord.x]);
            if (snake_head->which_one == 1)
                new_body_part->declareWhichOne(1);
            else if (snake_head->which_one == 2)
                new_body_part->declareWhichOne(2);
            snake_body.push_front(new_body_part);

            //update score & remaining food
            score++;
            num_of_food--;
        }
        else if (my_world[coord.y + 1][coord.x]->who() == DRINK) //if meet a food then grow
        {
            Snake* snake_head = static_cast<Snake*>(my_world[coord.y][coord.x]);
            swap(my_world[coord.y + 1][coord.x], my_world[coord.y][coord.x]);
            coord.y++;
            delete my_world[coord.y - 1][coord.x];
            my_world[coord.y - 1][coord.x] = new Snake(coord.x, coord.y - 1, my_world);

            //new body snake tile is pushed in the list
            Snake* new_body_part = static_cast<Snake*>(my_world[coord.y - 1][coord.x]);
            if (snake_head->which_one == 1)
                new_body_part->declareWhichOne(1);
            else if (snake_head->which_one == 2)
                new_body_part->declareWhichOne(2);
            snake_body.push_front(new_body_part);

            //update score & remaining food
            score += 2;
        }
        break;
    case LEFT:
        if (my_world[coord.y][coord.x - 1]->who() == TILE)
        {
            //move the head
            previous_coordX = coord.x;
            previous_coordY = coord.y;
            swap(my_world[coord.y][coord.x - 1], my_world[coord.y][coord.x]);
            coord.x--;

            //move the current body part into the position of previous body part
            body_follow_head(previous_coordX, previous_coordY);
        }
        else if (my_world[coord.y][coord.x - 1]->who() == FOOD) //if meet a food then grow
        {
            Snake* snake_head = static_cast<Snake*>(my_world[coord.y][coord.x]);

            //swap food and old head
            swap(my_world[coord.y][coord.x - 1], my_world[coord.y][coord.x]);
            coord.x--;

            //delete food and replace with a new body snake tile
            delete my_world[coord.y][coord.x + 1];
            my_world[coord.y][coord.x + 1] = new Snake(coord.x + 1, coord.y, my_world);

            //new body snake tile is pushed in the list
            Snake* new_body_part = static_cast<Snake*>(my_world[coord.y][coord.x + 1]);
            if (snake_head->which_one == 1)
                new_body_part->declareWhichOne(1);
            else if (snake_head->which_one == 2)
                new_body_part->declareWhichOne(2);
            snake_body.push_front(new_body_part);

            //update score & remaining food
            score++;
            num_of_food--;
        }
        else if (my_world[coord.y][coord.x - 1]->who() == DRINK) //if meet a food then grow
        {
            Snake* snake_head = static_cast<Snake*>(my_world[coord.y][coord.x]);
            swap(my_world[coord.y][coord.x - 1], my_world[coord.y][coord.x]);
            coord.x--;

            //delete food and replace with a new body snake tile
            delete my_world[coord.y][coord.x + 1];
            my_world[coord.y][coord.x + 1] = new Snake(coord.x + 1, coord.y, my_world);

            //new body snake tile is pushed in the list
            Snake* new_body_part = static_cast<Snake*>(my_world[coord.y][coord.x + 1]);
            if (snake_head->which_one == 1)
                new_body_part->declareWhichOne(1);
            else if (snake_head->which_one == 2)
                new_body_part->declareWhichOne(2);
            snake_body.push_front(new_body_part);

            //update score & remaining food
            score += 2;
        }
        break;
    case RIGHT:
        if (my_world[coord.y][coord.x + 1]->who() == TILE)
        {
            //move the head
            previous_coordX = coord.x;
            previous_coordY = coord.y;
            swap(my_world[coord.y][coord.x + 1], my_world[coord.y][coord.x]);
            coord.x++;

            //move the current body part into the position of previous body part
            body_follow_head(previous_coordX, previous_coordY);
        }
        else if (my_world[coord.y][coord.x + 1]->who() == FOOD) //if meet a food then grow
        {
            Snake* snake_head = static_cast<Snake*>(my_world[coord.y][coord.x]);

            //swap food and old head
            swap(my_world[coord.y][coord.x + 1], my_world[coord.y][coord.x]);
            coord.x++;

            //delete food and replace with a new body snake tile
            delete my_world[coord.y][coord.x - 1];
            my_world[coord.y][coord.x - 1] = new Snake(coord.x - 1, coord.y, my_world);

            //new body snake tile is pushed in the list
            Snake* new_body_part = static_cast<Snake*>(my_world[coord.y][coord.x - 1]);
            if (snake_head->which_one == 1)
                new_body_part->declareWhichOne(1);
            else if (snake_head->which_one == 2)
                new_body_part->declareWhichOne(2);
            snake_body.push_front(new_body_part);

            //update score & remaining food
            score++;
            num_of_food--;
        }
        else if (my_world[coord.y][coord.x + 1]->who() == DRINK) //if meet a food then grow
        {
            Snake* snake_head = static_cast<Snake*>(my_world[coord.y][coord.x]);
            swap(my_world[coord.y][coord.x + 1], my_world[coord.y][coord.x]);
            coord.x++;

            //delete food and replace with a new body snake tile
            delete my_world[coord.y][coord.x - 1];
            my_world[coord.y][coord.x - 1] = new Snake(coord.x - 1, coord.y, my_world);

            //new body snake tile is pushed in the list
            Snake* new_body_part = static_cast<Snake*>(my_world[coord.y][coord.x - 1]);
            if (snake_head->which_one == 1)
                new_body_part->declareWhichOne(1);
            else if (snake_head->which_one == 2)
                new_body_part->declareWhichOne(2);
            snake_body.push_front(new_body_part);

            //update score & remaining food
            score += 2;
        }
        break;
    }
}
void Snake::body_follow_head(int x_head, int y_head)
{
    int previous_X = x_head;
    int previous_Y = y_head;
    for (auto body_part : snake_body)
    {
        //snake_body_move(body_part, previous_coordX, previous_coordY);
        int gotoX = previous_X - body_part->coord.x;
        int gotoY = previous_Y - body_part->coord.y;
        if (gotoX == 1)
        {
            //go right
            swap(my_world[body_part->coord.y][body_part->coord.x + 1], my_world[body_part->coord.y][body_part->coord.x]);
            previous_X = body_part->coord.x;
            previous_Y = body_part->coord.y;
            body_part->coord.x++;
        }
        else if (gotoX == -1)
        {
            //go left 
            swap(my_world[body_part->coord.y][body_part->coord.x - 1], my_world[body_part->coord.y][body_part->coord.x]);
            previous_X = body_part->coord.x;
            previous_Y = body_part->coord.y;
            body_part->coord.x--;
        }
        else if (gotoY == 1)
        {
            //go down
            swap(my_world[body_part->coord.y + 1][body_part->coord.x], my_world[body_part->coord.y][body_part->coord.x]);
            previous_X = body_part->coord.x;
            previous_Y = body_part->coord.y;
            body_part->coord.y++;
        }
        else if (gotoY == -1)
        {
            //go up
            swap(my_world[body_part->coord.y - 1][body_part->coord.x], my_world[body_part->coord.y][body_part->coord.x]);
            previous_X = body_part->coord.x;
            previous_Y = body_part->coord.y;
            body_part->coord.y--;
        }
    }
}
bool Snake::checkCollision()
{
    //cout << "Snake hits other snake or hit wall :(" << endl;
    switch (current_way)
    {
    case UP:
        if (my_world[coord.y - 1][coord.x]->who() == SNAKE
            || my_world[coord.y - 1][coord.x]->who() == WALL)
        {
            //delete the body
            Snake* head = static_cast<Snake*>(my_world[coord.y][coord.x]);
            for (auto body_part : head->snake_body)
            {
                int tempX = body_part->getCoordX();
                int tempY = body_part->getCoordY();
                delete my_world[tempY][tempX];
                my_world[tempY][tempX] = new Tile(tempX, tempY, my_world);
            }

            //delete the snake that hit other snake
            int tempX = coord.x;
            int tempY = coord.y;
            delete my_world[coord.y][coord.x];
            my_world[tempY][tempX] = new Tile(tempX, tempY, my_world);
            return true;
        }
        break;
    case DOWN:
        if (my_world[coord.y + 1][coord.x]->who() == SNAKE
            || my_world[coord.y + 1][coord.x]->who() == WALL)
        {
            //delete the body
            Snake* head = static_cast<Snake*>(my_world[coord.y][coord.x]);
            for (auto body_part : head->snake_body)
            {
                int tempX = body_part->getCoordX();
                int tempY = body_part->getCoordY();
                delete my_world[tempY][tempX];
                my_world[tempY][tempX] = new Tile(tempX, tempY, my_world);
            }

            //delete the snake that hit other snake
            int tempX = coord.x;
            int tempY = coord.y;
            delete my_world[coord.y][coord.x];
            my_world[tempY][tempX] = new Tile(tempX, tempY, my_world);
            return true;
        }
        break;
    case LEFT:
        if (my_world[coord.y][coord.x - 1]->who() == SNAKE
            || my_world[coord.y][coord.x - 1]->who() == WALL)
        {
            //delete the body
            Snake* head = static_cast<Snake*>(my_world[coord.y][coord.x]);
            for (auto body_part : head->snake_body)
            {
                int tempX = body_part->getCoordX();
                int tempY = body_part->getCoordY();
                delete my_world[tempY][tempX];
                my_world[tempY][tempX] = new Tile(tempX, tempY, my_world);
            }

            //delete the snake that hit other snake
            int tempX = coord.x;
            int tempY = coord.y;
            delete my_world[coord.y][coord.x];
            my_world[tempY][tempX] = new Tile(tempX, tempY, my_world);
            return true;
        }
        break;
    case RIGHT:
        if (my_world[coord.y][coord.x + 1]->who() == SNAKE
            || my_world[coord.y][coord.x + 1]->who() == WALL)
        {
            //delete the body
            Snake* head = static_cast<Snake*>(my_world[coord.y][coord.x]);
            for (auto body_part : head->snake_body)
            {
                int tempX = body_part->getCoordX();
                int tempY = body_part->getCoordY();
                delete my_world[tempY][tempX];
                my_world[tempY][tempX] = new Tile(tempX, tempY, my_world);
            }

            //delete the snake that hit other snake
            int tempX = coord.x;
            int tempY = coord.y;
            delete my_world[coord.y][coord.x];
            my_world[tempY][tempX] = new Tile(tempX, tempY, my_world);
            return true;
        }
        break;
    }
    return false;
}