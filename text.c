#include <stdio.h>
#include <string.h>

void change(int* j){
    *j = 5;
}

int main(){
    int j = 3;
    change(&j);
    printf("%d" ,j);
}