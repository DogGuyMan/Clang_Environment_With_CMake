#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <libgen.h>
#include <stdbool.h>

#include <sjhaddresstype.h>
#include <queue.h>
#include <binarytree_primitive.h>
#include <vector_primitive.h>
#include <complete_binarytree_primitive.h>

static VectorChar * preorder_result;
static VectorChar * inorder_result;
static VectorChar * postorder_result;

/*
        1
      /   \
     2     3
   /  \   /  \
  4    5 6    7
 / \  /
8  9 10
*/
static const int inputs[]              = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
static const int expected_bfs[]        = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
static const int expected_preorder[]   = {1, 2, 4, 8, 9, 5, 10, 3, 6, 7};
static const int expected_inorder[]    = {8, 4, 9, 2, 10, 5, 1, 6, 3, 7};
static const int expected_postorder[]  = {8, 9, 4, 10, 5, 2, 6, 7, 3, 1};

static void search_callback(BinaryTreeCharTravelInfo * travel_info, char data) {
    if(travel_info->m_array_ptr == preorder_result->m_array_ptr)    {
        preorder_result->push_back(preorder_result, data);
        travel_info->m_size = preorder_result->size(preorder_result);
        return;
    }
    if(travel_info->m_array_ptr == inorder_result->m_array_ptr)     {
        inorder_result->push_back(inorder_result, data);
        travel_info->m_size = inorder_result->size(inorder_result);
        return;
    }
    if(travel_info->m_array_ptr == postorder_result->m_array_ptr)   {
        postorder_result->push_back(postorder_result, data);
        travel_info->m_size = postorder_result->size(postorder_result);
        return;
    }
    *(travel_info->m_array_ptr + travel_info->m_size++) = data;
    printf("%d ", data);
}

int binarytree_demo_1(int argc, char* argv[]) {

	VectorAddressType * bt_ptr_vector = CreateVectorAddressTypeDefault();

	bt_ptr_vector->push_back(bt_ptr_vector, (uintptr_t)CreateBinaryTreeInt(1));
	bt_ptr_vector->push_back(bt_ptr_vector, (uintptr_t)CreateBinaryTreeInt(2));
	bt_ptr_vector->push_back(bt_ptr_vector, (uintptr_t)CreateBinaryTreeInt(3));
	bt_ptr_vector->push_back(bt_ptr_vector, (uintptr_t)CreateBinaryTreeInt(4));
	bt_ptr_vector->push_back(bt_ptr_vector, (uintptr_t)CreateBinaryTreeInt(5));
	bt_ptr_vector->push_back(bt_ptr_vector, (uintptr_t)CreateBinaryTreeInt(6));

	/*
	(BinaryTreeInt *)	(*	bt_ptr_vector->at(bt_ptr_vector, 0)); ✅
	(BinaryTreeInt *)	(	bt_ptr_vector->at(bt_ptr_vector, 0)); ❌ 절대 이렇게 하면 안된다.

	at은  (uintptr_t) 를 내보내는것이 아니라 (uintptr_t *)인 포인터를 내보낸다.
	그리고 (BinaryTreeInt *)로 캐스팅 해야하는것은 다름 아닌 포인터가 아니라 uintptr_t 자체를 캐스팅 해야한다.
	따라서 아래처럼 (BinaryTreeInt *)*bt_ptr_vector->at(bt_ptr_vector, 0))를 캐스팅 해야하는것
	*/
	BinaryTreeInt * bitree = CAST_ADDRESS_TYPE(BinaryTreeInt, *bt_ptr_vector->at(bt_ptr_vector, 0));

	// printf("bt1 : uintptr_t : %lu, pointer %p\n", (uintptr_t)bt1, bt1);
	// printf("bitree : uintptr_t : %lu, pointer %p\n", *bt_ptr_vector->at(bt_ptr_vector, 0), bitree);

	bitree->insert(bitree, bitree, LEFT_INSERT_NODE, CAST_ADDRESS_TYPE(BinaryTreeInt, *bt_ptr_vector->at(bt_ptr_vector, 1)));
	bitree->insert(bitree, bitree, RIGHT_INSERT_NODE, CAST_ADDRESS_TYPE(BinaryTreeInt, *bt_ptr_vector->at(bt_ptr_vector, 2)));
	bitree->insert(bitree, bitree->m_left_child, RIGHT_INSERT_NODE, CAST_ADDRESS_TYPE(BinaryTreeInt, *bt_ptr_vector->at(bt_ptr_vector, 3)));
	bitree->insert(bitree, bitree->m_left_child->m_right_child, LEFT_INSERT_NODE, CAST_ADDRESS_TYPE(BinaryTreeInt, *bt_ptr_vector->at(bt_ptr_vector, 4)));
	bitree->insert(bitree, bitree->m_left_child->m_right_child, RIGHT_INSERT_NODE, CAST_ADDRESS_TYPE(BinaryTreeInt, *bt_ptr_vector->at(bt_ptr_vector, 5)));
	printf("BinaryTreeIntBFS(bitree, bitree, NULL);\n");
	BinaryTreeIntBFS(bitree, bitree, NULL);

	VectorAddressType * rm_bt_ptr_vector = CreateVectorAddressTypeDefault();
	rm_bt_ptr_vector->push_back(rm_bt_ptr_vector, (uintptr_t)bitree->remove(bitree, bitree->m_left_child->m_right_child->m_right_child));

	printf("original tree 0 : BinaryTreeIntBFS(bitree, bitree, NULL);\n");
	printf("bitree.size : %zu, bitree.depth : %zu\n", bitree->size(bitree, bitree), bitree->max_depth(bitree, bitree));
	BinaryTreeIntBFS(bitree, bitree, NULL);
	printf("\n");

	BinaryTreeInt * rm_0 = CAST_ADDRESS_TYPE(BinaryTreeInt, *rm_bt_ptr_vector->at(rm_bt_ptr_vector, 0));
	printf("removed tree : BinaryTreeIntBFS(rm_0, rm_0, NULL);\n");
	printf("rm_0.size : %zu, rm_0.depth : %zu\n", rm_0->size(rm_0, rm_0), rm_0->max_depth(rm_0, rm_0));
	BinaryTreeIntBFS(rm_0, rm_0, NULL);
	printf("\n");

	rm_bt_ptr_vector->push_back(rm_bt_ptr_vector, (uintptr_t)bitree->remove(bitree, bitree->m_left_child));
	BinaryTreeInt * rm_1 = CAST_ADDRESS_TYPE(BinaryTreeInt, *rm_bt_ptr_vector->at(rm_bt_ptr_vector, 1));
	printf("removed tree 1 : BinaryTreeIntBFS(rm_1, rm_1, NULL);\n");
	printf("rm_1.size : %zu, rm_1.depth : %zu\n", rm_1->size(rm_1, rm_1), rm_1->max_depth(rm_1, rm_1));
	BinaryTreeIntBFS(rm_1, rm_1, NULL);
	printf("\n");

	printf("original tree : BinaryTreeIntBFS(bitree, bitree, NULL);\n");
	printf("bitree.size : %zu, bitree.depth : %zu\n", bitree->size(bitree, bitree), bitree->max_depth(bitree, bitree));
	BinaryTreeIntBFS(bitree, bitree, NULL);
	printf("\n");

	rm_bt_ptr_vector->push_back(rm_bt_ptr_vector, (uintptr_t)bitree->remove(bitree, bitree->m_right_child));
	BinaryTreeInt * rm_2 = CAST_ADDRESS_TYPE(BinaryTreeInt, *rm_bt_ptr_vector->at(rm_bt_ptr_vector, 2));
	printf("removed tree 2 : BinaryTreeIntBFS(rm_2, rm_2, NULL);\n");
	printf("rm_2.size : %zu, rm_2.depth : %zu\n", rm_2->size(rm_2, rm_2), rm_2->max_depth(rm_2, rm_2));
	BinaryTreeIntBFS(rm_2, rm_2, NULL);
	printf("\n");

	printf("original tree : BinaryTreeIntBFS(bitree, bitree, NULL);\n");
	printf("bitree.size : %zu, bitree.depth : %zu\n", bitree->size(bitree, bitree), bitree->max_depth(bitree, bitree));
	BinaryTreeIntBFS(bitree, bitree, NULL);
	printf("\n");

	size_t bt_ptr_vector_size_cache = rm_bt_ptr_vector->size(rm_bt_ptr_vector);
	for(size_t i = 0; i < bt_ptr_vector_size_cache; i++) {
		BinaryTreeInt * destroy_target = CAST_ADDRESS_TYPE(BinaryTreeInt, *rm_bt_ptr_vector->at(rm_bt_ptr_vector, i));
		DestroyBinaryTreeInt(destroy_target);
	}
	DestroyVectorAddressType(rm_bt_ptr_vector);
	DestroyVectorAddressType(bt_ptr_vector);

	return 1;
}

int binarytree_demo_2() {
	VectorAddressType * bt_ptr_vector = CreateVectorAddressTypeDefault();
	bt_ptr_vector->push_back(bt_ptr_vector, (uintptr_t) CreateBinaryTreeInt(55)); // 0
	bt_ptr_vector->push_back(bt_ptr_vector, (uintptr_t) CreateBinaryTreeInt(30)); // 1
	bt_ptr_vector->push_back(bt_ptr_vector, (uintptr_t) CreateBinaryTreeInt(91)); // 2
	bt_ptr_vector->push_back(bt_ptr_vector, (uintptr_t) CreateBinaryTreeInt(18)); // 3
	bt_ptr_vector->push_back(bt_ptr_vector, (uintptr_t) CreateBinaryTreeInt(77)); // 4
	bt_ptr_vector->push_back(bt_ptr_vector, (uintptr_t) CreateBinaryTreeInt(59)); // 5
	bt_ptr_vector->push_back(bt_ptr_vector, (uintptr_t) CreateBinaryTreeInt(83)); // 6

	BinaryTreeInt * bitree = CAST_ADDRESS_TYPE(BinaryTreeInt, * bt_ptr_vector->at(bt_ptr_vector, 0));
	bitree->insert	(bitree, bitree,
					LEFT_INSERT_NODE, CAST_ADDRESS_TYPE(BinaryTreeInt, * bt_ptr_vector->at(bt_ptr_vector, 1)));
	bitree->insert(bitree, bitree->m_left_child,
					LEFT_INSERT_NODE, CAST_ADDRESS_TYPE(BinaryTreeInt, * bt_ptr_vector->at(bt_ptr_vector, 3)));
	bitree->insert	(bitree, bitree,
					RIGHT_INSERT_NODE, CAST_ADDRESS_TYPE(BinaryTreeInt, * bt_ptr_vector->at(bt_ptr_vector, 2)));
	bitree->insert	(bitree, bitree->m_right_child,
					LEFT_INSERT_NODE, CAST_ADDRESS_TYPE(BinaryTreeInt, * bt_ptr_vector->at(bt_ptr_vector, 4)));
	bitree->insert	(bitree, bitree->m_right_child->m_left_child,
					LEFT_INSERT_NODE, CAST_ADDRESS_TYPE(BinaryTreeInt, * bt_ptr_vector->at(bt_ptr_vector, 5)));
	bitree->insert	(bitree, bitree->m_right_child->m_left_child,
					RIGHT_INSERT_NODE, CAST_ADDRESS_TYPE(BinaryTreeInt, * bt_ptr_vector->at(bt_ptr_vector, 6)));

	BinaryTreeIntBFS(bitree, bitree, NULL);

	BinaryTreeIntDataSwap(
		CAST_ADDRESS_TYPE(BinaryTreeInt, * bt_ptr_vector->at(bt_ptr_vector, 0)),
		CAST_ADDRESS_TYPE(BinaryTreeInt, * bt_ptr_vector->at(bt_ptr_vector, 6))
	);

	BinaryTreeIntBFS(bitree, bitree, NULL);

	BinaryTreeIntDataSwap(
		CAST_ADDRESS_TYPE(BinaryTreeInt, * bt_ptr_vector->at(bt_ptr_vector, 0)),
		CAST_ADDRESS_TYPE(BinaryTreeInt, * bt_ptr_vector->at(bt_ptr_vector, 6))
	);

	BinaryTreeIntBFS(bitree, bitree, NULL);

	BinaryTreeIntRightReconnectSubtree(
		bitree->m_root,
		CAST_ADDRESS_TYPE(BinaryTreeInt, * bt_ptr_vector->at(bt_ptr_vector, 4))
	);

	BinaryTreeIntBFS(bitree, bitree, NULL);

	BinaryTreeIntLeftReconnectSubtree(
		bitree->m_root,
		CAST_ADDRESS_TYPE(BinaryTreeInt, * bt_ptr_vector->at(bt_ptr_vector, 4))
	);

	BinaryTreeIntBFS(bitree, bitree, NULL);

	DestroyBinaryTreeInt(bitree);
	DestroyVectorAddressType(bt_ptr_vector);
	return 1;
}
