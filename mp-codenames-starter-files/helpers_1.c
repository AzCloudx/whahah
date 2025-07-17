#ifndef HELPERS_1_C
#define HELPERS_1_C
#include <stdio.h>
#include <string.h>
#include "defs.h"

// Function to load players from players.txt for specific team
void loadPlayersFromFile(Team *team, const char *teamName) {
    FILE *file = fopen("players.txt", "r");
    if (file == NULL) {
        printf("Warning: Could not open players.txt. Starting with empty team.\n");
        return;
    }
    
    char line[50];
    char sectionHeader[50];
    int foundSection = 0;
    int playersAdded = 0;
    
    // Create section header to look for (e.g., "[BLUE]" or "[RED]")
    sprintf(sectionHeader, "[%s]", teamName);
    
    // Don't reset memberCount - we want to append to existing players
    // Reset spy selection when loading from file (since player indices might change)
    team->spyIndex = -1;
    
    // Read each line from the file
    while (fgets(line, sizeof(line), file) != NULL && team->memberCount < 50) {
        // Remove newline character if present
        line[strcspn(line, "\n")] = '\0';
        
        // Skip empty lines
        if (strlen(line) == 0) continue;
        
        // Check if this is a section header
        if (line[0] == '[' && line[strlen(line)-1] == ']') {
            foundSection = (strcmp(line, sectionHeader) == 0);
            continue;
        }
        
        // If we're in the right section, check for duplicates and add the player
        if (foundSection) {
            // Check if player already exists in the team
            int isDuplicate = 0;
            for (int i = 0; i < team->memberCount; i++) {
                if (strcmp(team->members[i].userName, line) == 0) {
                    isDuplicate = 1;
                    printf("Player '%s' already exists in team, skipping...\n", line);
                    break;
                }
            }
            
            // Add player if not duplicate
            if (!isDuplicate) {
                strcpy(team->members[team->memberCount].userName, line);
                team->memberCount++;
                playersAdded++;
            }
        }
    }
    
    fclose(file);
    printf("Loaded %d new players from players.txt for %s team\n", playersAdded, teamName);
    printf("Total players in %s team: %d\n", teamName, team->memberCount);
}


void displayTeamMembers(Team *team, const char *teamName) {
    printf("\n\n==%s TEAM== \n", teamName);
    printf("Current %s Team members: \n", teamName);
   
    if(team->memberCount == 0) {
        printf("No members added yet.\n");
    } else {
        for(int i = 0; i < team->memberCount; i++) {
            if(i == team->spyIndex) {
                printf("+ %s (SPYMASTER) \n", team->members[i].userName);
            } else {
                printf("+ %s \n", team->members[i].userName);
            }
        }
    }
    
    // Display spy information
    if(team->spyIndex == -1) {
        printf("No spymaster selected.\n");
    } else {
        printf("Spymaster: %s\n", team->members[team->spyIndex].userName);
    }
}

// Function to add a new player to team
void addPlayerToTeam(Team *team) {
    if(team->memberCount < 50) {
        printf("Input Username: ");
        scanf("%s", team->members[team->memberCount].userName);
        team->memberCount++;
        printf("Player added successfully!\n");
    } else {
        printf("Team is full! Maximum 50 players.\n");
    }
}

// Function to select spy for the team
void selectSpyForTeam(Team *team, const char *teamName) {
    if(team->memberCount == 0) {
        printf("No players in the team! Add players first.\n");
        return;
    }
    
    printf("\n=== SELECT SPYMASTER FOR %s TEAM ===\n", teamName);
    printf("Available players:\n");
    
    for(int i = 0; i < team->memberCount; i++) {
        printf("[%d] %s\n", i + 1, team->members[i].userName);
    }
    
    int spyChoice;
    printf("Enter the number of the player to make spymaster (1-%d): ", team->memberCount);
    scanf("%d", &spyChoice);
    
    if(spyChoice >= 1 && spyChoice <= team->memberCount) {
        team->spyIndex = spyChoice - 1;
        printf("Successfully selected %s as the spymaster for %s team!\n", 
               team->members[team->spyIndex].userName, teamName);
    } else {
        printf("Invalid selection. Please try again.\n");
    }
}

// Function to manage a team (generic for both blue and red)
void manageTeam(Team *team, const char *teamName) {
    // Initialize spy index to -1 (no spy selected)
    team->spyIndex = -1;
    
    int done = 0;
   
    while(!done) {
        displayTeamMembers(team, teamName);
       
        int optionSelect;
        printf("==Choose Option== \n");
        printf("[0] Done adding team & spy members \n");
        printf("[1] Add new player \n");
        printf("[2] Load players from file \n");
        printf("[3] Select spymaster \n");
        printf("Enter choice: ");
        scanf("%d", &optionSelect);
       
        switch(optionSelect) {
            case 1:
                addPlayerToTeam(team);
                break;
            case 2:
                loadPlayersFromFile(team, teamName);
                break;
            case 3:
                selectSpyForTeam(team, teamName);
                break;
            case 0:
                // Check if team has members and a spy selected
                if(team->memberCount == 0) {
                    printf("Cannot finish setup: No players in the team! Add players first.\n");
                    break;
                }
                
                if(team->spyIndex == -1) {
                    printf("\nWARNING: No spymaster selected for %s team!\n", teamName);
                    printf("You must select a spymaster before finishing team setup.\n");
                    printf("Please select option [3] to choose a spymaster.\n");
                    break;
                }
                
                done = 1;
                printf("Finished managing %s team.\n", teamName);
                break;
            default:
                printf("Invalid option. Please try again.\n");
                break;
        }
    }
}

void newGame() {
    Team blueTeam = {0};
    Team redTeam = {0};
   
    printf("\n=== NEW GAME SETUP ===\n");
   
    // Set up blue team
    printf("Setting up Blue Team...\n");
    manageTeam(&blueTeam, "BLUE");
   
    // Set up red team
    printf("\nSetting up Red Team...\n");
    manageTeam(&redTeam, "RED");
   
    printf("\n=== GAME SETUP COMPLETE ===\n");
    printf("Blue Team: %d members", blueTeam.memberCount);
    if(blueTeam.spyIndex != -1) {
        printf(" (Spymaster: %s)", blueTeam.members[blueTeam.spyIndex].userName);
    }
    printf("\n");
    
    printf("Red Team: %d members", redTeam.memberCount);
    if(redTeam.spyIndex != -1) {
        printf(" (Spymaster: %s)", redTeam.members[redTeam.spyIndex].userName);
    }
    printf("\n");
}

#endif