/*
	@brief:十字链表存储有向图
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
typedef struct ArcBox {//弧结点
	int		tailvex, headvex;//弧尾和弧头结点的下标
	struct	ArcBox *hlink, *tlink;//指向弧头/弧尾相同的下一条弧
	InfoType *info;
}ArcBox;
typedef struct VexNode {//顶点结点
	VertexType	data;//顶点信息
	ArcBox		*firstin, *firstout;//指向以该顶点为弧尾\弧头的第一条弧
}VexNode;
typedef struct {
	VexNode		xlist[MAX_VERTEX_NUM];//表头向量
	int			vexnum, arcnum;//顶点数和弧数
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
	printf("请输入图中的顶点数和弧数：");
	scanf("%d %d", &G->vexnum, &G->arcnum);
	getchar();
	printf("请输入所有顶点的值:");
	for (i = 0; i < G->vexnum; ++i) {
		scanf("%c", &G->xlist[i].data);
		G->xlist[i].firstin = NULL;
		G->xlist[i].firstout = NULL;
	}
	getchar();
	for (i = 0; i < G->arcnum; ++i) {
		printf("请输入第%d条弧的弧尾和弧头：", i + 1);
		scanf("%c %c", &tail, &head);
		getchar();
		p = (ArcBox*)malloc(sizeof(ArcBox));//为新的弧结点申请空间
		p->headvex = LocateVex(G,head);//弧头顶点下标
		p->tailvex = LocateVex(G,tail);//弧尾顶点下标
		p->hlink = G->xlist[p->headvex].firstin;//将新的结点插入十字链表
		p->tlink = G->xlist[p->tailvex].firstout;//将新的结点插入十字链表
		G->xlist[p->headvex].firstin = p;//将新的结点插入十字链表
		G->xlist[p->tailvex].firstout = p;//将新的结点插入十字链表
	}
	return 1;
}


void printDG(OLGraph *G)
{
	int i;
	ArcBox *p = NULL;
	printf("------------顺序------------\n");
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
	printf("------------逆序------------\n");
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