#include "listaadj/Grafo.h" 
#include <fstream>
using namespace std;

int main (int argc, char **argv) 
{
    ifstream in ("input.txt");
    Grafo *grafo = new Grafo (in);
    grafo->imprime ();  

    //Ex1: criar e imprimir grafo transposto.

    cout << "Transposta" << endl;

    Grafo *grafo_trans = grafo->grafoTransposto();

    grafo_trans->imprime();

    //Ex2: Criar e imprimir um grafo não orientado.

    cout << "Nao Direcional" << endl;

    Grafo *grafoND = grafo->grafoNaoDirecionado();

    grafoND->imprime();

    vector<int> listaadj = grafo->listaAdj(2);

    for(int i = 0; i < listaadj.size(); i++)
        cout << listaadj.at(i) << " ";
    cout << endl;

    cout<<"Caminho: "<<grafoND->ExisteCaminhoEuler()<<endl;
    cout<<"Ciclor: "<<grafoND->ExisteCicloEuler()<<endl;
    cout<<"Direcional: "<<grafoND->Direcional()<<endl;
    cout<<"Completo: "<<grafoND->Completo()<<endl;
    cout<<"Autoloop: "<<grafoND->Autoloop()<<endl;

    grafo->imprime();  
    grafoND->buscaLargura();

    Grafo *grafoKru = grafo->Kruscal();
    Grafo *grafoPrim = grafo->Prim(0);

    grafoKru->imprime();
    grafoPrim->imprime();
}



