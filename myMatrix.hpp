#ifndef MY_MATRIX_HPP
#define MY_MATRIX_HPP

#include <bits/stdc++.h>

#define rep(i, st, ed) for (int i = st; i <= ed; ++ i)

#define release(p) do {\
	if (p != nullptr) delete p;\
	p = nullptr;\
} while (0)

typedef long long LL;

const int MOD = 1000000007;

template <typename T>
class Node {
public:
	Node(int x, int y, T val);
	Node() {
		this->down = this->right = nullptr;
		data = x = y = 0;
	}
	~Node();
	void insertHorizonal(Node <T> * );
	void insertHorizonal(int , int , T );
	void insertVertical(Node <T> * );
	void insertVertical(int , int , T );

	Node <T> *down, *right;
	T data;
	int x, y;
} ;

template <typename T> class myMatrix;

template <typename T> std:: ostream& operator << (std::ostream &, const myMatrix <T> & );

template <typename T>
class myMatrix {
public:
	myMatrix(const int &, const int & );
	myMatrix(const myMatrix <T> & );
	~myMatrix();

	// reload << operator to cout
	friend std:: ostream& operator << <T> (std:: ostream &, const myMatrix <T> & );
	// Mat + Mat
	myMatrix <T> operator + (const myMatrix <T> & );
	// Mat - Mat
	myMatrix <T> operator - (const myMatrix <T> & );
	// Mat *= Mat
	myMatrix <T> operator *= (const myMatrix <T> & );
	// Mat *= k
	myMatrix <T> operator *= (const T & );
	// Mat = Mat
	myMatrix <T>& operator = (const myMatrix <T> & );
	// Mat = Pow(Mat, k)
	myMatrix <T> operator ^ (LL );
	// set Mat[i, j] to val
	void set(int , int , T );
	// set Mat to ZERO Mat
	void init(int , int );
	// set Mat to N*N IDEN Mat
	void identity(int );

	static const int N = 505;
	Node <T> *Col[N], *Row[N], *tmp[N];

private:
	// connect vertical links after Mat opreations
	void connect();

	int n, m;
} ;

template <typename T> Node <T> :: Node(int x, int y, T val) {
	this->down = this->right = nullptr;
	this->x = x; this->y = y; this->data = val;
}

template <typename T> myMatrix <T> myMatrix <T>:: operator ^ (LL k) {
	if (this->n != this->m) {
		return *this;
	}
	myMatrix <T> C(this->n, this->m);
	myMatrix <T> D(this->n, this->m);
	D = *this;
	rep(i, 1, this->n) {
		C.set(i, i, 1);
	}
	for (; k; k >>= 1) {
		if (k & 1) C *= D;
		D *= D;
	}
	return C;
}

template <typename T> void Node <T>:: insertHorizonal(Node <T> *p) {
	if (this->right != nullptr) p->right = this->right;
	this->right = p;
}

template <typename T> void Node <T>:: insertHorizonal(int x, int y, T val) {
	Node <T> *p = new Node <T> (x, y, val);
	if (this->right != nullptr) p->right = this->right;
	this->right = p;
}

template <typename T> void Node <T>:: insertVertical(Node <T> *p) {
	if (this->down != nullptr) p->down = this->down;
	this->down = p;
}

template <typename T> void Node <T>:: insertVertical(int x, int y, T val) {
	Node <T> *p = new Node <T> (x, y, val);
	if (this->down != nullptr) p->down = this->down;
	this->down = p;
}

template <typename T> Node <T> :: ~Node() {
	this->data = this->x = this->y = 0;
	this->right = this->down = nullptr;
}

template <typename T> void myMatrix <T>:: connect() {
	rep(i, 1, n) tmp[i] = this->Row[i];
	rep(j, 1, m) {
		rep(i, 1, n) {
			while (tmp[i]->right->y <= j) tmp[i] = tmp[i]->right;
		}
		Node <T> *last = this->Col[j];
		rep(i, 1, n) {
			if (tmp[i]->y == j) {
				tmp[i]->down = last->down;
				last->down = tmp[i];
				last = tmp[i];
			}
		}
	}
	rep(i, 1, n) tmp[i] = nullptr;
}

template <typename T> void myMatrix <T>:: init(int n, int m) {
	this->n = n, this->m = m;
	rep(i, 0, n + 1) this->Row[i] = nullptr;
	rep(i, 0, m + 1) this->Col[i] = nullptr;

	rep(j, 1, m) {
		this->Col[j] = new Node <T> (0, j, 0);
		this->Col[j]->down = new Node <T> (n + 1, j, 0);
	}
	rep(j, 1, m - 1) {
		this->Col[j]->right = this->Col[j + 1];
		this->Col[j]->down->right = this->Col[j]->right->down;
	}

	rep(i, 1, n) {
		this->Row[i] = new Node <T> (i, 0, 0);
		this->Row[i]->right = new Node <T> (i, m + 1, 0);
	}
	rep(i, 1, n - 1) {
		this->Row[i]->down = this->Row[i + 1];
		this->Row[i]->right->down = this->Row[i]->down->right;
	}
}

template <typename T> myMatrix <T>:: myMatrix(const int &n, const int &m) {
	this->init(n, m);
}

template <typename T> myMatrix <T>:: myMatrix(const myMatrix <T> &B) {
	this->n = this->m = 0;
	*this = B;
}

template <typename T> myMatrix <T>:: ~myMatrix() {
	if (!this->m && !this->n) return ;
	std:: queue <Node <T> *> que;

	rep(i, 1, this->m) {
		if (this->Col[i] != nullptr) {
			que.push(this->Col[i]);
			auto it = this->Col[i];
			while (it->down != nullptr) it = it->down;
			que.push(it);
		}
	}

	rep(i, 1, this->n) {
		auto it = this->Row[i];
		while (it != nullptr) {
			que.push(it);
			it = it->right;
		}
	}

	rep(i, 0, this->n + 1) this->Row[i] = nullptr;
	rep(i, 0, this->m + 1) this->Col[i] = nullptr;
	rep(i, 0, this->m + 1) this->tmp[i] = nullptr;

	for (Node <T> *it; !que.empty(); que.pop()) {
		it = que.front();
		delete it;
	}
}

template <typename T> myMatrix <T>& myMatrix <T>:: operator = (const myMatrix <T> &B) {
	if (this == &B) return *this;
	this->~myMatrix();
	this->init(B.n, B.m);

	Node <T> *A_x, *B_x;
	
	rep(i, 1, this->n) {
		A_x = this->Row[i];
		B_x = B.Row[i]->right;

		while (B_x->y <= this->m) {
			Node <T> *new_node = new Node <T> (B_x->x, B_x->y, B_x->data);
			A_x->insertHorizonal(new_node);
			
			A_x = A_x->right, B_x = B_x->right;
		}
	}

	this->connect();
	return *this;
}

template <typename T> myMatrix <T> myMatrix <T>:: operator + (const myMatrix <T> &B) {
	if (this->n != B.n || this->m != B.m) return *this;
	Node <T> *A_x, *B_x, *C_x;
	
	myMatrix C(B.n, B.m);
	rep(i, 1, B.n) {
		A_x = this->Row[i]->right, B_x = B.Row[i]->right;
		C_x = C.Row[i];

		while (A_x->y <= B.m || B_x->y <= B.m) {
			bool flag = true;
			if (A_x->y == B_x->y) {
				T sum = (A_x->data + B_x->data) % MOD;
				if (sum) {
					Node <T> *new_node = new Node <T> (A_x->x, A_x->y, sum);
					C_x->insertHorizonal(new_node);
				} else flag = false;
				
				A_x = A_x->right, B_x = B_x->right;
			} else if (A_x->y < B_x->y) {
				Node <T> *new_node = new Node <T> (A_x->x, A_x->y, A_x->data);
				C_x->insertHorizonal(new_node);

				A_x = A_x->right;
			} else {
				Node <T> *new_node = new Node <T> (B_x->x, B_x->y, B_x->data);
				C_x->insertHorizonal(new_node);

				B_x = B_x->right;
			}
			if (flag) C_x = C_x->right;
		}
	}

	C.connect();
	return C;
}

template <typename T> myMatrix <T> myMatrix <T>:: operator - (const myMatrix <T> &B) {
	if (this->n != B.n || this->m != B.m) return *this;
	Node <T> *A_x, *B_x, *C_x;
	
	myMatrix C(B.n, B.m);
	rep(i, 1, B.n) {
		A_x = this->Row[i]->right, B_x = B.Row[i]->right;
		C_x = C.Row[i];

		while (A_x->y <= B.m || B_x->y <= B.m) {
			bool flag = true;
			if (A_x->y == B_x->y) {
				if (A_x->data - B_x->data) {
					Node <T> *new_node = new Node <T> (A_x->x, A_x->y, A_x->data - B_x->data);
					C_x->insertHorizonal(new_node);
				} else flag = false;
				
				A_x = A_x->right, B_x = B_x->right;
			} else if (A_x->y < B_x->y) {
				Node <T> *new_node = new Node <T> (A_x->x, A_x->y, A_x->data);
				C_x->insertHorizonal(new_node);

				A_x = A_x->right;
			} else {
				Node <T> *new_node = new Node <T> (B_x->x, B_x->y, -B_x->data);
				C_x->insertHorizonal(new_node);

				B_x = B_x->right;
			}
			if (flag) C_x = C_x->right;
		}
	}

	C.connect();
	return C;
}

template <typename T> myMatrix <T> myMatrix <T>:: operator *= (const myMatrix <T> &B) {
	if (this->m != B.n) return *this;

	myMatrix <T> *C = new myMatrix <T>(this->n, B.m);
	rep(i, 1, this->n) {
		Node <T> *tc = C->Row[i];
		rep(j, 1, B.m) {
			Node <T> *ta, *tb;
			LL sum = 0;
			ta = this->Row[i]->right;
			tb = B.Col[j]->down;
			while ( (ta->y != this->m + 1) || (tb->x != B.n + 1) ) {
				while (ta->y != tb->x) {
					if (ta->y < tb->x) ta = ta->right;
					else if (ta->y > tb->x) tb = tb->down;
				}
				if (ta->y <= this->m) sum = (sum + ta->data * tb->data % MOD) % MOD;
				if (ta->y <= this->m) ta = ta->right;
				if (tb->x <= B.n) tb = tb->down;
			}
			if (sum != 0) {
				Node <T> *new_node = new Node <T>(i, j, sum);
				tc->insertHorizonal(new_node);
				tc = tc->right;
			}
		}
	}

	C->connect();
	*this = *C; delete C;
	return *this;
}

template <typename T> std:: ostream& operator << (std:: ostream &out, const myMatrix <T> &A)  {
	rep(i, 1, A.n) {
		if (A.Row[i]->right->y == A.m + 1) {
			rep(j, 1, A.m) out << "0 ";
		} else {
			Node <T> *t_it = A.Row[i]->right;
			rep(j, 1, A.m) {
				for (; j < t_it->y; ++ j) out << "0 ";
				if (j != A.m + 1) out << t_it->data << " ";
				t_it = t_it->right;
			}
		}
		out << std:: endl;
	}
	return out;
}

template <typename T> void myMatrix <T>:: set(int x, int y, T val) {
	Node <T> *A_x = this->Row[x], *A_y = this->Col[y];

	while (A_x->right->y < y) A_x = A_x->right;
	while (A_y->down->x < x) A_y = A_y->down;

	if (A_x->right->y == y || A_y->down->x == x) {
		return (void) (A_x->right->data = val);
	}

	Node <T> *p = new Node <T> (x, y, val);
	A_x->insertHorizonal(p);
	A_y->insertVertical(p);
}


#endif
