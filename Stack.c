#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct node
{
	char data;
	struct node *next;
} node;

typedef struct stack
{
	struct node *top;
	int size;
} stack;

bool Push(stack*st, char data) 
{
  if(st){
      node *el = (node*)malloc(sizeof(node));
      if(el){
          el->data = data;
          el->next = NULL;
          if(st->top == NULL){
              st->top = el;
          } else {
              el->next = st->top;
              st->top = el;
          }
          st->size += 1;
          return true;
      }
      else return false;
  }
  return false;
}

char Pop(stack *st)
{
    if(st){
        if(st->top){
            node *el = st->top;
            char data = el->data;
            st->top = el->next;
            free(el);
            st->size -= 1;
            return data;
        }
        else return 0;
    }
    else return 0;
}

bool ShowTop(stack st, char *data) {
    if(data){
        if(st.top){
            *data = st.top->data;
            return true;
        }
        else return false;
    }
    else return false;
}

bool isEmpty(stack  st){
	if (st.top)
		return false;
	return true;
}

void Clearstack(stack *st)
{
    if(st){
        if(st->top){
            node *el = st->top;
            while(el){
                node *ptr = el;
                el = el->next;
                st->size--;
                free(ptr);
            }
            st->top = NULL;
        }
        else return;
    }
    else return;
}

void PrintStack(stack st){
    if(!isEmpty(st)){
        node *ptr = st.top;
        while (ptr){
            printf("%c\n", ptr->data);
            ptr = ptr->next;
        }
    }
    else printf("stack is empty\n");
}


bool CheckSentes(stack *st) {
    if (st) {
        int i = 0;
        while (!isEmpty(*st)) {
            char ptr = Pop(st);
            if (('0' <= ptr && ptr <= '9') || (('a' <= ptr && ptr <= 'z') || ('A' <= ptr && ptr <= 'Z'))) {
                if (i == 1) return false;
            }
            if ((ptr == '+') || (ptr == '-') || (ptr == '*') || (ptr == '/')) {
                if (i == 0 || i == 2) return false;
            }
            i++;
        }
        return true;
    }
    return false;
}

bool ValidCheck(char *st) {
    if (st) {
        stack save = {NULL, 0};
        bool ysl = false; // ysl условия на скобки
        for (int i = 0; st[i]; i++) {
            if (st[i] == '(') {
                ysl = true;
            } else if (st[i] == ')') {
                if (!ysl) return false;
                ysl = false;
            } else if (st[i] != ' ') {
                if (ysl && (st[i] == '+' || st[i] == '-')) {
                    Push(&save, '0');
                }
                Push(&save, st[i]);
            }
        }
        if (isEmpty(save)) return false;
        if (ysl) return false;

        bool flag = true;
        while (flag) {
            stack sentes = {NULL, 0};
            for (int i = 0; i < 3; i++) {
                char tmp = Pop(&save);
                if (tmp) {
                    Push(&sentes, tmp);
                }
            }
            if (CheckSentes(&sentes)) {
                Push(&save, 'v');
            } else {
                return false;
            }
            if (save.size == 1) {
                flag = false;
            }
        }
        return true;
    }
    return false;
}

int main() {
    stack st = {NULL, 0};

    char *str = "(-1)-(-2)-(-3)-(-4)-(-5)-6";
    if (ValidCheck(str))
        printf("Expression is correct!!\n");
    else
        printf("The expression is not correct!!\n");

    return 0;
}