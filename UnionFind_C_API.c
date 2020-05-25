#include <stdio.h>
#include <stdlib.h>


typedef float UF_DATA_TYPE;

typedef struct UnionFind_Node {

	int parentIndex;
	UF_DATA_TYPE data;

} UF_Node;

typedef struct UnionFind_DS {

	int size;
	int numberOfElements;
	UF_Node** nodes;

} UF;


typedef enum UnionFind_Error_Codes { unknownError } UF_Error_Codes;
UF Create_UnionFind(int size);
int UF_makeSet(UF* UF_obj_ptr, UF_DATA_TYPE data);
int UF_find(UF* UF_obj_ptr, int nodeIndex);
int UF_union(UF* UF_obj_ptr, int node1_index, int node2_index);

int main()
{
	UF unionFind_1 = Create_UnionFind(10);

	printf("%d\n", UF_makeSet(&unionFind_1, 45));
	printf("%d\n", UF_makeSet(&unionFind_1, 8));
	printf("%d\n", UF_makeSet(&unionFind_1, 445));
	printf("%d\n", UF_makeSet(&unionFind_1, 73));

	UF_union(&unionFind_1, 0, 2);

	printf("Find %d\n", UF_find(&unionFind_1, 0));

	return 0;
}


UF Create_UnionFind(int size)
{
	UF UF_object;
	UF_object.nodes = (UF_Node**)malloc(sizeof(UF_Node*) * size);
	UF_object.size = size;
	UF_object.numberOfElements = 0;
	return UF_object;
}

int UF_makeSet(UF* UF_obj_ptr, UF_DATA_TYPE data)
{
	if(UF_obj_ptr == NULL) return 0;
	UF_Node* node = (UF_Node*)malloc(sizeof(UF_Node));
	node->parentIndex = UF_obj_ptr->numberOfElements;
	node->data = data;

	UF_obj_ptr->nodes[UF_obj_ptr->numberOfElements] = node;
	UF_obj_ptr->numberOfElements += 1;

	return node->parentIndex;
}

int UF_find(UF* UF_obj_ptr, int nodeIndex)
{
	if(UF_obj_ptr == NULL) return 0;
	int parentIndex = UF_obj_ptr->nodes[nodeIndex]->parentIndex;
	int nodeIndexTemp = nodeIndex;
	while(nodeIndexTemp != parentIndex)
	{
		nodeIndexTemp = parentIndex;
		parentIndex = UF_obj_ptr->nodes[nodeIndexTemp]->parentIndex;
	}
	return nodeIndexTemp;
}

int UF_union(UF* UF_obj_ptr, int node1_index, int node2_index)
{

	if(UF_obj_ptr == NULL) return 0;
	if(UF_obj_ptr->nodes[node1_index] == NULL || UF_obj_ptr->nodes[node2_index] == NULL);

	int parent1 = UF_find(UF_obj_ptr, node1_index);
	int parent2 = UF_find(UF_obj_ptr, node2_index);

	UF_obj_ptr->nodes[parent1]->parentIndex = parent2;
	return 1;
}
