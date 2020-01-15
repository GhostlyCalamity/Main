#include "function.h"
int *X = new int[1600];
int *Y = new int[1600];
int x=0,y=0;
int realtimefunction(int t){
    for(int i=0;i<1500;i++){
     x+=1;
     y=x;
     Y[i]=y;
    }
return Y[t];
}
