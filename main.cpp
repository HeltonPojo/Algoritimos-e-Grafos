#include "listaadj/Grafo.h" 
#include <fstream>
#include <vector>
#include <bits/stdc++.h>
using namespace std;

int main (int argc, char **argv) 
{
    ifstream in ("input.txt");
    Grafo *grafo = new Grafo (in);
    cout << "Grafo" << endl;
    grafo->imprime ();  
   
    cout << "\nExecutando algoritmo de Louvain..." << endl;
    grafo->louvain();
}



