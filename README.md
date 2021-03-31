# ReactionGame
A Small ***C++*** and ***OpenCV*** based Game to test the Reaction Time of the Player

## Navigating The Game
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
Instantaneous Scores are calculated on the basis of Reaction Time by the `int iScore()` function. Score is incremented on a Hit and decremented on a Miss. The Mathematical Expressions for score calculation is as below

**Positive Score / Hit Score** is a Piecewise function with score decreasing by time:

<Graph & Formula Here>

**Negative Score / Miss Score** is a Piecewise function with score increasing by time:

<Graph & Formula Here>

The Score is updated for *every* Hit / Miss and the Total Score of one game is the Algebraic Sum of all instantaneous scores

<Formula Here>
  
The Maximum Scores for each mode are as follows:
- *Quickie Mode:* 50000
- *Normal Mode:* 100000
- *Long Mode:* 200000

## Hardware Requirements
A PC / Laptop running Windows. Nothing else **(:P)**
