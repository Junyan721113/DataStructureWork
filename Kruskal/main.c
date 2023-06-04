#define _CRT_SECURE_NO_DEPRECATE
#include<stdio.h>
#include"Datastruct.h"
MSTEdge* Kruskal(EGraph* g) {
	int i, j, k, s1, s2;
	MSTEdge* TE;
	TE = (MSTEdge*)malloc(g->vexnum * sizeof(MSTEdge));
	int* vSet;// 存放图中每个顶点所在的连通分量的编号
	vSet = (int*)malloc(g->vexnum * sizeof(int));
	for (i = 0; i < g->vexnum; i++) vSet[i] = i;//初始化数组vSet
	//对边按权值从小到大排序
	BubbleSort(g->edgelist, g->edgenum);
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
void BubbleSort(ElemType s[], int n) {

}

int main() {

}
