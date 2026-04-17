/*

This program was written 100% by Google AI 
using the prompt: write a simple program for the esp32 that plays tic-tac-toe with output to the serial console using platformio

It wrote the platformio.ini file as well, which was changed to work with my specific ESP32 device (M5Stick-C), it was also changed 
to use an older version of espressif32.  Other wise no other changes were made.

This a appears to work as is, and is what I prompted for. 

Google Gemini - Friday April 10, 2026

Google websearch, AI results.

*/

#include <Arduino.h>

char board[9] = {'0','1','2','3','4','5','6','7','8'};
char currentPlayer = 'X';

void printBoard() {
  Serial.println("\n-----------");
  for (int i = 0; i < 9; i += 3) {
    Serial.printf(" %c | %c | %c \n", board[i], board[i+1], board[i+2]);
    if (i < 6) Serial.println("-----------");
  }
}

bool checkWin() {
  int winStates[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
  for (auto& state : winStates) {
    if (board[state[0]] == board[state[1]] && board[state[1]] == board[state[2]]) return true;
  }
  return false;
}

void resetGame() {
  for (int i = 0; i < 9; i++) board[i] = '0' + i;
  currentPlayer = 'X';
  printBoard();
  Serial.printf("Player %c's turn. Enter 0-8: ", currentPlayer);
}

void setup() {
  Serial.begin(115200);
  delay(1000);
  Serial.println("Welcome to ESP32 Tic-Tac-Toe!");
  resetGame();
}

void loop() {
  if (Serial.available() > 0) {
    char input = Serial.read();
    if (input >= '0' && input <= '8') {
      int idx = input - '0';
      if (board[idx] != 'X' && board[idx] != 'O') {
        board[idx] = currentPlayer;
        printBoard();
        
        if (checkWin()) {
          Serial.printf("\n*** Player %c Wins! ***\nRestarting...", currentPlayer);
          delay(3000);
          resetGame();
        } else {
          currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
          Serial.printf("Player %c's turn. Enter 0-8: ", currentPlayer);
        }
      }
    }
  }
}

