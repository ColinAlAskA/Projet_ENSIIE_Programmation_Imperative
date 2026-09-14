#include <stdlib.h>
#include <stdio.h>
#include "opacite.h"

list_op cons_op(list_op l, opacite e) {
    list_op ll = malloc(sizeof(struct maillon_op));
    ll -> val = e;
    ll -> next = l;
    return ll;
}

void add_op(list_op *l, opacite e) {
    *l = cons_op(*l, e);
}

void print_list_op(list_op l) {
    while (l!=NULL) {
        printf("-> [%d] ",l->val);
        l = l->next;
    }
    printf("-> []\n");
}

opacite moyenne_op(list_op l) {
    //printf("liste opacite : ");
    //print_list_op(l);
    opacite res = 0;
    int nb = 0;
    while (l!=NULL){
        res += l->val;
        nb ++;
        l=l->next;
    }
    if (nb==0) res=255;
    else res = res/nb;
    return res;
}