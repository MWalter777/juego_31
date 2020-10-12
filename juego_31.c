#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>
#include <termios.h>
#include <unistd.h>

/*
** Autor: Walter Ernesto Marroquin Herrera
** ultima modificacion: 2020-07-02
*/

/*
** Definicion de metodos a utilizar
*/

void setCartas();
void imprimirCartasJugador();
int getValorCarta(bool banca);
void jugar();
int suma_cartas();
int suma_banca();
void imprimirCartasBanco(bool mostrar);
int seleccionar();
void gotoxy(int x,int y);
int getch(void);
/*
** Constante
*/

int CANTIDAD_CARTAS = 48;

/*
** Variables globales
*/

int indice_cartas = 0;
int indice_banca = 0;
int cartas[48];
int mis_cartas[12];
int tipo_carta[12];
int carta_banca[12];
int tipo_banca[12];
char nombre[60];

int main(){
    char salir;
    system("clear"); //Limpiamos la pantalla
    printf("\nComo te llamas?\n");
    scanf("%s",nombre);
    do{
        setCartas(); //inicializamos las cartas
        system("clear");
        jugar(); //Llamamos al metodo Jugar
        do{
            printf("\nPresione \'N\' para salir y \'Y\' para continuar \n");
            salir = getch();
        }while(salir != 'y' && salir != 'Y' && salir != 'n' && salir != 'N');
    }while(salir=='y' || salir=='Y');
    return 0;
}

/*
** Funcion principal, esta funcion se encarga de ejecutar todo el proceso del juego
*/
void jugar(){
    int stand = 0;
    mis_cartas[indice_cartas] = getValorCarta(false);
    indice_cartas++;
    mis_cartas[indice_cartas] = getValorCarta(false);
    indice_cartas++;
    carta_banca[indice_banca] = getValorCarta(true);
    indice_banca++;
    carta_banca[indice_banca] = getValorCarta(true);
    indice_banca++;
    carta_banca[indice_banca] = getValorCarta(true);
    indice_banca++;
    do{
        mis_cartas[indice_cartas] = getValorCarta(false);
        indice_cartas++;
        system("clear");
        imprimirCartasBanco(false);
        imprimirCartasJugador();
        if (suma_cartas()<31 && suma_banca()<31){
            stand = seleccionar();
        }
    }while(stand !=1 && suma_cartas()<31);

    if (suma_cartas()<31){
        while(suma_banca()<27){
            carta_banca[indice_banca] = getValorCarta(true);
            indice_banca++;
        }
    }

    system("clear");
    imprimirCartasBanco(true);
    imprimirCartasJugador();
    int mi_suma = suma_cartas();
    int banca_suma = suma_banca();
    if (mi_suma == 31 || (mi_suma<31 && banca_suma>31) || (mi_suma > banca_suma && banca_suma < 31 && mi_suma<31)){
        printf("\nFelicidades, ganaste con %d puntos\n", suma_cartas());
    }else{
        if (banca_suma == 31 || (banca_suma<31 && mi_suma>31) || (banca_suma > mi_suma && mi_suma < 31 && banca_suma < 31)){
            printf("\nGana la Banca con %d puntos \n", suma_banca());
        }
        else printf("\nNo hay ganador \n");
    }

}

//Funcion para verificar los puntos del jugador
int suma_cartas(){
    int suma = 0, i;
    for(i=0; i<12;i++){
        suma += mis_cartas[i];        
    }
    return suma;
}

//Funcion para verificar los puntos de la banca
int suma_banca(){
    int suma = 0, i;
    for(i=0; i<12;i++){
        suma += carta_banca[i];
    }
    return suma;
}


// Funcion para inicializar las cartas
void setCartas(){
    indice_cartas = 0;
    indice_banca = 0;
    int indice = 0;
    int valor = 0, i, j;
    for (i=0; i<4; i++){
        valor = 2;
        for (int j=0; j<8;j++){
            cartas[indice] = valor;
            indice++;
            valor++;
        }
        cartas[indice] = 11;
        indice++;
        cartas[indice] = 10;
        indice++;
        cartas[indice] = 10;
        indice++;
        cartas[indice] = 10;
        indice++;
    }
    for (int i=0; i<12;i++){
        mis_cartas[i]=0;
        carta_banca[i]=0;
        tipo_carta[i]=0;
        tipo_banca[i]=0;
    }
}


//Funcion que se utiliza para la seleccion de si desea continuar o no
int seleccionar(){
    int valor = 2;
    char cTecla;
    gotoxy(1,20);
    printf("Uiliza las teclas A y D (o flechas) para moverte y presiona Y para seleccionar la opcion");
    gotoxy(10,23);
    printf("Plantarse");
    gotoxy(40,23);
    printf("Pedir");
    gotoxy(40,22);
    printf("______");
    gotoxy(40,24);
    printf("______");
    while (cTecla != 'y' && cTecla != 'Y'){
        cTecla = getch();
        if(cTecla == 'a' || cTecla == 'A' || cTecla == 68){
            gotoxy(40,22);
            printf("      ");
            gotoxy(40,24);
            printf("      ");

            gotoxy(10,22);
            printf("___________");
            gotoxy(10,24);
            printf("___________");
            gotoxy(9,23);
            gotoxy(21,23);
            valor = 1;
        }
        else{
            if(cTecla == 'd' || cTecla == 'D' || cTecla == 67){
                gotoxy(10,22);
                printf("           ");
                gotoxy(10,24);
                printf("           ");
                valor = 2;
                gotoxy(40,22);
                printf("______");
                gotoxy(40,24);
                printf("______");
            }
        }
    }
    return valor;
}

// valor_carta tiene que ser el valor del indice (0-9) + 2
// asi el indice 0 = 2, 1=3... 7=9, 8 =10 or AS.. 11 = 13
int getValorCarta(bool banca){
    srand (time(NULL));
    int indice = rand()%CANTIDAD_CARTAS;
    int valor_carta;
    int salir = 0;

    while (cartas[indice]==0){
        indice = rand()%CANTIDAD_CARTAS;
    }
    valor_carta = cartas[indice];
    if(banca){
        tipo_banca[indice_banca] = indice;
    }else{
        tipo_carta[indice_cartas] = indice;
    }
    if (valor_carta==11 && !banca){
        do{
            printf("Seleccione una opcion \n");
            printf("1. Quiero que el AS valga 1 \n");
            printf("2. Quiero que el AS valga 11 \n");
            scanf("%d",&salir);
            if (salir==1){
                valor_carta = 1;
            }
        }while (salir != 1 && salir != 2);
    }
    cartas[indice] = 0;
    return valor_carta;
}

void imprimirCartasJugador(){
    int i;
    short x = 10;
    gotoxy(1,10);
    printf(" %s tus puntos son: %d ",nombre, suma_cartas());
    for (i=0; i<12; i++){
        if(mis_cartas[i]!=0){
            gotoxy(x+i*10,11);
            printf(" _____ ");
            gotoxy(x+i*10,12);
            printf("|     |");
            gotoxy(x+i*10,13);
            printf("|     |");
            gotoxy(x+i*10,14);
            printf("|");
            if(mis_cartas[i]<=9){
                printf("  %d",mis_cartas[i]);
            }else{
                if (tipo_carta[i] == 8 || tipo_carta[i] == 20 || tipo_carta[i] == 32 || tipo_carta[i] == 44)printf(" AS");
                if (tipo_carta[i] == 9 || tipo_carta[i] == 21 || tipo_carta[i] == 33 || tipo_carta[i] == 45)printf("  J");
                if (tipo_carta[i] == 10 || tipo_carta[i] == 22 || tipo_carta[i] == 34 || tipo_carta[i] == 46)printf("  Q");
                if (tipo_carta[i] == 11 || tipo_carta[i] == 23 || tipo_carta[i] == 35 || tipo_carta[i] == 47)printf("  K");
            }

            if (tipo_carta[i]<12){
                printf("P ");
            }else{
                if (tipo_carta[i]<24){
                    printf("C ");
                }else{
                    if (tipo_carta[i]<36){
                        printf("D ");
                    }else{
                        printf("T ");
                    }
                }
            }
            printf("|");
            gotoxy(x+i*10,15);
            printf("|     |");
            gotoxy(x+i*10,16);
            printf("|_____|");
            gotoxy(x+i*10,17);
        }
    }
}



void imprimirCartasBanco(bool mostrar){
    int i, j=0;
    short x = 10;
    gotoxy(1,1);
    if(mostrar) printf("Total banca: %d",suma_banca());
    else printf("BANCA...");
    for (i=0; i<12; i++){
        if(carta_banca[i]!=0){
            gotoxy(x+j*10,3);
            printf(" _____ ");
            gotoxy(x+j*10,4);
            printf("|     |");
            gotoxy(x+j*10,5);
            printf("|     |");
            gotoxy(x+j*10,6);
            printf("|");
            if(mostrar){
                if(carta_banca[i]<=9){
                    printf("  %d",carta_banca[i]);
                }else{
                    if (tipo_banca[i] == 8 || tipo_banca[i] == 20 || tipo_banca[i] == 32 || tipo_banca[i] == 44)printf(" AS");
                    if (tipo_banca[i] == 9 || tipo_banca[i] == 21 || tipo_banca[i] == 33 || tipo_banca[i] == 45)printf("  J");
                    if (tipo_banca[i] == 10 || tipo_banca[i] == 22 || tipo_banca[i] == 34 || tipo_banca[i] == 46)printf("  Q");
                    if (tipo_banca[i] == 11 || tipo_banca[i] == 23 || tipo_banca[i] == 35 || tipo_banca[i] == 47)printf("  K");
                }

                if (tipo_banca[i]<12){
                    printf("P ");
                }else{
                    if (tipo_banca[i]<24){
                        printf("C ");
                    }else{
                        if (tipo_banca[i]<36){
                            printf("D ");
                        }else{
                            printf("T ");
                        }
                    }
                }
            }else printf("  X  ");
            printf("|");
            gotoxy(x+j*10,7);
            printf("|     |");
            gotoxy(x+j*10,8);
            printf("|_____|");
            gotoxy(x+j*10,9);
            j++;
        }
    }
}

void gotoxy(int x,int y){
    printf("%c[%d;%df",0x1B,y,x);
}

int getch(void)
{
       struct termios oldattr, newattr;
       int ch;
       tcgetattr( STDIN_FILENO, &oldattr );
       newattr = oldattr;
       newattr.c_lflag &= ~( ICANON | ECHO );
       tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
       ch = getchar();
       tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
       return ch;
}

