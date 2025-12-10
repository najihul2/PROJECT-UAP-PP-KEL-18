#include <fstream>

using namespace std;

const char* FILE_NAME = "highscore.txt";

int loadHighScore() {
    int hs = 0;
    ifstream fileInput(FILE_NAME);
    if (fileInput.is_open()) {
        fileInput >> hs;
        fileInput.close();
    }
    return hs;
}

void saveHighScore(int score) {
    ofstream fileOutput(FILE_NAME);
    if (fileOutput.is_open()) {
        fileOutput << score;
        fileOutput.close();
    }
}
