/*
  Program 1: Wumpus, version 1 (fixed size array)

  Course: CS 211, Fall 2022.
  System: Mac using Visual Studio Code and Replit
  Author: Yamaan Nandolia
*/

//------------------------------ Libraries ------------------------------
#include <ctype.h> // for toupper
#include <stdio.h>
#include <stdlib.h> // for srand

//------------------------------ Helper Funtions ------------------------------

/* The function below displays an ASCII art of the map of the game*/
void displayCave() {
  printf("\n"
         "       ______18______             \n"
         "      /      |       \\           \n"
         "     /      _9__      \\          \n"
         "    /      /    \\      \\        \n"
         "   /      /      \\      \\       \n"
         "  17     8        10     19       \n"
         "  | \\   / \\      /  \\   / |    \n"
         "  |  \\ /   \\    /    \\ /  |    \n"
         "  |   7     1---2     11  |       \n"
         "  |   |    /     \\    |   |      \n"
         "  |   6----5     3---12   |       \n"
         "  |   |     \\   /     |   |      \n"
         "  |   \\       4      /    |      \n"
         "  |    \\      |     /     |      \n"
         "  \\     15---14---13     /       \n"
         "   \\   /            \\   /       \n"
         "    \\ /              \\ /        \n"
         "    16---------------20           \n"
         "\n");
} // end of displayCave()

/* The function below displays the game instructions on the screen */
void displayInstructions() {
  printf("Hunt the Wumpus:                                             \n"
         "The Wumpus lives in a completely dark cave of 20 rooms. Each \n"
         "room has 3 tunnels leading to other rooms.                   \n"
         "                                                             \n"
         "Hazards:                                                     \n"
         "1. Two rooms have bottomless pits in them.  If you go there you fall "
         "and die.   \n"
         "2. The Wumpus is not bothered by the pits, as he has sucker feet. "
         "Usually he is \n"
         "   asleep. He will wake up if you enter his room. When you move into "
         "the Wumpus'\n"
         "   room, then he wakes and moves if he is in an odd-numbered room, "
         "but stays    \n"
         "   still otherwise.  After that, if he is in your room, he snaps "
         "your neck and  \n"
         "   you die!                                                          "
         "           \n"
         "                                                                     "
         "           \n"
         "Moves:                                                               "
         "           \n"
         "On each move you can do the following, where input can be upper or "
         "lower-case:  \n"
         "1. Move into an adjacent room.  To move enter 'M' followed by a "
         "space and       \n"
         "   then a room number.                                               "
         "           \n"
         "2. Enter 'R' to reset the person and hazard locations, useful for "
         "testing.      \n"
         "3. Enter 'C' to cheat and display current board positions.           "
         "           \n"
         "4. Enter 'D' to display this set of instructions.                    "
         "           \n"
         "5. Enter 'P' to print the maze room layout.                          "
         "           \n"
         "6. Enter 'G' to guess which room Wumpus is in, to win or lose the "
         "game!         \n"
         "7. Enter 'X' to exit the game.                                       "
         "           \n"
         "                                                                     "
         "           \n"
         "Good luck!                                                           "
         "           \n"
         " \n\n");
} // end displayInstructions()

/* The function below checks for pits in the game and exits the game once the
 * condition is met */
void checkPits(int *player, int *pit1, int *pit2) {
  if (*player == *pit1 ||
      *player ==
          *pit2) { // condition to check if player entered a room with a pit
    printf("Aaaaaaaaahhhhhh....\n    You fall into a pit and die.\n\n");
    printf("Exiting Program ...");
    exit(0); // immediately exits the program
  }
} // end of checkPits()

/* The function below checks for the status of wumpus in certain rooms. IF the
 * player enters an even numbered room with the wumpus in it, the wumpus kills
 * the player and the game ends. If the player enters an odd numbered room with
 * the wumpus in it, the wumpus moves to the lowest numbered adjacent room */
void checkWumpus(int *player, int *wumpus, int *adjRoom) {
  if (*wumpus % 2 == 0 &&
      *player == *wumpus) { // condition to check even numbered room
    printf("You briefly feel a slimy tentacled arm as your neck is snapped. "
           "\nIt is over.\n\n");
    printf("Exiting Program ...");
    exit(0);
  } else if (*wumpus % 2 != 0 &&
             *player == *wumpus) { // condition to check odd numbered room
    *wumpus = *adjRoom;
    printf("You hear a slithering sound, as the Wumpus slips away. \nWhew, "
           "that was close!\n");
  }
} // end of checkWumpus()

/* The function below checks for any potential hazards in the rooms adjacent to
 * where the player is and alerts them of either a stench(of wumpus) or a
 * draft(due to pits) */
void hazardNotifs(int *wumpus, int *adjRoom1, int *adjRoom2, int *adjRoom3,
                  int *pit1, int *pit2) {
  if (*adjRoom1 == *wumpus || *adjRoom2 == *wumpus ||
      *adjRoom3 == *wumpus) { // condition to check stench
    printf("You smell a stench. ");
  }

  if (*adjRoom1 == *pit1 || *adjRoom2 == *pit1 || *adjRoom3 == *pit1 ||
      *adjRoom1 == *pit2 || *adjRoom2 == *pit2 ||
      *adjRoom3 == *pit2) { // condition to check pits
    printf("You feel a draft. ");
  }
} // end of hazardNotifs()

/* The function below lets the player guess the room where the wumpus is
 * currently in. If the player guesses correctly, they instantly win the game.
 * If they make a wrong guess, they die and the game ends */
void guessOption(int *wumpus) {
  int guessInput;

  printf("Enter room (1..20) you think Wumpus is in: ");
  scanf("%d", &guessInput);    // input for guess
  if (guessInput == *wumpus) { // condition for correct guess
    printf("You won!\n");
    printf("\nExiting Program ...\n");
    exit(0);
  } else { // conditon for wrong guess
    printf("You lost!\n");
    printf("\nExiting Program ...\n");
    exit(0);
  }
} // end of guessOption()

/* The function below displays the locations of the player, pits and the wumpus
 */
void cheatOption(int *player, int *wumpus, int *pit1, int *pit2) {
  printf("Cheating! Game elements are in the following rooms: \n"
         "Player Wumpus Pit1 Pit2  \n"
         "%4d %7d %5d %5d \n\n",
         *player, *wumpus, *pit1, *pit2);
} // end of cheatOption()

/* The funtion below exits the program ending the game*/
void exitOption() {
  printf("\nExiting Program ...\n");
  exit(0);
} // end of exitOption()

/* The funtion below checks if a move made by the player is possible or not by
 * checking which rooms are adjacent */
void moveRooms(int *player, int *adjRoom1, int *adjRoom2, int *adjRoom3,
               int *moveIncrement) {
  int moveRoom; // variable to store the room the player wishes to move to

  scanf("%d", &moveRoom);
  if (moveRoom == *adjRoom1 || moveRoom == *adjRoom2 ||
      moveRoom == *adjRoom3) { // condition to check if the room is adjacent
    *player = moveRoom;
    *moveIncrement += 1;
  } else { // condition for an invalid move request
    printf("Invalid move.  Please retry. \n");
  }
} // end of moveRooms()

/* The function below call numerous functions and sets up the game by utilizing
 * the functions stated above */
void setup(int *player, int *pit1, int *pit2, int *wumpus, int *adjRoom1,
           int *adjRoom2, int *adjRoom3, int *moveIncrement, char *userInput) {

  checkPits(*&player, *&pit1, *&pit2);         // call to checkPits()
  checkWumpus(*&player, *&wumpus, *&adjRoom1); // call to checkWumpus()

  printf("You are in room %d. ", *player);

  hazardNotifs(*&wumpus, *&adjRoom1, *&adjRoom2, *&adjRoom3, *&pit1,
               *&pit2); // call to hazardNotifs()

  printf("\n\n");
  printf("%d. Enter your move (or 'D' for directions): ", *moveIncrement);
  scanf(" %c", *&userInput);
  *userInput = toupper(*userInput); // changes all the char input to uppercase
} // end of setup()


void resetOption(int *player, int *wumpus, int *pit1, int *pit2) {
  printf("Enter the room locations (1..20) for player, wumpus, pit1, and "
         "pit2: \n\n");
  scanf("%d", *&player); // input to reset
  scanf("%d", *&wumpus);
  scanf("%d", *&pit1);
  scanf("%d", *&pit2);
} // end of resetOption

//----------------------------- Main Fuction ----------------------------

/* The function below is the main function of the program. All function calls
 * are made in this function and all the other functions work together here */
int main(void) {
  int roomSelection[20][4] = {
      {2, 5, 8},    {1, 3, 10},  {2, 4, 12},   {3, 5, 14},   {1, 4, 6},
      {5, 7, 15},   {6, 8, 17},  {1, 7, 9},    {8, 10, 18},  {2, 9, 11},
      {10, 12, 19}, {3, 11, 13}, {12, 14, 20}, {4, 13, 15},  {6, 14, 16},
      {15, 17, 20}, {7, 16, 18}, {9, 17, 19},  {11, 18, 20}, {13, 16, 19}};

  srand(1); // random function is seeded to aviod randomized values each time
  int pit1 =
      rand() % 20 + 1; // assigned random value between but not including 0-21
  int pit2 = rand() % 20 + 1;
  int wumpus = rand() % 20 + 1;
  int player = rand() % 20 + 1;
  char userinputCharacter;
  int moveIncrement = 1; // to keep track of the number of successful moves
  int adjRoom1;
  int adjRoom2;
  int adjRoom3; // stores the value of one of the adjacent rooms

  while (1) { // important loop for the game to continue
    adjRoom1 = roomSelection[player - 1][0];
    adjRoom2 = roomSelection[player - 1][1];
    adjRoom3 = roomSelection[player - 1][2];

    setup(&player, &pit1, &pit2, &wumpus, &adjRoom1, &adjRoom2, &adjRoom3,
          &moveIncrement, &userinputCharacter); // call to setup()

    switch (userinputCharacter) {
    case 'D':
      displayCave();
      displayInstructions();
      break;
    case 'P':
      displayCave();
      break;
    case 'C':
      cheatOption(&player, &wumpus, &pit1, &pit2);
      break;
    case 'M':
      moveRooms(&player, &adjRoom1, &adjRoom2, &adjRoom3, &moveIncrement);
      break;
    case 'R':
      resetOption(&player, &wumpus, &pit1, &pit2);
      break;
    case 'G':
      guessOption(&wumpus);
      break;
    case 'X':
      exitOption();
      break;
    default:
      printf("Invalid move.  Please retry. \n");
    }
  }
  return 0;
} // end of main and end of program