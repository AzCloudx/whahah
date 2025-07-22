#include <stdio.h>
#include "helpers_1.c"
#include "helpers_2.c"
#include <string.h>

int main() {
    int menuInput;
	GameState game;
	int output[25];
	char maxFiles[20][50];
	int filesFound = 0; 
	
    do {
        printf("\n=== CODENAMES GAME (blue team setup first then red team) ===\n");
        printf("MENU: \n");
        printf("1. New game \n");
        printf("2. Top Spymaster \n");
        printf("0. Exit \n");
        printf("Enter choice: ");
        scanf("%d", &menuInput);
        
        switch(menuInput) {
            case 1:
                newGame();
             
                break;
            case 2:
                printf("Top Spymaster feature coming soon!\n");
                selectCard(maxFiles, &filesFound);
        		break;
        		case 3:wordRandom(output);
				loadWords(&game, output);
                displayBoard(&game);                
                break;
            case 0:
                printf("Goodbye!\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    } while(menuInput != 0);
    
    return 0;
}
