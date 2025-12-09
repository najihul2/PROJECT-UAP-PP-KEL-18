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
// Input
        int ch = getch();
        if (ch == ' ') velocity = jumpForce;
        else if (ch == 'q') gameOver = true;

        // Fisika
        velocity += gravity;
        if (velocity > maxFall) velocity = maxFall;
        birdY += velocity;
        pipeX -= 0.8;

        // Animasi karakter burung
        if (velocity < -0.5) birdChar = '^';
        else if (velocity > 0.5) birdChar = 'v';
        else birdChar = '>';

        // Logika Pipa
        if (pipeX < 0) {
            pipeX = w - 2;
            gapY = rand() % (h - gapSize - 4) + 2;
            score++;
            if (score % 5 == 0 && gapSize > minGapSize) gapSize--;
        }

        // Tabrakan (Collision Detection)
        if (birdY >= h - 1 || birdY < 0) gameOver = true;
        
        int pX = (int)pipeX;
        if (birdX >= pX && birdX <= pX + 2) {
            if (birdY < gapY || birdY > gapY + gapSize) gameOver = true;
        }

        // RENDERING
        box(stdscr, 0, 0); 
        mvprintw(0, 2, " SCORE: %d | BEST: %d ", score, highScore);
        mvprintw(0, w - 25, " TIME: %.0fs | LVL: %d ", difftime(currTime, startTime), level);

        // Gambar Burung
        attron(A_BOLD); 
        mvaddch((int)birdY, birdX, birdChar);
        attroff(A_BOLD);

        // Gambar Pipa
        for (int y = 1; y < h - 1; y++) {
            if (y < gapY || y > gapY + gapSize) {
                mvaddch(y, pX, '#'); 
                mvaddch(y, pX + 1, '#');
            }
        }

        refresh();
        napms(gameDelay); 
    }

    // GAME OVER LOGIC
    if (score > highScore) {
        saveHighScore(score);
        highScore = score;
    }

    nodelay(stdscr, FALSE);
    erase();
    box(stdscr, 0, 0);
    
    int startY = h / 2 - 8;
    int startX = (w - 24) / 2;
    drawGameOverText(startY, startX); // Memanggil dari Drawings.cpp
    
    mvprintw(startY + 9, w/2 - 5, "SCORE: %d", score);
    mvprintw(startY + 10, w/2 - 8, "HIGH SCORE: %d", highScore);
    
    attron(A_BOLD); 
    mvprintw(startY + 12, w/2 - 12, "Tekan SPASI untuk kembali");
    attroff(A_BOLD);
    
    refresh();
    while(getch() != ' '); 
}

void showHighScore() {
    clear();
    int h, w;
    getmaxyx(stdscr, h, w);
    int hs = loadHighScore(); // Memanggil dari HighScore.cpp
    
    box(stdscr, 0, 0);
    drawTitle(h/2 - 8, (w - 30)/2); // Memanggil dari Drawings.cpp
    
    mvprintw(h/2 - 1, w/2 - 8, "REKOR TERTINGGI");
    
    attron(A_BOLD | A_UNDERLINE);
    mvprintw(h/2 + 1, w/2 - 1, "%d", hs);
    attroff(A_BOLD | A_UNDERLINE);
    
    mvprintw(h/2 + 4, w/2 - 12, "Tekan tombol apa saja...");
    refresh();
    getch();
}

void mainMenu() {
    const char* options[] = {"MAINKAN", "HIGH SCORE", "KELUAR"};
    int choice = 0;
    
    while(true) {
        erase();
        int h, w;
        getmaxyx(stdscr, h, w);

        drawTitle(h/4, (w - 30) / 2);

        int menuY = h / 2 + 2;
        for(int i = 0; i < 3; i++) {
            if (i == choice) {
                attron(A_REVERSE | A_BOLD); 
                mvprintw(menuY + (i*2), (w-20)/2, "  %s  ", options[i]);
                attroff(A_REVERSE | A_BOLD);
                
                mvprintw(menuY + (i*2), (w-20)/2 - 3, "->");
                mvprintw(menuY + (i*2), (w-20)/2 + 12, "<-");
            } else {
                mvprintw(menuY + (i*2), (w-20)/2, "  %s  ", options[i]);
            }
        }
        
        mvprintw(h-2, 2, "Gunakan Panah Atas/Bawah & Enter");

        refresh();

        int ch = getch(); 

        if (ch == KEY_UP) {
            if (choice > 0) choice--;
        }
        else if (ch == KEY_DOWN) {
            if (choice < 2) choice++;
        }
        else if (ch == 10) { 
            if (choice == 0) playGame();
            else if (choice == 1) showHighScore();
            else if (choice == 2) break;
        }
    }
}
