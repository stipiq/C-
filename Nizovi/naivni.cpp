#include <iostream>
#include <string>
using namespace std;

int Search(string A, string Pattern){
        int i,j,m,n;
        n = A.length();
        m = Pattern.length();

        for ( j = 0; j <= n-m; j++)
        {
            for ( i = 0; i < m && Pattern[i] == A[i + j]; i++);
            if (i >= m)
            {
                return j;
            }    
        }
        return -1;

    };


int main(){
    string A = "iiiiiiiiiiivan";
    string Pattern = "ivan";
    int lokacija = Search(A, Pattern);
    if(lokacija != -1){
        cout << "Trazeni uzorak se nalazi na indeksu: " << lokacija << endl;
    }else{
        cout << "Nema ga nigdje!"<< endl;
    }
    return 0;
}