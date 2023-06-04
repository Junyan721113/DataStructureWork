#define MAX_VEX 50
#define MAX_EDGE 100
#define MAX_TREE_SIZE 50
typedef int ElemType;

typedef struct Enode {
	int  ivex, jvex; //边所依附的两个顶点
	int  weight; //边的权值 
} ENode; //边表元素类型定义
typedef struct {
	int  vexnum, edgenum; //顶点数和边数
	ElemType vexlist[MAX_VEX];   //顶点表
	ENode  edgelist[MAX_EDGE];  //边表
} EGraph;    //用边表存放图
typedef struct MSTEdge {
	int vex1, vex2, weight; //边所依附的两个顶点及权重
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