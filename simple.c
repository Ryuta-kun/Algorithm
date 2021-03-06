/*
sample04 スタックの実現例
*/

#include  <stdio.h>
#include  <stdlib.h>

/*--- スタックを実現する構造体 ---*/
typedef struct {
	int	 max;		/* スタックのサイズ */
	int	 ptr1;		/* スタックポインタ */
	int  ptr2;
	int	 *stk;		/* スタック（の先頭要素へのポインタ） */
} Stack;

/*--- スタックの初期化 ---*/
int StackAlloc(Stack *s, int max)
{
	s->ptr1 = 0;
	s->ptr2 = max-1;
	if ((s->stk = (int *)calloc(max, sizeof(int))) == NULL) {
		s->max = 0;								/* 配列の確保に失敗 */
		return (-1);
	}
	s->max = max;
	return (0);
}

/*--- スタックの後始末 ---*/
void StackFree(Stack *s)
{
	if (s->stk != NULL) {
		free(s->stk);
		s->max = s->ptr1 = s->ptr2 = 0;
	}
}

/*--- Aスタックにデータをプッシュ ---*/
int StackPush1(Stack *s, int x)
{
	if (StackIsFull1(s))
		 return (-1);
	s->stk[s->ptr1++] = x;
	return (0);
}

/*--- Bスタックにデータをプッシュ ---*/
int StackPush2(Stack *s, int x)
{
	if (StackIsFull2(s))
		return (-1);
	s->stk[s->ptr2--] = x;
	return (0);
}

/*--- Aスタックからデータをポップ ---*/
int StackPop1(Stack *s, int *x)
{
	if (StackIsEmpty1(s))							/* スタックは空 */
		return (-1);
	*x = s->stk[--s->ptr1];
	return (0);
}

/*--- Bスタックからデータをポップ ---*/
int StackPop2(Stack *s, int *x)
{
	if (StackIsEmpty2(s))							/* スタックは空 */
		return (-1);
	*x = s->stk[++s->ptr2];
	return (0);
}

/*--- Aスタックからデータをピーク ---*/
int StackPeek1(const Stack *s, int *x)
{
	if (s->ptr1 <= 0)							/* スタックは空 */
		return (-1);
	*x = s->stk[s->ptr1 - 1];
	return (0);
}

/*--- Bスタックからデータをピーク ---*/
int StackPeek2(const Stack *s, int *x)
{
	if (s->ptr2 >= s->max)							/* スタックは空 */
		return (-1);
	*x = s->stk[s->ptr2 - 1];
	return (0);
}

/*--- スタックの大きさ ---*/
int StackSize(const Stack *s)
{
	return (s->max);
}

/*--- Aスタックに積まれているデータ数 ---*/
int StackNo1(const Stack *s)
{
	return (s->ptr1);
}

/*--- Bスタックに積まれているデータ数 ---*/
int StackNo2(const Stack *s)
{
	return (s->ptr2);
}

/*--- Aスタックは空か ---*/
int StackIsEmpty1(const Stack *s)
{
	return (s->ptr1 <= 0); 
}

/*--- Bスタックは空か ---*/
int StackIsEmpty2(const Stack *s)
{
	return (s->ptr2 >= s->max-1);
}

/*--- Aスタックは満杯か ---*/
int StackIsFull1(const Stack *s)
{
	return (s->ptr1 >= s->max/2);
}

/*--- スタックは満杯か ---*/
int StackIsFull2(const Stack *s)
{
	return (s->ptr2 <= s->max/2);
}


/*--- スタックを空にする ---*/
void StackClear(Stack *s)
{
	s->ptr1 = 0;  
	s->ptr2 = 0;
}

int main(void)
{
	Stack  s;

	if (StackAlloc(&s, 9) == -1) {
		puts("スタックの確保に失敗しました。");
		return (1);
	}
	while (1) {
		int  m, x;

		printf("現在のデータ数：A-%d/%d B-%d/%d\n", StackNo1(&s), StackSize(&s), StackNo2(&s), StackSize(&s));
		printf("(1) Aにプッシュ  (2) Aからポップ　(3) Bにプッシュ  (4) Bからポップ  (0) 終了：");
		scanf("%d", &m);

		if (m == 0) break;

		switch (m) {
		 case 1: printf("データ：");   scanf("%d", &x);
				 if (StackPush1(&s, x) == -1)
					puts("Aスタックへのプッシュに失敗しました。");	break;

		 case 2: if (StackPop1(&s, &x) == -1)
					puts("ポップできません。");
				 else
					printf("Aからポップしたデータは%dです。\n", x);		break;

		 case 3: printf("データ：");   scanf("%d", &x);
			 if (StackPush2(&s, x) == -1)
				 puts("Bスタックへのプッシュに失敗しました。");	break;

		 case 4: if (StackPop2(&s, &x) == -1)
			 puts("ポップできません。");
				 else
					 printf("Bからポップしたデータは%dです。\n", x);		break;
		}
	}
	StackFree(&s);

	return (0);
}
