#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
LALR parser.
LALR is the same as CLR except two similar states differing only in lookaheads in CLR are merged in LALR
*/
// @ is null symbol
// structure for representing grammar rules (eg. S -> A)
struct Rules {
  char var;
  char der[10];
};
// structure for representing LALR items
struct Item {
  int dotposition;
  struct Rules r;
  int lookahead[255];
  int f;
};
// structure for representing states
struct State {
  int len;
  struct Item itm[20];
  int transition[255];
};
// Structure for storing a list of states
struct list {
  struct State data;
  struct list *next;
};
int variables[26] = {0};
int terminals[255] = {0};
int nullable[26] = {0};
char first[26][255] = {{0}}; // Array to store first of each variable
char follow[26][255] = {{0}}; // Array to store follow of each variable
char *var, *term;
char start;
int n, n_var = 0, n_term = 0;
struct Rules *a;
struct list *head, *tail;

// Given a character(variable or terminal) check if it's nullable or not
int is_nullable(char *s) {
  char *p;
  p = s;
  while (*p != '\0') {
    if (*p < 'A' || *p > 'Z' || !nullable[*p - 'A'])
      return 0;
    p++;
  }
  return 1;
}

// Check if an item is in a given state and return its position
int is_item_in(struct State *l, struct Rules r, int dot) {
  for (int i = 0; i < l->len; i++) {
    if ((l->itm[i].dotposition == dot) && (l->itm[i].r.var == r.var) && (strcmp(l->itm[i].r.der, r.der) == 0))
      return i;
  }
  return -1;
}

int is_item_in_advanced(struct State *l, struct Rules r, int dot, int *bit) {
  int f = 0;
  for (int i = 0; i < l->len; i++) {
    f = 1;
    for (int j = 0; j < 255; j++) {
      if (bit[j] != l->itm[i].lookahead[j]) {
        f = 0;
        break;
      }
    }
    if (f && (l->itm[i].dotposition == dot) && (l->itm[i].r.var == r.var) && (strcmp(l->itm[i].r.der, r.der) == 0))
      return 1;
  }
  return 0;
}

// Fill the look aheads in a given item
void fill_lookaheads(int *bit, struct Item *l) {
  int length = strlen(l->r.der + l->dotposition + 1);
  char sto;
  int f = 0;
  for (int i = l->dotposition + 1; i < l->dotposition + length + 1; i++) {
    if (l->r.der[i] == '\0')
      continue;
    if (l->r.der[i] < 'A' || l->r.der[i] > 'Z') {
      bit[l->r.der[i]] = 1;
      return;
    }
    for (int j = 0; j < 255; j++) {
      if (first[l->r.der[i] - 'A'][j]) {
        bit[j] = 1;
      }
    }
    sto = l->r.der[i];
    l->r.der[i] = '\0';
    if (!is_nullable(l->r.der + l->dotposition + 1)) {
      l->r.der[i] = sto;
    } else {
      l->r.der[i] = sto;
      f = 1;
      break;
    }
  }
  if (!f) {
    for (int i = 0; i < 255; i++) {
      if (l->lookahead[i])
        bit[i] = 1;
    }
  }
}

// Fill the dot position, look ahead and item of a given state
void build_state(struct State *l) {
  int s;
  for (int i = 0; i < l->len; i++) {
    if (l->itm[i].r.der[l->itm[i].dotposition] >= 'A' && l->itm[i].r.der[l->itm[i].dotposition] <= 'Z') {
      for (int j = 0; j < n; j++) {
        if ((a[j].var == l->itm[i].r.der[l->itm[i].dotposition])) {
          if ((s = is_item_in(l, a[j], 0)) == -1) {
            l->itm[l->len].dotposition = 0;
            l->itm[l->len].r = a[j];
            l->itm[l->len].f = 0;
            memset(l->itm[l->len].lookahead, 0, 255);
            fill_lookaheads(l->itm[l->len].lookahead, &l->itm[i]);
            l->len++;
          } else {
            fill_lookaheads(l->itm[s].lookahead, &l->itm[i]);
          }
        }
      }
    }
  }
}

// Print a given list of states
void print_state(struct list *q) {
  for (int i = 0; i < q->data.len; i++) {
    printf("%c :: ", q->data.itm[i].r.var);
    if (q->data.itm[i].r.der[0] == '@')
      q->data.itm[i].r.der[0] = '\0';
    char sto = q->data.itm[i].r.der[q->data.itm[i].dotposition];
    q->data.itm[i].r.der[q->data.itm[i].dotposition] = '\0';
    printf("%s.", q->data.itm[i].r.der);
    q->data.itm[i].r.der[q->data.itm[i].dotposition] = sto;
    printf("%s", q->data.itm[i].r.der + q->data.itm[i].dotposition);
    printf(" { ");
    for (int j = 0; j < 255; j++) {
      if (q->data.itm[i].lookahead[j])
        printf("%c,", (char)j);
    }
    printf(" }\n");
  }
}

// Check if a state is already in the list of states
int state_already_included(struct list *l, struct State *s) {
  struct list *q;
  q = l;
  int f, rtn = -1;
  int ind = 0;
  while (q != NULL) {
    f = 0;
    if (q->data.len != s->len) {
      q = q->next;
      ind++;
      continue;
    }
    for (int i = 0; i < s->len; i++) {
      if (is_item_in(&q->data, s->itm[i].r, s->itm[i].dotposition) == -1) {
        f = 1;
        break;
      }
    }
    if (!f) {
      return ind;
    }
    ind++;
    q = q->next;
  }
  return -1;
}

int num = 0;

// Add look aheads and also merge two states if they are similar except w.r.t lookaheads
void add_lookaheads(struct list *l, int s, struct State *t) {
  struct list *q;
  q = l;
  while (s--)
    q = q->next;
  for (int i = 0; i < t->len; i++) {
    for (int j = 0; j < q->data.len; j++) {
      if ((t->itm[i].r.var == q->data.itm[j].r.var) && (strcmp(t->itm[i].r.der, q->data.itm[j].r.der) == 0) && (t->itm[i].dotposition == q->data.itm[j].dotposition)) {
        for (int k = 0; k < 255; k++)
          if (t->itm[i].lookahead[k])
            q->data.itm[j].lookahead[k] = 1;
        break;
      }
    }
  }
}

// Find out all the states and their transitions
void find_out_states(struct list *l) {
  if (l == NULL)
    return;
  for (int i = 0; i < l->data.len; i++) {
    if (l->data.itm[i].f)
      continue;
    else if (l->data.itm[i].dotposition == strlen(l->data.itm[i].r.der)) {
      l->data.itm[i].f = 1;
      continue;
    }
    struct list *t;
    t = (struct list *)malloc(sizeof(struct list));
    for (int ind = 0; ind < 255; ind++) {
      t->data.transition[ind] = -1;
    }
    t->data.len = 0;
    t->next = NULL;
    for (int j = i; j < l->data.len; j++) {
      if (l->data.itm[i].r.der[l->data.itm[i].dotposition] == l->data.itm[j].r.der[l->data.itm[j].dotposition]) {
        t->data.itm[t->data.len] = l->data.itm[j];
        t->data.itm[t->data.len].dotposition++;
        t->data.itm[t->data.len].f = 0;
        t->data.len++;
        l->data.itm[j].f = 1;
      }
    }
    build_state(&t->data);
    int s;
    if ((s = state_already_included(head, &t->data)) == -1) {
      tail->next = t;
      tail = t;
      l->data.transition[(int)l->data.itm[i].r.der[l->data.itm[i].dotposition]] = num++;
    } else {
      add_lookaheads(head, s, &t->data);
      free(t);
      l->data.transition[(int)l->data.itm[i].r.der[l->data.itm[i].dotposition]] = s;
    }
  }
  find_out_states(l->next);
}

int main() {
  // Input
  printf("Enter the starting symbol: ");
  scanf(" %c", &start);

  printf("Enter the number of rules\n");
  scanf("%d", &n);
  while (getchar() != '\n'); // Clear the buffer
  a = (struct Rules *)malloc(sizeof(struct Rules) * n);
  
  for (int i = 0; i < n; i++) {
    printf("Enter the variable\n");
    scanf(" %c", &a[i].var);
    
    if (variables[a[i].var - 'A'] != 1) {
      variables[a[i].var - 'A'] = 1;
      n_var++;
    }
    while (getchar() != '\n'); // Clear the buffer
    printf("Enter the derivation\n");
    scanf("%s", a[i].der);
    
    for (int j = 0; j < strlen(a[i].der); j++) {
      if (a[i].der[j] != '@' && (a[i].der[j] < 'A' || a[i].der[j] > 'Z') && terminals[a[i].der[j]] != 1) {
        terminals[a[i].der[j]] = 1;
        n_term++;
      }
    }
    while (getchar() != '\n'); // Clear the buffer
  }

  struct State temp;
  temp.len = 1;
  temp.itm[0].r.var = 'Z';
  temp.itm[0].r.der[0] = start;
  temp.itm[0].r.der[1] = '\0';
  temp.itm[0].dotposition = 0;
  temp.itm[0].f = 0;
  memset(temp.itm[0].lookahead, 0, 255);
  temp.itm[0].lookahead['$'] = 1;

  build_state(&temp);
  num = 1;
  head = (struct list *)malloc(sizeof(struct list));
  head->data = temp;
  head->next = NULL;
  tail = head;
  find_out_states(head);
  
  struct list *q = head;
  int ind = 0;
  while (q != NULL) {
    printf("State %d\n", ind++);
    print_state(q);
    q = q->next;
  }

  return 0;
}
