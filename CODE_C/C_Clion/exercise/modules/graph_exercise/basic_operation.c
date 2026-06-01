#include "graph.h"

bool matrix_insert_vertex(MatrixGraph *G, VertexType v){
    if (G==NULL || G->vexnum>=MAX_VERTEX_NUM) return false;
    for (int i=0;i<G->vexnum;i++) {
        int temp=G->vertex[i];
        if (v==temp) return false;
    }
    G->vertex[G->vexnum]=v;
    G->vexnum++;
    for (int i=0;i<G->vexnum;i++) {
        G->arcs[G->vexnum-1][i]=0;
        G->arcs[i][G->vexnum-1]=0;
    }
    return true;
}

bool matrix_insert_arc(MatrixGraph *G, VertexType v, VertexType w){
    int v_record=-1,w_record=-1;
    for (int i=0;i<G->vexnum;i++) {
        if (v==G->vertex[i]) v_record=i;
        if (w==G->vertex[i]) w_record=i;
    }
    if (v_record==-1 || w_record==-1) return false;
    if (G->arcs[v_record][w_record]==1) return false;
    G->arcs[v_record][w_record]=1;
    if (G->type==UDG) G->arcs[w_record][v_record]=1;
    G->arcnum++;
    return true;
}