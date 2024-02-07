#include<iostream>
using namespace std;

int main(){
int x[] = {55,43,-12};
int *p = x;
int *o = &x[2];

cout << *p << " "<< *(p+1) << " "<<*(p+2) <<"\n";
cout << o << "\n";
cout << o-p ;
return 0;
}
