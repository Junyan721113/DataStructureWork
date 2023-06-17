#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
Status MixMFSet(MFSet* S, int i, int j) {
	if (i<0 || i>S->n - 1 || j<0 || j>S->n - 1)   return ERROR;
	if (S->nodes[i].parent > S->nodes[j].parent) {
		S->nodes[j].parent += S->nodes[i].parent;
		S->nodes[i].parent = j;//i所在集合合并到j所在集合
	}
	else {
		S->nodes[i].parent += S->nodes[j].parent;
		S->nodes[j].parent = i;
	}
	return OK;
}
int FindMFSet(MFSet* S, int i) {
	if (i<0 || i>S->n - 1)  return ERROR;
	int j;
	for (j = i; S->nodes[j].parent >= 0; j = S->nodes[j].parent);
	return j;
}

void InitEGraph(EGraph* g, int vexnum, int edgenum) {
	if (vexnum > MAX_VEX || edgenum > MAX_EDGE)exit(-1);
	g->vexnum = vexnum; g->edgenum = edgenum;
	memset(g->edgelist, 0, edgenum * sizeof(ENode));
	memset(g->vexlist, (ElemType)0, vexnum * sizeof(ElemType));
}
void swap(ENode* a, ENode* b) {
	ENode temp = *b;
	*b = *a;
	*a = temp;
}
void HeapAdjust(ENode R[], int s, int m) {
	ENode rc = R[s];    //暂存 R[s] 
	for (int j = 2 * s; j <= m; j *= 2) { //j 初值指向左孩子
		//沿着key较大的孩子结点自上而下筛选
		if (j < m && R[j].weight < R[j + 1].weight)
			++j;  //j为key较大的记录下标
		if (rc.weight >= R[j].weight)  break; //rc应插入在位置s上
		R[s] = R[j];   s = j;
	}
	R[s] = rc;  //将调整前的堆顶记录插入到 s 位置
} //HeapAdjust

void HeapSort(ENode arr[], int len) {
	int i;
	//初始化，i从最后一个父节点开始调整
	for (i = len / 2 - 1; i >= 0; i--)
		HeapAdjust(arr, i, len - 1);
	//先将第一个元素和已排好元素前一位做交换，再从新调整，直到排序完毕
	for (i = len - 1; i > 0; i--) {
		swap(&arr[0], &arr[i]);
		HeapAdjust(arr, 0, i - 1);
	}
}
void InsertSort(ENode a[], int len)
{
	int i, j;
	ENode temp;
	for (i = 1; i < len; i++)
	{
		temp.ivex = a[i].ivex;
		temp.jvex = a[i].jvex;
		temp.weight = a[i].weight;
		//当前数小于前一位数时
		if (a[i].weight < a[i - 1].weight)
		{
			//将子序列重新排列为有序序列
			for (j = i - 1; temp.weight < a[j].weight; j--)
			{
				a[j + 1] = a[j];
			}
			a[j + 1].ivex = temp.ivex;
			a[j + 1].jvex = temp.jvex;
			a[j + 1].weight = temp.weight;
		}
	}
}
MSTEdge* Kruskal(EGraph* g) {
	int i, j, k, s1, s2;
	MSTEdge* TE;
	TE = (MSTEdge*)malloc(sizeof(MSTEdge));
	if (TE) { memset(TE->edgelist, 0, g->vexnum * sizeof(ENode)); TE->n = 0; }
	else exit(-1);
	MFSet* VSet;// 存放图中每个顶点所在的连通分量的编号	
	VSet = (PTree*)malloc(g->vexnum * sizeof(PTree));
	VSet->n = g->vexnum;
	for (i = 0; i < g->vexnum; i++) { VSet->nodes[i].parent = -1; VSet->nodes[i].data = g->vexlist[i]; }//初始化数组vSet
	//对边按权值从小到大排序
	HeapSort(g->edgelist, g->edgenum);
	i = 0; j = 0;
	int max = 0;
	while (i < g->vexnum && j < g->edgenum) {
		s1 = FindMFSet(VSet, g->edgelist[j].ivex - 1);
		s2 = FindMFSet(VSet, g->edgelist[j].jvex - 1);
		if (s1 != s2) {//则将该边加入到TE中
			TE->edgelist[i].ivex = g->edgelist[j].ivex;
			TE->edgelist[i].jvex = g->edgelist[j].jvex;
			TE->edgelist[i].weight = g->edgelist[j].weight;
			max = g->vexlist[g->edgelist[j].ivex - 1];
			if (g->vexlist[g->edgelist[j].jvex - 1] > max)max = g->vexlist[g->edgelist[j].jvex - 1];
			i++;//顶点数加1
			TE->n++;
			printf("加入边：%d-%d,权值：%d\n", g->edgelist[j].ivex, g->edgelist[j].jvex, g->edgelist[j].weight);
			MixMFSet(VSet, s1, s2);
		}
		j++; //边数加1
	}
	free(VSet);
	for (k = 0; max != g->vexlist[k]; k++);
	TE->boot = k + 1;//度数最大的节点作为根节点
	return TE;
}

int main() {
	printf("输入分为多行，第一行为节点数和边数，中间用空格隔开\n");
	printf("其他行为边，两个节点中间‘-’隔开表示，如vex1-vex2 weight\n");
	printf("输入结束后ctrl+z添加文件结束符再使用回车开始运行程序\n");
	EGraph G;
	int vexnum, edgenum;
	int a, b, c;
	scanf("%d %d", &vexnum, &edgenum);
	getchar();
	InitEGraph(&G, vexnum, edgenum);
	int i = 0;
	while (scanf("%d-%d %d", &a, &b, &c)) {
		G.edgelist[i].ivex = a;
		G.edgelist[i].jvex = b;
		G.edgelist[i].weight = c;
		G.vexlist[a - 1]++;
		G.vexlist[b - 1]++;
		i++;
		if (i == edgenum || (getchar()) == EOF) break;
	}
	if (i < edgenum - 1)printf("输入边数不符，请继续输入：\n");
	printf("====================\n");
	MSTEdge* TE = Kruskal(&G);
	printf("MST中度数最大的节点为%d，设其为根节点\n", TE->boot);
	int Weight = 0;
	for (int j = 0; j < TE->n; j++) {
		Weight += TE->edgelist[j].weight;
	}
	printf("MST的权值为%d\n", Weight);
	printf("====================");
}
