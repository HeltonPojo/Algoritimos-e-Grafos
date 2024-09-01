#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <array>
#include <cstring>
#include <float.h>
using namespace std;
	class Grafo {
	public:
		class Aresta {
	  private:
	    int v1, v2, peso; 
	  public: 
	    Aresta (int v1, int v2, int peso) {
	      this->v1 = v1; this->v2 = v2; this->peso = peso;
	    }
      
	    int _peso () { return this->peso; }
	    int _v1 () { return this->v1; }
	    int _v2 () { return this->v2; }
	    ~Aresta () {}
	  };
	private:
	  int **mat; // @{\it pesos do tipo inteiro}@
    int numVertices;
    int *pos; // @{\it posi\c{c}\~ao atual ao se percorrer os adjs de um v\'ertice v}@
    vector<vector<int> > fluxo;
    vector<vector<int> > capacidade;

  public:
    Grafo (int numVertices);
    Grafo(istream &in);
    Grafo(int numVertices, int numArestas);
    void insereAresta(int v1, int v2, int peso);
    bool existeAresta(int v1, int v2) const;
    bool listaAdjVazia(int v) const;
    Aresta *lerAresta();
    Aresta *primeiroListaAdj(int v);
    Aresta *proxAdj(int v);
    Aresta *retiraAresta(int v1, int v2);
    void imprime() const;
    int _numVertices() const;
    Grafo *grafoTransposto();
    Grafo *grafoNaoDirecionado();
    bool ExisteCaminhoEuler();
    bool ExisteCicloEuler();
    vector<int> listaAdj(int v1);
    void floydWarshall(int origem, int destino);
    bool bfs(int s, int t, vector<int>& pai);
    int fordFulkerson(int origem, int destino);
    void adicionarAresta(int u, int v, int capacidade);
    ~Grafo ();	  
	};

  Grafo::Grafo( istream &in )
  {
   int v1, v2, peso;
   in >> this->numVertices;
   this->mat = new int*[numVertices];
    for (int i = 0; i < numVertices; i++) 
      this->mat[i] = new int[numVertices];
    this->pos = new int[numVertices]; 
    
    for (int i = 0; i < this->numVertices; i++) {
      for (int j = 0; j < this->numVertices; j++) this->mat[i][j] = 0;
      this->pos[i] = -1; 
    }
    capacidade.resize(numVertices, vector<int>(numVertices, 0));
    fluxo.resize(numVertices, vector<int>(numVertices, 0));

    while (in>>v1>>v2>>peso) {
      Grafo::Aresta *a = new Grafo::Aresta (v1, v2, peso);
      this->insereAresta (a->_v1 (), a->_v2 (), a->_peso ());
      this->adicionarAresta(a->_v1 (), a->_v2 (), a->_peso ());
      delete a;
    }
  }

  Grafo::Grafo (int numVertices) {
    this->mat = new int*[numVertices];
    for (int i = 0; i < numVertices; i++) 
      this->mat[i] = new int[numVertices];
    this->pos = new int[numVertices]; 
    this->numVertices = numVertices; 
    for (int i = 0; i < this->numVertices; i++) {
      for (int j = 0; j < this->numVertices; j++) this->mat[i][j] = 0;
      this->pos[i] = -1; 
    }
    capacidade.resize(numVertices, vector<int>(numVertices, 0));
    fluxo.resize(numVertices, vector<int>(numVertices, 0));
  }
  
  Grafo::Grafo (int numVertices, int numArestas) {
    this->mat = new int*[numVertices];
    for (int i = 0; i < numVertices; i++) 
      this->mat[i] = new int[numVertices];
    this->pos = new int[numVertices]; 
    this->numVertices = numVertices; 
    for (int i = 0; i < this->numVertices; i++) {
      for (int j = 0; j < this->numVertices; j++) this->mat[i][j] = 0;
      this->pos[i] = -1; 
    }
  }	  

  void Grafo::insereAresta (int v1, int v2, int peso) {
    this->mat[v1][v2] = peso; 
  }
  bool Grafo::existeAresta (int v1, int v2) const {
    return (this->mat[v1][v2] > 0);
  }
  bool Grafo::listaAdjVazia (int v) const {
    for (int i = 0; i < this->numVertices; i++)
      if (this->mat[v][i] > 0) return false;
    return true;
  }

  void Grafo::adicionarAresta(int u, int v, int capacidade) {
      this->capacidade[u][v] = capacidade;
  }

  bool Grafo::bfs(int s, int t, vector<int>& pai) {
      vector<bool> visitado(numVertices, false);
      queue<int> fila;
      
      fila.push(s);
      visitado[s] = true;
      pai[s] = -1;
      
      while (!fila.empty()) {
          int u = fila.front();
          fila.pop();
          
          for (int v = 0; v < numVertices; v++) {
              if (!visitado[v] && (capacidade[u][v] - fluxo[u][v]) > 0) {
                  fila.push(v);
                  pai[v] = u;
                  visitado[v] = true;
                  if (v == t) {
                      return true;
                  }
              }
          }
      }
      
      return false;
  }

  int Grafo::fordFulkerson(int origem, int destino) {
      int fluxoMaximo = 0;
      vector<int> pai(numVertices);
      
      while (bfs(origem, destino, pai)) {
          int caminhoFluxo = INT_MAX;
          
          for (int v = destino; v != origem; v = pai[v]) {
              int u = pai[v];
              caminhoFluxo = min(caminhoFluxo, capacidade[u][v] - fluxo[u][v]);
          }
          
          for (int v = destino; v != origem; v = pai[v]) {
              int u = pai[v];
              fluxo[u][v] += caminhoFluxo;
              fluxo[v][u] -= caminhoFluxo;
          }
          
          fluxoMaximo += caminhoFluxo;
      }
      
      return fluxoMaximo;
  }

  Grafo::Aresta *Grafo::lerAresta()
  {
    cout << "Aresta:" << endl;
    cout << "  V1:"; int v1 = 0;
    cin >> v1;
    cout << "  V2:"; int v2 = 0;
    cin >> v2;
    cout << "  Peso:"; int peso = 0;
    cin >> peso;
    return new Aresta (v1, v2, peso);
  }

  Grafo::Aresta *Grafo::primeiroListaAdj (int v) {
    // @{\it Retorna a primeira aresta que o v\'ertice v participa ou}@ 
    // @{\it {\bf NULL} se a lista de adjac\^encia de v for vazia}@
    this->pos[v] = -1; return this->proxAdj (v);
  }
  
  Grafo::Aresta *Grafo::proxAdj (int v) {
    // @{\it Retorna a pr\'oxima aresta que o v\'ertice v participa ou}@ 
    // @{\it {\bf NULL} se a lista de adjac\^encia de v estiver no fim}@ 
    this->pos[v] ++;
    while ((this->pos[v] < this->numVertices) && 
           (this->mat[v][this->pos[v]] == 0)) this->pos[v]++;
    if (this->pos[v] == this->numVertices) return NULL;
    else return new Aresta (v, this->pos[v], this->mat[v][this->pos[v]]);
  }
  
  Grafo::Aresta *Grafo::retiraAresta (int v1, int v2) {
    if (this->mat[v1][v2] == 0) return NULL; // @{\it Aresta n\~ao existe}@
    else {
      Aresta *aresta = new Aresta (v1, v2, this->mat[v1][v2]);
      this->mat[v1][v2] = 0; return aresta;
    }
  }
  
  void Grafo::imprime () const {
    cout << "   ";
    for (int i = 0; i < this->numVertices; i++) 
      cout << i << "   "; 
    cout << endl;
    for (int i = 0; i < this->numVertices; i++) { 
      cout << i <<  "  ";
      for (int j = 0; j < this->numVertices; j++)
        cout << this->mat[i][j] << "   ";
      cout << endl;
    }
  }
  
  int Grafo::_numVertices () const { return this->numVertices; }
  
  Grafo *Grafo::grafoTransposto () {
    Grafo *grafoT = new Grafo (this->numVertices); 
    for (int v = 0; v < this->numVertices; v++)
      if (!this->listaAdjVazia (v)) {
        Aresta *adj = this->primeiroListaAdj (v);
        while (adj != NULL) {
          grafoT->insereAresta (adj->_v2 (), adj->_v1 (), adj->_peso ());
          delete adj;
          adj = this->proxAdj (v);
        }
      }
    return grafoT;
  }

  Grafo *Grafo::grafoNaoDirecionado () {
    Grafo *grafoND = new Grafo (this->numVertices); 
    cout << "   ";
    for (int i = 0; i < this->numVertices; i++) { 
      for (int j = 0; j < this->numVertices; j++)
        if(this->existeAresta(i, j)){
          grafoND->insereAresta(i, j, this->mat[i][j]);
          grafoND->insereAresta(j, i, this->mat[i][j]);
        }
    }
    return grafoND;
  }

  
  vector<int> Grafo::listaAdj(int v){
    vector<int> adj;
    
    for(int i = 0; i < this->numVertices; i++)
      if(this->existeAresta(v, i))
        adj.push_back(i);

    return adj;
  }

  bool Grafo::ExisteCaminhoEuler(){
    int caminhos = 0;
    for(int i = 0; i < this->numVertices; i++)
      if(this->listaAdj(i).size()%2!=0) caminhos++;

    return caminhos=2;
  }

  bool Grafo::ExisteCicloEuler(){
    int caminhos = 0;
    for(int i = 0; i < this->numVertices; i++)
      if(this->listaAdj(i).size()%2!=0) caminhos++;

    return caminhos=0;
  }
  Grafo::~Grafo()
  {
    for (int i = 0; i < numVertices; i++) 
      delete [] this->mat[i];
    delete [] this->mat;
    delete [] this->pos;
  }

  void Grafo::floydWarshall(int origem, int destino){
    cout << "Teste" << endl;
    int** d = new int*[this->numVertices];
    int** antecessor = new int*[this->numVertices];
    for (int i = 0; i < this->numVertices; i++) {
        d[i] = new int[this->numVertices];
        antecessor[i] = new int[this->numVertices];
    }

    for(int i = 0; i < this->numVertices; i++){
      for (int j = 0; j < this->numVertices; j++) {
        if (this->mat[i][j] != 0) {
          d[i][j] = this->mat[i][j];
          antecessor[i][j] = i;
        } else {
          d[i][j] = INT16_MAX;
          antecessor[i][j] = -1;
        }
      }
    }
    for (int k = 0; k < this->numVertices; k++){
      for (int i = 0; i < this->numVertices; i++){
        for (int j = 0; j < this->numVertices; j++){
         if(d[i][k] + d[k][j] < d[i][j]) {
            d[i][j] = d[k][j] + d[i][k];
            antecessor[i][j] = antecessor[k][j];
         }
        }
      }
    }
    
    if (d[origem][destino] == INT_MAX) {
        cout << "Não existe caminho entre " << origem << " e " << destino << endl;
    } else {
        cout << origem << " -> ";
        int atual = destino;
        while (atual != origem) {
            cout << antecessor[origem][atual] << " -> ";
            atual = antecessor[origem][atual];
        }
        cout << destino << endl;
    }

    for (int i = 0; i < this->numVertices; i++) {
        delete[] d[i];
        delete[] antecessor[i];
    }
    delete[] d;
    delete[] antecessor;
  }




		
