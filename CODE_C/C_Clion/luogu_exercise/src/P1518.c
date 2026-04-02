#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAP_SIZE 10
#define UP 0
#define DOWN 2
#define LEFT 3
#define RIGHT 1

typedef struct {
    int x;
    int y;
    int direction;
    char type;
}position;

char* creat_map();
void print_map(char* map);
void find_CF(char* map,position* C,position* F);
void init_CF(position* CF);
bool can_move(char* map,position* CF);
void CF_move(char* map,position* CF);
bool move(char* map,position* C,position* F);
int get_result(char* map,position* C,position* F);

int main() {
    // FILE* original_stdin = stdin;
    // freopen("test.txt", "r", stdin);
    char *map = creat_map();
    //freopen("CON", "r", stdin);

    // print_map(map);
    position C,F;
    init_CF(&C);init_CF(&F);
    find_CF(map,&C,&F);
    int result=get_result(map,&C,&F);
    printf("%d",result);
    free(map);
    return 0;
}

int get_result(char* map,position* C,position* F) {
    int minutes=0;
    bool catch=false;
    while (catch==false) {
        catch=move(map,C,F);
        minutes++;
        if (minutes>10000) {
            return 0;
        }
    }
    return minutes;
}

void find_CF(char* map,position* C,position* F) {
    bool findC = false,findF = false;
    for (int i=0;i<MAP_SIZE;i++) {
        for (int j=0;j<MAP_SIZE;j++) {
            if (map[i*MAP_SIZE+j]=='C') {
                C->x = i;C->y = j;C->type = 'C';
                findC = true;
            }
            if (map[i*MAP_SIZE+j]=='F') {
                F->x = i;F->y = j;F->type = 'F';
                findF = true;
            }
            if (findC && findF) {
                return;
            }
        }
    }
}

void init_CF(position* CF) {
    CF->x = CF->y = 0;
    CF->direction = UP;
}

bool move(char* map,position* C,position* F) {
    CF_move(map,C);
    map[C->x*MAP_SIZE+C->y] = C->type;
    CF_move(map,F);
    if (map[F->x*MAP_SIZE+F->y]=='C') {
        return true;
    }else {
        map[F->x*MAP_SIZE+F->y] = F->type;
        return false;
    }

}

void CF_move(char* map,position* CF) {
    // printf("if%d\n",CF->direction);

    if (can_move(map,CF)) {
        map[CF->x*MAP_SIZE+CF->y] = '.';
        switch (CF->direction) {
            case UP:
                CF->x = CF->x-1;
                break;
            case DOWN:
                CF->x = CF->x+1;
                break;
            case RIGHT:
                CF->y = CF->y+1;
                break;
            case LEFT:
                CF->y = CF->y-1;
                break;
            default:
                printf("DIRECTION ERROR");
                break;
        }
    }else {
        CF->direction = (CF->direction+1)%4;
    }

    // printf("wait");
    // getchar();
}

bool can_move(char* map,position* CF) {
    int x=CF->x,y=CF->y;

    // printf("方向%d\n",CF->direction);

    if (CF->direction == UP) {
        if (x==0) {
            return false;
        }
        if (map[x*MAP_SIZE+y-1*MAP_SIZE]=='*') {
            return false;
        }
    }else if (CF->direction == DOWN) {
        if (x==MAP_SIZE-1) {
            return false;
        }
        if (map[x*MAP_SIZE+y+1*MAP_SIZE]=='*') {
            return false;
        }
    }else if (CF->direction == LEFT) {
        if (y==0) {
            return false;
        }
        if (map[x*MAP_SIZE+y-1]=='*') {
            return false;
        }
    }else if (CF->direction == RIGHT) {
        if (y==MAP_SIZE-1) {
            return false;
        }
        if (map[x*MAP_SIZE+y+1]=='*') {
            return false;
        }
    }
    return true;
}

char* creat_map() {
    char* map=(char*)malloc(MAP_SIZE*MAP_SIZE*sizeof(char));
    for (int i=0;i<MAP_SIZE;i++) {
        char str[MAP_SIZE+1];
        scanf("%s",str);
        for (int j=0;j<MAP_SIZE;j++) {
            map[i*MAP_SIZE+j]=str[j];
        }
    }
    return map;
}

void print_map(char* map) {
    for (int i=0;i<MAP_SIZE;i++) {
        for (int j=0;j<MAP_SIZE;j++) {
            printf("%c",map[i*MAP_SIZE+j]);
        }
        printf("\n");
    }
}