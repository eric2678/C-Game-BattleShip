#include <stdlib.h>
#include <stdio.h>
#include <windows.h>

int Com_Map[100][100], Pla_Map[100][100];
int i, j;

int Recursion(int times, int row, int column, int choice, int Player, int size){
    if(times==0)    return 0;
    if(choice==1){
        if(row+times<=size-1){
            if(Player==0){
                if(Com_Map[row][column]!=99){
                    if(Recursion(times-1, row+1, column, choice, Player, size)==0){
                        Com_Map[row][column]=99;
                        return 0;
                    }else{
                        Com_Map[row][column]=0;
                        return 1;
                    }
                }else{
                    return 1;
                }
            }else if(Player==1){
                if(Pla_Map[row][column]!=99){
                    if(Recursion(times-1, row+1, column, choice, Player, size)==0){
                        Pla_Map[row][column]=99;
                        return 0;
                    }else{
                        Pla_Map[row][column]=0;
                        return 1;
                    }
                }else{
                    return 1;
                }
            }
        }else{
            return 1;
        }
    }else if(choice==2){
        if(column+times<=size-1){
            if(Player==0){
                if(Com_Map[row][column]!=99){
                    if(Recursion(times-1, row, column+1, choice, Player, size)==0){
                        Com_Map[row][column]=99;
                        return 0;
                    }else{
                        Com_Map[row][column]=0;
                        return 1;
                    }
                }else{
                    return 1;
                }
            }else if(Player==1){
                if(Pla_Map[row][column]!=99){
                    if(Recursion(times-1, row, column+1, choice, Player, size)==0){
                        Pla_Map[row][column]=99;
                        return 0;
                    }else{
                        Pla_Map[row][column]=0;
                        return 1;
                    }
                }else{
                    return 1;
                }
            }
        }else{
            return 1;
        }
    }
}

void Assign(int Player, int size){
    char Ships[5][20] = {"Carrier", "BattleShip", "Crusier", "Submarine", "Destroyer"};
    int length[5] = {5, 4, 3, 3, 2};
    int choice;
    int row, column;
    for (i=0; i<5; i++){
        if (Player == 0){
            row=rand()%size;
            column=rand()%size;
            choice=rand()%2+1;
            // printf("times:%3d, Row:%3d, Column:%3d, Choice:%3d, Player:%3d, Size:%3d\n", length[i], row, column, choice, Player, size);
            if(Recursion(length[i], row, column, choice, Player, size)==1)  i--;
        }else if(Player == 1){
            do{
                printf("Please assign the position of your %s.\n", Ships[i]);
                printf("Row, Column: ");
                scanf("%d %d", &row, &column);
                do{
                    printf("Do you want to assign it vertically(1) or horizontally(2)?");
                    scanf("%d", &choice);
                }while(choice<1 || choice>2);
            }while(Recursion(length[i], row, column, choice, Player, size) == 1);
        }
    }
}

int CreateMap(){
    int size;
    do{
        printf("How big is the map?(>=10)");
        scanf("%d", &size);
        for(i=0; i<size; i++){
            for(j=0; j<size; j++){
                Com_Map[i][j]=0;
                Pla_Map[i][j]=0;
            }
        }
    }while (size<10);
    return size;
}

int main(){
    int seed, size;
    int PlayAgain=0;
    int i, j;

    printf("Enter the Random Seed:");
    scanf("%d", &seed);
    srand(seed);
    do{
        size=CreateMap();
        printf("Please wait for Computer to set its Battleships.\n");
        Sleep(2000);
        Assign(0, size);
        Assign(1, size);
        printf("\n(This is Com1's Map)                        (This is Pla1's Map)\n");
        for(i=0; i<size; i++){
            for(j=0; j<size; j++){
                printf("%3d", Com_Map[i][j]);
            }
            printf("        ");
            for(j=0; j<size; j++){
                printf("%3d", Pla_Map[i][j]);
            }
            printf("\n");
        }
        // for(i=0; i<size^2; i++){

        // }
    }while(PlayAgain==1);
    system("Pause");
    return 0;
}