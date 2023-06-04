#define MAX_VEX 50
#define MAX_EDGE 100
#define MAX_TREE_SIZE 50
typedef int ElemType;

typedef struct Enode {
	int  ivex, jvex; //������������������
	int  weight; //�ߵ�Ȩֵ 
} ENode; //�߱�Ԫ�����Ͷ���
typedef struct {
	int  vexnum, edgenum; //�������ͱ���
	ElemType vexlist[MAX_VEX];   //�����
	ENode  edgelist[MAX_EDGE];  //�߱�
} EGraph;    //�ñ߱���ͼ
typedef struct MSTEdge {
	int vex1, vex2, weight; //�����������������㼰Ȩ��
} MSTEdge; //�����С������

typedef struct PTNode {
	ElemType data;
	int parent;
}PTNode;
typedef struct {
	PTNode nodes[MAX_TREE_SIZE];
	int n;
}PTree;
typedef PTree MFSet;