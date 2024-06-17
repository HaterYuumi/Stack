# Отчет 
## Постановка задачи
Моя программа реализует стек и использует его для проверки правильности арифмитических выражений (строки). 

> [!NOTE]
> Стек - динамическая структура данных, в которой элементыы добавляются и удаляются с вершины (головы) стека.

Так же стоит рассказать о ограничениях. 
1. Скобки опускаются, так как нам не важен приоритет операций.
2. Данная программа не учитывает многозначные числа.

## Предлагаемое решение 
Для начала разберем основные функции работы со стеком.
1. Структуры дынных:
   
- **node** - узел стека, содержащий данные типа `char` и указатель на следующий узел "*next*".
```C
typedef struct node
{
	char data;
	struct node *next;
} node;
```
- **stack** - структура стека, содержащая указатель на вершину стека "*top*" и размер стека "*size*".
```C
typedef struct stack
{
	struct node *top;
	int size;
} stack;
```
>[!NOTE]
> typedef - это специальная функция языка программирования **C** , которая позволяет нам создать новые имена для существующих или определленных пользователем типов данных.

>В данном случае используется, чтобы не использовать `struct` при каждом обращении к стеку или к его узлу.

2. Функции для работы со стеком:

- **Push** - функция, которая добавляет элемент на вершину стека.
```C
bool Push(stack*st, char data) 
{
  if(st){                                      //Проверка, чтобы указатель на стек был не NULL
      node *el = (node*)malloc(sizeof(node));  //Создаем указатель, с передаваемым значением
      if(el){                                  //Проверка, что он был создан
          el->data = data;
          el->next = NULL;
          if(st->top == NULL){                 //Если стек пуст
              st->top = el;                    //Передаваемый элемент теперь вершина стека 
          } else {                             //Если стек не пуст
              el->next = st->top;              //Указатель теперь указывает на старую вершину стека
              st->top = el;                    //И становиться новой вершиной стека 
          }
          st->size += 1;                       //увеличиваем размер стека после выполнения функции
          return true;                         //возвращаем истину, если функция отработала коректно
      }
      else return false;                       //возвращаем ложь иначе
  }
  return false;                                //возвращаем ложь иначе
}
```
- **Pop** - функция, достающая эелмент из вершины стека, при этом из стека этот элемент удаляется.
```C
char Pop(stack *st)
{
    if(st){                       //Проверка, чтобы указатель на стек был не NULL
        if(st->top){              //Проверка не пуст ли стек
            node *el = st->top;   //Создаем указатель на вершину стека 
            char data = el->data; //Копируем данные в переменую data 
            st->top = el->next;   //Вершиной становиться следующий элемент
            free(el);             //удаляем старую вершину
            st->size -= 1;        //уменьшаем размер стека
            return data;          //возвращаем даные узла
        }
        else return 0;            //если не прошла проверку, значит останавливаем фукнцию
    }
    else return 0;                //если не прошла проверку, значит останавливаем фукнцию
}
```
- **ShowTop** - похожа на **Pop**, но не удаляет элемент из стека.
```C
bool ShowTop(stack st, char *data) {
    if(data){                     //Проверка, чтобы указатель на данные был не NULL
        if(st.top){               //Проверка не пуст ли стек
            *data = st.top->data; //Копируем значение в data
            return true;          //Истина если программа отработала верно
        }
        else return false;        //Ложь иначе
    }
    else return false;            //Ложь иначе
}
```
- **isEmpty** - функция, проверяющая пуст ли стек.
```C
bool isEmpty(stack  st){
	if (st.top) 
		return false;
	return true;
}
```
- **Clearstack** - очищает стек.
```C
void Clearstack(stack *st)
{
    if(st){                     //Проверка, чтобы указатель на стек был не NULL
        if(st->top){            //Проверка не пуст ли стек
            node *el = st->top; //Указатель на вершину стека
            while(el){          //Цикл, пока el не NULL 
                node *ptr = el; //Указатель, на узел который нужно удалить
                el = el->next;  //el теперь указывает на следующий узел
                st->size--;     //Размер стека -1
                free(ptr);      //Удалить узел на который указывает ptr
            }
            st->top = NULL;     //Вершина теперь NULL
        }
        else return;            //если не прошла проверку, значит останавливаем фукнцию
    }
    else return;                //если не прошла проверку, значит останавливаем фукнцию
}
```
- **PrintStack** - печатает все элементы стека начиная с вершины.
```C
void PrintStack(stack st){
    if(!isEmpty(st)){                  //Проверка, что стек не пустой
        node *ptr = st.top;            //Указатель на вершину стека 
        while (ptr){                   //Цикл пока ptr не NULL
            printf("%c\n", ptr->data); //Выводим данные 
            ptr = ptr->next;           //Указатель теперь указывает на следующий элемент
        }
    }
    else printf("stack is empty\n");   //Если стек пуст
}
```

3. Функции проверки выражений

- **CheckSentens** - функция, которая проверяет, что тройка элементов правильная, то есть например *2-3*, а не *+2-*.
```C
bool CheckSentes(stack *st) {
    if (st) {                                       //Проверка, чтобы указатель на стек был не NULL
        int i = 0;                                  //Позиция в тройке
        while (!isEmpty(*st)) {                     //Цикл пока указатель на стек не NULL
            char ptr = Pop(st);                     //Достаем данные из вершины стека
            if (('0' <= ptr && ptr <= '9') || (('a' <= ptr && ptr <= 'z') || ('A' <= ptr && ptr <= 'Z'))) {
                if (i == 1) return false;           
            }                                       //Если в тройке второй элемент цифра или латинская буква, то ложь
            if ((ptr == '+') || (ptr == '-') || (ptr == '*') || (ptr == '/')) {
                if (i == 0 || i == 2) return false; 
            }                                       //Если в тройке первый или третьий элемент математический оператор, то ложь
            i++;                                    //Следущая позиция
        }
        return true;                                //Если цикл закончился то истина
    }
    return false;                                   //Ложь, если проверка не прошла
}
```
Идея функции: 

1. Отдельно проверять правильность скобки, и добавить в стек *save* строку без скобок.
   - когда встретим число в скобке со знаком плюс или минус ставить передним 0: **(-5)** → **0-5**.
2. С помощью функции проверять *CheckSentes* и если истино то заменять тройку на *v*.
- **ValidCheck** - функция провеврки 
```C
bool ValidCheck(char *str) {
    if (str) {
        stack save = {NULL, 0};
        bool ysl = false;              //Флаг на скобки
        for (int i = 0; str[i]; i++) {
            if (str[i] == '(') {
                ysl = true;
            } else if (str[i] == ')') {
                if (!ysl) return false;
                ysl = false;
            } else if (str[i] != ' ') {
                if (ysl && (str[i] == '+' || str[i] == '-')) {
                    Push(&save, '0');
                }
                Push(&save, str[i]);
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
```
