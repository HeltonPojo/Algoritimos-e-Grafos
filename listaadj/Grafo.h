#include "Lista.h"
#include "FPHeapMinIndireto.h"
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <array>
#include <cstring>
#include <float.h>
using namespace std;

class Grafo
{
public:
  class Aresta
  {
  private:
    int v1, v2, peso;

  public:
    Aresta(int v1, int v2, int peso)
    {
      this->v1 = v1;
      this->v2 = v2;
      this->peso = peso;
    }
    int _peso() { return this->peso; }
    int _v1() { return this->v1; }
    int _v2() { return this->v2; }
    ~Aresta() {}
  };

private:
  class Celula
  {
    friend class Grafo;
    friend ostream &operator<<(ostream &out, const Celula &celula)
    {
      out << "vertice:" << celula.vertice << endl;
      out << "peso:" << celula.peso << endl;
      return out;
    }

  private:
    int vertice, peso;

  public:
    Celula(int v, int p)
    {
      this->vertice = v;
      this->peso = p;
    }
    Celula(const Celula &cel) { *this = cel; }
    bool operator==(const Celula &celula) const
    {
      return this->vertice == celula.vertice;
    }
    bool operator!=(const Celula &celula) const
    {
      return this->vertice != celula.vertice;
    }
    const Celula &operator=(const Celula &cel)
    {
      this->vertice = cel.vertice;
      this->peso = cel.peso;
      return *this; // @{\it permite atribui\c{c}\~oes encadeadas}@
    }
    ~Celula() {}
  };
  Lista<Celula> *adj;
  int numVertices;

public:
  Grafo(istream &in);
  Grafo(int numVertices);
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
  Grafo *Kruscal();
  Grafo *Prim(int root);
  int EncontraConjunt(int x, int *v);
  void UnirConjunt(int x, int y, int *v);
  void VisitaDfs(int u, vector<int> &cor, vector<int> &ant);
  void VisitaDfs(int u, vector<int> &cor, vector<int> &ant, list<int> &L);
  void ImprimeCaminho(int u, int v, vector<int> &ant);
  void BuscaProfundidade();
  void VisitarBfs(int u, vector<int> &cor, vector<int> &dist, vector<int> &ant);
  bool Direcional();
  bool Completo();
  bool Autoloop();
  ~Grafo();
};

Grafo::Grafo(istream &in)
{
  int v1, v2, peso, numVertices;
  in >> numVertices;

  this->adj = new Lista<Celula>[numVertices];
  this->numVertices = numVertices;

  while (in >> v1 >> v2 >> peso)
  {
    Grafo::Aresta *a = new Grafo::Aresta(v1, v2, peso);
    this->insereAresta(a->_v1(), a->_v2(), a->_peso());
    delete a;
  }
}

Grafo::Grafo(int numVertices)
{
  this->adj = new Lista<Celula>[numVertices];
  this->numVertices = numVertices;
}
Grafo::Grafo(int numVertices, int numArestas)
{
  this->adj = new Lista<Celula>[numVertices];
  this->numVertices = numVertices;
}

Grafo::Aresta *lerAresta()
{
  cout << "Aresta:" << endl;
  cout << "  V1:";
  int v1 = 0;
  cin >> v1;
  cout << "  V2:";
  int v2 = 0;
  cin >> v2;
  cout << "  Peso:";
  int peso = 0;
  cin >> peso;
  return new Grafo::Aresta(v1, v2, peso);
}

void Grafo::insereAresta(int v1, int v2, int peso)
{
  if (!this->existeAresta(v1, v2))
  {
    Celula item(v2, peso);
    this->adj[v1].insere(item);
  }
}
bool Grafo::existeAresta(int v1, int v2) const
{
  Celula item(v2, 0);
  return (this->adj[v1].pesquisa(item) != NULL);
}
bool Grafo::listaAdjVazia(int v) const
{
  return this->adj[v].vazia();
}
Grafo::Aresta *Grafo::primeiroListaAdj(int v)
{
  // @{\it Retorna a primeira aresta que o v\'ertice v participa ou}@
  // @{\it {\bf NULL} se a lista de adjac\^encia de v for vazia}@
  Celula *item = this->adj[v]._primeiro();
  return item != NULL ? new Aresta(v, item->vertice, item->peso) : NULL;
}
Grafo::Aresta *Grafo::proxAdj(int v)
{
  // @{\it Retorna a pr\'oxima aresta que o v\'ertice v participa ou}@
  // @{\it {\bf NULL} se a lista de adjac\^encia de v estiver no fim}@
  Celula *item = this->adj[v].proximo();
  return item != NULL ? new Aresta(v, item->vertice, item->peso) : NULL;
}
Grafo::Aresta *Grafo::retiraAresta(int v1, int v2)
{
  Celula chave(v2, 0);
  Celula *item = this->adj[v1].retira(chave);
  Aresta *aresta = item != NULL ? new Aresta(v1, v2, item->peso) : NULL;
  delete item;
  return aresta;
}
void Grafo::imprime() const
{
  for (int i = 0; i < this->numVertices; i++)
  {
    cout << i << ":";
    Celula *item = this->adj[i]._primeiro();
    while (item != NULL)
    {
      cout << "  " << item->vertice << " (" << item->peso << ")";
      item = this->adj[i].proximo();
    }
    cout << endl;
  }
}
int Grafo::_numVertices() const { return this->numVertices; }

Grafo *Grafo::grafoTransposto()
{
  Grafo *grafoT = new Grafo(this->numVertices);
  for (int v = 0; v < this->numVertices; v++)
    if (!this->listaAdjVazia(v))
    {
      Aresta *adj = this->primeiroListaAdj(v);
      while (adj != NULL)
      {
        grafoT->insereAresta(adj->_v2(), adj->_v1(), adj->_peso());
        delete adj;
        adj = this->proxAdj(v);
      }
    }
  return grafoT;
}

Grafo *Grafo::grafoNaoDirecionado()
{
  Grafo *grafoND = new Grafo(this->numVertices);
  for (int i = 0; i < this->numVertices; i++)
  {
    Celula *item = this->adj[i]._primeiro();
    while (item != NULL)
    {
      grafoND->insereAresta(i, item->vertice, item->peso);
      grafoND->insereAresta(item->vertice, i, item->peso);
      item = this->adj[i].proximo();
    }
  }
  return grafoND;
}

vector<int> Grafo::listaAdj(int v)
{
  vector<int> adj;
  Celula *item = this->adj[v]._primeiro();
  while (item != NULL)
  {
    adj.push_back(item->vertice);
    item = this->adj[v].proximo();
  }
  return adj;
}

bool Grafo::ExisteCaminhoEuler()
{
  int caminhos = 0;
  for (int i = 0; i < this->numVertices; i++)
    if (this->listaAdj(i).size() % 2 != 0)
      caminhos++;

  return (caminhos == 2);
}

bool Grafo::ExisteCicloEuler()
{
  int caminhos = 0;
  for (int i = 0; i < this->numVertices; i++)
    if (this->listaAdj(i).size() % 2 != 0)
      caminhos++;

  return caminhos == 0;
}

bool Grafo::Direcional()
{
  for (int i = 0; i < this->numVertices; i++)
  {
    Celula *item = this->adj[i]._primeiro();
    while (item != NULL)
    {
      if (!this->existeAresta(item->vertice, i))
        return true;
      item = this->adj[i].proximo();
    }
  }
  return false;
}

int EncontraConjunt(int x, int *v)
{
  if (v[x] == -1)
  {
    return x;
  }
  return EncontraConjunt(v[x], v);
}

void UnirConjunt(int x, int y, int *v)
{
  int conjuntoX = EncontraConjunt(x, v);
  int conjuntoY = EncontraConjunt(y, v);
  v[conjuntoX] = conjuntoY;
}

Grafo *Grafo::Kruscal()
{
  Grafo *grafo = new Grafo(this->numVertices);
  int *v = new int[this->numVertices];
  for (int i = 0; i < this->numVertices; i++)
  {
    v[i] = -1;
  }
  vector<Aresta> arestas;
  for (int i = 0; i < this->numVertices; i++)
  {
    Celula *item = this->adj[i]._primeiro();
    while (item != NULL)
    {
      Aresta *nova = new Aresta(i, item->vertice, item->peso);
      arestas.push_back(*nova);
      item = this->adj[i].proximo();
    }
  }
  sort(arestas.begin(), arestas.end());
  for (int i = 0; i < arestas.size(); i++)
  {
    if (EncontraConjunt(arestas[i]._v1(), v) != EncontraConjunt(arestas[i]._v2(), v))
    {
      grafo->insereAresta(arestas[i]._v1(), arestas[i]._v2(), arestas[i]._peso());
      if (Direcional())
        grafo->insereAresta(arestas[i]._v2(), arestas[i]._v1(), arestas[i]._peso());
    }
  }
}

Grafo *Grafo::Prim(int root)
{
  double *peso = new double[this->numVertices];
  int antecessor[this->numVertices];
  int itensHeap[this->numVertices];
  int *vs = new int[this->numVertices + 1];
  for (int i = 0; i < this->numVertices; i++)
  {
    Celula *item = this->adj[i]._primeiro();
    peso[i] = INT32_MAX;
    antecessor[i] = -1;
    itensHeap[i] = 1;
    vs[i + 1] = item->vertice;
    item = this->adj[i].proximo();
  }

  peso[root] = 0;
  FPHeapMinIndireto *Q = new FPHeapMinIndireto(peso, vs, this->numVertices);
  while (Q->vazio())
  {
    int vertice = Q->retiraMin();
    itensHeap[vertice] = false;
    Celula *item = this->adj[vertice]._primeiro();
    while (item != NULL)
    {
      if (itensHeap[item->vertice] && item->peso < peso[item->vertice])
      {
        antecessor[item->vertice] = vertice;
        Q->diminuiChave(item->vertice, item->peso);
      }
      item = this->adj[vertice].proximo();
    }
  }

  Grafo *grafo = new Grafo(this->numVertices);
  for (int i = 0; i < this->numVertices; i++)
  {
    grafo->insereAresta(i, antecessor[i], peso[i]);
    if (Direcional())
      grafo->insereAresta(antecessor[i], i, peso[i]);
  }
  return grafo;
}

bool Grafo::Completo()
{
  for (int i = 0; i < this->numVertices; i++)
  {
    if (this->listaAdj(i).size() != this->numVertices - 1)
      return false;
  }
  return true;
}

bool Grafo::Autoloop()
{
  for (int i = 0; i < this->numVertices; i++)
    if (this->existeAresta(i, i))
      return true;
  return false;
}

void Grafo::VisitaDfs(int u, vector<int> &cor, vector<int> &ant)
{
  int branco = 1;
  int cinza = 2;
  int preto = 3;
  bool ciclo = false;

  vector<int> d(this->numVertices);
  vector<int> t(this->numVertices);

  cor[u] = cinza;

  Celula *item = this->adj[u]._primeiro();
  d[item->vertice]++;
  while (item != NULL)
  {
    if (cor[item->vertice] == cinza)
      ciclo = true;
    if (cor[item->vertice] == branco)
    {
      ant[item->vertice] = u;
      VisitaDfs(item->vertice, cor, ant);
    }
    item = this->adj[u].proximo();
  }
  cor[u] = preto;
  t[item->vertice]++;
}

void Grafo::VisitaDfs(int u, vector<int> &cor, vector<int> &ant, list<int> &L)
{

  int branco = 1;
  int cinza = 2;
  int preto = 3;
  bool ciclo = false;

  vector<int> d(this->numVertices);
  vector<int> t(this->numVertices);

  cor[u] = cinza;

  Celula *item = this->adj[u]._primeiro();
  d[item->vertice]++;
  while (item != NULL)
  {
    if (cor[item->vertice] == cinza)
      ciclo = true;
    if (cor[item->vertice] == branco)
    {
      ant[item->vertice] = u;
      VisitaDfs(item->vertice, cor, ant);
    }

    item = this->adj[u].proximo();
  }
  cor[u] = preto;
  t[item->vertice]++;
  L.push_front(u);
}

void Grafo::buscaLargura()
{

  int branco = 1;
  int cinza = 2;
  int preto = 3;

  vector<int> cor(this->numVertices, branco);
  vector<int> dist(this->numVertices, -1);
  vector<int> ant(this->numVertices, -1);

  for (int i = 0; i < this->numVertices; i++)
  {
    if (cor[i] == branco)
    {

      V(i, cor, dist, ant);
    }
  }

  for (int i = 0; i < this->numVertices; i++)
  {
    cout << dist[i] << " ";
  }
  cout << endl;

  for (int i = 0; i < this->numVertices; i++)
  {
    cout << ant[i] << " ";
  }
  cout << endl;
}

void Grafo::ImprimeCaminho(int u, int v, vector<int> &ant)
{
  if (u == v)
    cout << v;

  if (ant[v] == -1)
    cout << "Não existe caminho de u para v";
  else
  {
    ImprimeCaminho(u, ant[v], ant);
    cout << v;
  }
}

void Grafo::V(int u, vector<int> &cor, vector<int> &dist, vector<int> &ant)
{

  int branco = 1;
  int cinza = 2;
  int preto = 3;
  queue<int> fila;

  dist[u] = 0;
  cor[u] = cinza;

  fila.push(u);

  while (!fila.empty())
  {
    u = fila.front();
    fila.pop();
    vector<int> adj = ListarAdj(u);
    for (int i = 0; i < adj.size(); i++)
    {
      if (cor[adj[i]] == branco)
      {
        cor[adj[i]] = cinza;
        dist[adj[i]] = dist[u] + 1;
        ant[adj[i]] = u;
        fila.push(adj[i]);
      }
    }
    cor[u] = preto;
  }
}

void Grafo::BuscaProfundidade()
{

  int branco = 1;
  int cinza = 2;
  int preto = 3;

  vector<int> cor(this->numVertices, branco);
  vector<int> ant(this->numVertices, -1);
  list<int> L;

  int k = 0;

  for (int i = 0; i < this->numVertices; i++)
  {
    if (cor[i] == branco)
    {
      k++;
      VisitaDfs(i, cor, ant, L);
    }
  }
}

Grafo::~Grafo()
{
  delete[] this->adj;
}
