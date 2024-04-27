#include <iostream>
#include <queue>
using namespace std;


class Intervalheap {
	int hsize; //number of elements in heap;
	int maxsize; //size of the array
	int** h;
public:
	Intervalheap(int s = 100) {
		maxsize = s;
		hsize = 0;
		h = new int* [2];
		h[0] = new int[maxsize];//store the lower end of closed interval
		h[1] = new int[maxsize];//store the higher end of closed interval
	}

	void Swap(int* arr, int a, int b) {
		int temp = arr[a];
		arr[a] = arr[b];
		arr[b] = temp;
	}

	void Swapinterval(int* arr1, int* arr2, int a, int b) {
		int temp = arr1[a];
		arr1[a] = arr2[b];
		arr2[b] = temp;
	}

	void ReheapUpmax(int root, int bottom) {
		int parent;
		if (bottom > root) { // tree is not empty
			parent = (bottom - 1) / 2;
			if (h[1][parent] < h[1][bottom]) {
				Swap(h[1], parent, bottom);
				ReheapUpmax(root, parent);
			}
		}
	}

	void ReheapDownmax(int root, int bottom) {
		int maxChild, rightChild, leftChild;
		leftChild = 2 * root + 1;
		rightChild = 2 * root + 2;
		if (leftChild <= bottom) { // left child is part of the heap
			if (leftChild == bottom) // only one child
				maxChild = leftChild;
			else {
				if (h[1][leftChild] <= h[1][rightChild])
					maxChild = rightChild;
				else
					maxChild = leftChild;
			}
			if (h[1][root] < h[1][maxChild]) {
				Swap(h[1], root, maxChild);
				ReheapDownmax(maxChild, bottom);
			}
		}
	}


	void ReheapUpmin(int root, int bottom) {
		int parent;
		if (bottom > root) { // tree is not empty
			parent = (bottom - 1) / 2;
			if (h[0][parent] > h[0][bottom]) {
				Swap(h[0], parent, bottom);
				ReheapUpmin(root, parent);
			}
		}
	}

	void ReheapDownmin(int root, int bottom) {
		int minChild, rightChild, leftChild;
		leftChild = 2 * root + 1;
		rightChild = 2 * root + 2;
		if (leftChild <= bottom) { // left child is part of the heap
			if (leftChild == bottom) // only one child
				minChild = leftChild;
			else {
				if (h[0][leftChild] >= h[0][rightChild])
					minChild = rightChild;
				else
					minChild = leftChild;
			}
			if (h[0][root] > h[0][minChild]) {
				Swap(h[0], root, minChild);
				ReheapDownmin(minChild, bottom);
			}
		}
	}


	void insert(int d) {

		if (hsize % 2 == 0) {
			if (d <= h[0][(hsize - 1) / 2]) {
				h[0][hsize / 2] = d;
				ReheapUpmin(0, hsize / 2);
				hsize++;
			}
			else {
				h[1][hsize / 2] = d;
				ReheapUpmax(0, hsize / 2);
				h[0][hsize / 2] = h[1][hsize / 2];
				hsize++;
			}
		}
		else {
			h[1][(hsize - 1) / 2] = d;
			ReheapUpmax(0, (hsize - 1) / 2);
			hsize++;
		}

		for (int i = 0; i < hsize / 2; i++) {
			if (h[0][i] > h[1][i]) {
				int t = h[0][i];
				h[0][i] = h[1][i];
				h[1][i] = t;
				ReheapUpmax(0, (hsize - 1) / 2);
				ReheapUpmin(0, (hsize - 1) / 2);
			}
		}

	}

	void update(int org, int New) {
		bool flag1 = 0, flag2 = 0;
		int k = 0;
		for (int i = 0; i < hsize / 2; i++) {
			if (h[0][i] == org) {
				k = i;
				flag1 = 1;
				break;
			}
			else if (h[1][i] == org) {
				k = i;
				flag2 = 1;
				break;
			}
		}
		if (flag1) {
			h[0][k] = New;
			ReheapUpmin(0, k);
		}
		else if (flag2) {
			h[1][k] = New;
			ReheapUpmax(0, k);
		}
		else cout << "Value does not exists!" << endl;
	}

	void swap(int& a, int& b) {
		int temp = a;
		a = b;
		b = temp;
	}

	void Delete() {
		if (hsize % 2 == 0) {
			h[0][0] = h[0][(hsize / 2) - 1];
			h[1][0] = h[1][((hsize - 1) / 2)];
			hsize -= 2;
			ReheapDownmax(0, (hsize - 1) / 2);
			ReheapDownmin(0, hsize / 2);


		}
		else {
			h[0][0] = h[0][(hsize / 2)];
			h[1][0] = h[1][((hsize - 1) / 2) - 1];
			hsize -= 2;
			ReheapDownmax(0, (hsize - 1) / 2);
			ReheapDownmin(0, hsize / 2);
			if (h[0][hsize / 2] > h[1][((hsize - 1) / 2) - 1]) {
				swap(h[0][hsize / 2], h[1][((hsize - 1) / 2) - 1]);
				ReheapUpmax(0, hsize / 2);
			}
		}



		for (int i = 0; i < hsize / 2; i++) {
			if (h[0][i] > h[1][i]) {
				int t = h[0][i];
				h[0][i] = h[1][i];
				h[1][i] = t;
				ReheapUpmax(0, (hsize - 1) / 2);
				ReheapUpmin(0, (hsize - 1) / 2);
			}
		}

	}



	void print() {

		for (int i = 0; i < hsize / 2; i++) {
			cout << "(" << h[0][i] << "," << h[1][i] << ") ";
			cout << endl;
		}
		if (hsize % 2 != 0) {
			cout << "(" << h[0][hsize / 2] << ", ) ";
		}
		cout << endl << endl;
	}

};

int main() {
	//Intervalheap h1(15);
	//h1.insert(2);
	//h1.insert(30);
	//h1.insert(6);
	//h1.insert(4);
	//h1.insert(11);
	//h1.insert(60);
	//h1.insert(3);
	//h1.insert(7);
	//h1.insert(55);
	//h1.print();
	//cout << endl;
	//h1.Delete();
	//h1.print();
	///*h1.insert(8);
	//h1.insert(34);
	//h1.insert(94);
	//h1.insert(24);
	//h1.insert(55);
	//h1.insert(12);
	//h1.insert(3);
	//h1.insert(66);
	//h1.insert(4);
	//h1.insert(8);
	//h1.insert(34);
	//h1.insert(94);
	//h1.insert(24);
	//h1.insert(555);
	//h1.insert(0);
	//h1.insert(344);
	//h1.insert(454);
	//cout << "AFTER INSERTING: " << endl;
	//h1.print();
	//h1.Delete();
	//cout << "AFTER DELETING: " << endl;
	//h1.print();
	//h1.update(34, 888);
	//cout << "AFTER UPDATING: " << endl;
	//h1.print();*/
	return 0;
}