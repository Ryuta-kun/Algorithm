/*
sample06　リングバッファによるキューの実現例
*/

#include  <stdio.h>
#include  <stdlib.h>

/*--- キューを実現する構造体 ---*/
typedef struct {
	int	 max;		/* キューのサイズ */
	int	 num;		/* 現在の要素数 */
	int	 front;		/* 先頭要素カーソル */
	int	 rear;		/* 末尾要素カーソル */
	int	 *que;		/* キュー（の先頭要素へのポインタ） */
} Queue;

/*--- キューの初期化 ---*/
int QueueAlloc(Queue *q, int max)
{
	q->num = q->front = q->rear = 0;
	if ((q->que = (int *)calloc(max, sizeof(int))) == NULL) {
		q->max = 0;								/* 配列の確保に失敗 */
		return (-1);
	}
	q->max = max;
	return (0);
}

/*--- キューの後始末 ---*/
void QueueFree(Queue *q)
{
	if (q->que != NULL) {
		free(q->que);							/* 配列を解放 */
		q->max = q->num = q->front = q->rear = 0;
	}
}

/*--- キューにデータをエンキュー ---*/
int QueueEnqueR(Queue *q, int x)
{
	if (q->num >= q->max)
		return (-1);							/* キューは満杯 */
	else {
		q->num++;
		if (q->front == 0 && q->rear == 0)
			q->front++;
		q->que[++q->rear] = x;
		return (0);
	}
}

/*--- キューにデータをエンキュー ---*/
int QueueEnqueF(Queue *q, int x)
{
	if (q->num >= q->max)
		return (-1);							/* キューは満杯 */
	else {
		q->num++;
		int i, j;
		if (q->front == 0)
			q->front++;
		i = q->front - 1;
		while (i>0)
		{
			q->que[i + 1] = q->que[i];
			i--;
		}
		j = q->rear;
		while (j >= q->front)
		{
			q->que[j + 1] = q->que[j];
			j--;
		}
		q->rear++;
		q->que[q->front] = x;
		return (0);
	}
}

/*--- キューからデータをデキュー ---*/
int QueueDequeF(Queue *q, int *x)
{
	if (q->num <= 0)							/* キューは空 */
		return (-1);
	else {
		q->num--;
		if (q->front == 0)
			q->front++;
		*x = q->que[q->front++];
		return (0);
	}
}

/*--- キューからデータをデキュー ---*/
int QueueDequeR(Queue *q, int *x)
{
	if (q->num <= 0)							/* キューは空 */
		return (-1);
	else {
		q->num--;
		*x = q->que[q->rear--];
		return (0);
	}
}

/*--- キューの大きさ ---*/
int QueueSize(const Queue *q)
{
	return (q->max);
}

/*--- キューに蓄えられているデータ数 ---*/
int QueueNo(const Queue *q)
{
	return (q->num);
}

/*--- キューは空か ---*/
int QueueIsEmpty(const Queue *q)
{
	return (q->num <= 0);
}

/*--- キューは満杯か ---*/
int QueueIsFull(const Queue *q)
{
	return (q->num >= q->max);
}

int main(void)
{
	Queue  que;

	if (QueueAlloc(&que, 5) == -1) {
		puts("キューの確保に失敗しました。");
		return (1);
	}
	while (1) {
		int  m, x;

		printf("現在のデータ数：%d/%d\n", QueueNo(&que), QueueSize(&que));
		printf("(1) 先頭からエンデック  (2)末尾からエンデック　(３) 先頭からデデック  (４)末尾から デデック (0) 終了：");
		scanf("%d", &m);

		if (m == 0) break;

		switch (m) {
		 case 1: printf("データ：");   scanf("%d", &x);
				 if (QueueEnqueF(&que, x) == -1)
					puts("データのエンキューに失敗しました。");		break;
 		
		case 2: printf("データ：");   scanf("%d", &x);
				 if (QueueEnqueR(&que, x) == -1)
					puts("データのエンキューに失敗しました。");		break;

		 case 3: if (QueueDequeF(&que, &x) == -1)
					puts("デキューできません。");
				 else
					printf("デキューしたデータは%dです。\n", x);	break;

		 case 4: if (QueueDequeR(&que, &x) == -1)
					puts("デキューできません。");
				 else
					printf("デキューしたデータは%dです。\n", x);	break;
		}
	}
	QueueFree(&que);

	return (0);
}
