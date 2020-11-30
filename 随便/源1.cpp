#ifndef header
#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#include<string.h>
#include<string>
#include<stack>
using namespace std;
#endif // !header

#define LIMIT 100
#define FIRST 1
#define SECOND 2
#define THIRD 3

//����ջԪ�صĶ���
typedef struct TElemType {
	int data;//�˴���ԭ����char���͵�data��Ϊ��int���͵�data���ں��������õ��ıȽ���intͨ��ASCIIͬ��������ɹ����������ǿռ���˼����ֽ�
	int op;
}TElemType;

//�������Ķ���
typedef struct BiTNode {
	TElemType tdata;
	struct BiTNode* lchild, * rchild;
}BiTNode,*BiTree;

//������ջ�Ķ���
typedef struct LSNode {
	TElemType tdata;
	struct LSNode* next;
}LSNode,*LStack;

//��ʼ��������ջ
bool InitStack_LS(LStack& S) {
	S = (LStack)malloc(sizeof(LSNode));
	if (NULL == S) return false;
	S->next = NULL;
	return true;
}

void DestroyStack(LStack& S);

//�ж�������ջ��
bool StackEmpty_LS(LStack S) {
	if (NULL == S->next) return true;
	return false;
}

//������ջ��ջ
bool Push_LS(LStack& S, TElemType e) {
	LSNode* t;
	t = (LSNode*)malloc(sizeof(LSNode)); //����ڵ�ռ�
	if (NULL == t) return false;
	t->tdata = e;
	t->next = S; S = t;
	return true;
}

//������ջ��ջ
bool Pop_LS(LStack& S, TElemType& e) {
	LSNode* t;
	if (nullptr == S) return false;
	t = S;
	e = S->tdata;
	S = S->next;
	free(t);
	return true;
}

//���������ջջ��Ԫ��
bool GetTop_LS(LStack S, TElemType& e) {
	if (NULL == S) return false;
	e = S->tdata;
	return true;
}

//������ջԪ�صĶ���
typedef struct {
	struct BiTNode *bit;
	int tag;
}SElemType;

//��������ջ�Ķ���
typedef struct TSNode {
	SElemType stree;
	struct TSNode* next;
}TSNode, * TStack;

//��ʼ��������ջ
bool InitStack_TS(TStack& T) {
	T = (TStack)malloc(sizeof(TSNode));
	if (T == NULL) return false;
	T->next = NULL;
	return true;
}

//������ջ��ջ
bool Push_TS(TStack& T, SElemType s) {
	TSNode* t;
	t = (TStack)malloc(sizeof(TSNode));
	if (t == NULL) return false;
	t->stree = s;
	t->next = T;
	T = t;
	return true;
}

//������ջ��ջ
bool Pop_TS(TStack& T, SElemType &s) {
	TSNode* t;
	if (T == NULL) return false;
	t = T;
	s = T->stree;
	T = T->next;
	free(t);
	return true;
}

bool StackEmpty_TS(TStack T) {
	if (T->next == NULL) return true;
	return false;
}

//������������Ȩ
void GiveOp(TElemType* e,int n) {
	TElemType* p=e;
	while (n > 0) {
		if (p->data == '+'||p->data == '-') {
			p->op = 1;
		}
		else if (p->data == '*' ||p->data == '/' || p->data == '^') {
			p->op = 2;
		}
		else if (p->data == '(' || p->data == ')') {
			p->op = 3;
		}
		else p->op = 0;
		p++; n--;
	}
}

void InputSelem(SElemType* p, char* str) {
	printf("����㸳ֵ���ԣ�");//�������˸�data�����ַ�
	while (*str) {
		p->bit->tdata.data = *str;
		str++;
		p++;
	}
	putchar('\n');
}

//���ݺ�׺���ʽ���������
TStack	Postfix_to_BiTree(char* str) {
	TStack Ts;
	InitStack_TS(Ts);
	SElemType *tree;
	//SElemType tree[LIMIT];
	//InputSelem(tree, str);
	//SElemType* p=tree;
	//tree = NULL;
	//tree->bit->tdata.data = *str;
	tree = (SElemType*)malloc(sizeof(SElemType));
	SElemType* ptr1, * ptr2;
	ptr1 = (SElemType*)malloc(sizeof(SElemType));
	ptr2 = (SElemType*)malloc(sizeof(SElemType));
	if (NULL == Ts) return NULL;
	while (*str) {
		if ((*str <= '9' && *str >= '0') || (*str <= 'z' && *str >= 'a'))
		{//������
			tree->bit->tdata.data = *str;
			tree->bit->lchild = NULL;
			tree->bit->rchild = NULL;
			Push_TS(Ts, *tree);
		}
		else {//������
			tree->bit->tdata.data = *str;
			Pop_TS(Ts, *ptr1);
			tree->bit->rchild = ptr1->bit;
			Pop_TS(Ts, *ptr2);
			tree->bit->lchild = ptr2->bit;
			Push_TS(Ts, *tree);
		}
		str++;
	}
	free(ptr1); free(ptr2);
	free(tree);
	return Ts;
}

//���ʺ���
void visit(TElemType tdata) {
	putchar(tdata.data);
}

//�ǵݹ��������������
void PostOrder(BiTree T, void (*visit)(TElemType)) {
	if (T == NULL) return;

	printf("�����������ԣ�");

	TStack S;
	InitStack_TS(S);
	SElemType now;
	now.tag = FIRST;
	Push_TS(S, now);
	while (!StackEmpty_TS(S)) {
		Pop_TS(S, now);
		if (now.tag == FIRST) {
			now.tag = SECOND;
			Push_TS(S, now);
			if (now.bit->lchild) {
				now.bit = now.bit->lchild;
				now.tag = FIRST;
				Push_TS(S, now);
			}
		}
		else if (now.tag == SECOND) {
			now.tag = THIRD;
			Push_TS(S, now);
			if (now.bit->rchild) {
				now.bit = now.bit->rchild;
				now.tag = FIRST;
			}
		}
		else visit(now.bit->tdata);
	}
}

void TestTree(TStack S) {
	SElemType test;
	Pop_TS(S, test);

}


//���������Ƿ���ȷ
void testinputvalid(TElemType* ptr, int num) {
	printf("������ȷ�Բ��ԣ�");
	for (int i = 0; i < num; i++, ptr++) {
		putchar(ptr->data);
	}
	printf("\n");
}

//�����������ȼ�
void testpriority(TElemType* ptr, int num) {
	printf("�������ȼ����ԣ�");
	for (int i = 0; i < num; i++, ptr++) {
		printf("%d", ptr->op);
	}
	printf("\n");
}

//���������ַ���
void testinputnum(int num) {
	printf("�����ַ������ԣ�");
	printf("%d\n", num);
}

void Infix_to_Postfix(TElemType* p, LStack &S, int num) {
	bool flag = false;
	printf("�����������ǣ�");
	for (int i = 0; i < num; i++, p++) {
		TElemType top;
		if (p->data <= '9' && p->data >= '0') printf("%c", p->data);
		else {
			switch (p->data)
			{
			case '+':
			case '-':
			case '*':
			case '/':
			case '^':
				if (flag == false) {
					S->tdata = *p;
					flag = true;
				}
				else {
					GetTop_LS(S, top);
					if (top.op < p->op) Push_LS(S, (*p));
					else {
						do
						{
							Pop_LS(S, top);
							if(top.data!='(')
							printf("%c", top.data);
							if(!StackEmpty_LS(S))		GetTop_LS(S, top);
						} while (!StackEmpty_LS(S) && top.op <= p->op);
						Push_LS(S, *p);
					}
				}
				break;
			case '(':
				if (flag == false) {
					flag = true; p->op = -1; S->tdata = *p;
				}
				else {
					p->op = -1;
					Push_LS(S, *p);
				}
				break;
			case ')':
				while (GetTop_LS(S, top) && top.data != '(') {
					Pop_LS(S, top);
					printf("%c", top.data);
				}
				Pop_LS(S, top);
				break;
			default:
				break;
			}
		}
		if (i == num - 1) {
			while (!StackEmpty_LS(S)) {
				Pop_LS(S, top);			// printf("fucking doubling\n");
				printf("%c", top.data);
			}
		}
	}
}

//��׺ת��׺ver1.2
void Infix_to_Postfix2(TElemType* p, LStack& S, int num, char *str) {
	//bool flag = false;//ԭ��ʹ��flag�ж���һ���ַ��Ƿ��ǲ�����������ԭ������ͷջ������Чֵ��
	//��ջ��ʽ����һ���ǲ������Ļ���ջ��Ҫ���ѳ�ʼ���õ�ͷ��㸳ֵ
	S->tdata.op = -1;
	TElemType top;
	printf("�����������ǣ�");
	for (int i = 0; i < num; i++, p++) {
		if (p->data <= '9' && p->data >= '0') {
			printf("%c", p->data);
			*str++ = p->data;
		}
		//	Push(S, *p);
		else {
			switch (p->data)
			{
			case '+':
			case '-':
			case '*':
			case '/':
			case '^':
				putchar('#');
				*str++ = '#';
				GetTop_LS(S, top);
				if (top.op < p->op) Push_LS(S, (*p));
				else {
					do
					{
				//		GetTop_LS(S, top);
						if (top.data == '(') break;
						Pop_LS(S, top);
						*str++ = top.data;
						//if (top.data != '(')
						printf("%c", top.data);
						//if (!StackEmpty_LS(S))	
						GetTop_LS(S, top);
					} while (!StackEmpty_LS(S) && top.op <= p->op);
					Push_LS(S, *p);
				}
				
				break;
			case '(':
				//if (flag == false) { S->tdata.op = -1; flag = true; }
					p->op = -1;
					Push_LS(S, *p);
				break;
			case ')':
				while (GetTop_LS(S, top) && top.data != '(') {
					Pop_LS(S, top);
					*str++ = top.data;
					printf("%c", top.data);
				}
				Pop_LS(S, top);
				break;
			default:
				break;
			}
		}
		if (i == num - 1) {
			while (!StackEmpty_LS(S)) {
				Pop_LS(S, top);			// printf("fucking doubling\n");
				*str++ = top.data;
				printf("%c", top.data);
			}
		}
	}
	*str = '\0';
	putchar('\n');
}

int inputdata(TElemType* ptr, int limit) {//��������
	//��Ȼ�Ǵ��ݵ�ֵַ����ͨ����ַ�ı��Ӧ������Ҳ��ʹʵ�η����ı�
	char c;
	int num = 0;
	while (num < limit)
	{
		c = getchar();
		if (c == '\0' || c == '\n') break;
		ptr->data = c;
		num++; ptr++;
	}
	return num;
}

void fileinput(TElemType *p, int &num) {//���ļ�����
	FILE* fp;
	char ch;
	if ((fp = fopen("testdata.txt", "r")) != NULL) {
		ch = fgetc(fp);
		while (ch != '\n' && ch != '\0' && ch != EOF) {
			p->data = ch;
			ch = fgetc(fp);
			num++;
			p++;
		}
	}
}

void teststrinput(char* str) {
	printf("�ַ������Խ����");
	while (*str) {
		printf("%c", *str++);
	}
	printf("\n");
}

void printPostfix() {//��׺ת��׺
	LStack S;
	InitStack_LS(S);
	TElemType soc[LIMIT];
	TElemType* p = soc;
	printf("��������ʽ��\n");

	int num = 0;

	fileinput(p, num);//ͨ���ļ�������
	//num = inputdata(p, LIMIT);//ͨ������̨������
	char str[LIMIT];

	testinputvalid(p, num);//�������������

	GiveOp(soc, num);//�������븳�����ȼ�

	//printf("%d\n", num);//���������ַ���

	testpriority(p, num);//�������ȼ�

	Infix_to_Postfix2(p, S, num,str);//��׺ת��׺����ʱ��str��д��ת���������

	//TStack T;

	//T = Postfix_to_BiTree(str);

	//SElemType s;

	//Pop_TS(T, s);

	//PostOrder(&s.bit,visit);

	//printf("��������Խ����");

	putchar(s.bit->tdata.data);

	//�ʼǣ����ڶ�����ջԪ�ض���ʱ������ǽ�����ͺ���������ٵõ����һ��Ԫ�ص�data
	//����������������������⣬ȡdataҲ�����쳣

	//putchar(s.bit->lchild->tdata.data);

	//putchar(s.bit.rchild->tdata.data);

	//putchar('\n');

	teststrinput(str);
}

void calpostfix() {

}


int main() {
	
	printPostfix();
	int ch='q';//char���͸���int���ͣ�ʵ���ϸ������ASCII��
	putchar(ch);//�ƺ�putcharֻ�����char���ͣ���ʵ���Ͽ��Դ���ASCII�������Ӧ�ַ�
	
	printf("%c", ch);
	return 0;
}