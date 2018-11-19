#include <iostream>
#include "node.cpp"
using namespace std;

//삽입
template <typename T>
void insertBST(Node<T>* root, T newKey) {

	Node<T>* p = root;	//노드를 삽입할 위치
	Node<T>* q = NULL;	//p의 부모 노드

	while (p != NULL) {
		//동일한 키 값이 이미 있을 경우
		if (newKey == p->getKey()) 
			return;
		
		//부모노드
		q = p;

		//자식노드
		if (newKey < p->getKey()) 
			p = p->getLeft();		
		else 
			p = p->getRight();
	}
	
	//삽입할 노드 생성
	Node<T>* newNode = new Node<T>(newKey);

	//새로운 노드 삽입
	//트리가 비어있을 경우
	if (root->getKey() == NULL) 
		*root = *newNode;	
	//트리가 비어있지 않을 경우
	else if (newKey < q->getKey()) 
		q->setLeft(newNode);	
	else 
		q->setRight(newNode);
}

//최대 노드 검색
template <typename T>
Node<T>* maxNode(Node<T>* root) {

	Node<T>* p = root;

	//p가 트리의 최대값일 때
	if (p->getRight() == NULL)
		return p;
	
	//Recursive
	return maxNode(p->getRight());
}

//최소 노드 검색
template <typename T>
Node<T>* minNode(Node<T>* root) {

	Node<T>* p = root;

	//p가 트리의 최소값일 때
	if (p->getLeft() == NULL)
		return p;

	//Recursive
	return minNode(p->getLeft());
}

//트리 높이 리턴
template <typename T>
int height(Node<T>* root) {
	
	//트리가 비어있을 때
	if (root == NULL)
		return 0;

	//Recursive
	if (height(root->getLeft()) >= height(root->getRight()))
		return 1 + height(root->getLeft());
	else
		return 1 + height(root->getRight());
}

//트리 노드 개수 리턴
template <typename T>
int noNodes(Node<T>* root) {

	//트리가 비어있을 때
	if (root == NULL)
		return 0;

	//Recursive
	return 1 + noNodes(root->getLeft()) + noNodes(root->getRight());
}

//검색
template <typename T>
Node<T>* searchBST(Node<T>* root, T searchKey) {

	Node<T>* p = root;

	//못찾음
	if (p == NULL)
		return NULL;

	//찾음
	if (p->getKey() == searchKey)
		return p;

	//Recursive
	if (p->getKey() < searchKey)
		return searchBST(p->getRight(), searchKey);
	else
		return searchBST(p->getLeft(), searchKey);
}

//부모노드 검색
//q = 루트의 부모 = NULL 값
//p = 루트 노드
template <typename T>
Node<T>* searchParentBST(Node<T>* root, T searchKey, Node<T>* q, Node<T>* p) {

	//자식노드가 있는지
	while (p != NULL) {

		//자식노드를 찾았을 때
		if (searchKey == p->getKey())
			return q;

		//포인터 이동
		q = p;
		if (searchKey < p->getKey())
			p = p->getLeft();
		else
			p = p->getRight();
	}
	//자식노드가 없을 경우
	return NULL;
}

//삭제
//p = 삭제하려는 노드(searchBST 이용)
//q = p의 부모노드(searchParentBST 이용)
template <typename T>
void deleteBST(Node<T>* root, T deleteKey, Node<T>* q, Node<T>* p) {

	//삭제하려는 노드가 없을 경우
	if (p == NULL) 
		return;	

	//p의 자식노드가 없을 경우
	if (p->getLeft() == NULL && p->getRight() == NULL)

		//q가 없을 경우
		if (q == NULL)
			*p = NULL;
		//p가 q의 왼쪽 서브트리일 때
		else if (q->getLeft() == p) 
			q->setLeft(NULL);
		//p가 q의 오른쪽 서브트리일 때
		else 
			q->setRight(NULL);		

	//p의 자식노드가 하나인 경우
	else if(p->getLeft() == NULL || p->getRight() == NULL)
		//자식노드가 왼쪽에 있을 때
		if (p->getLeft() != NULL) {
			
			//q가 없을 경우
			if (q == NULL) 
				*p = *(p->getLeft());			
			//p가 q의 왼쪽 서브트리일 때
			else if (q->getLeft() == p) 
				q->setLeft(p->getLeft());
			//p가 q의 오른쪽 서브트리일 때
			else 
				q->setRight(p->getLeft());			
		}
		//자식노드가 오른쪽에 있을 때
		else {
			if (q == NULL) 
				*p = *(p->getRight());			
			else if (q->getLeft() == p) 
				q->setLeft(p->getRight());			
			else 
				q->setRight(p->getRight());			
		}
	
	//자식이 둘인 경우
	else if (p->getLeft() != NULL && p->getRight() != NULL) {

		//노드를 가져올 자식 노드
		char flag;
		Node<T>* r = NULL;

		//왼쪽이 높은 경우
		if (height(p->getLeft()) > height(p->getRight())) {
			r = maxNode(p->getLeft());
			flag = 'L';
		}
		//오른쪽이 높은 경우
		else if (height(p->getLeft()) < height(p->getRight())) {
			r = minNode(p->getRight());
			flag = 'R';
		}
		//높이가 같은 경우
		else if (height(p->getLeft()) == height(p->getRight())) {
			//왼쪽 서브트리의 노드 개수가 많을 경우
			if (noNodes(p->getLeft()) >= noNodes(p->getRight())) {
				r = maxNode(p->getLeft());
				flag = 'L';
			}
			//오른쪽 서브트리의 노드 개수가 많을 경우
			else {
				r = minNode(p->getRight());
				flag = 'R';
			}
		}

		//r의 부모노드
		Node<T>* pr = NULL;
		pr = searchParentBST(root, r->getKey(), pr, root);

		//노드 가져오기
		p->setKey(r->getKey());

		//가져온 노드 Recursive하게 제거
		if (flag == 'L') 
			deleteBST(p->getLeft(), r->getKey(), pr, r);		
		else 
			//pr = searchParentBST(p->getRight(), r->getKey(), pr, p->getRight());
			deleteBST(p->getRight(), r->getKey(), pr, r);		
	}
}

//중위 순회
template <typename T>
void inorder(Node<T>* root) {

	if (root->getKey() == 0)
		return;

	if (root->getLeft() != NULL)
		inorder(root->getLeft());
	

	cout << root->getKey() << " ";

	if (root->getRight() != NULL) 
		inorder(root->getRight());	
}

//메인함수
int main() {
	
	int arr[] = { 8, 18, 11, 5, 15, 4, 9, 1, 7, 17, 6 ,14 ,10 ,3 ,19, 20 };
	int arr_rev[] = { 20 ,19 ,3 ,10 ,14, 6 ,17 ,7 ,1, 9, 4 ,15, 5, 11, 18, 8 };
	int size = sizeof(arr) / sizeof(int);

	Node<int>* tree = new Node<int>();

	for (int i = 0; i < size; i++) {
		cout << "(" << arr[i] << " 삽입)" << endl;
		insertBST(tree, arr[i]);
		inorder(tree);
		cout << "\n" << endl;
	}

	cout << "////////////////////////////////////\n" << endl;

	for (int i = 0; i < size; i++) {
		Node<int>* p;			//삭제하려는 키
		Node<int>* q = NULL;	//삭제하려는 키의 부모 키
		cout << "(" << arr[i] << " 삭제)" << endl;
		p = searchBST(tree, arr[i]);
		q = searchParentBST(tree, arr[i], q, tree);
		deleteBST(tree, arr[i], q, p);
		inorder(tree);
		cout << "\n" << endl;
	}

	cout << "////////////////////////////////////\n" << endl;

	for (int i = 0; i < size; i++) {
		cout << "(" << arr_rev[i] << " 삽입)" << endl;
		insertBST(tree, arr_rev[i]);
		inorder(tree);
		cout << "\n" << endl;
	}

	cout << "////////////////////////////////////\n" << endl;

	for (int i = 0; i < size; i++) {
		Node<int>* p;			//삭제하려는 키
		Node<int>* q = NULL;	//삭제하려는 키의 부모 키
		cout << "(" << arr_rev[i] << " 삭제)" << endl;
		p = searchBST(tree, arr_rev[i]);
		q = searchParentBST(tree, arr_rev[i], q, tree);
		deleteBST(tree, arr_rev[i], q, p);
		inorder(tree);
		cout << "\n" << endl;
	}
	
	delete tree;
}

//searchParentBST 재귀
////찾음
//if (p->getKey() == deleteKey)
//	return q;
////Recursive
//if (p->getKey() < deleteKey)
//	return searchParentBST(p->getRight(), deleteKey, p, p->getRight());
//else
//	return searchParentBST(p->getLeft(), deleteKey, p, p->getLeft());