/*
sample04 �X�^�b�N�̎�����
*/

#include  <stdio.h>
#include  <stdlib.h>

/*--- �X�^�b�N����������\���� ---*/
typedef struct {
	int	 max;		/* �X�^�b�N�̃T�C�Y */
	int	 ptr1;		/* �X�^�b�N�|�C���^ */
	int  ptr2;
	int	 *stk;		/* �X�^�b�N�i�̐擪�v�f�ւ̃|�C���^�j */
} Stack;

/*--- �X�^�b�N�̏����� ---*/
int StackAlloc(Stack *s, int max)
{
	s->ptr1 = 0;
	s->ptr2 = max-1;
	if ((s->stk = (int *)calloc(max, sizeof(int))) == NULL) {
		s->max = 0;								/* �z��̊m�ۂɎ��s */
		return (-1);
	}
	s->max = max;
	return (0);
}

/*--- �X�^�b�N�̌�n�� ---*/
void StackFree(Stack *s)
{
	if (s->stk != NULL) {
		free(s->stk);
		s->max = s->ptr1 = s->ptr2 = 0;
	}
}

/*--- A�X�^�b�N�Ƀf�[�^���v�b�V�� ---*/
int StackPush1(Stack *s, int x)
{
	if (StackIsFull1(s))
		 return (-1);
	s->stk[s->ptr1++] = x;
	return (0);
}

/*--- B�X�^�b�N�Ƀf�[�^���v�b�V�� ---*/
int StackPush2(Stack *s, int x)
{
	if (StackIsFull2(s))
		return (-1);
	s->stk[s->ptr2--] = x;
	return (0);
}

/*--- A�X�^�b�N����f�[�^���|�b�v ---*/
int StackPop1(Stack *s, int *x)
{
	if (StackIsEmpty1(s))							/* �X�^�b�N�͋� */
		return (-1);
	*x = s->stk[--s->ptr1];
	return (0);
}

/*--- B�X�^�b�N����f�[�^���|�b�v ---*/
int StackPop2(Stack *s, int *x)
{
	if (StackIsEmpty2(s))							/* �X�^�b�N�͋� */
		return (-1);
	*x = s->stk[++s->ptr2];
	return (0);
}

/*--- A�X�^�b�N����f�[�^���s�[�N ---*/
int StackPeek1(const Stack *s, int *x)
{
	if (s->ptr1 <= 0)							/* �X�^�b�N�͋� */
		return (-1);
	*x = s->stk[s->ptr1 - 1];
	return (0);
}

/*--- B�X�^�b�N����f�[�^���s�[�N ---*/
int StackPeek2(const Stack *s, int *x)
{
	if (s->ptr2 >= s->max)							/* �X�^�b�N�͋� */
		return (-1);
	*x = s->stk[s->ptr2 - 1];
	return (0);
}

/*--- �X�^�b�N�̑傫�� ---*/
int StackSize(const Stack *s)
{
	return (s->max);
}

/*--- A�X�^�b�N�ɐς܂�Ă���f�[�^�� ---*/
int StackNo1(const Stack *s)
{
	return (s->ptr1);
}

/*--- B�X�^�b�N�ɐς܂�Ă���f�[�^�� ---*/
int StackNo2(const Stack *s)
{
	return (s->ptr2);
}

/*--- A�X�^�b�N�͋� ---*/
int StackIsEmpty1(const Stack *s)
{
	return (s->ptr1 <= 0); 
}

/*--- B�X�^�b�N�͋� ---*/
int StackIsEmpty2(const Stack *s)
{
	return (s->ptr2 >= s->max-1);
}

/*--- A�X�^�b�N�͖��t�� ---*/
int StackIsFull1(const Stack *s)
{
	return (s->ptr1 >= s->max/2);
}

/*--- �X�^�b�N�͖��t�� ---*/
int StackIsFull2(const Stack *s)
{
	return (s->ptr2 <= s->max/2);
}


/*--- �X�^�b�N����ɂ��� ---*/
void StackClear(Stack *s)
{
	s->ptr1 = 0;  
	s->ptr2 = 0;
}

int main(void)
{
	Stack  s;

	if (StackAlloc(&s, 9) == -1) {
		puts("�X�^�b�N�̊m�ۂɎ��s���܂����B");
		return (1);
	}
	while (1) {
		int  m, x;

		printf("���݂̃f�[�^���FA-%d/%d B-%d/%d\n", StackNo1(&s), StackSize(&s), StackNo2(&s), StackSize(&s));
		printf("(1) A�Ƀv�b�V��  (2) A����|�b�v�@(3) B�Ƀv�b�V��  (4) B����|�b�v  (0) �I���F");
		scanf("%d", &m);

		if (m == 0) break;

		switch (m) {
		 case 1: printf("�f�[�^�F");   scanf("%d", &x);
				 if (StackPush1(&s, x) == -1)
					puts("A�X�^�b�N�ւ̃v�b�V���Ɏ��s���܂����B");	break;

		 case 2: if (StackPop1(&s, &x) == -1)
					puts("�|�b�v�ł��܂���B");
				 else
					printf("A����|�b�v�����f�[�^��%d�ł��B\n", x);		break;

		 case 3: printf("�f�[�^�F");   scanf("%d", &x);
			 if (StackPush2(&s, x) == -1)
				 puts("B�X�^�b�N�ւ̃v�b�V���Ɏ��s���܂����B");	break;

		 case 4: if (StackPop2(&s, &x) == -1)
			 puts("�|�b�v�ł��܂���B");
				 else
					 printf("B����|�b�v�����f�[�^��%d�ł��B\n", x);		break;
		}
	}
	StackFree(&s);

	return (0);
}