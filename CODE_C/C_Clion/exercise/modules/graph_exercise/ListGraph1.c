#include "Graph.h"

bool insert_vertex(ListGraph *G, VertexType v){
    if (G->vexnum>=MAX_VERTEX_NUM) return false;
    for (int i=0; i<G->vexnum; i++) {
        if (G->vertex[i].data == v) return false;
    }
    VNode new_node;
    new_node.data=v;new_node.firstarc=NULL;
    G->vertex[G->vexnum]=new_node;
    G->vexnum++;
    return true;
}


bool insert_arc(ListGraph *G, VertexType v, VertexType w){
    int v_location=locate_vertex(G,v),w_location=locate_vertex(G,w);
    if (v_location==-1 || w_location==-1) return false;
    ArcNode *now=G->vertex[v_location].firstarc;
    if (now==NULL) {
        ArcNode* new_node=malloc(sizeof(ArcNode));new_node->adjvex=w_location;new_node->nextarc=NULL;new_node->info=NULL;
        G->vertex[v_location].firstarc=new_node;
    }
    else {
        if (G->vertex[now->adjvex].data==w) return false;
        while (now->nextarc!=NULL) {
            if (G->vertex[now->nextarc->adjvex].data==w) return false;
            now=now->nextarc;
        }
        ArcNode* new_node=malloc(sizeof(ArcNode));new_node->adjvex=w_location;new_node->nextarc=NULL;new_node->info=NULL;
        now->nextarc=new_node;
    }
    if (G->type==UDG) {
        ArcNode* new_node=malloc(sizeof(ArcNode));new_node->adjvex=v_location;new_node->nextarc=NULL;new_node->info=NULL;
        now=G->vertex[w_location].firstarc;
        if (now==NULL) G->vertex[w_location].firstarc=new_node;
        else {
            while (now->nextarc!=NULL) {
                now=now->nextarc;
            }
            now->nextarc=new_node;
        }
    }
    G->arcnum++;
    return true;
}
