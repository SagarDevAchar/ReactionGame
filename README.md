# ReactionGame
A Small ***C++*** and ***OpenCV 4*** based Game to test the Reaction Time of Players

The recent (and the only) version of Reaction game is 1.1. Click [here](https://github.com/SagarDevAchar/ReactionGame/archive/refs/tags/v1.1.zip) to download the release and extract to play!

## Navigating through the Game
The Game Supports **only** Keyboard Input. Any part of the game will **not** respond to the mouse pointer / click. Follow the Instruction as said in the game to navigate through

## How to Play
- There will be 6 Boxes / Targets on your Screen
- These boxes are mapped to **`Z` `X` `C` `B` `N` `M`** keys respectively
- Press the respective keys as the boxes light up
- Every **HIT** increases your Score & Accuracy
- Every **MISS** decreases your Score & Accuracy
- The faster you are, the higher is your Score
- The Game ends on 50 / 100 / 200 Hits based on the Game Mode:  
  
  - *Quickie Mode:* 50 Hits
  - *Normal Mode:* 100 Hits
  - *Long Mode:* 200 Hits

## Scoring System
Instantaneous Scores are calculated on the basis of Reaction Time by the `iScore()` function. Score is incremented on a Hit and decremented on a Miss. The Mathematical Expressions for score calculation is as below

**Positive Score / Hit Score** is a Piecewise function with score decreasing by time:

![Positive Score](https://user-images.githubusercontent.com/51400137/113157981-fcbdb300-9258-11eb-801e-c1927ec9d820.JPG)

**Negative Score / Miss Score** is a Piecewise function with score increasing by time:

![Negative Score](https://user-images.githubusercontent.com/51400137/113157920-ee6f9700-9258-11eb-9dfc-0a9bb4a06bc6.JPG)

The Score is updated for *every* Hit / Miss and the Total Score of one game is the Algebraic Sum of all instantaneous scores

![Net Score](https://user-images.githubusercontent.com/51400137/113157793-d435b900-9258-11eb-95b4-1bc535d21cc8.jpg)
  
The Maximum Scores for each mode are as follows:
- *Quickie Mode:* 50000
- *Normal Mode:* 100000
- *Long Mode:* 200000

## Hardware Requirements
A PC / Laptop running Windows. Nothing else **(:-P)**

## Files in Repository
- *LICENSE :* Creative Commons Zero v1.0 Universal License for ReactionGame
- *README.md :* Here you are! **(:-P)**
- *ReactionGame.exe :* The actual game executable
- *libXXXX.dll :* Dynamic Link Libraries required to run ReactionGame
- */src/main.cpp :* C++ Source Code for ReactionGame
- */res :* Audio Resource Directory for ReactionGame. Contains WAV files used in Runtime

## Disclaimer

To ensure a bug-free game experience, do **NOT** move the files inside the **ReactionGame-v1.x** folder. Please move the whole folder if required.

Windows Defender might block the running of **ReactionGame.exe** as it fails to recognize the origin of the Executable (I don't know how to get EXEs signed). Click on **More Info** and **Run anyway** to play the game. To ensure that there is no Virus / Malware, download ReactionGame from this Repository only

Any Bugs / Issues / Features Requests can be posted in the **[Issues Tab](https://github.com/SagarDevAchar/ReactionGame/issues/new/choose)** of this Repository

## Well, I guess that's it!
This "game" isn't much...

So, Enjoy..?!

Do share if you like it!
