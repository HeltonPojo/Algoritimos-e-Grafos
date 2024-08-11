// #include "listaadj/Grafo.h" 
#include "matrizadj/Grafo.h"
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
    cout<<"Floyd Warshall"<< endl;
    grafo->floydWarshall(0, 6);

    //Ex1: criar e imprimir grafo transposto.

    // cout << "Transposto" << endl;

    // Grafo *grafo_trans = grafo->grafoTransposto();

    // grafo_trans->imprime();

    // //Ex2: Criar e imprimir um grafo não orientado.

    // cout << "Nao Direcional" << endl;

    // Grafo *grafoND = grafo->grafoNaoDirecionado();

    // grafoND->imprime();

    // vector<int> listaadj = grafo->listaAdj(2);

    // for(int i = 0; i < listaadj.size(); i++)
    //     cout << listaadj.at(i) << " ";
    // cout << endl;

    // cout<<"Caminho: "<<grafoND->ExisteCaminhoEuler()<<endl;
    // cout<<"Ciclor: "<<grafoND->ExisteCicloEuler()<<endl;
    // cout<<"Direcional: "<<grafoND->Direcional()<<endl;
    // cout<<"Completo: "<<grafoND->Completo()<<endl;
    // cout<<"Autoloop: "<<grafoND->Autoloop()<<endl;
   
    // cout << "Busca Largura" << endl;
    // grafoND->BuscaLargura();

    // cout << "Busca Profundidade" << endl;
    // grafoND->BuscaProfundidade();
    // Grafo *grafoKru = grafoND->Kruscal();
    // Grafo *grafoPrim = grafoND->Prim(0);

    // cout << "Kruscal"<< endl;
    // grafoKru->imprime();
    // cout << "Prim"<< endl;
    // grafoPrim->imprime();

    // Grafo *grafoDj = grafoND->Dijkstra(*grafoND, 0);
    // cout<<"Djikstra"<< endl;
    // grafoDj->imprime();
}



