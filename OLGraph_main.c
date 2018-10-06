/*
	@brief:ʮ������洢����ͼ
	@autuor:WavenZ
	@time:2018/10/5
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

#define Status int
#define MAX_VERTEX_NUM 20
#define InfoType int
#define VertexType char
typedef struct ArcBox {//�����
	int		tailvex, headvex;//��β�ͻ�ͷ�����±�
	struct	ArcBox *hlink, *tlink;//ָ��ͷ/��β��ͬ����һ����
	InfoType *info;
}ArcBox;
typedef struct VexNode {//������
	VertexType	data;//������Ϣ
	ArcBox		*firstin, *firstout;//ָ���Ըö���Ϊ��β\��ͷ�ĵ�һ����
}VexNode;
typedef struct {
	VexNode		xlist[MAX_VERTEX_NUM];//��ͷ����
	int			vexnum, arcnum;//�������ͻ���
}OLGraph;;

int LocateVex(OLGraph *G, char vex) {
	int i;
	for (i = 0; i < G->vexnum; ++i) {
		if (vex == G->xlist[i].data)
			return i;
	}
	return -1;

}

Status CreateDG(OLGraph *G) {
	int i;
	char tail, head;
	ArcBox *p = NULL;
	printf("������ͼ�еĶ������ͻ�����");
	scanf("%d %d", &G->vexnum, &G->arcnum);
	getchar();
	printf("���������ж����ֵ:");
	for (i = 0; i < G->vexnum; ++i) {
		scanf("%c", &G->xlist[i].data);
		G->xlist[i].firstin = NULL;
		G->xlist[i].firstout = NULL;
	}
	getchar();
	for (i = 0; i < G->arcnum; ++i) {
		printf("�������%d�����Ļ�β�ͻ�ͷ��", i + 1);
		scanf("%c %c", &tail, &head);
		getchar();
		p = (ArcBox*)malloc(sizeof(ArcBox));//Ϊ�µĻ��������ռ�
		p->headvex = LocateVex(G,head);//��ͷ�����±�
		p->tailvex = LocateVex(G,tail);//��β�����±�
		p->hlink = G->xlist[p->headvex].firstin;//���µĽ�����ʮ������
		p->tlink = G->xlist[p->tailvex].firstout;//���µĽ�����ʮ������
		G->xlist[p->headvex].firstin = p;//���µĽ�����ʮ������
		G->xlist[p->tailvex].firstout = p;//���µĽ�����ʮ������
	}
	return 1;
}


void printDG(OLGraph *G)
{
	int i;
	ArcBox *p = NULL;
	printf("------------˳��------------\n");
	for (i = 0; i < G->vexnum; ++i) {
		p = G->xlist[i].firstout;
		printf("%c: ", G->xlist[i].data);
		while (p)
		{
			printf("%c --> %c  ", G->xlist[p->tailvex].data, G->xlist[p->headvex].data);
			p = p->tlink;
		}
		printf("\n");
	}
	printf("------------����------------\n");
	for (i = 0; i < G->vexnum; ++i) {
		p = G->xlist[i].firstin;
		printf("%c: ", G->xlist[i].data);
		while (p)
		{
			printf("%c <-- %c  ", G->xlist[p->headvex].data, G->xlist[p->tailvex].data);
			p = p->hlink;
		}
		printf("\n");
	}
}




int main(int argc, char *argv[]){

	OLGraph G;
	CreateDG(&G);
	printDG(&G);
	system("pause");
	return 0;
}