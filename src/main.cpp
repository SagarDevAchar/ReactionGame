// 8:17 AM

#include <stdlib.h>
#include <time.h>
#include <string>

#include <windows.h>
#include <shellapi.h>

#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

enum gameInputs {Z = 1, X, C, B, N, M};

typedef struct gameParams {
    int gameMode;
    int targetCount;
    int hitCount;
    int missCount;

    int currentScore;
    float accuracy;

    int gameStarted;
    int gameEnded;
} game;

// TODO: Rectify this Function using Loops
char* gstrfmt(char type, int value) {
    char* strf = (char*)malloc(sizeof(char));

    switch (type) {
    case 'T':
        sprintf(strf, "Target : %03d", value);
        break;
    case 'H':
        sprintf(strf, "Hits    : %03d", value);
        break;
    case 'M':
        sprintf(strf, "Misses : %03d", value);
        break;
    case 'S':
        sprintf(strf, "Score : %06d", value);
        break;
    case 'A':
        sprintf(strf, "Accuracy : %03d%%", value);
        break;
    }

    return strf;
}

int gWaitKey(int timeout_ms) {
    int key = waitKey(timeout_ms) & 0xFF;

    if (key >= 65 && key <= 90)
        key += 32;

    switch (key) {
    case 'z':
        return Z;
    case 'x':
        return X;
    case 'c':
        return C;
    case 'b':
        return B;
    case 'n':
        return N;
    case 'm':
        return M;
    default:
        return key;
    }
}

int iScore(int hit, float time) {
    int score = 0;

    if (hit == 1) {
        if (time <= 100)
            score = 1000;
        else if (time >= 1000)
            score = 100;
        else {
            score = 1100 - time;
        }
    }

    else {
       if (time <= 100)
            score = -10;
        else if (time >= 1000)
            score = -50;
        else {
            score = (-4.0 * time / 90.0) - (50.0 / 9.0);
        }
    }

    return score;
}

Mat createStartScreen() {
    Mat frame = Mat(1080, 1920, CV_8UC3);

    putText(frame, "REACTION GAME", Point(485, 200), FONT_HERSHEY_PLAIN, 7.5, Scalar(255, 255, 255), 10);
    putText(frame, "(This Game supports Keyboard Input Only)", Point(600, 250), FONT_HERSHEY_PLAIN, 2, Scalar(255, 255, 255), 2);

    rectangle(frame, Point(585, 340), Point(1335, 490), Scalar(0, 255, 0), -1);
    putText(frame, "START REACTION GAME", Point(635, 400), FONT_HERSHEY_PLAIN, 3.5, Scalar(0, 0, 0), 4);
    putText(frame, "[Press SPACE]", Point(800, 470), FONT_HERSHEY_PLAIN, 2.5, Scalar(0, 0, 0), 3);

    rectangle(frame, Point(585, 550), Point(1335, 625), Scalar(0, 255, 255), -1);
    putText(frame, "How to Play [Press H]", Point(690, 605), FONT_HERSHEY_PLAIN, 3, Scalar(0, 0, 0), 3);

    rectangle(frame, Point(585, 685), Point(1335, 755), Scalar(0, 0, 255), -1);
    putText(frame, "Quit Game [Press Q]", Point(710, 735), FONT_HERSHEY_PLAIN, 3, Scalar(0, 0, 0), 3);

    putText(frame, "Music and Design by Sagar Dev Achar", Point(490, 900), FONT_HERSHEY_PLAIN, 3, Scalar(255, 255, 255), 4);
    putText(frame, "https://www.github.com/SagarDevAchar", Point(640, 975), FONT_HERSHEY_PLAIN, 2, Scalar(255, 255, 255), 2);
    putText(frame, "[Press L to open link]", Point(770, 1015), FONT_HERSHEY_PLAIN, 2, Scalar(255, 255, 255), 2);

    return frame;
}

Mat createHTPScreen() {
    Mat frame = Mat(1080, 1920, CV_8UC3);

    putText(frame, "How to Play", Point(600, 200), FONT_HERSHEY_PLAIN, 7.5, Scalar(255, 255, 255), 10);

    putText(frame, "- There will be 6 Boxes / Targets on your Screen", Point(150, 300), FONT_HERSHEY_PLAIN, 2, Scalar(255, 255, 255), 2);
    putText(frame, "- These boxes are mapped to [Z] [X] [C] [B] [N] [M] keys respectively", Point(150, 350), FONT_HERSHEY_PLAIN, 2, Scalar(255, 255, 255), 2);
    putText(frame, "- Press the respective keys as the boxes light up", Point(150, 400), FONT_HERSHEY_PLAIN, 2, Scalar(255, 255, 255), 2);
    putText(frame, "- Every HIT increases your Score & Accuracy", Point(150, 450), FONT_HERSHEY_PLAIN, 2, Scalar(255, 255, 255), 2);
    putText(frame, "- Every MISS decreases your Score & Accuracy", Point(150, 500), FONT_HERSHEY_PLAIN, 2, Scalar(255, 255, 255), 2);
    putText(frame, "- The faster you are, the higher is your Score", Point(150, 550), FONT_HERSHEY_PLAIN, 2, Scalar(255, 255, 255), 2);
    putText(frame, "- The Game ends on 50 / 100 / 200 Hits based on the Game Mode", Point(150, 600), FONT_HERSHEY_PLAIN, 2, Scalar(255, 255, 255), 2);

    putText(frame, "This \"game\" isn't much, so, um, Enjoy..?!", Point(150, 700), FONT_HERSHEY_PLAIN, 2, Scalar(255, 255, 255), 2);

    rectangle(frame, Point(585, 750), Point(1335, 900), Scalar(0, 255, 0), -1);
    putText(frame, "START REACTION GAME", Point(635, 800), FONT_HERSHEY_PLAIN, 3.5, Scalar(0, 0, 0), 4);
    putText(frame, "[Press SPACE]", Point(800, 880), FONT_HERSHEY_PLAIN, 2.5, Scalar(0, 0, 0), 3);

    rectangle(frame, Point(585, 960), Point(1335, 1035), Scalar(0, 0, 255), -1);
    putText(frame, "Go Back [Press Q]", Point(740, 1015), FONT_HERSHEY_PLAIN, 3, Scalar(0, 0, 0), 3);

    return frame;
}

Mat createModeScreen() {
    Mat frame = Mat(1080, 1920, CV_8UC3);

    putText(frame, "Select Mode", Point(580, 200), FONT_HERSHEY_PLAIN, 7.5, Scalar(255, 255, 255), 10);

    rectangle(frame, Point(585, 300), Point(1335, 450), Scalar(255, 100, 65), -1);
    putText(frame, "Quickie Mode : 50 Hits", Point(635, 360), FONT_HERSHEY_PLAIN, 3.5, Scalar(0, 0, 0), 4);
    putText(frame, "[Press I]", Point(865, 420), FONT_HERSHEY_PLAIN, 2.5, Scalar(0, 0, 0), 3);

    rectangle(frame, Point(585, 475), Point(1335, 625), Scalar(255, 100, 65), -1);
    putText(frame, "Normal Mode : 100 Hits", Point(635, 535), FONT_HERSHEY_PLAIN, 3.5, Scalar(0, 0, 0), 4);
    putText(frame, "[Press O]", Point(865, 595), FONT_HERSHEY_PLAIN, 2.5, Scalar(0, 0, 0), 3);

    rectangle(frame, Point(585, 650), Point(1335, 800), Scalar(255, 100, 65), -1);
    putText(frame, "Long Mode : 200 Hits", Point(635, 710), FONT_HERSHEY_PLAIN, 3.5, Scalar(0, 0, 0), 4);
    putText(frame, "[Press P]", Point(865, 770), FONT_HERSHEY_PLAIN, 2.5, Scalar(0, 0, 0), 3);

    rectangle(frame, Point(585, 875), Point(1335, 950), Scalar(0, 0, 255), -1);
    putText(frame, "Go Back [Press Q]", Point(740, 930), FONT_HERSHEY_PLAIN, 3, Scalar(0, 0, 0), 3);

    return frame;
}

Mat createGameScreen(game gameInfo, int onCell) {
    Mat frame = Mat(1080, 1920, CV_8UC3);

    putText(frame, gstrfmt('T', gameInfo.targetCount), Point(185, 200), FONT_HERSHEY_PLAIN, 5, Scalar(255, 255, 255), 7);
    putText(frame, gstrfmt('H', gameInfo.hitCount), Point(185, 375), FONT_HERSHEY_PLAIN, 5, Scalar(0, 255, 0), 5);
    putText(frame, gstrfmt('M', gameInfo.missCount), Point(190, 475), FONT_HERSHEY_PLAIN, 5, Scalar(0, 0, 255), 5);

    putText(frame, gstrfmt('S', gameInfo.currentScore), Point(1100, 200), FONT_HERSHEY_PLAIN, 5, Scalar(255, 255, 255), 7);
    putText(frame, gstrfmt('A', gameInfo.accuracy), Point(1050, 325), FONT_HERSHEY_PLAIN, 5, Scalar(255, 255, 255), 7);

    rectangle(frame, Point(185, 600), Point(385, 800), Scalar(255, 255, 255), 10);
    rectangle(frame, Point(455, 600), Point(655, 800), Scalar(255, 255, 255), 10);
    rectangle(frame, Point(725, 600), Point(925, 800), Scalar(255, 255, 255), 10);
    rectangle(frame, Point(995, 600), Point(1195, 800), Scalar(255, 255, 255), 10);
    rectangle(frame, Point(1265, 600), Point(1465, 800), Scalar(255, 255, 255), 10);
    rectangle(frame, Point(1535, 600), Point(1735, 800), Scalar(255, 255, 255), 10);

    putText(frame, "Z", Point(265, 900), FONT_HERSHEY_PLAIN, 5, Scalar(255, 255, 255), 3);
    putText(frame, "X", Point(535, 900), FONT_HERSHEY_PLAIN, 5, Scalar(255, 255, 255), 3);
    putText(frame, "C", Point(805, 900), FONT_HERSHEY_PLAIN, 5, Scalar(255, 255, 255), 3);
    putText(frame, "B", Point(1075, 900), FONT_HERSHEY_PLAIN, 5, Scalar(255, 255, 255), 3);
    putText(frame, "N", Point(1345, 900), FONT_HERSHEY_PLAIN, 5, Scalar(255, 255, 255), 3);
    putText(frame, "M", Point(1615 , 900), FONT_HERSHEY_PLAIN, 5, Scalar(255, 255, 255), 3);

    if (gameInfo.gameStarted == 0)
        putText(frame, "(Press [SPACE] to START)", Point(750, 1015), FONT_HERSHEY_PLAIN, 2, Scalar(255, 255, 255), 2);
    else
        putText(frame, "(Press [Q] to Go Back)", Point(775, 1015), FONT_HERSHEY_PLAIN, 2, Scalar(255, 255, 255), 2);

    if (gameInfo.gameEnded == 1)
        putText(frame, "GAME OVER!", Point(1075, 500), FONT_HERSHEY_PLAIN, 7, Scalar(255, 0, 255), 6);
    else {
        if (onCell == 1)
            rectangle(frame, Point(185, 600), Point(385, 800), Scalar(0, 255, 255), -1);
        else if (onCell == 2)
            rectangle(frame, Point(455, 600), Point(655, 800), Scalar(0, 255, 255), -1);
        else if (onCell == 3)
            rectangle(frame, Point(725, 600), Point(925, 800), Scalar(0, 255, 255), -1);
        else if (onCell == 4)
            rectangle(frame, Point(995, 600), Point(1195, 800), Scalar(0, 255, 255), -1);
        else if (onCell == 5)
            rectangle(frame, Point(1265, 600), Point(1465, 800), Scalar(0, 255, 255), -1);
        else if (onCell == 6)
            rectangle(frame, Point(1535, 600), Point(1735, 800), Scalar(0, 255, 255), -1);
    }

    return frame;
}

int main() {
    char basePath[200], music_title[250], effect_hit[250], effect_miss[250], effect_over[250];

    GetCurrentDirectory(200, basePath);
    strcpy(music_title, basePath);
    strcpy(effect_hit, basePath);
    strcpy(effect_miss, basePath);
    strcpy(effect_over, basePath);

    strcat(music_title, "\\res\\music_title.wav");
    strcat(effect_hit, "\\res\\effect_hit.wav");
    strcat(effect_miss, "\\res\\effect_miss.wav");
    strcat(effect_over, "\\res\\effect_over.wav");

    int activeFrame = 0;
    int musicPlaying = 0;
    char key = 0;

    game GAME;
    GAME.gameMode = 0;
    GAME.targetCount = 0;
    GAME.hitCount = 0;
    GAME.missCount = 0;
    GAME.currentScore = 0;
    GAME.accuracy = 0.0;
    GAME.gameStarted = 0;
    GAME.gameEnded = 0;

    Mat FRAME;

    namedWindow("Reaction Game", WINDOW_NORMAL);
    setWindowProperty("Reaction Game", WND_PROP_FULLSCREEN, WINDOW_FULLSCREEN);

    srand(time(0));

    // Application Loop
    while (true) {
        if (activeFrame == 0){
            if (musicPlaying == 0) {
                PlaySound(NULL, 0, SND_ASYNC);
                PlaySound(LPCSTR(music_title), 0, SND_LOOP | SND_ASYNC);
                musicPlaying = 1;
            }

            FRAME = createStartScreen();
            imshow("Reaction Game", FRAME);

            if (key == ' ') {
                activeFrame = 1;
            } else if (key == 'q') {
                break;
            } else if (key == 'h') {
                activeFrame = -1;
            } else if (key == 'l') {
                ShellExecuteW(0, 0, L"https://www.github.com/SagarDevAchar", 0, 0 , SW_SHOW);
            }
        }

        else if (activeFrame == -1) {
            FRAME = createHTPScreen();
            imshow("Reaction Game", FRAME);

            if (key == ' ') {
                activeFrame = 1;
                // START GAME
            } else if (key == 'q') {
                activeFrame = 0;
            }
        }

        else if (activeFrame == 1) {
            FRAME = createModeScreen();
            imshow("Reaction Game", FRAME);

            if (key == 'q') {
                activeFrame = 0;
            }

            else if (key == 'i') {
                GAME.gameMode = 1;
                GAME.targetCount = 50;
                activeFrame = 2;
            }

            else if (key == 'o') {
                GAME.gameMode = 2;
                GAME.targetCount = 100;
                activeFrame = 2;
            }

            else if (key == 'p') {
                GAME.gameMode = 3;
                GAME.targetCount = 200;
                activeFrame = 2;
            }
        }

        else if (activeFrame == 2) {
            if (musicPlaying == 1) {
                PlaySound(NULL, 0, SND_ASYNC);
                musicPlaying = 0;
            }

            FRAME = createGameScreen(GAME, 0);
            imshow("Reaction Game", FRAME);

            clock_t hit, show;

            int currentTarget = 0;

            // Game Loop
            while (true) {
                key = gWaitKey(0);

                hit = clock();

                if (key == 'q') {
                    GAME.gameMode = 0;
                    GAME.targetCount = 0;
                    GAME.hitCount = 0;
                    GAME.missCount = 0;
                    GAME.currentScore = 0;
                    GAME.accuracy = 0.0;
                    GAME.gameStarted = 0;
                    GAME.gameEnded = 0;

                    activeFrame = 0;
                    break;
                }

                if (GAME.gameEnded == 0) {
                    if (GAME.gameStarted == 0) {
                        if (key == ' ') {
                            GAME.gameStarted = 1;

                            currentTarget = (rand() % 6) + 1;

                            FRAME = createGameScreen(GAME, currentTarget);
                            imshow("Reaction Game", FRAME);

                            show = clock();
                        }
                    }

                    else {
                        if (key == currentTarget) {
                            double ttk_ms = (1000.0 * (hit - show) / CLOCKS_PER_SEC);

                            GAME.hitCount++;
                            GAME.accuracy = 100.0 * GAME.hitCount / (GAME.hitCount + GAME.missCount);
                            GAME.currentScore += iScore(1, ttk_ms);

                            if (GAME.hitCount == GAME.targetCount) {
                                PlaySound(LPCSTR(effect_over), 0, SND_ASYNC);
                                GAME.gameEnded = 1;
                            } else
                                PlaySound(LPCSTR(effect_hit), 0, SND_ASYNC);

                            int tempRand = (rand() % 6) + 1;
                            while (tempRand == currentTarget)
                                tempRand = (rand() % 6) + 1;

                            currentTarget = tempRand;

                            FRAME = createGameScreen(GAME, currentTarget);
                            imshow("Reaction Game", FRAME);

                            show = clock();
                        }

                        else {
                            PlaySound(LPCSTR(effect_miss), 0, SND_ASYNC);
                            double ttk_ms = (1000.0 * (hit - show) / CLOCKS_PER_SEC);

                            GAME.missCount++;
                            GAME.accuracy = 100.0 * GAME.hitCount / (GAME.hitCount + GAME.missCount);
                            GAME.currentScore += iScore(0, ttk_ms);

                            FRAME = createGameScreen(GAME, currentTarget);
                            imshow("Reaction Game", FRAME);
                        }
                    }
                }
            }
        }

        key = gWaitKey(100);
    }

    return 0;
}
