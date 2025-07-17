#ifndef DEFS_H 
#define DEFS_H 



typedef struct player
{
  char userName[50];  
} Player;



typedef struct {
    Player members[50];
    int memberCount;
    int spyIndex;  // Index of the spy (-1 if no spy selected)
} Team;



typedef struct card
{
    char word[20];          // The codename word
    char identity;          // 'B', 'R', 'I', 'A' (blue, red, innocent, assassin)
    int isRevealed;         // 0 if hidden, 1 if revealed
} Card;

typedef struct gameState
{
    Card grid[5][5];        // 5x5 grid of cards
    Team blueTeam;
    Team redTeam;
    char currentTurn;       // 'B' or 'R' for current team
    int gameOver;           // 0 if ongoing, 1 if finished
    char winner;            // 'B', 'R', or 'N' (none/assassin loss)
} GameState;

#endif // DEFS_H; Include this to prevent redefinition error