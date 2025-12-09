#include <curses.h>
#include <cstdlib>
#include <ctime>
#include <string>
#include "Drawings.cpp"
#include "HighScore.cpp"

using namespace std;

void playGame() {
    int highScore = loadHighScore();
    
    int h, w;
    getmaxyx(stdscr, h, w);
    
    // Variabel Fisika
    float birdY = h / 2.0;
    float velocity = 0.0;
    float gravity = 0.25;    
    float jumpForce = -1.8;  
    float maxFall = 2.0;
    
    int birdX = w / 4;
    float pipeX = w - 2;
    
    // Variabel Kesulitan
    int gapSize = 9;     
    int minGapSize = 4;             
    int gameDelay = 30;           
    int minDelay = 5;              
    
    time_t startTime = time(NULL);       
    time_t lastIncreaseTime = startTime; 
    
    int gapY = rand() % (h - gapSize - 4) + 2;
    int score = 0;
    int level = 1;                  
    bool gameOver = false;
    char birdChar = '>'; 

    nodelay(stdscr, TRUE); 

    while(!gameOver) {
        erase(); 

        // Update Kesulitan
        time_t currTime = time(NULL);
        if (difftime(currTime, lastIncreaseTime) >= 10.0) {
            if (gameDelay > minDelay) {
                gameDelay -= 4; 
                level++;
                attron(A_REVERSE); // Efek visual flash saat level naik
                attroff(A_REVERSE);
            }
            lastIncreaseTime = currTime;
        }
