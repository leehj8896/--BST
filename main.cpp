#include <iostream>
#include "node.cpp"
using namespace std;

//����
template <typename T>
void insertBST(Node<T>* root, T newKey) {

	Node<T>* p = root;	//��带 ������ ��ġ
	Node<T>* q = NULL;	//p�� �θ� ���

	while (p != NULL) {
		//������ Ű ���� �̹� ���� ���
		if (newKey == p->getKey()) 
			return;
		
		//�θ���
		q = p;

		//�ڽĳ��
		if (newKey < p->getKey()) 
			p = p->getLeft();		
		else 
			p = p->getRight();
	}
	
	//������ ��� ����
	Node<T>* newNode = new Node<T>(newKey);

	//���ο� ��� ����
	//Ʈ���� ������� ���
	if (root->getKey() == NULL) 
		*root = *newNode;	
	//Ʈ���� ������� ���� ���
	else if (newKey < q->getKey()) 
		q->setLeft(newNode);	
	else 
		q->setRight(newNode);
}

//�ִ� ��� �˻�
template <typename T>
Node<T>* maxNode(Node<T>* root) {

	Node<T>* p = root;

	//p�� Ʈ���� �ִ밪�� ��
	if (p->getRight() == NULL)
		return p;
	
	//Recursive
	return maxNode(p->getRight());
}

//�ּ� ��� �˻�
template <typename T>
Node<T>* minNode(Node<T>* root) {

	Node<T>* p = root;

	//p�� Ʈ���� �ּҰ��� ��
	if (p->getLeft() == NULL)
		return p;

	//Recursive
	return minNode(p->getLeft());
}

//Ʈ�� ���� ����
template <typename T>
int height(Node<T>* root) {
	
	//Ʈ���� ������� ��
	if (root == NULL)
		return 0;

	//Recursive
	if (height(root->getLeft()) >= height(root->getRight()))
		return 1 + height(root->getLeft());
	else
		return 1 + height(root->getRight());
}

//Ʈ�� ��� ���� ����
template <typename T>
int noNodes(Node<T>* root) {

	//Ʈ���� ������� ��
	if (root == NULL)
		return 0;

	//Recursive
	return 1 + noNodes(root->getLeft()) + noNodes(root->getRight());
}

//�˻�
template <typename T>
Node<T>* searchBST(Node<T>* root, T searchKey) {

	Node<T>* p = root;

	//��ã��
	if (p == NULL)
		return NULL;

	//ã��
	if (p->getKey() == searchKey)
		return p;

	//Recursive
	if (p->getKey() < searchKey)
		return searchBST(p->getRight(), searchKey);
	else
		return searchBST(p->getLeft(), searchKey);
}

//�θ��� �˻�
//q = ��Ʈ�� �θ� = NULL ��
//p = ��Ʈ ���
template <typename T>
Node<T>* searchParentBST(Node<T>* root, T searchKey, Node<T>* q, Node<T>* p) {

	//�ڽĳ�尡 �ִ���
	while (p != NULL) {

		//�ڽĳ�带 ã���� ��
		if (searchKey == p->getKey())
			return q;

		//������ �̵�
		q = p;
		if (searchKey < p->getKey())
			p = p->getLeft();
		else
			p = p->getRight();
	}
	//�ڽĳ�尡 ���� ���
	return NULL;
}

//����
//p = �����Ϸ��� ���(searchBST �̿�)
//q = p�� �θ���(searchParentBST �̿�)
template <typename T>
void deleteBST(Node<T>* root, T deleteKey, Node<T>* q, Node<T>* p) {

	//�����Ϸ��� ��尡 ���� ���
	if (p == NULL) 
		return;	

	//p�� �ڽĳ�尡 ���� ���
	if (p->getLeft() == NULL && p->getRight() == NULL)

		//q�� ���� ���
		if (q == NULL)
			*p = NULL;
		//p�� q�� ���� ����Ʈ���� ��
		else if (q->getLeft() == p) 
			q->setLeft(NULL);
		//p�� q�� ������ ����Ʈ���� ��
		else 
			q->setRight(NULL);		

	//p�� �ڽĳ�尡 �ϳ��� ���
	else if(p->getLeft() == NULL || p->getRight() == NULL)
		//�ڽĳ�尡 ���ʿ� ���� ��
		if (p->getLeft() != NULL) {
			
			//q�� ���� ���
			if (q == NULL) 
				*p = *(p->getLeft());			
			//p�� q�� ���� ����Ʈ���� ��
			else if (q->getLeft() == p) 
				q->setLeft(p->getLeft());
			//p�� q�� ������ ����Ʈ���� ��
			else 
				q->setRight(p->getLeft());			
		}
		//�ڽĳ�尡 �����ʿ� ���� ��
		else {
			if (q == NULL) 
				*p = *(p->getRight());			
			else if (q->getLeft() == p) 
				q->setLeft(p->getRight());			
			else 
				q->setRight(p->getRight());			
		}
	
	//�ڽ��� ���� ���
	else if (p->getLeft() != NULL && p->getRight() != NULL) {

		//��带 ������ �ڽ� ���
		char flag;
		Node<T>* r = NULL;

		//������ ���� ���
		if (height(p->getLeft()) > height(p->getRight())) {
			r = maxNode(p->getLeft());
			flag = 'L';
		}
		//�������� ���� ���
		else if (height(p->getLeft()) < height(p->getRight())) {
			r = minNode(p->getRight());
			flag = 'R';
		}
		//���̰� ���� ���
		else if (height(p->getLeft()) == height(p->getRight())) {
			//���� ����Ʈ���� ��� ������ ���� ���
			if (noNodes(p->getLeft()) >= noNodes(p->getRight())) {
				r = maxNode(p->getLeft());
				flag = 'L';
			}
			//������ ����Ʈ���� ��� ������ ���� ���
			else {
				r = minNode(p->getRight());
				flag = 'R';
			}
		}

		//r�� �θ���
		Node<T>* pr = NULL;
		pr = searchParentBST(root, r->getKey(), pr, root);

		//��� ��������
		p->setKey(r->getKey());

		//������ ��� Recursive�ϰ� ����
		if (flag == 'L') 
			deleteBST(p->getLeft(), r->getKey(), pr, r);		
		else 
			//pr = searchParentBST(p->getRight(), r->getKey(), pr, p->getRight());
			deleteBST(p->getRight(), r->getKey(), pr, r);		
	}
}

//���� ��ȸ
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

//�����Լ�
int main() {
	
	int arr[] = { 8, 18, 11, 5, 15, 4, 9, 1, 7, 17, 6 ,14 ,10 ,3 ,19, 20 };
	int arr_rev[] = { 20 ,19 ,3 ,10 ,14, 6 ,17 ,7 ,1, 9, 4 ,15, 5, 11, 18, 8 };
	int size = sizeof(arr) / sizeof(int);

	Node<int>* tree = new Node<int>();

	for (int i = 0; i < size; i++) {
		cout << "(" << arr[i] << " ����)" << endl;
		insertBST(tree, arr[i]);
		inorder(tree);
		cout << "\n" << endl;
	}

	cout << "////////////////////////////////////\n" << endl;

	for (int i = 0; i < size; i++) {
		Node<int>* p;			//�����Ϸ��� Ű
		Node<int>* q = NULL;	//�����Ϸ��� Ű�� �θ� Ű
		cout << "(" << arr[i] << " ����)" << endl;
		p = searchBST(tree, arr[i]);
		q = searchParentBST(tree, arr[i], q, tree);
		deleteBST(tree, arr[i], q, p);
		inorder(tree);
		cout << "\n" << endl;
	}

	cout << "////////////////////////////////////\n" << endl;

	for (int i = 0; i < size; i++) {
		cout << "(" << arr_rev[i] << " ����)" << endl;
		insertBST(tree, arr_rev[i]);
		inorder(tree);
		cout << "\n" << endl;
	}

	cout << "////////////////////////////////////\n" << endl;

	for (int i = 0; i < size; i++) {
		Node<int>* p;			//�����Ϸ��� Ű
		Node<int>* q = NULL;	//�����Ϸ��� Ű�� �θ� Ű
		cout << "(" << arr_rev[i] << " ����)" << endl;
		p = searchBST(tree, arr_rev[i]);
		q = searchParentBST(tree, arr_rev[i], q, tree);
		deleteBST(tree, arr_rev[i], q, p);
		inorder(tree);
		cout << "\n" << endl;
	}
	
	delete tree;
}

//searchParentBST ���
////ã��
//if (p->getKey() == deleteKey)
//	return q;
////Recursive
//if (p->getKey() < deleteKey)
//	return searchParentBST(p->getRight(), deleteKey, p, p->getRight());
//else
//	return searchParentBST(p->getLeft(), deleteKey, p, p->getLeft());