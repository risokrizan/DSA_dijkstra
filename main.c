// zadanie3.c -- Richard Križan, 27.11.2017 20:45

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#define INF INT_MAX

typedef struct vertex {
    int x;
    int y;
    int time;
    int index;
    //0-hore 1-doprava 2-dole 3-dolava
    int zoznam[4];
}V;

typedef struct postava{
    int vrchol[3];
    int index;
}POSTAVA;

typedef struct cesta{
    int *x;
    int *y;
    int indexXY;
    int dlzka;
}CELKOVA;


CELKOVA direction[8];
int index_dir;

void print_mapa (V *map,int n, int m){
    for (int i=0;i<n*m;i++){
        
        if (i%m==0 && i!=0)
            printf ("\n");
        printf ("%d",map[i].time);
        
    }
}

int cas (char c){
    if (c == 'C')
        return 1;
    else if (c == 'H')
        return 2;
    else if (c == 'N')
        return -1;
    else if (c == 'D')
        return 1;
    else if (c == 'P')
        return 1;
    else if (c == 'G')
        return 1;
    else if (isdigit(c))
        if ((int)c >='0' && c<='9')
            return 1;
    return -INF;
}
int edge_exist (V *vrcholy,int src, int dest){
    
    for (int i =0 ;i<=3;i++){
        if (vrcholy[src].zoznam[i]==dest)
            return 1;
    }
    return 0;
}
void printPath(V *vrcholy,int parent[], int j)
{
    
    //for (int i = j;i!=-1;i=parent[i]){
    //  printf("%d ",i);
    //}
    
    if (parent[j]==-1)
        return;
    
    printPath(vrcholy, parent, parent[j]);
    
    
    direction[index_dir].x[direction[index_dir].indexXY]=vrcholy[j].x;
    direction[index_dir].y[direction[index_dir].indexXY]=vrcholy[j].y;
    direction[index_dir].indexXY++;
}




int dijkstra(V *vrcholy, int src ,int dst, int n, int m)
{
    int dist[n*m];
    char visited[n*m];
    int path[n*m];
    
    for (int i = 0; i < n*m; i++){
        dist[i] = INF;
        //visited[i] = 0;
    }
    memset (visited,0,n*m);
    dist[src] = 0;
    path [src] = -1;
    
    for (int i = 0; i < (n*m)-1; i++)
    {
        int min = INF;
        int u = 0;
        for (int v = 0; v < n*m; v++){
            if (visited[v] == 0 && dist[v] <= min){
                min = dist[v];
                u = v;
            }
        }
        visited[u] = 1;
        for (int v = 0; v < n*m; v++){   
            if (!visited[v] && edge_exist(vrcholy,u, v) && dist[u] != INF && dist[u] + vrcholy[v].time < dist[v]){
                dist[v] = dist[u] + vrcholy[v].time;
                path[v]=u;
            }
        }
    }
    printPath(vrcholy,path, dst);
    return dist[dst];
}
int compare (const void * a, const void * b)
{
    //copyright (c) cplusplus.com
    //http://www.cplusplus.com/reference/cstdlib/qsort/

    return ( *(int*)a - *(int*)b );
}


int *zachran_princezne(char **mapa, int n, int m, int t, int *dlzka_cesty)
{
    
    index_dir=0;
    POSTAVA *drak = (POSTAVA*)calloc(1, sizeof(POSTAVA));
    POSTAVA *princezna = (POSTAVA*) calloc(1, sizeof(POSTAVA));
    V *node = (V*) calloc(n*m,sizeof(V));
    
    for (int i=0;i<8;i++){
        direction[i].x = (int*) calloc ((n*m),sizeof(int));
        direction[i].y = (int*) calloc ((n*m),sizeof(int));
        if (i==0){
            direction[i].x[0]=0;
            direction[i].y[0]=0;
            direction[i].indexXY++;
        }
    }
    for (int i=0 ; i<n ;i++){
        for (int j=0; j<m;j++){
            int index = j + (m*i);
            if (mapa[i][j]=='D')
                drak->vrchol[0]=index;
            if (mapa[i][j]=='P'){
                princezna->vrchol[princezna->index]=index;
                princezna->index++;
            }
            if (index !=0){
                direction[index % 8].x[index]=INF;
                direction[index % 8].y[index]=INF;
            }
            node[index].zoznam[0]=-INF;
            node[index].zoznam[1]=-INF;
            node[index].zoznam[2]=-INF;
            node[index].zoznam[3]=-INF;
            //node[index].index=index;
            node[index].x=j;
            node[index].y=i;
            node[index].time=cas(mapa[i][j]);
            //hore
            if (i-1>=0)
                node[index].zoznam[0] = j+(m*(i-1));
            //doprava
            if (j+1<m)
                node[index].zoznam[1] = (j+1)+(m*i);
            //dole
            if (i+1<n)
                node[index].zoznam[2] = j+(m*(i+1));
            //dolava
            if (j-1>=0)
                node[index].zoznam[3] = (j-1)+(m*i);
            //   printf ("SOM: %d Hore: %d Doprava %d Dole: %d Dolava: %d \n",index,node[index].zoznam[0],node[index].zoznam[1],node[index].zoznam[2],node[index].zoznam[3]);
        }
    }
    
    
    int minPath = dijkstra(node, 0, drak->vrchol[0], n, m);
    direction[index_dir].dlzka +=abs(minPath);
    index_dir++;
    
    int *vys = (int*) calloc (6,sizeof(int));
    //printf ("%d,%d,%d",princezna->vrchol[0],princezna->vrchol[1],princezna->vrchol[2]);
    vys[0]= minPath+dijkstra(node,drak->vrchol[0],princezna->vrchol[0], n, m)+dijkstra(node,princezna->vrchol[0],princezna->vrchol[1], n, m)+dijkstra(node,princezna->vrchol[1],princezna->vrchol[2], n, m);
    direction[index_dir].dlzka +=abs(vys[0]);
    index_dir++;
    vys[1]= minPath+dijkstra(node,drak->vrchol[0],princezna->vrchol[0], n, m)+dijkstra(node,princezna->vrchol[0],princezna->vrchol[2], n, m)+dijkstra(node,princezna->vrchol[2],princezna->vrchol[1], n, m);
    direction[index_dir].dlzka +=abs(vys[1]);
    index_dir++;
    vys[2]= minPath+dijkstra(node,drak->vrchol[0],princezna->vrchol[1], n, m)+dijkstra(node,princezna->vrchol[1],princezna->vrchol[0], n, m)+dijkstra(node,princezna->vrchol[0],princezna->vrchol[2], n, m);
    direction[index_dir].dlzka +=abs(vys[2]);
    index_dir++;
    vys[3]= minPath+dijkstra(node,drak->vrchol[0],princezna->vrchol[1], n, m)+dijkstra(node,princezna->vrchol[1],princezna->vrchol[2], n, m)+dijkstra(node,princezna->vrchol[2],princezna->vrchol[0], n, m);
    direction[index_dir].dlzka +=abs(vys[3]);
    index_dir++;
    vys[4]= minPath+dijkstra(node,drak->vrchol[0],princezna->vrchol[2], n, m)+dijkstra(node,princezna->vrchol[2],princezna->vrchol[0], n, m)+dijkstra(node,princezna->vrchol[0],princezna->vrchol[1], n, m);
    direction[index_dir].dlzka +=abs(vys[4]);
    index_dir++;
    vys[5]= minPath+dijkstra(node,drak->vrchol[0],princezna->vrchol[2], n, m)+dijkstra(node,princezna->vrchol[2],princezna->vrchol[1], n, m)+dijkstra(node,princezna->vrchol[1],princezna->vrchol[0], n, m);
    direction[index_dir].dlzka +=abs(vys[5]);
    index_dir++;
    
    qsort (vys, 6, sizeof(int), compare);
    //printf ("vys 0:%d\n",vys[0]);
    int i=0;
    for(i=1;i<index_dir;i++){
      //  printf ("vys %d\n",vys[i]);
        if (direction[i].dlzka==vys[0]){
            //printf("dlzka cesty %d",direction[i].dlzka);
            //dlzka_cesty = &direction[i].dlzka;
            break;
        }
    }
    
    
    
    //int j;
    // for (j=0;j<2*direction[0].indexXY;j++){
    //printf ("X:%d Y:%d\n",direction[0].x[j],direction[0].y[j]);
    //    vysledna_cesta[j]=direction[0].x[j];
    //  vysledna_cesta[j+1]=direction[0].x[j];
    //}
    
    for (int g=0;g<direction[i].indexXY;g++){
        direction[0].x[direction[0].indexXY]=direction[i].x[g];
        direction[0].y[direction[0].indexXY]=direction[i].y[g];
        direction[0].indexXY++;
    }
    
   
   
    int *vysledna_cesta = (int*)malloc((2*(direction[0].indexXY))* sizeof(int));
    
    for (int j=0;j<direction[0].indexXY;j++){
        //printf ("X:%d Y:%d\n",direction[0].x[i],direction[0].y[i]);
        vysledna_cesta[2*j]=direction[0].x[j];
        vysledna_cesta[2*j+1]=direction[0].y[j];
    }



   //for (int i=0;i<2*direction[0].indexXY;i++){
     //   printf ("%d ",vysledna_cesta[i]);
   //}
     
   
    *dlzka_cesty=direction[0].indexXY;
   
    
    return vysledna_cesta;
    // sem napis svoje riesenie
}






// Vlastna funkcia main() je pre vase osobne testovanie. Dolezite: pri testovacich scenaroch sa nebude spustat!
int main()
{
    
    char map[5][5] = {
        {'P', 'P', 'H', 'H', 'H'},
        {'H', 'C', 'H', 'H', 'C'},
        {'C', 'C', 'H', 'C', 'C'},
        {'C', 'H', 'C', 'H', 'C'},
        {'H', 'P', 'C', 'D', 'C'}
        
    };
    char * map_d_r[5] = { map[0], map[1], map[2], map[3], map[4]};
    char ** map_d = map_d_r;
    
    int ferko;
    
    zachran_princezne(map_d, 5, 5, 20, &ferko);
    
    printf ("\n%d",ferko);
    
    return 0;
}
