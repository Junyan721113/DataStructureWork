#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
void InitEGraph(EGraph *g,int vexnum,int edgenum) {
	if (vexnum > MAX_VEX || edgenum > MAX_EDGE)exit(-1);
	g->vexnum = vexnum; g->edgenum = edgenum;
	memset(g->edgelist, 0, edgenum);
	for (int i = 0; i < vexnum; i++) {
		g->vexlist[i] = i+1;
	}
}
MSTEdge* Kruskal(EGraph* g) {
	int i, j, k, s1, s2;
	MSTEdge* TE;
	TE = (MSTEdge*)malloc(g->vexnum * sizeof(MSTEdge));
	int* vSet;// 存放图中每个顶点所在的连通分量的编号
	vSet = (int*)malloc(g->vexnum * sizeof(int));
	for (i = 0; i < g->vexnum; i++) vSet[i] = i;//初始化数组vSet
	//对边按权值从小到大排序
	InsertSort(&g->edgelist, g->edgenum);
	i = 0; j = 0;
	while (i < g->vexnum && j < g->edgenum) {
		s1 = vSet[g->edgelist[j].ivex];
		s2 = vSet[g->edgelist[j].jvex];
		if (s1 != s2) {//则将该边加入到TE中
			TE[i].vex1 = g->edgelist[j].ivex;
			TE[i].vex2 = g->edgelist[j].jvex;
			TE[i].weight = g->edgelist[j].weight;
			i++; //顶点数加1
			for (k = 0; k < g->vexnum; k++)
				if (vSet[k] == s2) vSet[k] = s1;
		}
		j++; //边数加1
	}
	free(vSet);
	return TE;
}
void InsertSort(ENode *a, int len)
{
	int i, j;
	ENode temp;
	for (i = 1; i < len; i++)
	{
		temp.ivex = a[i].ivex;
		temp.jvex = a[i].jvex;
		temp.weight = a[i].weight;
		//当前数小于前一位数时
		if (a[i].weight< a[i - 1].weight)
		{
			//将子序列重新排列为有序序列
			for (j = i - 1; temp.weight< a[j].weight; j--)
			{
				a[j + 1] = a[j];
			}
			a[j + 1].ivex= temp.ivex;
			a[j + 1].jvex = temp.jvex;
			a[j + 1].weight = temp.weight;
		}
	}
}
int main() {
	EGraph G;
	int vexnum, edgenum;
	int a, b,c;
	scanf("%d %d", &vexnum, &edgenum);
	InitEGraph(&G,vexnum,edgenum);
	char tmp[CACHESIZE], * tmpp = tmp;
	int i = 0, offset;
	fgets(tmp, CACHESIZE, stdin);
	while (sscanf(tmpp, "%d-%d %d%n", &a,&b,&c, &offset) == 2)
	{
		tmpp += offset + 1;
		G.edgelist[i].ivex = a;
		G.edgelist[i].jvex = b;
		G.edgelist[i].weight = c;
		i++;
		if (i >= edgenum)break;
	}

}
