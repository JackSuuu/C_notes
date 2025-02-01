// Pacman Game in C language 
#include <ncurses.h>
#include <stdio.h> 
#include <stdlib.h> 

// TODO: DOES NOT WORK
  
// All the elements to be used 
// Declared here 
#define WIDTH 20
#define HEIGHT 20 
#define PACMAN 'C' 
#define WALL '#' 
#define FOOD '.' 
#define EMPTY ' ' 
#define DEMON 'D' 
  
// Global Variables are 
// Declared here
int res = 0;
int score = 0;
int pacman_x, pacman_y;
char board[HEIGHT][WIDTH];
int food = 0;
int curr = 0;

void initialize_board() {
    // Initialize board with EMPTY spaces
    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            board[i][j] = EMPTY;
        }
    }

    // Place Pacman at a starting position
    pacman_x = WIDTH / 2;
    pacman_y = HEIGHT / 2;
    board[pacman_y][pacman_x] = PACMAN;

    // Initialize walls, demons, and food
    // ... existing code for walls and demons ...

    // Initialize food count correctly
    food = 35; // Set the initial food count
    // Place food on the board
    int food_count = food;
    while (food_count > 0) {
        int i = rand() % HEIGHT;
        int j = rand() % WIDTH;
        if (board[i][j] == EMPTY) {
            board[i][j] = FOOD;
            food_count--;
        }
    }
}

void draw() 
{ 
    clear();  // Use ncurses clear function 
  
    // Drawing All the elements in the screen 
    for (int i = 0; i < HEIGHT; i++) { 
        for (int j = 0; j < WIDTH; j++) { 
            printf("%c", board[i][j]); 
        } 
        printf("\n"); 
    } 
    printf("Score: %d\n", score);
    refresh();  // Update the screen
} 
  
// Function enables to move the Cursor 
void move_pacman(int move_x, int move_y) 
{ 
    int x = pacman_x + move_x; 
    int y = pacman_y + move_y; 
  
    if (board[y][x] != WALL) { 
        if (board[y][x] == FOOD) { 
            score++; 
            food--; 
            curr++; 
            if (food == 0) { 
                res = 2; 
                return; 
            } 
        } 
        else if (board[y][x] == DEMON) { 
            res = 1; 
        } 
  
        board[pacman_y][pacman_x] = EMPTY; 
        pacman_x = x; 
        pacman_y = y; 
        board[pacman_y][pacman_x] = PACMAN; 
    } 
} 
  
// Main Function 
int main() 
{   
    // init
    initscr();      // Start ncurses mode
    cbreak();       // Disable line buffering
    noecho();       // Don't print input characters
    keypad(stdscr, TRUE);  // Enable special keys

    initialize_board(); 

    char ch; 
    food -= 35; 
    int totalFood = food; 
    // Instructions to Play 
    printf(" Use buttons for w(up), a(left) , d(right) and "
           "s(down)\nAlso, Press q for quit\n"); 
  
    printf("Enter Y to continue: \n"); 
  
    ch = getch(); 
    if (ch != 'Y' && ch != 'y') { 
        printf("Exit Game! "); 
        endwin();  // Close ncurses
        return 1; 
    } 
  
    while (1) { 
        draw(); 
        printf("Total Food count: %d\n", totalFood); 
        printf("Total Food eaten: %d\n", curr); 
        if (res == 1) { 
            // Clear screen 
            clear(); 
            printw("Game Over! Dead by Demon\nYour Score: %d\n", score); 
            refresh();
            break;
        } 
  
        if (res == 2) { 
            // Clear screen 
            clear();
            printw("You Win! \nYour Score: %d\n", score);  
            refresh();
            break; 
        } 
  
        // Taking the Input from the user 
        ch = getch(); 
  
        // Moving According to the 
        // input character 
        switch (ch) { 
        case 'w': 
            move_pacman(0, -1); 
            break; 
        case 's': 
            move_pacman(0, 1); 
            break; 
        case 'a': 
            move_pacman(-1, 0); 
            break; 
        case 'd': 
            move_pacman(1, 0); 
            break; 
        case 'q': 
            printf("Game Over! Your Score: %d\n", score); 
            refresh();
            endwin();  // Close ncurses
            return 0; 
        } 
    } 
    
    endwin();  // Properly close ncurses
    return 0; 
}