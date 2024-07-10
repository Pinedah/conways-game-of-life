#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <conio.h>
#include <windows.h>

#define VIVA 1
#define MUERTA 0
#define TAMANO 15
#define PERIMETRO (TAMANO / 6)
#define ENTER 13
#define UP 72
#define DOWN 80

int Celulas[TAMANO][TAMANO];
int CelulasNuevaGeneracion[TAMANO][TAMANO];
int Ciclos;

void MostrarMenu();
void ValidarCiclos();
void PrepararJuego(int OpcionElegida);
void imprimirMatrizParaEleccion(int filaUsuario, int columnaUsuario);
void UsuarioEligeLasCelulas();
int MostrarNumeroDeVecinasVivas(int Fila, int Columna);
void ImprimirCelulas();
void GenerarCelulas();
void EmpezarJuego();
void Regla2(int Fila, int Columna);
void Regla1(int Fila, int Columna);

int main()
{
    MostrarMenu();
    EmpezarJuego();
}

void MostrarMenu()
{
    int TeclaPresionada, OpcionElegida = 0;

    ValidarCiclos();

    system("cls");

    printf("->Hacer un patron por mi cuenta\n");
    printf("Dejar que la maquina piense por mi\n");

    while (TeclaPresionada != ENTER)
    {
        TeclaPresionada = getch();
        if (TeclaPresionada == 0)
            TeclaPresionada = getch();
        else
            switch (TeclaPresionada)
            {
            case UP:
                system("cls");
                printf("->Hacer un patron por mi cuenta\n");
                printf("Dejar que la maquina piense por mi\n");
                OpcionElegida = 0;
                break;
            case DOWN:
                system("cls");
                printf("Hacer un patron por mi cuenta\n");
                printf("->Dejar que la maquina piense por mi\n");
                OpcionElegida = 1;
                break;
            }
    }

    PrepararJuego(OpcionElegida);

    return;
}

void ValidarCiclos()
{
    do {
        printf("\nIntroduzca el numero de ciclos que deseas ver: ");
        
        // Verificar si la entrada es un número válido
        // Scanf devuelve el numero de elementos que ha leido, por lo que si es diferente del unico entero que se deberia leer (por ejemplo una palabra de varias letras), lanzara el error
        if (scanf("%i", &Ciclos) != 1 || Ciclos <= 1) {

            // Limpiar el búfer de entrada en caso de error
            while (getchar() != '\n');
            
            printf("Error, por favor ingresa un numero positivo mayor que 1\n");
        } else {
            break;
        }
    } while (1);
}

void PrepararJuego(int OpcionElegida)
{
    switch (OpcionElegida)
    {
    case 0:
        UsuarioEligeLasCelulas();
        break;
    case 1:
        GenerarCelulas();
        break;
    }
}

void imprimirMatrizParaEleccion(int filaUsuario, int columnaUsuario)
{
    system("cls"); // Limpiar la consola

    for (int i = 0; i < TAMANO; i++)
    {
        for (int j = 0; j < TAMANO; j++)
        {
            if (i == filaUsuario && j == columnaUsuario)
            {
                printf("* ");
            }
            else
            {
                printf("%d ", Celulas[i][j]);
            }
        }
        printf("\n");
    }
}

void UsuarioEligeLasCelulas()
{
    int filaUsuario = 0;
    int columnaUsuario = 0;

    char tecla;

    while (1)
    {
        imprimirMatrizParaEleccion(filaUsuario, columnaUsuario);

        printf("Use las teclas W, A, S, D para moverse. \nPresione 'P' para cambiar un 0 a 1. \nPresione 'q' para comenzar.\n");

        // Leer un caracter sin necesidad de presionar Enter
        tecla = getch();

        if (tecla == 'q')
        {
            break;
        }

        // Cambiar el valor en la posición del usuario en la matriz al presionar 'p'
        if (tecla == 'P' || tecla == 'p')
        {
            if (Celulas[filaUsuario][columnaUsuario] == 0)
            {
                Celulas[filaUsuario][columnaUsuario] = 1;
            }
            else
            {
                Celulas[filaUsuario][columnaUsuario] = 0;
            }
        }

        // Actualizar la posición del usuario en la matriz
        switch (tecla)
        {
        case 'W':
        case 'w':
            filaUsuario = (filaUsuario - 1 + TAMANO) % TAMANO;
            break;
        case 'A':
        case 'a':
            columnaUsuario = (columnaUsuario - 1 + TAMANO) % TAMANO;
            break;
        case 'S':
        case 's':
            filaUsuario = (filaUsuario + 1) % TAMANO;
            break;
        case 'D':
        case 'd':
            columnaUsuario = (columnaUsuario + 1) % TAMANO;
            break;
        default:
            break;
        }
    }
}

int MostrarNumeroDeVecinasVivas(int Fila, int Columna)
{
    int Vecinas = 0;
    for (int FilaPermitida = -1; FilaPermitida < 2; FilaPermitida += 1)
    {
        if (!((Fila + FilaPermitida) < 0 || (Fila + FilaPermitida) == TAMANO))
            for (int ColumnaPermitida = -1; ColumnaPermitida < 2; ColumnaPermitida++)
            {
                if (FilaPermitida == 0 && ColumnaPermitida == 0)
                    continue;
                if (!((Columna + ColumnaPermitida) < 0 || (Columna + ColumnaPermitida) == TAMANO))
                    if (Celulas[Fila + FilaPermitida][Columna + ColumnaPermitida])
                        Vecinas++;
            }
    }
    return Vecinas;
}

void ImprimirCelulas()
{

    Sleep(1000); // Pequeña pausa en milisegundos para ver la salida
    system("cls");
    printf("\n");
    for (int Filas = 0; Filas < TAMANO; Filas++)
    {
        for (int Columnas = 0; Columnas < TAMANO; Columnas++)
            printf("%d ", Celulas[Filas][Columnas]);
        printf("\n");
    }

    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    for (int Filas = 0; Filas < TAMANO; Filas++)
    {
        for (int Columnas = 0; Columnas < TAMANO; Columnas++)
        {
            if (Celulas[Filas][Columnas])
                SetConsoleTextAttribute(hConsole, 20);
            else
                SetConsoleTextAttribute(hConsole, 119);
            printf(" ");
            SetConsoleTextAttribute(hConsole, 00);
            printf("  ");
        }
        SetConsoleTextAttribute(hConsole, 00);
        printf("\n\n");
    }
}

void GenerarCelulas()
{

    srand(time(NULL));

    for (int Filas = 0; Filas < TAMANO; Filas++)
    {
        for (int Columnas = 0; Columnas < TAMANO; Columnas++)
            Celulas[Filas][Columnas] = rand() % (2);
    }
    // Establecer un perímetro de 0's
    for (int i = 0; i < TAMANO; i++)
    {
        for (int j = 0; j < TAMANO; j++)
        {
            if (i < PERIMETRO || i >= TAMANO - PERIMETRO || j < PERIMETRO || j >= TAMANO - PERIMETRO)
            {
                Celulas[i][j] = 0;
            }
        }
    }

    return;
}

void EmpezarJuego()
{
    for (int i = 0; i < Ciclos; i++)
    {
        ImprimirCelulas();
        for (int Fila = 0; Fila < TAMANO; Fila++)
        {
            for (int Columna = 0; Columna < TAMANO; Columna++)
            {
                if (Celulas[Fila][Columna] == 1)
                    Regla1(Fila, Columna);
                else
                    Regla2(Fila, Columna);
            }
        }
        for (int Fila = 0; Fila < TAMANO; Fila++)
        {
            for (int Columna = 0; Columna < TAMANO; Columna++)
            {
                Celulas[Fila][Columna] = CelulasNuevaGeneracion[Fila][Columna];
            }
        }
    }
}

void Regla1(int Fila, int Columna)
{

    if (MostrarNumeroDeVecinasVivas(Fila, Columna) == 2 || MostrarNumeroDeVecinasVivas(Fila, Columna) == 3)
        CelulasNuevaGeneracion[Fila][Columna] = VIVA;
    else
        CelulasNuevaGeneracion[Fila][Columna] = MUERTA;

    return;
}

void Regla2(int Fila, int Columna)
{
    if (MostrarNumeroDeVecinasVivas(Fila, Columna) == 3)
        CelulasNuevaGeneracion[Fila][Columna] = VIVA;
    return;
}