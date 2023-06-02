#include <stdio.h>
#include <stdlib.h>
#define rep(i,a,b) for (int i=a; i<b; i++)
#define MAXV 100001
int discovered[MAXV];
int dist[MAXV];
int far,d;
typedef struct edgenode {
    int y;
    struct edgenode *next;
} edgenode;
typedef struct {
    edgenode *edges[MAXV];
    int degree[MAXV];
    int nvertices,nedges;
} graph;
typedef struct {
    int q[MAXV+1];
    int first,last,count;
} queue;
void init_queue(queue *q) {
    q->first=0; q->last=MAXV-1; q->count=0;
}
void enqueue(queue *q, int x) {
    q->last=(q->last+1)%MAXV;
    q->q[q->last]=x;
    q->count++;
}
int dequeue(queue *q) {
    int res=q->q[q->first];
    q->first=(q->first+1)%MAXV;
    q->count--; return res;
}
int empty_queue(queue *q) {
    return (q->count<=0);
}
void initialize_graph(graph *g) {
    g->nvertices=0; g->nedges=0;
    rep (i,0,MAXV) g->edges[i]=NULL;
    rep (i,0,MAXV) g->degree[i]=0;
}
void insert_edge(graph *g, int x, int y, int und) {
    edgenode *p=malloc(sizeof(edgenode));
    p->y=y; p->next=g->edges[x]; g->edges[x]=p; g->degree[x]++;
    if (und==1) {
        insert_edge(g,y,x,0);
        g->nedges++;
    }
}
void read_graph(graph *g, int n, int m) {
    initialize_graph(g);
    g->nvertices=n; int x,y;
    rep (i,0,m) {
        scanf("%d %d\n",&x,&y);
        insert_edge(g,x,y,1);
    }
}
void initialize_search() {
    rep (i,0,MAXV) discovered[i]=0;
    rep (i,0,MAXV) dist[i]=0;
    far=0; d=0;
}
void process_edge(int v, int y) {
    dist[y]=dist[v]+1;
    if (dist[y]>d) {
        d=dist[y];
        far=y;
    }
}
void bfs(graph *g, int start) {
    edgenode *p; int v,y; queue q;
    init_queue(&q); enqueue(&q,start);
    discovered[start]=1; dist[start]=0;
    while (empty_queue(&q)==0) {
        v=dequeue(&q);
        p=g->edges[v];
        while (p!=NULL) {
            y=p->y;
            if (discovered[y]==0) {
                discovered[y]=1;
                enqueue(&q,y);
                process_edge(v,y);
            }
            p=p->next;
        }
    }
}
int latency(graph *g) {
    initialize_search(); bfs(g,1);
    int aux=d,vert=far;
    initialize_search(); bfs(g,vert);
    return d;
}
int main() {
    int n,m; scanf("%d %d\n",&n,&m);
    graph g; read_graph(&g,n,m);
    printf("%d",latency(&g));
    return 0;
}
