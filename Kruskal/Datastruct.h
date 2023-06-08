typedef int ElemType;
typedef int Status;
typedef struct Enode {
	int  ivex, jvex; //边所依附的两个顶点
	int  weight; //边的权值 
} ENode; //边表元素类型定义
typedef struct {
	int  vexnum, edgenum; //顶点数和边数
	ElemType vexlist[MAX_VEX];   //顶点表其中值存放度数
	ENode  edgelist[MAX_EDGE];  //边表
} EGraph;    //用边表存放图
typedef struct MSTEdge {
	ENode  edgelist[MAX_EDGE]; //边所依附的两个顶点及权重
	int n;
	int boot;
} MSTEdge; //存放最小生成树
typedef struct PTNode {
	ElemType data;
	int parent;
}PTNode;
typedef struct {
	PTNode nodes[MAX_TREE_SIZE];
	int n;
}PTree;
typedef PTree MFSet;
