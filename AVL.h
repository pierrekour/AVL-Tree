#ifndef TREEAVL_H_
#define TREEAVL_H_

#include <iostream>
#include <string>
#include <stddef.h>
using std::exception;
using std::cout;
using std::endl;
using std::string;

class TreeAlreadyExists: public exception {
};
class TreeDoesntExists: public exception {
};
class TreeIsEmpty: public exception {
};

template<class C, class D>
class VertexNode {
	C comp;
	D* data;
	int balanceFactor;
	int leftSonHeight;
	int rightSonHeight;
	unsigned int height;
	VertexNode<C, D>* leftSon;
	VertexNode<C, D>* father;
	VertexNode<C, D>* rightSon;
public:
	VertexNode() :
			data(NULL), balanceFactor(0), leftSonHeight(0), rightSonHeight(0), height(
					0), leftSon(NULL), father(NULL), rightSon(NULL) {
	}
	VertexNode(D& data) :
			data(new D(data)), balanceFactor(0), leftSonHeight(0), rightSonHeight(
					0), height(0), leftSon(NULL), father(NULL), rightSon(NULL) {
	}
	VertexNode(D& data, VertexNode<C, D>* father) :
			data(new D(data)), balanceFactor(0), leftSonHeight(0), rightSonHeight(
					0), height(0), leftSon(NULL), father(father), rightSon(NULL) {
	}
	;
	~VertexNode() {
		if (data) {
			delete data;
		}
	}
	D& VertexGetData();
	bool operator==(const VertexNode<C, D>& ver1) const;
	bool operator<(const VertexNode<C, D>& ver1) const;
	bool operator>(const VertexNode<C, D>& ver1) const;
	VertexNode<C, D>* getFather();
	VertexNode<C, D>* getRightSon();
	VertexNode<C, D>* getLeftSon();
	VertexNode<C, D>* NextOlderSon();
	void updateSonHeight(int key, int NewHeight);
	void updateThisHeight(int NewHeight);
	void updateThisBF();
	int getMaxHeightOfSons();
	int getThisHeight();
	int getThisBF();
	D& getData();
	D* getDataP();
	void asignData(D* data);
	int getLeftSonHeight();
	int getRightSonHeight();
	int getLeftSonBF();
	int getRightSonBF();
	void makeFather(VertexNode<C, D>* newFather);
	void adoptLeftSon(VertexNode<C, D>* newFather);
	void adoptRightSon(VertexNode<C, D>* newFather);
	bool ifLeaf();
	void refreshHeights();
};

template<class C, class D>
class Tree {
	C comp1;
	VertexNode<C, D>* treeRoot;
	unsigned int treeSize;
public:
	Tree() :
			treeRoot(NULL), treeSize(0) {
	}
	~Tree();
	void insertVertex(D& data);
	void removeVertex(D& data);
	D** inOrderTraversal();
	void killTree(VertexNode<C, D>* vertex);
	void inOrderRecursive(D** array, VertexNode<C, D>* current, int* count);
	VertexNode<C, D>* removeLeaf(VertexNode<C, D>* son);
	VertexNode<C, D>* doubleDisown(VertexNode<C, D>* son);
	VertexNode<C, D>* removeSonWithChild(VertexNode<C, D>* son);
	void regrowXY(VertexNode<C, D>* vertex, string direction);
	void shiftRight(VertexNode<C, D>* vertex);
	void shiftLeft(VertexNode<C, D>* vertex);
	unsigned int getTreeSize();
	D& find(D& data);
	D* getData();
	VertexNode<C, D>* Grab(VertexNode<C, D>* newVertex);
	bool ifExits(VertexNode<C, D>* newVertex);
	void RegrowTree(VertexNode<C, D>* Vertex, bool key);
	void reheightAux(VertexNode<C, D>* Vertex);
	void reHeight(VertexNode<C, D>* Vertex);
	D& getTopVertex() const;
};

template<class C, class D>
bool VertexNode<C, D>::ifLeaf() {
	if (leftSon == NULL && rightSon == NULL) {
		return true;
	}
	return false;
}

template<class C, class D>
int VertexNode<C, D>::getThisHeight() {
	return this->height;
}

template<class C, class D>
int VertexNode<C, D>::getThisBF() {
	int left = leftSon->getMaxHeightOfSons();
	int rigth = rightSon->getMaxHeightOfSons();
	return left - rigth;
}

template<class C, class D>
int VertexNode<C, D>::getMaxHeightOfSons() {
	if (this == NULL || this->ifLeaf()) {
		return 0;
	}
	int right = 1 + this->rightSon->getMaxHeightOfSons();
	int left = 1 + this->leftSon->getMaxHeightOfSons();
	if (right > left) {
		return right;
	}
	return left;
}

template<class C, class D>
void VertexNode<C, D>::updateThisHeight(int NewHeight) {
	this->height = NewHeight;
}

template<class C, class D>
void VertexNode<C, D>::updateThisBF() {
	this->balanceFactor = leftSonHeight - rightSonHeight;
}

template<class C, class D>
int VertexNode<C, D>::getLeftSonHeight() {
	return this->leftSonHeight;
}

template<class C, class D>
int VertexNode<C, D>::getRightSonHeight() {
	return this->rightSonHeight;
}

template<class C, class D>
int VertexNode<C, D>::getLeftSonBF() {
	(this->leftSon)->updateThisBF();
	return (this->leftSon)->getThisBF();
}

template<class C, class D>
int VertexNode<C, D>::getRightSonBF() {
	(this->rightSon)->updateThisBF();
	return (this->rightSon)->getThisBF();
}

template<class C, class D>
void VertexNode<C, D>::makeFather(VertexNode<C, D>* newFather) {
	this->father = newFather;
}

template<class C, class D>
void VertexNode<C, D>::adoptLeftSon(VertexNode<C, D>* newSon) {
	this->leftSon = newSon;
	this->leftSonHeight++;
}

template<class C, class D>
void VertexNode<C, D>::adoptRightSon(VertexNode<C, D>* newSon) {
	this->rightSon = newSon;
	this->rightSonHeight++;
}

template<class C, class D>
VertexNode<C, D>* VertexNode<C, D>::getRightSon() {
	return this->rightSon;
}

template<class C, class D>
VertexNode<C, D>* VertexNode<C, D>::getLeftSon() {
	return this->leftSon;
}

template<class C, class D>
D& VertexNode<C, D>::getData() {
	return *data;
}

template<class C, class D>
D* VertexNode<C, D>::getDataP() {
	return data;
}

template<class C, class D>
void VertexNode<C, D>::asignData(D* data) {
	this->data = data;
}

template<class C, class D>
bool VertexNode<C, D>::operator>(const VertexNode<C, D>& ver1) const {
	D& x = *(this->data);
	D& y = *(ver1.data);
	if (comp(x, y) > 0) {
		return true;
	}
	return false;
}

template<class C, class D>
bool VertexNode<C, D>::operator<(const VertexNode<C, D>& ver1) const {
	D& x = *(this->data);
	D& y = *(ver1.data);
	if (comp(x, y) < 0) {
		return true;
	}
	return false;
}

template<class C, class D>
bool VertexNode<C, D>::operator==(const VertexNode<C, D>& ver1) const {
	D& x = *(this->data);
	D& y = *(ver1.data);
	if (comp(x, y) == 0) {
		return true;
	}
	return false;
}

template<class C, class D>
Tree<C, D>::~Tree() {
	killTree(this->treeRoot);
}

template<class C, class D>
void Tree<C, D>::killTree(VertexNode<C, D>* vertex) {
	if (vertex == NULL) {
		return;
	}
	killTree(vertex->getLeftSon());
	killTree(vertex->getRightSon());
	delete vertex;
}

template<class C, class D>
VertexNode<C, D>* VertexNode<C, D>::getFather() {
	return this->father;
}

template<class C, class D>
void VertexNode<C, D>::updateSonHeight(int key, int NewHeight) {
	switch (key) {
	case 1:
		this->rightSonHeight = NewHeight;
		break;
	case -1:
		this->leftSonHeight = NewHeight;
		break;
	default:
		break;
	}
	return;
}

template<class C, class D>
void Tree<C, D>::insertVertex(D& data) {
	VertexNode<C, D> temp = VertexNode<C, D>(data, NULL);
	if (Tree<C, D>::ifExits(&temp)) {
		throw TreeAlreadyExists();
	}
	if (treeRoot == NULL) {
		this->treeRoot = new VertexNode<C, D>(data, NULL);
		this->treeSize++;
		return;
	}
	bool whatSon = 0;
	VertexNode<C, D>* father = Tree<C, D>::Grab(&temp);
	if (comp1(temp.getData(), father->getData()) > 0) {
		father->adoptRightSon(new VertexNode<C, D>(data, father));
		whatSon = 1;
	} else if (comp1(temp.getData(), father->getData()) < 0) {
		father->adoptLeftSon(new VertexNode<C, D>(data, father));
	}
	this->treeSize++;
	if (whatSon == 1) {
		Tree<C, D>::reheightAux(father->getRightSon());
		Tree<C, D>::RegrowTree(father->getRightSon(), false);

	} else {
		Tree<C, D>::reheightAux(father->getLeftSon());
		Tree<C, D>::RegrowTree(father->getLeftSon(), false);
	}
	return;
}

template<class C, class D>
VertexNode<C, D>* Tree<C, D>::Grab(VertexNode<C, D>* vertex) {
	if (treeRoot == NULL) {
		return treeRoot;
	}
	if (comp1(treeRoot->getData(), vertex->getData()) == 0) {
		return treeRoot;
	}
	VertexNode<C, D> *pivot = treeRoot;
	while (pivot) {
		if (comp1(vertex->getData(), pivot->getData()) == 0) {
			return pivot;
		}
		if (comp1(vertex->getData(), pivot->getData()) > 0) {
			if (pivot->getRightSon() == NULL) {
				return pivot;
			}
			pivot = pivot->getRightSon();
		} else if (comp1(vertex->getData(), pivot->getData()) < 0) {
			if (pivot->getLeftSon() == NULL) {
				return pivot;
			}
			pivot = pivot->getLeftSon();
		}
	}
	return NULL;
}

template<class C, class D>
bool Tree<C, D>::ifExits(VertexNode<C, D>* checkVertex) {
	VertexNode<C, D> *check = Tree<C, D>::Grab(checkVertex);
	if (check == NULL) {
		return false;
	} else if (comp1(check->getData(), checkVertex->getData()) == 0) {
		return true;
	}
	return false;
}

template<class C, class D>
D& Tree<C, D>::find(D& data) {
	VertexNode<C, D> temp1 = VertexNode<C, D>(data);
	VertexNode<C, D>* temp2 = Grab(&temp1);
	if (temp2 == NULL) {
		throw TreeDoesntExists();
	} else if (!(comp1(temp2->getData(), temp1.getData()) == 0)) {
		throw TreeDoesntExists();
	}
	return temp2->getData();
}

template<class C, class D>
unsigned int Tree<C, D>::getTreeSize() {
	return treeSize;
}

template<class C, class D>
void Tree<C, D>::RegrowTree(VertexNode<C, D>* Vertex, bool key) {
	VertexNode<C, D>* pivot = Vertex;
	while (pivot) {
		switch (pivot->getThisBF()) {
		case 2:
			(pivot->getLeftSonBF() >= 0) ?
					regrowXY(pivot, "LL") : regrowXY(pivot, "LR");
			reheightAux(pivot);
			break;
		case -2:
			(pivot->getRightSonBF() <= 0) ?
					regrowXY(pivot, "RR") : regrowXY(pivot, "RL");
			reheightAux(pivot);
			break;
		default:
			break;
		}
		if (key) {
			break;
		}
		pivot->updateThisBF();
		pivot = pivot->getFather();
	}
}

template<class C, class D>
void Tree<C, D>::reheightAux(VertexNode<C, D>* Vertex) {
	VertexNode<C, D>* currnetVertex = Vertex;
	currnetVertex = Vertex->getFather();
	while (currnetVertex) {
		reHeight(currnetVertex);
		currnetVertex = currnetVertex->getFather();
	}
	return;
}

template<class C, class D>
void Tree<C, D>::reHeight(VertexNode<C, D>* Vertex) {
	if (Vertex->getRightSon() == NULL) {
		Vertex->updateSonHeight(1, 0);
	} else {
		Vertex->updateSonHeight(1,
				1 + (Vertex->getRightSon())->getMaxHeightOfSons());
	}
	if (Vertex->getLeftSon() == NULL) {
		Vertex->updateSonHeight(-1, 0);
	} else {
		Vertex->updateSonHeight(-1,
				1 + (Vertex->getLeftSon())->getMaxHeightOfSons());
	}
	return;
}

template<class C, class D>
void Tree<C, D>::regrowXY(VertexNode<C, D>* vertex, string XY) {
	if (XY == "LL") {
		Tree<C, D>::shiftRight(vertex);
	} else if (XY == "LR") {
		Tree<C, D>::shiftLeft(vertex->getLeftSon());
		Tree<C, D>::shiftRight(vertex);
	}
	if (XY == "RR") {
		Tree<C, D>::shiftLeft(vertex);
	} else if (XY == "RL") {
		Tree<C, D>::shiftRight(vertex->getRightSon());
		Tree<C, D>::shiftLeft(vertex);
	}
	return;
}

template<class C, class D>
void Tree<C, D>::shiftRight(VertexNode<C, D>* vertex) {
	if (vertex == NULL) {
		return;
	}
	if (vertex == treeRoot) {
		treeRoot = vertex->getLeftSon();
	}
	VertexNode<C, D>* vertexFather = vertex->getFather();
	VertexNode<C, D>* vertexLeftSon = vertex->getLeftSon();
	VertexNode<C, D>* vertexLeftRightSon = vertexLeftSon->getRightSon();
	vertexLeftSon->adoptRightSon(vertex);
	vertex->makeFather(vertexLeftSon);
	vertex->adoptLeftSon(vertexLeftRightSon);
	vertexLeftSon->makeFather(vertexFather);
	VertexNode<C, D>* bigFather = vertexLeftSon->getFather();
	if (bigFather != NULL) {
		if (bigFather->getRightSon() == vertex) {
			bigFather->adoptRightSon(vertexLeftSon);
		} else {
			bigFather->adoptLeftSon(vertexLeftSon);
		}
	}
	VertexNode<C, D>* LeftSon = vertex->getLeftSon();
	if (LeftSon == NULL) {
		vertex->updateSonHeight(-1, 0);
	} else {
		vertex->updateSonHeight(-1, 1 + LeftSon->getMaxHeightOfSons());
		LeftSon->makeFather(vertex);
	}
	VertexNode<C, D>* rightSon = vertexLeftSon->getRightSon();
	vertexLeftSon->updateSonHeight(1, 1 + rightSon->getMaxHeightOfSons());
}

template<class C, class D>
void Tree<C, D>::shiftLeft(VertexNode<C, D>* vertex) {
	if (vertex == NULL) {
		return;
	}
	if (vertex == treeRoot) {
		treeRoot = vertex->getRightSon();
	}
	VertexNode<C, D>* vertexFather = vertex->getFather();
	VertexNode<C, D>* vertexRightSon = vertex->getRightSon();
	VertexNode<C, D>* vertexRightLeftSon = vertexRightSon->getLeftSon();
	vertexRightSon->adoptLeftSon(vertex);
	vertex->makeFather(vertexRightSon);
	vertex->adoptRightSon(vertexRightLeftSon);
	vertexRightSon->makeFather(vertexFather);
	VertexNode<C, D>* bigFather = vertexRightSon->getFather();
	if (bigFather != NULL) {
		if (bigFather->getRightSon() == vertex) {
			bigFather->adoptRightSon(vertexRightSon);
		} else {
			bigFather->adoptLeftSon(vertexRightSon);
		}
	}
	VertexNode<C, D>* RightSon = vertex->getRightSon();
	if (RightSon == NULL) {
		vertex->updateSonHeight(1, 0);
	} else {
		vertex->updateSonHeight(1, 1 + RightSon->getMaxHeightOfSons());
		RightSon->makeFather(vertex);
	}
	VertexNode<C, D>* LeftSon = vertexRightSon->getLeftSon();
	vertexRightSon->updateSonHeight(-1, 1 + LeftSon->getMaxHeightOfSons());
}

template<class C, class D>
void Tree<C, D>::removeVertex(D& data) {
	VertexNode<C, D> temp = VertexNode<C, D>(data);
	VertexNode<C, D>* father;
	int oldH;
	int newH;
	if (!Tree<C, D>::ifExits(&temp)) {
		throw TreeDoesntExists();
	}
	VertexNode<C, D>* toBeDeletedVertex = Tree<C, D>::Grab(&temp);
	VertexNode<C, D>* father1 = toBeDeletedVertex->getFather();
	if (toBeDeletedVertex->ifLeaf()) {
		father = removeLeaf(toBeDeletedVertex);
	} else if (toBeDeletedVertex->getLeftSon()
			&& toBeDeletedVertex->getRightSon()) {
		father = doubleDisown(toBeDeletedVertex);
	} else {
		father = removeSonWithChild(toBeDeletedVertex);
		delete toBeDeletedVertex;
	}
	this->treeSize--;
	if (father == NULL) {
		father1 = father;
	}
	while (father1) {
		oldH = father1->getMaxHeightOfSons();
		reHeight(father1);
		newH = father1->getMaxHeightOfSons();
		if (father1->getThisBF() == 2 || father1->getThisBF() == -2) {
			VertexNode<C, D>* grandFather = father1->getFather();
			RegrowTree(father1, true);
			if (father1->getFather() == grandFather) {
			} else {
				father1 = father1->getFather();
			}
		} else if (oldH == newH) {
			break;
		}
		father1 = father1->getFather();
	}
	return;
}

template<class C, class D>
VertexNode<C, D>* Tree<C, D>::removeLeaf(VertexNode<C, D>* son) {
	VertexNode<C, D>* father = son->getFather();
	if (father == NULL) {
		treeRoot = NULL;
		delete son;
		return treeRoot;
	}
	if (father->getRightSon() == son) {
		father->adoptRightSon(NULL);
	} else {
		father->adoptLeftSon(NULL);
	}
	delete son;
	return father;
}

template<class C, class D>
VertexNode<C, D>* VertexNode<C, D>::NextOlderSon() {
	VertexNode<C, D>* brother = this->getRightSon();
	if (brother == NULL) {
		return NULL;
	}
	while (brother->getLeftSon()) {
		brother = brother->getLeftSon();
	}
	return brother;
}

template<class C, class D>
VertexNode<C, D>* Tree<C, D>::doubleDisown(VertexNode<C, D>* son) {
	VertexNode<C, D>* nextOlder = son->NextOlderSon();
	VertexNode<C, D>* nextOlderFather = nextOlder->getFather();
	D* data = son->getDataP();
	son->asignData(nextOlder->getDataP());
	nextOlder->asignData(data);
	if (nextOlder->ifLeaf()) {
		if (nextOlderFather->getLeftSon() == nextOlder) {
			nextOlderFather->adoptLeftSon(NULL);
		} else {
			nextOlderFather->adoptRightSon(NULL);
		}
		delete nextOlder;
	} else {
		VertexNode<C, D>* ret = removeSonWithChild(nextOlder);
		delete nextOlder;
		return ret;
	}
	return nextOlderFather;
}

template<class C, class D>
VertexNode<C, D>* Tree<C, D>::removeSonWithChild(VertexNode<C, D>* son) {
	VertexNode<C, D> *father = son->getFather();
	VertexNode<C, D>* left = son->getLeftSon();
	VertexNode<C, D>* right = son->getRightSon();
	VertexNode<C, D>* grandSon;
	if (father == NULL) {
		if (left) {
			treeRoot = left;
		} else {
			treeRoot = right;
		}
		treeRoot->makeFather(NULL);
	} else {
		if (left) {
			grandSon = left;
		} else {
			grandSon = right;
		}
		if (father->getRightSon() == son) {
			father->adoptRightSon(grandSon);
			grandSon->makeFather(father);
		} else {
			father->adoptLeftSon(grandSon);
			grandSon->makeFather(father);
		}
		return father;
	}
	return NULL;
}

template<class C, class D>
D** Tree<C, D>::inOrderTraversal() {
	D** array = new D *[this->treeSize];
	int count = 0;
	inOrderRecursive(array, treeRoot, &count);
	return array;
}

template<class C, class D>
void Tree<C, D>::inOrderRecursive(D** array, VertexNode<C, D>* pivot,
		int* count) {
	if (pivot) {
		inOrderRecursive(array, pivot->getLeftSon(), count);
		array[*count] = (pivot->getDataP());
		(*count)++;
		inOrderRecursive(array, pivot->getRightSon(), count);
	}
	return;
}

template<class C, class D>
D& Tree<C, D>::getTopVertex() const {
	if (treeRoot == NULL) {
		throw TreeIsEmpty();
	}
	VertexNode<C, D>* OlderSon = treeRoot;
	while (OlderSon->getRightSon()) {
		OlderSon = OlderSon->getRightSon();
	}
	return OlderSon->getData();
}

#endif /* TREEAVL_H_ */
