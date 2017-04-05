/*
sample06�@�����O�o�b�t�@�ɂ��L���[�̎�����
*/

#include  <stdio.h>
#include  <stdlib.h>

/*--- �L���[����������\���� ---*/
typedef struct {
	int	 max;		/* �L���[�̃T�C�Y */
	int	 num;		/* ���݂̗v�f�� */
	int	 front;		/* �擪�v�f�J�[�\�� */
	int	 rear;		/* �����v�f�J�[�\�� */
	int	 *que;		/* �L���[�i�̐擪�v�f�ւ̃|�C���^�j */
} Queue;

/*--- �L���[�̏����� ---*/
int QueueAlloc(Queue *q, int max)
{
	q->num = q->front = q->rear = 0;
	if ((q->que = (int *)calloc(max, sizeof(int))) == NULL) {
		q->max = 0;								/* �z��̊m�ۂɎ��s */
		return (-1);
	}
	q->max = max;
	return (0);
}

/*--- �L���[�̌�n�� ---*/
void QueueFree(Queue *q)
{
	if (q->que != NULL) {
		free(q->que);							/* �z������ */
		q->max = q->num = q->front = q->rear = 0;
	}
}

/*--- �L���[�Ƀf�[�^���G���L���[ ---*/
int QueueEnqueR(Queue *q, int x)
{
	if (q->num >= q->max)
		return (-1);							/* �L���[�͖��t */
	else {
		q->num++;
		if (q->front == 0 && q->rear == 0)
			q->front++;
		q->que[++q->rear] = x;
		return (0);
	}
}

/*--- �L���[�Ƀf�[�^���G���L���[ ---*/
int QueueEnqueF(Queue *q, int x)
{
	if (q->num >= q->max)
		return (-1);							/* �L���[�͖��t */
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

/*--- �L���[����f�[�^���f�L���[ ---*/
int QueueDequeF(Queue *q, int *x)
{
	if (q->num <= 0)							/* �L���[�͋� */
		return (-1);
	else {
		q->num--;
		if (q->front == 0)
			q->front++;
		*x = q->que[q->front++];
		return (0);
	}
}

/*--- �L���[����f�[�^���f�L���[ ---*/
int QueueDequeR(Queue *q, int *x)
{
	if (q->num <= 0)							/* �L���[�͋� */
		return (-1);
	else {
		q->num--;
		*x = q->que[q->rear--];
		return (0);
	}
}

/*--- �L���[�̑傫�� ---*/
int QueueSize(const Queue *q)
{
	return (q->max);
}

/*--- �L���[�ɒ~�����Ă���f�[�^�� ---*/
int QueueNo(const Queue *q)
{
	return (q->num);
}

/*--- �L���[�͋� ---*/
int QueueIsEmpty(const Queue *q)
{
	return (q->num <= 0);
}

/*--- �L���[�͖��t�� ---*/
int QueueIsFull(const Queue *q)
{
	return (q->num >= q->max);
}

int main(void)
{
	Queue  que;

	if (QueueAlloc(&que, 5) == -1) {
		puts("�L���[�̊m�ۂɎ��s���܂����B");
		return (1);
	}
	while (1) {
		int  m, x;

		printf("���݂̃f�[�^���F%d/%d\n", QueueNo(&que), QueueSize(&que));
		printf("(1) �擪����G���f�b�N  (2)��������G���f�b�N�@(�R) �擪����f�f�b�N  (�S)�������� �f�f�b�N (0) �I���F");
		scanf("%d", &m);

		if (m == 0) break;

		switch (m) {
		 case 1: printf("�f�[�^�F");   scanf("%d", &x);
				 if (QueueEnqueF(&que, x) == -1)
					puts("�f�[�^�̃G���L���[�Ɏ��s���܂����B");		break;
 		
		case 2: printf("�f�[�^�F");   scanf("%d", &x);
				 if (QueueEnqueR(&que, x) == -1)
					puts("�f�[�^�̃G���L���[�Ɏ��s���܂����B");		break;

		 case 3: if (QueueDequeF(&que, &x) == -1)
					puts("�f�L���[�ł��܂���B");
				 else
					printf("�f�L���[�����f�[�^��%d�ł��B\n", x);	break;

		 case 4: if (QueueDequeR(&que, &x) == -1)
					puts("�f�L���[�ł��܂���B");
				 else
					printf("�f�L���[�����f�[�^��%d�ł��B\n", x);	break;
		}
	}
	QueueFree(&que);

	return (0);
}
