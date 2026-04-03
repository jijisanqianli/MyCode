#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "tsmatrix.h"

int M_compare_N(const Triple* M, const Triple* N) {
    if (M->i!=N->i) return M->i-N->i;
    return M->j-N->j;
}

bool add_matrix(const TSMatrix *pM, const TSMatrix *pN, TSMatrix *pQ){
    if (!pM || !pN || !pQ) {
        return false;
    }
    if (pM->m!=pN->m || pM->n!=pN->n) {
        return false;
    }
    pQ->m=pM->m;pQ->n=pM->n;
    int Qcount=0,Mcount=0,Ncount=0;
    while (Mcount<=pM->len-1&&Ncount<=pN->len-1) {
        int compare_result=M_compare_N(&pM->data[Mcount],&pN->data[Ncount]);
        if (compare_result<0) {
            pQ->data[Qcount]=pM->data[Mcount];
            Qcount++;Mcount++;
        }else if (compare_result>0) {
            pQ->data[Qcount]=pN->data[Ncount];
            Qcount++;Ncount++;
        }else{
            int sum=pN->data[Ncount].e+pM->data[Mcount].e;
            if (sum!=0) {
                pQ->data[Qcount]=pN->data[Ncount];
                pQ->data[Qcount].e=sum;
                Qcount++;
            }
            Mcount++;Ncount++;
        }
    }
    while (Mcount<=pM->len-1) {
        pQ->data[Qcount]=pM->data[Mcount];
        Qcount++;Mcount++;
    }
    while (Ncount<=pN->len-1) {
        pQ->data[Qcount]=pN->data[Ncount];
        Qcount++;Ncount++;
    }
    pQ->len=Qcount;
    return true;
}