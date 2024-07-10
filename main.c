
// Conways game of life
// Programming Fundamentals (First Semester - ESCOM IPN)
// Pineda Hernandez Francisco

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <windows.h>

#define ALIVE 1
#define DEAD 0
#define SIZE 17
#define PERIMETER (SIZE / 6)
#define ENTER 13
#define UP 72
#define DOWN 80

int Cells[SIZE][SIZE];
int NewGenerationCells[SIZE][SIZE];
int Cycles;

void ShowMenu();
void ValidateCycles();
void PrepareGame(int selectedOption);
void PrintMatrixForSelection(int userRow, int userCol);
void UserSelectsCells();
int CountAliveNeighbors(int row, int col);
void PrintCells();
void GenerateCells();
void StartGame();
void ApplyRule1(int row, int col);
void ApplyRule2(int row, int col);

int main()
{
    ShowMenu();
    StartGame();
}

void ShowMenu()
{
    int keyPressed, selectedOption = 0;

    ValidateCycles();

    system("cls");

    printf("->\tCreate a pattern myself\n");
    printf("\tLet the machine create a pattern\n");

    while (keyPressed != ENTER)
    {
        keyPressed = getch();
        if (keyPressed == 0)
            keyPressed = getch();
        else
            switch (keyPressed)
            {
            case UP:
                system("cls");
                printf("->\tCreate a pattern myself\n");
                printf("\tLet the machine create a pattern\n");
                selectedOption = 0;
                break;
            case DOWN:
                system("cls");
                printf("\tCreate a pattern myself\n");
                printf("->\tLet the machine create a pattern\n");
                selectedOption = 1;
                break;
            }
    }

    PrepareGame(selectedOption);

    return;
}

void ValidateCycles()
{
    do {
        printf("\nEnter the number of cycles to display: ");
        
        // Verify if the input is a valid number
        if (scanf_s("%i", &Cycles) != 1 || Cycles <= 1) {

            // Clear the input buffer in case of error
            while (getchar() != '\n');
            
            printf("Error, please enter a positive number greater than 1\n");
        } else {
            break;
        }
    } while (1);
}

void PrepareGame(int selectedOption)
{
    switch (selectedOption)
    {
    case 0:
        UserSelectsCells();
        break;
    case 1:
        GenerateCells();
        break;
    }
}

void PrintMatrixForSelection(int userRow, int userCol)
{
    system("cls"); // Clear the console

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE); // Get the console output handle

    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (i == userRow && j == userCol)
            {
                SetConsoleTextAttribute(hConsole, 32);
                printf("*");
            }
            else
            {
                if (Cells[i][j])
                {
                    SetConsoleTextAttribute(hConsole, 31);
                    printf("A");
                }
                else
                {
                    SetConsoleTextAttribute(hConsole, 112);
                    printf("D");
                }
            }
            SetConsoleTextAttribute(hConsole, 0x07);
            printf(" ");
        }
        printf("\n\n");
    }
}

void UserSelectsCells()
{
    int userRow = 0;
    int userCol = 0;

    char key;

    while (1)
    {
        PrintMatrixForSelection(userRow, userCol);

        printf("Use W, A, S, D keys to move. \nPress 'P' to toggle between Dead (D) and Alive (A). \nPress 'Q' to start.\n");

        // Read a character without needing to press Enter
        key = getch();

        if (key == 'q' || key == 'Q')
        {
            break;
        }

        // Toggle the value at the user's position in the matrix when 'P' is pressed
        if (key == 'P' || key == 'p')
        {
            if (Cells[userRow][userCol] == DEAD)
            {
                Cells[userRow][userCol] = ALIVE;
            }
            else
            {
                Cells[userRow][userCol] = DEAD;
            }
        }

        // Update the user's position in the matrix
        switch (key)
        {
        case 'W':
        case 'w':
            userRow = (userRow - 1 + SIZE) % SIZE;
            break;
        case 'A':
        case 'a':
            userCol = (userCol - 1 + SIZE) % SIZE;
            break;
        case 'S':
        case 's':
            userRow = (userRow + 1) % SIZE;
            break;
        case 'D':
        case 'd':
            userCol = (userCol + 1) % SIZE;
            break;
        default:
            break;
        }
    }
}

int CountAliveNeighbors(int row, int col)
{
    int neighbors = 0;
    for (int rowOffset = -1; rowOffset < 2; rowOffset++)
    {
        if (!((row + rowOffset) < 0 || (row + rowOffset) == SIZE))
            for (int colOffset = -1; colOffset < 2; colOffset++)
            {
                if (rowOffset == 0 && colOffset == 0)
                    continue;
                if (!((col + colOffset) < 0 || (col + colOffset) == SIZE))
                    if (Cells[row + rowOffset][col + colOffset])
                        neighbors++;
            }
    }
    return neighbors;
}

void PrintCells()
{
    Sleep(750); // Small pause in milliseconds to see the output
    system("cls");
    printf("\n");

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
        {
            if (Cells[row][col])
                SetConsoleTextAttribute(hConsole, 20);
            else
                SetConsoleTextAttribute(hConsole, 119);
            printf(" ");
            SetConsoleTextAttribute(hConsole, 0x07);
            printf("  ");
        }
        SetConsoleTextAttribute(hConsole, 0x07);
        printf("\n\n");
    }
}

void GenerateCells()
{
    srand(time(NULL));

    for (int row = 0; row < SIZE; row++)
    {
        for (int col = 0; col < SIZE; col++)
            Cells[row][col] = rand() % 2;
    }
    // Set a perimeter of DEAD cells
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++)
        {
            if (i < PERIMETER || i >= SIZE - PERIMETER || j < PERIMETER || j >= SIZE - PERIMETER)
            {
                Cells[i][j] = DEAD;
            }
        }
    }

    return;
}

void StartGame()
{
    for (int i = 0; i < Cycles; i++)
    {
        PrintCells();
        for (int row = 0; row < SIZE; row++)
        {
            for (int col = 0; col < SIZE; col++)
            {
                if (Cells[row][col] == ALIVE)
                    ApplyRule1(row, col);
                else
                    ApplyRule2(row, col);
            }
        }
        for (int row = 0; row < SIZE; row++)
        {
            for (int col = 0; col < SIZE; col++)
            {
                Cells[row][col] = NewGenerationCells[row][col];
            }
        }
    }
}

void ApplyRule1(int row, int col)
{
    int aliveNeighbors = CountAliveNeighbors(row, col);
    if (aliveNeighbors == 2 || aliveNeighbors == 3)
        NewGenerationCells[row][col] = ALIVE;
    else
        NewGenerationCells[row][col] = DEAD;

    return;
}

void ApplyRule2(int row, int col)
{
    if (CountAliveNeighbors(row, col) == 3)
        NewGenerationCells[row][col] = ALIVE;
    return;
}
