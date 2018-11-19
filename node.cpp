#include <iostream>

using namespace std;

//노드 클래스
template <typename T>
class Node {

private:
	T key;
	Node<T>* left;
	Node<T>* right;

public:
	Node() {
		key = NULL;
		left = NULL;
		right = NULL;
	}
	Node(T key) {
		this->key = key;
		left = NULL;
		right = NULL;
	}
	T getKey() const {	return key;}
	Node<T>* getLeft() const { return left; }
	Node<T>* getRight() const { return right; }
	void setKey(T k) {	key = k;}
	void setLeft(Node<T>* l) {	left = l;}
	void setRight(Node<T>* r) {	right = r;}
};