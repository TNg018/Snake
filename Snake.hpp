//Snake.hpp

# ifndef SNAKE_HPP
# define SNAKE_HPP

# ifdef _WIN32
# define CLEAN_SCREEN system("CLS");
# elif __APPLE__
# define CLEAN_SCREEN system("clear");
# elif __linux__ 
# define CLEAN_SCREEN system("clear");
# endif

const int WIDTH = 20;
const int HEIGHT = 17;

class Snake {
    //public member functions
    public:
        Snake();
        void playGame();
    
    //private member functions
    private:
        void Setup();
        void Draw();
        void Input();
        void Algorithm();

    //private member variables
    bool gameOver;
    int x, y, fruitX, fruitY, score;
    //snake coordinates
    int tailX[100], tailY[100];
    int nTail;

    enum eDirection {STOP = 0, LEFT, RIGHT, UP, DOWN};
    eDirection dir;
};

# endif