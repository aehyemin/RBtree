#include "rbtree.h"

#include <stdlib.h>

// typedef struct node_t {
//   color_t color;
//   key_t key;
//   struct node_t *parent, *left, *right;
// } node_t;

// typedef struct {
//   node_t *root;
//   node_t *nil;  // for sentinel
// } rbtree;

rbtree *new_rbtree(void) {
  rbtree *p = (rbtree *)calloc(1, sizeof(rbtree));
  // TODO: initialize struct if needed
  node_t *nil = (node_t *)calloc(1, sizeof(node_t));
  nil->color = RBTREE_BLACK;

  p->nil = nil;
  p->root = nil;

  return p;
}
// // erase should delete root node
// void test_erase_root(const key_t key) {
//   rbtree *t = new_rbtree();
//   node_t *p = rbtree_insert(t, key);
//   assert(p != NULL);
//   assert(t->root == p);
//   assert(p->key == key);
void delete_node(rbtree *t, node_t *node){
	if (node == t->nil) {
		return;
	}
	delete_node(t, node->left);
	delete_node(t, node->right);

	free(node); //메모리를 해제한다
}

void delete_rbtree(rbtree *t) {
  //루트 노드를 돌면서 nil아니라면 들어가서 메모리를 없애야함
   if (t->root != t->nil)
   	delete_node(t, t->root);
   free(t->nil); // nil 노드도 해제
   free(t);
}


void left_rotate(rbtree *t, node_t *x) {
	node_t *y = x->right; // x의 오른쪽 자식을 y로 설정
	x->right = y->left; //y의 왼쪽자식을 x의 오른쪽 자식으로 이동
	if (y->left != t->nil) {//y의 왼쪽 자식이 존재하면,
		y->left->parent = x; //y의 왼쪽 자식의 부모를 x로 설정
	}

	y->parent = x->parent; //y의 부모를 x의 부모로 설정

	if (x->parent == t->nil) { //x의 부모가 nil, 루트 노드라면
    t->root = y; //y를 새로운 루트로 설정

	} else if (x == x->parent->left) {//x가 왼쪽 자식이면
	x->parent->left = y; //x의 부모의 왼쪽 자식을 y로 설정

	} else { // x가 오른쪽 자식이면
    x->parent->right = y;
	}

	y->left = x;
	x->parent =y;
}

void right_rotate(rbtree *t, node_t *y) {
	node_t *x = y->left; //y의 오른쪽 자식을 x로 설정
	y->left = x->right; //x의 오른쪽 자식을 y의 왼쪽 자식으로 이동
	if (x->right != t->nil) { //x의 오른쪽 자식이 존재하면
		x->right->parent = y; //x의 오른쪽 자식의 부모를 y로 
	}
	x->parent = y->parent; //x의 부모를 y의 부모로 설정

	if(y->parent == t->nil) {
		t->root = x;

	} else if (y == y->parent->right) { //y가 오른쪽 자식이면
		y->parent->right = x; //y의 부모의 오른쪽 자식을 x로

	} else {
		y->parent->left = x;
	}

	x->right = y;
	y->parent = x;
}
//void는 어떤 값도 반환하지 않는다
void rbtree_insert_fixup(rbtree *t, node_t *x) {
	while(x->parent->color == RBTREE_RED) { 
		if (x->parent == x->parent->parent->left) { //부모와왼쪽삼촌이1자
			
			node_t *right_uncle = x->parent->parent->right;
		
			if (right_uncle->color == RBTREE_RED) {
				x->parent->color = RBTREE_BLACK;
				right_uncle->color = RBTREE_BLACK;
				x->parent->parent->color = RBTREE_RED;

				x = x->parent->parent;

			} else {
			if (x == x->parent->right) {
				x = x->parent;

				left_rotate(t,x);
			}
			x->parent->color = RBTREE_BLACK;
			x->parent->parent->color = RBTREE_RED;

			right_rotate(t,x->parent->parent);
			}
			
		} else {
			node_t *left_uncle = x->parent->parent->left;

			if (left_uncle->color == RBTREE_RED) {
				x->parent->color = RBTREE_BLACK;
				left_uncle->color = RBTREE_BLACK;
				x->parent->parent->color = RBTREE_RED;

				x = x->parent->parent;
			} else {
				if (x == x->parent->left) {
					x = x->parent;
					right_rotate(t, x);
				}
				x->parent->color = RBTREE_BLACK;
				x->parent->parent->color = RBTREE_RED;
				left_rotate(t, x->parent->parent);
			}
		}
	}
	t->root->color = RBTREE_BLACK;
}


node_t *rbtree_insert(rbtree *t, const key_t key) {
	node_t *y = t->nil;
	node_t *x = t->root;
	node_t *new_node = (node_t *)calloc(1,sizeof(node_t));

	if (new_node == NULL) return NULL;

	while(x != t->nil) {
		y = x;
		if(key < x->key) {
			x = x->left;

		} else {
			x = x->right;
		}
	}
	new_node->parent = y;
	new_node->key = key;
	
	if(y == t->nil) { //부모가 없는 경우 while안들어감
		t->root = new_node;
	} else if (new_node->key < y->key) {
		y->left = new_node;
	} else {
		y->right = new_node;
	}
	new_node->left = t->nil;
	new_node->right = t->nil;
	new_node->color = RBTREE_RED;

	rbtree_insert_fixup(t, new_node);
	return new_node;
}

node_t *rbtree_find(const rbtree *t, const key_t key) {
  // TODO: implement find
  node_t *cur = t->root;
  
  while (cur != t->nil) {
    if (key == cur->key) {
      return cur;
    }

    if (key > cur->key) {
      cur = cur->right;

    } else {
      cur = cur->left;
    }  
  } 
  return NULL;
}

node_t *rbtree_min(const rbtree *t) {
  // TODO: implement find
  node_t *cur = t->root;

  if (t->root == t->nil) {
    return NULL;
  }

  while (cur->left != t->nil) {
    cur = cur->left;
  }

  return cur;
}

node_t *rbtree_max(const rbtree *t) {
  // TODO: implement find
  node_t *cur = t->root;

  if (t->root == t->nil) {
    return NULL;
  }

  while (cur->right != t->nil) {
    cur = cur->right;
  }
  
  return cur;
}




void rbtree_transplant(rbtree *t, node_t *u, node_t *v) {
	//u는 교체할 대상, v는 그자리에 올 새로운 노드
	if (u->parent == t->nil) {//u가 루트 노드인 경우
		t->root = v; //v가 새로운 root가 된다
	} else if (u  == u->parent->left) { // u가 왼쪽 자식이면
		u->parent->left = v;
	} else {
		u->parent->right = v;
	}
	v->parent = u->parent;
}

void rbtree_erase_fixup(rbtree *t, node_t *x) {
	
	while(x != t->root && x->color == RBTREE_BLACK) { //x가 루트노드가 아니고 x가 블랙일때
	//왼쪽 케이스(x가 왼쪽 자식일때)
		if (x == x->parent->left) {
			node_t *w = x->parent->right; //w는 x의 형제
		
			//경우1. x의 형제 w가 적색일 경우
			if(w->color == RBTREE_RED) { 
				w->color = RBTREE_BLACK;
				x->parent->color = RBTREE_RED;
				left_rotate(t, x->parent);
				w = x->parent->right;
			}

			//경우2. x의 형제 w는 흑색이고 w의 두 자식이 모두 흑색인 경우
				//w가 적색인걸 위의 if문에서 처리해주었기 때문에 이미 흑색임이 보장됨
			if(w->left->color == RBTREE_BLACK && w->right->color == RBTREE_BLACK) {
				w->color = RBTREE_RED;
				x = x->parent;
			}

			//경우3. x의 형제 w는 흑색, w의 왼쪽 자식은 적색, w의 오른쪽 자식은 흑색인 경우
			else {
			if (w->left->color == RBTREE_RED && w->right->color == RBTREE_BLACK) {
				w->left->color = RBTREE_BLACK;
				w->color = RBTREE_RED;
				right_rotate(t, w);
				w = x->parent->right;
			}

			//경우4. x의 형제 w는 흑색이고 w의 오른쪽 자식은 적색인 경우
			w->color = x->parent->color;
			x->parent->color = RBTREE_BLACK;
			w->right->color = RBTREE_BLACK;
			left_rotate(t, x->parent);
			x = t->root;
		}

	   } else { 
		//오른쪽 케이스(x가 오른쪽 자식일때)
		node_t *w = x->parent->left;
			//경우5.w가 적색인 경우
			if (w->color == RBTREE_RED) {
				w->color = RBTREE_BLACK;
				x->parent->color = RBTREE_RED;
				right_rotate(t, x->parent);
				w = x->parent->left;
			}

			//경우6. w가 흑색이고 w의 두 자식이 흑색인 경우
			if (w->right->color == RBTREE_BLACK && w->left->color == RBTREE_BLACK) {
				w->color = RBTREE_RED;
				x = x->parent;
			}

			//경우7.w가 흑색이고 w의 왼쪽자식이 흑색, 오른쪽 자식이 적색인 경우
			else {
			  if (w->left->color == RBTREE_BLACK) {
				w->right->color = RBTREE_BLACK;
				w->color = RBTREE_RED;
				left_rotate(t, w);
				w = x->parent->left;
			}

			//경우8. w가 흑색이고 w의 왼쪽 자식이 적색인 경우
			w->color = x->parent->color;
			x->parent->color = RBTREE_BLACK;
			w->left->color = RBTREE_BLACK;
			right_rotate(t, x->parent);
			x = t->root;
		  }
	//루프 종료 후
	   }
	}
	x->color = RBTREE_BLACK;
	
}

int rbtree_erase(rbtree *t, node_t *p) {//특정 노드를 다른 노드로 대체하는 역할
	node_t *y; //tree에서 삭제된 노드 또는 트리에서 이동한 노드
	color_t y_origin_color; //변경 전 y의 색
	node_t *x; //노드 y의 자식노드

	y=p;
	y_origin_color = y->color;
	
	if(p->left == t->nil) { //경우1.삭제할 노드가 리프노드(자식x)
		x = p->right;
		rbtree_transplant(t, p, p->right); //p를 p->right로 대체
	} else if(p->right == t->nil) { //경우2.삭제할 노드가 오른쪽 자식이 없는 노드
		x = p->left;
		rbtree_transplant(t, p, p->left);
	} else { //삭제할 노드가 두 자식을 모두 가진 경우
		y = p->right;
		while (y->left != t->nil)
		{
		y = y->left;
		}
		y_origin_color = y->color;
		x = y->right;
		if (y->parent == p)
		{
		x->parent = y;
		} else {
			rbtree_transplant(t, y, y->right);
			y->right = p->right;
			y->right->parent =y;
		}
		rbtree_transplant(t, p, y);
		y->left = p->left;
		y->left->parent = y;
		y->color = p->color;
	}
	if (y_origin_color == RBTREE_BLACK) {
		rbtree_erase_fixup(t, x);
	}
	free(p);
	return 0;
  	
}

// - `tree_to_array(tree, array, n)`
//   - RB tree의 내용을 *key 순서대로* 주어진 array로 변환
//   - array의 크기는 n으로 주어지며 tree의 크기가 n 보다 큰 경우에는 순서대로 n개 까지만 변환
//   - array의 메모리 공간은 이 함수를 부르는 쪽에서 준비하고 그 크기를 n으로 알려줍니다.
int inorder(const rbtree *t, node_t *node, key_t *arr, int idx, int n) {
	if (idx >= n) {
		return 0;
	}
	
	if (node != t->nil) {
		if (node->left != t->nil)
			idx = inorder(t, node->left, arr, idx, n);
		arr[idx++] = node->key;
		if (node->right != t->nil)
			idx = inorder(t, node->right, arr, idx, n);

	}
	return idx;
}

int rbtree_to_array(const rbtree *t, key_t *arr, const size_t n) {
	inorder(t, t->root, arr, 0, n);
	return 0;
}
