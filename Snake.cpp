#include <iostream>
#include "Snake.hpp"
#include <cstdlib>
#include <ctime>

//initialize Snake variable
Snake::Snake() {}

void Snake::playGame() {
    Setup();
    
    while (!gameOver) {
        Draw();
        Input();
        Algorithm();
    } 
}

void Snake::Setup() {
    srand(time(NULL));
    gameOver = false;
    dir = STOP;
    x = WIDTH / 2;
    y = HEIGHT / 2;
    //place fruit randomly
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    nTail = 1;
    score = 0;
}

// Draw the borders of the game
// Draw snake head in center of screen: HEIGHT/2, WIDTH/2
// Keep track of snake tail
// Place fruit randomly on screen
void Snake::Draw() {
    CLEAN_SCREEN;
    bool print = false;
    std::cout << "Welcome to Snake! " << std::endl;
   
    //top wall
    for (int i = 0; i < WIDTH+2; i++) {
        std::cout << "#";
    }
    //line break below needed; otherwise random # to the right of the top column
    std::cout<< "\n";

    for (int i = 0; i <= HEIGHT; i++) {
        for (int j = 0; j <= WIDTH; j++) {
            // left wall
            if (j == 0) {
                std::cout << "#";
            }
            //right wall
            if (j == WIDTH){
                std::cout<< "#";
            }
            // snake head placed in center to start
            if (i == y && j == x) {
                std::cout << "*";
            }
            // placing fruit randomly
            else if (i == fruitY && j == fruitX) {
                std::cout << "%";
            }
            // adding to tail if nTail increases
            else {
                print = false;
                // place a tail after the snake head
                for (int k = 0; k< nTail ; k++) {
                    if (tailX[k] == j && tailY[k] == i) {
                        std::cout << "*"; 
                        print = true;
                    }
                }
                // fill other squares with empty spaces
                if (!print){
                    std::cout << " ";
                }
            }  
        }
        std::cout << std::endl;
    }
    //bottom wall
    for (int i = 0; i < WIDTH+2; i++) {
        std::cout << "#";
    }
            

    std::cout << "\nScore:" << score;

    std::cout<<std::endl;

}

// Movement UP / DOWN / RIGHT / LEFT based on keypress
void Snake::Input() {
    char key_press;
    std::cin >> key_press;

    if ( (key_press == 'a') || (key_press == 'w') || (key_press == 's') || (key_press == 'd') || (key_press == 'q') ) {
        switch( key_press ) {
            case 'a':
                dir = LEFT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'q':
                gameOver = true;
                break;
        }
    }

    switch (dir) {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case DOWN:
            y++;
            break;
        case UP:
            y--;
            break;
        default:
            break;
    }
}

void Snake::Algorithm() {
    // tail coordinates
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    // 0 = head
    // adding a tail to snake 
    for (int i = 1; i < nTail; i++) {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    if (x >= WIDTH) {
        x =0;
    }
    else if (x <0) {
        x = WIDTH -1;
    }

    if (y >= HEIGHT) {
        y = 0; 
    }
    else if (y < 0) { 
        y = HEIGHT - 1; 
    }

    //if touching tail, game over
    for (int i = 1; i < nTail; i++) {
        if (tailX[i] == x && tailY[i] == y) {
            gameOver = true;
        }
    }

    // if touching fruit, increase score and increment tail
    if ( (x == fruitX) && (y == fruitY) ) {
        score += 1;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
        nTail++;
    }
}