# ReactionGame
A Small ***C++*** and ***OpenCV 4*** based Game to test the Reaction Time of Players

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
- *ReactionGame.cpp :* C++ Source Code for ReactionGame

## Well, I guess that's it!
This "game" isn't much...

So, Enjoy..?!

Do share if you like it!
