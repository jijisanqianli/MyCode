#include "Graph.h"

bool del_vertex(ListGraph *G, VertexType v){
    int decrease_DG=0;
    if (G==NULL) return false;
    int v_location=locate_vertex(G, v);
    if (v_location==-1) return false;
    for (int i=0;i<G->vexnum;i++) {
        ArcNode* now=G->vertex[i].firstarc;
        if (now==NULL) continue;
        if (i==v_location) {
            while (now!=NULL) {
                ArcNode* trash=now;
                now=now->nextarc;
                free(trash);decrease_DG++;;
            }
            G->vertex[i].firstarc=NULL;
            continue;
        }
        while (now->nextarc!=NULL) {
            if (now->nextarc->adjvex==v_location) {
                ArcNode* trash=now->nextarc;
                now->nextarc=now->nextarc->nextarc;
                free(trash);decrease_DG++;
                continue;
            }
            now=now->nextarc;
        }
        if (G->vertex[i].firstarc->adjvex==v_location) {
            ArcNode* trash=G->vertex[i].firstarc;
            G->vertex[i].firstarc=G->vertex[i].firstarc->nextarc;
            free(trash);decrease_DG++;
        }
        now=G->vertex[i].firstarc;
        while (now!=NULL) {
            if (now->adjvex>v_location) now->adjvex--;
            now=now->nextarc;
        }
    }
    if (G->type==DG) G->arcnum-=decrease_DG;
    else if (G->type==UDG) G->arcnum-=(decrease_DG/2);
    for (int i=v_location;i<G->vexnum-1;i++) {
        G->vertex[i]=G->vertex[i+1];
    }
    G->vexnum--;
    return true;
}