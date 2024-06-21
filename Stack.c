

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
            if(ptr == '(' || ptr == ')') return false;
            if (('0' <= ptr && ptr <= '9') || (('a' <= ptr && ptr <= 'z') || ('A' <= ptr && ptr <= 'Z'))) {
                if (i % 2 != 0) return false;
            }
            if ((ptr == '+') || (ptr == '-') || (ptr == '*') || (ptr == '/')) {
                if (i % 2 == 0) return false;
            }
            
            i++;
        }
        return true;
    }
    return false;
}

bool ValidCheck(char *str) {
    if (str) {
        stack save = {NULL, 0};
        for (int i = 0; str[i]; i++) {
            stack sentes = {NULL, 0};
            if (str[i] == '(') {
                if (str[i+1] && str[i+1] == ')'){
                    printf("1");
                    return false;
                } 
            }
            if (str[i] == ')'){
                if (str[i+1] && str[i+1] == '('){
                    printf("2");
                    return false;
                }
                char data;
                ShowTop(save, &data);
                for (int j = i-1; data != '('; j--){
                    int tmp = Pop(&save);
                    if (tmp){
                        Push(&sentes, tmp);
                    }
                    ShowTop(save, &data);
                }
                Pop(&save);
                for (int j=0; !isEmpty(sentes); j++){
                    int tmp = Pop(&sentes);
                    if(tmp){
                        Push(&save, tmp);
                    }
                }
            }
            if (str[i] != ' ' && str[i] != ')') {
                if (i>0 && str[i-1] == '(' && (str[i] == '+' || str[i] == '-')) {
                    Push(&save, '0');
                }
                Push(&save, str[i]);
            }
        }
        if (isEmpty(save)) {
            printf("4");
            return false;
        }
        PrintStack(save);
        if(!CheckSentes(&save)){
            printf("5");
            return false;
        }
        
        Clearstack(&save);
        return true;
    }
    return false;
}

int main() {
    stack st = {NULL, 0};
    char *str = "((-2))+(1)";
    if (ValidCheck(str))
        printf("Expression is correct!!\n"); 
    else
        printf("The expression is not correct!!\n");
    
}
