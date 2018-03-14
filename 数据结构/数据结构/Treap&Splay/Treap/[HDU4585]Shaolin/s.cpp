#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#define MAX_N 100100
#define INF 2147483647
using namespace std;

int N, a, g;

struct node {
  node* ch[2];
  int v;
  int r;
  int id;
  int cmp (int x) {
    if (x == v) return -1;
    return x < v ? 0 : 1;
  }
};
node *null, *root;

void init_null() {null = new node();null -> v = INF;null -> r = 0;}

void rot (node* &o, int d) {
  node* k = o -> ch[d];o -> ch[d] = k -> ch[d ^ 1]; k -> ch[d ^ 1] = o;
  o = k;
}

void ins (node* &o, int x, int id_) {
  if (o == null) {
    o = new node();
    o -> v = x;
    o -> id = id_;
    o -> r = rand();
    o -> ch[0] = o -> ch[1] = null;
    //printf("   %d %d\n", id_, x);
  }
  else {
    int d = o -> cmp(x);
    if (d == -1) return;
    ins (o -> ch[d], x, id_);
    if (o -> ch[d] -> r > o -> r) rot(o, d);
  }
}

void init (node* &o) {
  if (o == null) return;
  init(o -> ch[0]); init(o -> ch[1]);
  delete o;//o = NULL;
}

int ans;
node* ans_;

void pre (node* o, int x) {
  if (o == null) return;
  else if (o -> v <= x) {ans = o -> id;ans_ = o;pre(o -> ch[1], x);}
  else if (o -> v > x) pre(o -> ch[0], x);
}

void nxt (node* o, int x) {
  if (o == null) return;
  else if (o -> v >= x) {ans = o -> id;ans_ = o;nxt(o -> ch[0], x);}
  else if (o -> v < x) nxt(o -> ch[1], x);
}

int min_ (int a, int b, node* aa, node* bb) {
  if (aa -> v < bb -> v) return a;
  else if (aa -> v > bb -> v) return b;
  else return a < b ? a : b;
}

int main () {
  init_null();
  root = null;
  while (scanf("%d", &N) == 1 && N != 0) {
    init(root);
    root = null;
    scanf("%d %d", &a, &g);
    printf("%d 1\n", a);
    ins(root, g, a);
    
    for (int i = 3;i <= N + 1; ++i) {
      scanf("%d%d", &a, &g);
      //printf("dsa%d %d\n", a, g);
      ans_ = null;
      pre(root, g);
      int pre_ = ans;
      node* _pre = ans_;
      nxt(root, g);
      int nxt_ = ans;
      node* _nxt = ans_;
      //printf("pn%d %d  %d %d\n", pre_, nxt_, _pre -> v, _nxt -> v);
      if (abs(_pre -> v - g) > abs(_nxt -> v - g)) printf("%d %d\n", a, nxt_);
      else if (abs(_pre -> v - g) < abs(_nxt -> v - g)) printf("%d %d\n", a, pre_);
      else printf("%d %d\n", a, min_(pre_, nxt_, _pre, _nxt));
      ins (root, g, a);
    }
  }
  return 0;
}
