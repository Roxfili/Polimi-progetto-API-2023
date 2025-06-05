#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct station{
    int key;
    char col;
    struct car *root, *nil;
    struct station *p, *l, *r;
};
struct percorsoTree{
    struct percorsoNode *root;
};

struct percorsoNode{
    int key;
    int dist;
    struct percorsoNode *p, *l, *r,*prec;
};
struct car{
    int key;
    char col;
    struct car *p, *l, *r;
};

struct tree{
    struct station *root, *nil;
};
struct percorsoNode* searchPercorso(struct percorsoNode *x, int k){
    if(x==NULL || k==x->key){
        return x;
    }else{
        if(k<x->key && x->l!=NULL){
            return searchPercorso(x->l,k);
        }else if(x->r!=NULL){
            return searchPercorso(x->r,k);
        }else{
            return NULL;
        }
    }
}

struct percorsoNode* minPercorso(struct percorsoNode *x){
    while(x->l!=NULL){
        x=x->l;
    }
    return x;
}

struct percorsoNode* maxPercorso(struct percorsoNode *x){
    while(x->r!=NULL){
        x=x->r;
    }
    return x;
}
struct percorsoNode* percorsonext(struct percorsoNode *x){
    if(x->r!=NULL){
        return minPercorso(x->r);
    }
    if(x->p!=NULL){
        struct percorsoNode *y =x->p;
        while(y!=NULL && y->p!=NULL && x==y->r){
            x=y;
            y=y->p;
        }
        return y;
    }else{
        return NULL;
    }
}
struct percorsoNode* percorsoPrev(struct percorsoNode *x){
    if(x->l!=NULL){
        return maxPercorso(x->l);
    }
    if(x->p!=NULL){
        if(x->p->r==x){
            return x->p;
        }else{
            struct percorsoNode *y =x->p;
            while(y!=NULL && x==y->l){
                x=y;
                y=y->p;
            }
            return y;
        }
    }else{
        return NULL;
    }
}

void insertPercorso(struct percorsoNode *z, struct percorsoTree *T){
    if(searchPercorso(T->root,z->key)==NULL) {
        struct percorsoNode *y = NULL;
        struct percorsoNode *x = T->root;
        if (x == NULL) { //se l'albero è vuoto inserisco nella radice
            T->root = z;
        } else {
            while (x != NULL) {
                y = x;
                if (z->key <
                    x->key) { //se quello che voglio inserire è minore di quello che sto guardando, guardo il figlio sinistro
                    x = x->l;
                } else { //altrimenti guardo il figlio destro
                    x = x->r;
                }
            }
            z->p = y;
            if (y == NULL) {
                T->root = z;
            } else if (z->key < y->key) {
                y->l = z;
            } else {
                y->r = z;
            }
        }
    }
}
void deletePercorso(struct percorsoNode *z, struct percorsoTree *T){
    struct percorsoNode *y=NULL;
    struct percorsoNode *x=NULL;
    if(z->l ==NULL || z->r ==NULL){
        y=z;
    }else{
        y= percorsonext(z);
    }
    if(y->l!=NULL){
        x=y->l;
    }else{
        x=y->r;
    }
    if(x!=NULL){
        x->p=y->p;
    }
    if(y->p==NULL){
        T->root=x;
    }else if(y==y->p->l){
        y->p->l=x;
    }else{
        y->p->r=x;
    }
    if(y!=z){
        z->key=y->key;
    }
    free(y); //nodo eliminato
}
void leftRotateTree(struct tree *T, struct station *x){
    if(x->r!=T->nil) {
        struct station *y = x->r;
        x->r = y->l;

        if (y->l != T->nil) {
            y->l->p = x;
        }
        y->p = x->p;

        if (x->p == T->nil) {
            T->root = y;
        } else if (x == x->p->l) {
            x->p->l = y;
        } else {
            x->p->r = y;
        }

        y->l = x;
        x->p = y;
    }
}

void leftRotateStation(struct station *S, struct car *x){
    if(x->r!=S->nil) {
        struct car *y = x->r;
        x->r = y->l;

        if (y->l != S->nil) {
            y->l->p = x;
        }
        y->p = x->p;

        if (x->p == S->nil) {
            S->root = y;
        } else if (x == x->p->l) {
            x->p->l = y;
        } else {
            x->p->r = y;
        }

        y->l = x;
        x->p = y;
    }
}
void rightRotateTree(struct tree *T, struct station *y){
    if(y->l!=T->nil) {
        struct station *x = y->l;
        y->l = x->r;

        if (x->r != T->nil) {
            x->r->p = y;
        }
        x->p = y->p;

        if (y->p == T->nil) {
            T->root = x;
        } else if (y == y->p->r) {
            y->p->r = x;
        } else {
            y->p->l = x;
        }

        x->r = y;
        y->p = x;
    }
}

void rightRotateStation(struct station *S, struct car *y){
    if(y->l!=S->nil) {
        struct car *x = y->l;
        y->l = x->r;

        if (x->r != S->nil) {
            x->r->p = y;
        }
        x->p = y->p;

        if (y->p == S->nil) {
            S->root = x;
        } else if (y == y->p->r) {
            y->p->r = x;
        } else {
            y->p->l = x;
        }

        x->r = y;
        y->p = x;
    }
}

void fixColorInsertTree(struct tree *T, struct station *z){

    if (z == T->root ||z->p==NULL){
        T->root->col='b';
    } else{
        struct station *x = z->p;
        if(x->col =='r' && x->p !=T->nil && x->p->l !=T->nil){
            if(x->p!=T->nil && x->p->r !=T->nil && x == x->p->l){
                struct station *y = x->p->r;
                if(y != NULL && y->col == 'r'){
                    x->col = 'b';
                    y->col = 'b';
                    x->p->col ='r';
                    fixColorInsertTree(T,x->p);
                }else if(x!=NULL && z==x->r){
                    z=x;
                    leftRotateTree(T,z);
                    x=z->p;
                }
                x->col= 'b';
                x->p->col ='r';
                rightRotateTree(T,x->p);
            }else{
                struct station *y = x->p->l;
                if(y!= T->nil && y->col == 'r'){
                    x->col = 'b';
                    y->col = 'b';
                    x->p->col ='r';
                    fixColorInsertTree(T,x->p);
                }else if(z==x->l){
                    z=x;
                    rightRotateTree(T,z);
                    x=z->p;
                }
                x->col= 'b';
                x->p->col ='r';
                leftRotateTree(T,x->p);
            }
        }
    }
    T->root->col='b';
}

void fixColorInsertStation(struct station *S, struct car *z){
    if (z == S->root){
        S->root->col='b';
    }
    else{
        struct car *x = z->p;
        if(x->col =='r'){
            if(x == x->p->l){
                struct car *y = x->p->r;
                if(y!= NULL && y->col == 'r'){
                    x->col = 'b';
                    y->col = 'b';
                    x->p->col ='r';
                    fixColorInsertStation(S,x->p);
                }else if(z==x->r){
                    z=x;
                    leftRotateStation(S,z);
                    x=z->p;
                }
                x->col= 'b';
                x->p->col ='r';
                rightRotateStation(S,x->p);
            }else{
                struct car *y = x->p->l;
                if(y!= S->nil && y->col == 'r'){
                    x->col = 'b';
                    y->col = 'b';
                    x->p->col ='r';
                    fixColorInsertStation(S,x->p);
                }else if(x->l != NULL && z==x->l){
                    z=x;
                    rightRotateStation(S,z);
                    x=z->p;
                }
                x->col= 'b';
                x->p->col ='r';
                leftRotateStation(S,x->p);
            }
        }
    }
}

void fixColorDeleteTree(struct tree *T, struct station *x){
    if (x->col == 'r' || x->p == T->nil){ //se radice nera
        x->col = 'b';
    }else if(x == x->p->l){
        struct station *w = x->p->r;
        if(w!=NULL) {
            if (w->col == 'r') {
                w->col = 'b';
                x->p->col = 'r';
                leftRotateTree(T, x->p);
                w = x->p->r;
            }
            if (w!=NULL && w->l!=NULL && w->r!=NULL && w->l->col == 'b' && w->r->col == 'b') {
                w->col = 'r';
                fixColorDeleteTree(T, x->p);
            } else if (w!= NULL && w->r!=NULL && w->r->col == 'b') {
                if(w->l!=NULL){
                    w->l->col = 'b';
                }

                w->col = 'r';
                rightRotateTree(T, w);
                w = x->p->r;
            }
            if(w!=NULL && w->r!=NULL) {
                w->col = x->p->col;
                x->p->col = 'b';
                w->r->col = 'b';
                leftRotateTree(T, x->p);
            }
        }
    }else{
        struct station *w = x->p->l;
        if(w!=NULL) {
            if (w->col == 'r') {
                w->col = 'b';
                x->p->col = 'r';
                rightRotateTree(T, x->p);
                w = x->p->l;
            }
            if (w != NULL && w->r!=NULL && w->l!=NULL && w->r->col == 'b' && w->l->col == 'b') {
                w->col = 'r';
                fixColorDeleteTree(T, x->p);
            } else if (w != NULL && w->l!=NULL && w->l->col == 'b') {
                if(w->r!=NULL) w->r->col = 'b';
                w->col = 'r';
                leftRotateTree(T, w);
                w = x->p->l;
            }
            if (w != NULL) {
                w->col = x->p->col;
                x->p->col = 'b';
                if(w->r!=NULL) w->r->col = 'b';
                rightRotateTree(T, x->p);
            }
        }
    }
}

void fixColorDeleteStation(struct station *S, struct car *x){
    if(x!=S->nil) {
        if (x->col == 'r' || x->p == S->nil) {
            x->col = 'b';
        } else if (x == x->p->l) {
            struct car *w = x->p->r;
            if (w != NULL && w->col == 'r') {
                w->col = 'b';
                x->p->col = 'r';
                leftRotateStation(S, x->p);
                w = x->p->r;
            }
            if (w != NULL && w->l!=NULL && w->l->col == 'b' && w->r!=NULL && w->r->col == 'b') {
                w->col = 'r';
                fixColorDeleteStation(S, x->p);
            } else if (w != NULL && w->r !=NULL && w->r->col == 'b') {
                if(w->l!=NULL) w->l->col = 'b';
                w->col = 'r';
                rightRotateStation(S, w);
                w = x->p->r;
            }
            if (w != NULL) {
                w->col = x->p->col;
                x->p->col = 'b';
                if(w->r!=NULL) w->r->col = 'b';
                leftRotateStation(S, x->p);
            }
        } else {
            struct car *w = x->p->l;

            if (w != NULL && w->col == 'r') {
                w->col = 'b';
                x->p->col = 'r';
                rightRotateStation(S, x->p);
                w = x->p->l;
            }
            if (w != NULL && w->l !=NULL && w->r !=NULL && w->r->col == 'b' && w->l->col == 'b') {
                w->col = 'r';
                fixColorDeleteStation(S, x->p);
            } else if (w != NULL && w->l!=NULL && w->l->col == 'b') {
                if(w->r!=NULL){
                    w->r->col = 'b';
                }

                w->col = 'r';
                leftRotateStation(S, w);
                w = x->p->l;
            }
            if (w != NULL) {
                w->col = x->p->col;
                x->p->col = 'b';
                if(w->r!=NULL) w->r->col = 'b';
                rightRotateStation(S, x->p);
            }
        }
    }
}
void insertNodeTree(struct tree *T, struct station *z){

    struct station *y = T->nil;
    struct station *x = T->root;
    while (x != NULL){
        y=x;
        if(z->key < x->key){
            x = x->l;
        }else{
            x = x->r;
        }
    }
    z->p = y;
    if(T->root == NULL){
        T->root = z; //albero vuoto
    }else if(z->key < y->key){
        y->l =z;
    }else{
        y->r = z;
    }
    z->l = T->nil;
    z->r = T->nil;
    z->col = 'r';
    if(z->p!=NULL){
        fixColorInsertTree(T,z);
    }

}

void insertNodeStation(struct station *S, struct car *z){

    struct car *y = S->nil;
    struct car *x = S->root;
    while (x != S->nil){
        y=x;
        if(z->key < x->key){
            x = x->l;
        }else{
            x = x->r;
        }
    }
    z->p = y;
    if(S->root == NULL){
        S->root = z; //empty station
    }else if(z->key < y->key){
        y->l =z;
    }else{
        y->r = z;
    }
    z->l = S->nil;
    z->r = S->nil;
    z->col = 'r';
    fixColorInsertStation(S,z);
}
struct station* TreeMin(struct tree *T, struct station *x){
    while (x->l != T->nil){
        x = x->l;
    }
    return x;
}
struct station* TreeMax(struct tree *T, struct station *x){
    while (x->r != T->nil){
        x = x->r;
    }
    return x;
}

struct car* stationMin(struct station *S, struct car *x){
    while (x->l != S->nil){
        x = x->l;
    }
    return x;
}

struct car* stationMax(struct station *S, struct car *x){
    while(x->r != S->nil){
        x = x->r;
    }
    return x;
}
struct station* nextStation(struct tree *T,struct station *x){
    if (x->r != T->nil){
        return TreeMin(T, x->r);
    }
    struct station * y = x->p;
    while(y != T->nil && x == y->r){
        x = y;
        y=y->p;
    }
    return y;
}
struct station* precStation(struct tree* T, struct station* x) {

    if(x->l!=T->nil){
        return TreeMax(T,x->l); //massimo sottoalbero sx
    }
    struct station *y = x->p; //antenato con nodo o antenato a dx
    while(y!=T->nil && x==y->l){
        x=y;
        y=y->p;
       /* if(x==y->r){
            return y;
        }*/
    }
    if (y == T->nil) {
        return NULL; // Non c'è un predecessore
    } else {
        return y; // Restituisci l'antenato a destra
    }

}
//TODO delete find station2
struct station* findStationOrNearestMinor2(struct station* s, int k){

    if(s==NULL){
        return NULL;
    }
    if(s->key == k){
        return s;
    }
    struct station* close = NULL;

    if(s->key<k){

        close = findStationOrNearestMinor2(s->r,k); //se minore provo a vedere tra piu grandi
    }else{
        close = findStationOrNearestMinor2(s->l,k); //se maggiore guardo tra piu piccoli
        if(close == NULL || close->key < k){ //se sono a una foglia o in numeri piu bassi di quello iniziale, era s
            close = s;
        }
    }
    return close;
}

struct station* findStation(struct station *x, int k){
    if(x == NULL || x->key == k){
        return x;
    }
    if (k< x->key){
        return findStation(x->l,k);
    }else{
        return findStation(x->r,k);
    }
}

struct station* deleteNodeTree(struct tree *T, struct station *z) {
    struct station *y;
    struct station *x;
    if (z->l == T->nil || z->r == T->nil) {
        y = z;
    } else {
        y = nextStation(T, z);
    }
    if (y->l != T->nil) {
        x = y->l;
    } else {
        x = y->r;
    }
    if(x!=NULL) {
        x->p = y->p;
    }
    if (y->p == T->nil) {
        T->root = x;
    } else if (y == y->p->l) {
        if(y->l == NULL && y->r == NULL){
            y->p->l = NULL;
        }else{
            y->p->l = x;
        }

    } else {
        if(y->l == NULL && y->r == NULL){
            y->p->r = NULL;
        }else{
            y->p->r = x;
        }
    }

    if (y != z) {
        z->key = y->key;
        z->root = y->root;
    }
    if (y->col == 'b' && x!=NULL) {
        fixColorDeleteTree(T, x);
    }
    return y;
    //free(y);
}

struct station* findStationOrNearestGreater(struct tree *aut, struct station* s, int km_car){ //O(h^2) //reach
    struct station *curr = findStation(aut->root,s->key-km_car);
    struct station *reached = NULL;
    if(curr!=NULL){
        return curr;
    }else {
        struct station *found = findStation(aut->root,s->key-km_car);
        if(found !=NULL){
            return found;
        }
        struct station *new = (struct station*)malloc(sizeof(struct station));
        new->key = s->key-km_car;
        insertNodeTree(aut, new);

        reached = nextStation(aut,new);
        if(reached==s){
            struct station* del = deleteNodeTree(aut,new);
            free(del);
            return NULL;
        }else{
            struct station * temp = deleteNodeTree(aut,new);
            if(temp==new){
                free(temp);
                return reached;
            }else{
                free(temp);
                return new;
            }
        }
    }
}

struct car* nextCar(struct station *S,struct car *x){
    if (x->r != S->nil){
        return stationMin(S, x->r);
    }
    struct car * y = x->p;
    while(y != S->nil && x == y->r){
        x = y;
        y=y->p;
    }
    return y;
}


void deleteNodeStation(struct station *S, struct car *z){
    struct car *y;
    struct car *x;
    if(z->l == S->nil || z->r == S->nil){
        y = z;
    }else{
        y = nextCar(S,z);
    }
    if(y->l != S->nil){
        x = y->l;
    }else{
        x = y->r;
    }if(x!=S->nil){
        x->p = y->p;
    }

    if(y->p == S->nil){
        S->root = x;
    }else if(y == y->p->l){
        y->p->l = x;
    }else{
        y->p->r = x;
    }
    if (y != z){
        z->key = y->key;
    }
    if (y->col == 'b'){
        fixColorDeleteStation(S,x);
    }
    free(y);
}


struct car* findCar(struct car *x, int k){
    if(x == NULL || x->key == k){
        return x;
    }
    if (k< x->key){
        return findCar(x->l,k);
    }else{
        return findCar(x->r,k);
    }
}

struct tree* pianificaPercorsoAndata(struct tree* T, int start, int end){
    struct station *first = findStation(T->root,start); //start station
    struct station *last = findStation(T->root,end); //last station
    struct station *curr = NULL;
    struct station * next = NULL;
    int max = stationMax(first, first->root)->key; //highest car in starting station
    struct tree *P = (struct tree*)malloc(sizeof(struct tree)); //percorso
    P->root=NULL;
    P->nil=NULL;
    next = nextStation(T, first);
    if(start+max < next->key){ //se dalla partenza non si va da nessuna parte
        free(P);
        return NULL;
    }else{
        while(end>start){
            curr = first;
            int max_car=max;
            while(curr->key + max_car < end){
                next = nextStation(T, curr);
                if(next->key == end){
                    free(P);
                    return NULL;
                }
                max_car = stationMax(next,next->root)->key;
                curr=next;
            }
            struct station *s = (struct station*)malloc(sizeof(struct station));
            s->key=curr->key;

            insertNodeTree(P,s);
            end=curr->key;
        }
    }
    struct station *s = (struct station*)malloc(sizeof(struct station));
    s->key = last->key;
    insertNodeTree(P,s);
    return P;
}

void deallocStation(struct station* s, struct car* c){
    if(c==NULL){
        return;
    }else{
        deallocStation(s,c->l);
        deallocStation(s,c->r);
    }
    deleteNodeStation(s,c);
}
void deallocTree(struct tree *t, struct station *s){
    if(s==NULL){
        return;
    }else{
        deallocTree(t, s->l);
        deallocTree(t,s->r);
    }
    deallocStation(s,s->root);
    struct station *del=deleteNodeTree(t,s);
    free(del);
}

struct percorsoTree* pianificaPercorsoRitorno3(int start, int end, struct tree *aut){
    struct station *begin = findStation(aut->root, start); // stazione di partenza
    if(begin->root==NULL){
        return NULL;
    }
    //inizializzo daVisitare e distanze
    int max_car = stationMax(begin,begin->root)->key; //massima macchina disponibile nella stazione;
    struct station *reached = findStationOrNearestGreater(aut,begin, max_car); //massima stazione raggiungibile
    if(reached!=NULL) { //se dalla prima stazione posso raggiungere qualcosa, se no return NULL e bona
        struct percorsoTree *distanze = (struct percorsoTree*)malloc(sizeof(struct percorsoTree)); //distanze //key-dist-prec
        struct percorsoTree *daVisitare = (struct percorsoTree*)malloc(sizeof(struct percorsoTree)); //nodi da visitare //key-NULL-NULL
        daVisitare->root=NULL;
        distanze->root=NULL;
        int k = begin->key;
        struct station *n = begin;
        while (k >= end) { //inserisco da visitare tutti i nodi da inizio a fine, assegno a tutti distanza -1;
            struct percorsoNode *dis = (struct percorsoNode *) malloc(sizeof(struct percorsoNode));
            struct percorsoNode *vis = (struct percorsoNode *) malloc(sizeof(struct percorsoNode));
            vis->key = k; //in da visitare inserisco solo le chiavi, non mi sserve il resto
            vis->prec = NULL;
            vis->l=NULL;
            vis->r=NULL;
            if (k == begin->key) {
                dis->dist = 0;
                dis->key = k;
                dis->prec = NULL;
                dis->l=NULL;
                dis->r=NULL;
            } else {
                dis->dist = -1;
                dis->key = k;
                dis->prec = NULL;
                dis->l=NULL;
                dis->r=NULL;
            }
            insertPercorso(vis, daVisitare);
            insertPercorso(dis, distanze);

            if(n->key>end){
                n = precStation(aut,n);
                k=n->key;
            }else{
                break;
            }
        }//ho inserito in un BTS tutte le stazioni impostando distanza da 0 = -1, e in un altro solo le stazioni da visitare;

        struct percorsoNode *currVis = NULL;
        currVis = maxPercorso(daVisitare->root); //prima visita: stazione di partenza(maggiore)
        struct percorsoNode *currDist = searchPercorso(distanze->root,
                                                       currVis->key); //trovo il nodo in dist corrispondente a quello che sto visitando
        struct percorsoNode *visitingDist = currDist; //salvo puntatore a distanza che sto considerando
        currDist = percorsoPrev(currDist); //stazione successiva alla partenza
        while (currDist->key >= reached->key) {
            if (currDist->dist == -1) {
                currDist->dist = 1;
                currDist->prec = visitingDist;
            }
            currDist = percorsoPrev(currDist);
        }
        struct percorsoNode *toDelete = currVis;
        currVis = percorsoPrev(currVis);
        deletePercorso(toDelete, daVisitare); //elimino nodo visitato dall'elenco

        struct station *s = NULL;
        struct percorsoNode *p = percorsoPrev(currVis);
                
        while (currVis!=NULL && p!=NULL) { //fino al penultimo
            s = findStation(aut->root, currVis->key);
            while(s->root==NULL){
                           currVis= percorsoPrev(currVis);
                           s=findStation(aut->root, currVis->key);
                           p = percorsoPrev(currVis);
                           if(currVis==NULL || p==NULL){
                               break;
                           }
                       }
            reached = findStationOrNearestGreater(aut, s, stationMax(s, s->root)->key); //stazione raggiungibile da s
            if(reached==NULL){
                free(reached);
                free(distanze);
                free(daVisitare);
                return NULL;
            }
            currDist = searchPercorso(distanze->root, currVis->key);
            visitingDist = currDist; // salvo prima stazione che sto cagando
            currDist = percorsoPrev(currDist);
            while (currDist!=NULL && currDist->key >= reached->key) {
                if (currDist->dist == -1) {
                    currDist->dist = visitingDist->dist+1;
                    currDist->prec = visitingDist;
                } else {
                    int new_dist = visitingDist->dist + 1;
                    if (new_dist <= currDist->dist) {
                        currDist->prec = visitingDist;
                        currDist->dist = new_dist;
                    }
                }
                currDist = percorsoPrev(currDist);

            }
            toDelete = currVis;
            currVis = percorsoPrev(currVis);
            deletePercorso(toDelete, daVisitare);
            p = percorsoPrev(currVis);
        }
        free(daVisitare);
        struct percorsoNode *stamp = minPercorso(distanze->root); //arrivo
        if(stamp->key!=end || stamp->dist<0)
        {
             return NULL;
        }
        struct percorsoTree *toStamp = (struct percorsoTree*)malloc(sizeof(struct percorsoTree));
        toStamp->root=NULL;
        struct percorsoNode *in = (struct percorsoNode*)malloc(sizeof(struct percorsoNode));
        in->key=stamp->key;
        insertPercorso(in,toStamp);
        while(stamp->prec!=NULL){
            stamp=stamp->prec;
            struct percorsoNode *new = (struct percorsoNode*)malloc(sizeof(struct percorsoNode));
            new->key=stamp->key;
            insertPercorso(new,toStamp);
        }
        free(distanze);
        return toStamp;
    }else{
        
        return NULL;
    }
}

int main(void) {
    struct tree* autostrada = (struct tree*)malloc(sizeof(struct tree));
    autostrada->nil = NULL;
    autostrada->root = NULL;

    FILE *fin, *fout;
    /*
    fin = stdin;
    fout = stdout;
    */

    /**/
     if((fin=fopen("/Users/rossanafilisetti/CLionProjects/ProjectAPI/open_extra_gen.txt", "rt"))==NULL) {
        printf("Errore nell'apertura del file in'");
        exit(1);
    }

    if((fout=fopen("/Users/rossanafilisetti/CLionProjects/ProjectAPI/output.txt", "wt"))==NULL) {
        printf("Errore nell'apertura del file out'");
        exit(1);
    }
    /**/

    char* str = (char*)calloc(20, sizeof(char));
    while(fscanf(fin, "%19s", str) == 1){//read command
        //if(fscanf(fin, "%19s", str)==1){
            if(strcmp(str, "aggiungi-auto") == 0){

                int dist ;
                if(fscanf(fin, "%d", &dist) == 1) { //read station distance (key)
                    int cark;
                    struct station *s = findStation(autostrada->root, dist); //find station

                    if (s != NULL) {
                        if (fscanf(fin, "%d", &cark) == 1) { //read car key
                            struct car *c = (struct car *) malloc(sizeof(struct car)); //malloc car
                            c->key = cark;
                            insertNodeStation(s, c); //insert car in station

                            fprintf(fout,"aggiunta\n");
                        } else {
                            printf("error fscanf int 1\n");
                        }
                    } else {
                        if(fscanf(fin, "%*[^\n]")==1){} // Legge e scarta tutto fino al newline (\n)
                        fgetc(fin); //legge a capo e scarta
                        fprintf(fout,"non aggiunta\n");
                    }
                }else {
                    printf("error fscanf int 2\n");//TODO
                }
            }

            else if(strcmp(str, "aggiungi-stazione") == 0){

                int dist = 0 ;
                if(fscanf(fin, "%d", &dist) == 1) { //read station distance (key)

                    struct station *s = findStation(autostrada->root, dist); //check if already there
                    if (s == NULL) { //if doesn't already exist go on
                        s = (struct station *) malloc(sizeof(struct station));
                        s->root = NULL;
                        s->nil = NULL;
                        s->key = dist;
                        insertNodeTree(autostrada, s); //insert station in tree
                        fprintf(fout, "aggiunta\n");

                        int carsNumb=0;
                        if (fscanf(fin, "%d", &carsNumb) == 1) { //read number of cars;
                            int len = carsNumb;
                            int* cars = (int*)calloc(len, sizeof(int));

                            for (int i = 0; i < len; i++) {

                                if (fscanf(fin, "%d", &(cars[i])) == 1) {  //read cars keys

                                    struct car *c = (struct car *) malloc(sizeof(struct car)); //create car struct
                                    c->key = cars[i];
                                    insertNodeStation(s, c); //insert car in station
                                }
                            }
                            free(cars);
                        }
                    }else{
                        if(fscanf(fin, "%*[^\n]")==1){} // Legge e scarta tutto fino al newline (\n)
                        fgetc(fin); //legge a capo e scarta

                        fprintf(fout, "non aggiunta\n");
                    }
                }

            }
            else if(strcmp(str,"demolisci-stazione") == 0){

                int dist ;
                if(fscanf(fin, "%d", &dist)==1) { //read station key
                    struct station *s = findStation(autostrada->root, dist); //find station with that key
                    if(s!=NULL){
                        struct station *del= deleteNodeTree(autostrada, s); //remove station
                        free(del);
                        fprintf(fout, "demolita\n");

                    }else{
                        fprintf(fout, "non demolita\n");

                    }

                }

            }
            else if(strcmp(str, "rottama-auto") == 0){

                int dist ;
                if(fscanf(fin, "%d", &dist)==1) { //read station key
                    struct station *s = findStation(autostrada->root, dist); //find station with that key
                    if(s!=NULL){
                        int cars;
                        if (fscanf(fin, "%d", &cars) == 1) {  //read cars keys
                            struct car *c = findCar(s->root,cars);
                            if(c!=NULL){
                                deleteNodeStation(s,c);

                                fprintf(fout, "rottamata\n");

                            }else{
                                fprintf(fout, "non rottamata\n");
                            }

                        } else {
                            
                            break;
                        }
                    } else {
                        if(fscanf(fin, "%*[^\n]")==1){}; // Legge e scarta tutto fino al newline (\n)
                        fgetc(fin); //legge a capo e scarta
                        fprintf(fout, "non rottamata\n");
                    }

                }

            }
            else if(strcmp(str, "pianifica-percorso") == 0) {
                int *dist = (int *) calloc(2, sizeof(int));

                if (fscanf(fin, "%d", &(dist[0])) == 1) { //read start station key
                    if (fscanf(fin, "%d", &(dist[1])) == 1) { //read end station key
                        if (dist[0] < dist[1]) {
                            struct tree *p = pianificaPercorsoAndata(autostrada, dist[0], dist[1]);
                            if (p == NULL) {
                                fprintf(fout, "nessun percorso\n");
                                free(p);
                            } else {
                                struct station *first = TreeMin(p, p->root); //first station
                                fprintf(fout, "%d", first->key);
                                struct station *next = nextStation(p, first);
                                while (next != p->nil) {
                                    fprintf(fout, " %d", next->key);
                                    next = nextStation(p, next);
                                }
                                fprintf(fout, "\n");
                                //deallocTree(p,p->root);
                                free(p);
                            }
                        } else if (dist[0] == dist[1]) {
                            fprintf(fout, "%d\n", dist[0]); //stampa stazione unica
                        } else {
                            struct percorsoTree *p = pianificaPercorsoRitorno3(dist[0], dist[1], autostrada);
                            //struct tree *p= choosePercorso(dist[0], dist[1], autostrada);
                            //struct tree *p = pianificaPercorsoRitorno(dist[0], dist[1],autostrada);
                            /*if(p!=NULL){
                                p->nil=NULL;
                            }*/
                            if (p == NULL) {
                                fprintf(fout, "nessun percorso\n");
                                free(p);
                            } else {
                                struct percorsoNode *next = maxPercorso(p->root);
                                //struct station *first = TreeMax(p, p->root); //first station
                                fprintf(fout, "%d", next->key);
                                //next=next->prec;
                                //next= percorsoPrev(next);
                                //struct station *next = precStation(p, first);
                                while(percorsoPrev(next)!=NULL){
                                    next= percorsoPrev(next);
                                    fprintf(fout, " %d", next->key);
                                }/*
                                while (next->key > dist[1]) {
                                    fprintf(fout, " %d", next->key);
                                    next = precStation(p, next);
                                }
                                fprintf(fout, " %d", next->key);
                                */
                                fprintf(fout, "\n");
                                free(p);
                                //deallocTree(p,p->root);
                                //free(p);
                            }
                        }

                    }

                }
                free(dist);
            }else{
                break;
            }
    }
    fclose(fin);
    fclose(fout);
    free(str);
    deallocTree(autostrada,autostrada->root);
    free(autostrada);
    return 0;
}
