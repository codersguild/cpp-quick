// Custom C implementaion of some 
// common data structures.
// CodeChef Volunteering. 

#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#include <time.h>
#include <limits.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdbool.h>

/* Simple implementations in C programming language for CodeChef Volunteering */
#define __TYPE int64_t
#define __SIZE_TYPE int64_t
#define __ELEM_TYPE int64_t // graph element type.
#define __format " %lld, "
#define __format_input_number "%lld" // for the graph only actually.
#define __format_node_elems "%lld"
#define __format_sequence "%lu"
static __TYPE count = 1;

/* Circular double linked list with sentinel.
   Use as a queue, stack, deque, random-access array, linked-list, circular list etc. */

/* Red Black tree doesnot have the balancing factor yet. It is a plain simple BST implementation. */

/* Graph data structure added. */


struct pair
{
	__TYPE first;
	__TYPE second;
};

void swap(__TYPE* a, __TYPE* b)
{
	__TYPE *temp = a;
	*a = *b;
	*b = *temp;
}

void print_array(__TYPE* a, size_t MAX)
{
	for(size_t i = 0; i < MAX; ++i)
		printf(__format, a[i]);
	printf("\n");
}

struct pair min_max(__TYPE *a, size_t size) {
	struct pair elems;
	elems.first = a[0];
	elems.second = a[0];
	for(size_t i = 0; i < size; ++i){
		if(a[i] <= elems.first) elems.first = a[i];
		if(a[i] >= elems.second) elems.second = a[i]; 
	}
	return elems;
}

__TYPE max(const __TYPE a, const __TYPE b)
{
	if (a >= b) return a; 
	else return b;
}

__TYPE min(const __TYPE a, const __TYPE b)
{
	if (a >= b) return b; 
	else return a;
}

struct node {
	__TYPE _uuid;
	__TYPE data_item;
	__TYPE connection_weight; // for graph implementation.
	struct node* prev;
	struct node* next;
};

struct rb_tree_node {
	__TYPE __id;
	__TYPE data_item;
	size_t height, left_size, right_size;
	bool color; 
	struct rb_tree_node* left;
	struct rb_tree_node* right;
	struct rb_tree_node* parent;
}; 

struct rb_tree_node* create_rbtree_node(__TYPE data_item) 
{
	struct rb_tree_node* temp = (struct rb_tree_node*) malloc (sizeof(struct rb_tree_node));
	temp->__id = rand();
	temp->data_item = data_item;
	temp->height = temp->left_size = temp->right_size = 0LL;
	temp->color = false;
	temp->left = NULL;
	temp->right = NULL;
	temp->parent = NULL;
	return temp;
}

struct node_data_head {
	__TYPE _uuid;
	__TYPE data_item;
}; 

struct node_data_head* create_data_head()
{
	struct node* temp = (struct node*) malloc (sizeof(struct node_data_head));
	temp->_uuid = -1;
	temp->data_item = -1;
	return (struct node_data_head*) temp;
}

struct node* create_raw_node(__TYPE a, __TYPE B)
{
	struct node* temp = (struct node*) malloc (sizeof(struct node));
	temp->_uuid = rand();
	temp->data_item = a;
	temp->connection_weight = B;
	temp->prev = NULL;
	temp->next = NULL;
	return (struct node*)temp;
}

bool insert_node_front(struct node* head, __TYPE a, __TYPE B)
{
	struct node* temp = create_raw_node(a, B);
	if(head->next == NULL)
	{
		/* First Node Entry */ 
		head->next = temp;
		temp->prev = head;
		temp->next = head;
		head->prev = temp;
		count++;
		return true;
	}
	else
	{
		/* Insert at front of circular doubly-linked list */
		temp->next = head->next;
		temp->prev = head;
		head->next = temp;
		temp->next->prev = temp;
		count++;
		return true;
	}
	return false;
}

bool insert_node_back(struct node* head, __TYPE a, __TYPE B)
{
	struct node* temp = create_raw_node(a, B);
	if(head->next == NULL)
	{
		/* First Node Entry */ 
		head->next = temp;
		temp->prev = head;
		temp->next = head;
		head->prev = temp;
		count++;
		return true;		
	}
	else 
	{	/* Insert node at the end of circular doubly-linked list */
		temp->prev = head->prev;
		temp->next = head;
		head->prev->next = temp;
		head->prev = temp;
		count++;
		return true;
	}
	return false;
}

struct node_data_head* delete_back(struct node* head)
{
	struct node_data_head* data_head = create_data_head();
	data_head->_uuid = head->prev->_uuid;
	data_head->data_item = head->prev->data_item;
	head->prev->prev->next = head;
	head->prev = head->prev->prev;
	count--;
	return data_head;
}

struct node_data_head* delete_front(struct node* head)
{
	struct node_data_head* data_head = create_data_head();
	data_head->_uuid = head->next->_uuid;
	data_head->data_item = head->next->data_item;
	head->next = head->next->next;
	head->next->prev = head;
	count--;
	return data_head;
}

bool is_empty(struct node* head) 
{
	if(head->next == NULL) return true; 
	else return false;
}

bool list_search_method(struct node* head, __TYPE key) 
{
	if(head == NULL) return false;
	struct node* temp = create_raw_node(LONG_MIN, -1);
	temp = head->next; 
	while(true) {
		if(temp->next == head) {
			if(temp->data_item == key) return true;
			else return false;
		}
		else 
		{
			if(temp->data_item == key) return true;
			temp = temp->next;
		}

	}
	return false;
}

bool print(struct node* head)
{
	if(head == NULL) return false;
	struct node* temp = create_raw_node(LONG_MIN, -1);
	temp = head->next;
	while(true) {
		if(temp->next == head) {
			printf(__format, temp->data_item);
			printf(__format, temp->connection_weight);
			printf(", ");
			return true;
		}
		else
		{
			printf(__format, temp->data_item);
                        printf(__format, temp->connection_weight);
                        printf(", ");
			temp = temp->next;
		}

	}
	return false;
}

bool enqueue(struct node* queue, __TYPE a, __TYPE B)
{
	return insert_node_back(queue, a, B);
}

struct node_data_head* dequeue(struct node* queue)
{
	if(queue->next == NULL) {
		printf("Abort : Queue Empty.");
		return NULL;
	}
	return delete_front(queue);	
}

bool push(struct node* stack, __TYPE a, __TYPE B)
{
	return insert_node_back(stack, a, B);
}

struct node_data_head* pop(struct node* stack)
{
	if(stack->next == NULL) {
		printf("Abort : Stack Empty.");
		return NULL;
	}
	else return delete_back(stack);
}

__TYPE* populate_items_array(struct node* head) 
{
	size_t i = 0;
	__TYPE *arr = (__TYPE *) calloc ( (count + 1), sizeof(long long int));
	if(head == NULL) return NULL;
	struct node* temp = create_raw_node(LONG_MIN, -1);
	temp = head->next; 
	while(true) {
		if(temp->next == head) {
			arr[i++] = temp->data_item;
			return arr;
		}
		else 
		{
			arr[i++] = temp->data_item;
			temp = temp->next;
		}
	}
	return arr;	
}

bool insert_tree_node(struct rb_tree_node* root, __TYPE key) 
{
	if(key == root->data_item) 
		return false;
	else if(key > root->data_item) {
		if(root->right == NULL) { 
			root->right = create_rbtree_node(key);
			root->right->parent = root;
			return true;
		}	 
		else return insert_tree_node(root->right, key);
	}
	else {
		if(root->left == NULL) {
			root->left = create_rbtree_node(key);
			root->left->parent = root;
			return true;
		}
		else return insert_tree_node(root->left, key);
	}	
	return false;	
}

bool is_parent_left(struct rb_tree_node* parent, struct rb_tree_node* child)
{
	return (parent->left == child);
}

bool is_parent_right(struct rb_tree_node* parent, struct rb_tree_node* child)
{
	return (parent->right == child);
}

struct rb_tree_node* node_search_tree(struct rb_tree_node* root, __TYPE key) 
{
	if(root == NULL) return NULL;
	else if (root->data_item == key) return root;
	else if (root->data_item > key) return node_search_tree(root->left, key);
	else if (root->data_item < key) return node_search_tree(root->right, key);
	else return NULL;
}

__TYPE tree_minimum (struct rb_tree_node* root)
{
	struct rb_tree_node* temp = root;
	while (temp->left != NULL) {
		temp = temp->left;
	}
	return temp->data_item; 
}

__TYPE tree_maximum (struct rb_tree_node* root)
{
	struct rb_tree_node* temp = root;
	while (temp->right != NULL) {
		temp = temp->right;
	}
	return temp->data_item; 
}

bool delete_tree_node (struct rb_tree_node* root, __TYPE key)
{
	struct rb_tree_node* delete_node = node_search_tree(root, key);
		if(delete_node == NULL) return false;
	
	struct rb_tree_node* parent = delete_node->parent;
		
	if(delete_node->left == NULL && delete_node->right == NULL) {
		// printf("Leaf Node.\n");
		if(parent->left == delete_node) parent->left = NULL;
			else parent->right = NULL;
		free(delete_node);
		return true;
	}	
	
	else if (delete_node->left != NULL && delete_node->right == NULL) {
		// printf("Left Child Node.\n");
		if(parent->left == delete_node) parent->left = delete_node->left;
			else parent->right = delete_node->left;
		free(delete_node);
		return true;
	}	
	
	else if (delete_node->left == NULL && delete_node->right != NULL) {
		// printf("Right Child Node.\n");
		if(parent->left == delete_node) parent->left = delete_node->right;
			else parent->right = delete_node->right;
		free(delete_node);
		return true;		
	}
	
	else {
		// Tricky Case 
		__TYPE replace = tree_minimum(delete_node->right);
		// printf("Full Child Node.\n");
		delete_node->data_item = replace;
		delete_node = node_search_tree(delete_node->right, replace);
			parent = delete_node->parent;
		if(parent->left == delete_node) parent->left = delete_node->right;
			else parent->right = delete_node->right;
		free(delete_node);
		return true;
	}
	return false;
}

bool update_tree_node(struct rb_tree_node* root, __TYPE old_key, __TYPE new_key)
{
	delete_tree_node(root, old_key);
	insert_tree_node(root, new_key);
	return true;
}


bool search_tree(struct rb_tree_node* root, __TYPE key) 
{
	if(root == NULL) return 0;
	else if (root->data_item == key) return 1;
	else if (root->data_item > key) return search_tree(root->left, key);
	else if (root->data_item < key) return search_tree(root->right, key);
	else return 0;
}

bool inorder (struct rb_tree_node* root) 
{
	if(root == NULL) return false;
	inorder(root->left);
	printf(__format, root->data_item);
	inorder(root->right);
	return true;
}

bool preorder (struct rb_tree_node* root) 
{
	if(root == NULL) return false;
	printf(__format, root->data_item);
	preorder(root->left);
	preorder(root->right);
	return true;
}

bool postorder (struct rb_tree_node* root) 
{
	if(root == NULL) return false;
	postorder(root->left);
	postorder(root->right);
	printf(__format, root->data_item);
	return true;
}

__TYPE subtree_height (struct rb_tree_node* root)
{
	if((root->left == NULL && root->right == NULL) || root == NULL) return 0;
	if(root->left == NULL || root->right == NULL) return 1;
	else return (1 + max(subtree_height(root->left), subtree_height(root->right)));
}

__TYPE tree_successor(struct rb_tree_node* root)
{
	struct rb_tree_node* dummy_root = root;
	if (root->left != NULL) {
		return tree_minimum(root->right);
	}
	struct rb_tree_node* temp = dummy_root->parent;
	while((temp != NULL) && (temp == dummy_root->right)) {
		dummy_root = temp; 
		temp = temp->parent;
	}
	return temp->data_item;
}

__TYPE tree_predecessor(struct rb_tree_node* root)
{
	struct rb_tree_node* dummy_root = root;
	if (root->right != NULL) {
		return tree_maximum(root->left);
	}
	struct rb_tree_node* temp = dummy_root->parent;
	while((temp != NULL) && (temp == dummy_root->left)) {
		dummy_root = temp; 
		temp = temp->parent;
	}
	return temp->data_item;
}

bool update_height_order (struct rb_tree_node* root) 
{
	if (root == NULL) return false;	
	root->height = subtree_height(root);
	if (root->left != NULL) {
		root->left_size = subtree_height(root->left);
		update_height_order(root->left);
	}
	if (root->right != NULL) { 
		root->right_size = subtree_height(root->right);
		update_height_order(root->right);
	}
	return true;
}

bool list_tree_leaves (struct rb_tree_node* root)
{
	if(root == NULL) return true;
	if(root->left == NULL && root->right == NULL) {
		printf(__format, root->data_item);
		return true;
	}
	list_tree_leaves (root->left);
	list_tree_leaves (root->right);
}

struct graph
{
	__TYPE size;
	__TYPE *nodes, *adjlist_sizes;
	struct node* *adjlist;
};

struct graph* construct_graph(FILE *GRAPH)
{
	/* Dynamic Allocation of graph type struct */
	struct graph *network = (struct graph*) malloc (sizeof(struct graph));
	__SIZE_TYPE nodes = 0, size = 0, weight = 0;
	__ELEM_TYPE items = 0;
	
	/* Get the number of nodes in the graph */
	fscanf(GRAPH, __format_input_number, &size);
	network->size = size;

	/* Dynamic allocation for storing vertices names and no of vertices adjecent to each node.*/
	network->nodes = (__TYPE *) malloc (sizeof(long long int) * size);
	network->adjlist_sizes = (__TYPE*) malloc (sizeof(long long int) * size);

	/* Store the nodes in a array for quick access */
	for(int i = 0; i < size; ++i) {
		fscanf(GRAPH, __format_node_elems, &items);
		network->nodes[i] = items;
	}

	/* Allocate memory dynamically for storing the adjecency list of nodes. */
	network->adjlist = (struct node**) malloc (sizeof(struct node*) * size);
	
	for(int i  = 0; i < size; ++i) {
		/* Store the size of adjecent nodes list. */
		fscanf(GRAPH, __format_input_number, &nodes);

		/* Insert node into each respective adj list per node. */
		fscanf(GRAPH, __format_node_elems, &items);
		network->adjlist[i] = create_raw_node(items, LONG_MIN);

		/* Store the size of each list (just for auxiliary processing)*/
		network->adjlist_sizes[i] = nodes - 1;

		for(int j = 1; j < nodes; j++) {
			fscanf(GRAPH, __format_node_elems, &items);
			fscanf(GRAPH, __format_input_number, &weight);
			insert_node_back(network->adjlist[i], items, weight);
		}
	}
	/* Finally return the constructed graph (as a network) */
	return network;
}

void print_graph(struct graph* g)
{
	printf("\n Nodes in the graph are :  ");
	for(int i = 0; i < g->size; i++) {
		printf(__format, g->nodes[i]);
	}
	printf("\n\n For each node, adjecent vertices are : \n");
	for(int i = 0; i < g->size; ++i) {
		printf(__format, g->adjlist[i]->data_item);
		printf("Adjecent to Vertex numbers :");
		print(g->adjlist[i]);
		printf("\n");
	}
}

__TYPE* adjecent_to (struct node* vertex)
{
	return populate_items_array(vertex);
}


#define DIGITS 10

void print_space(size_t space) {
	while(space--) {
		fprintf(stdout, " ");
	}
}

size_t counter = 1;

__TYPE print_sequence(__TYPE base) {
	while(base--) {
		if (counter > 10) counter = 1;
		fprintf(stdout, __format_sequence, counter % DIGITS);
		counter++;
	}
}
/* ds */
