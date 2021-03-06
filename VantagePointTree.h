include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <limits>

using namespace std;

template <typename T>
class VantagePointTree
{
    struct Nodo {
        int vpoint;
        double radio;
        Nodo * left;
        Nodo * right;
		
		Nodo () : vpoint(0), radio(0), left(0), right(0) {}
	};

	struct heap_item {
		int vpoint;
		double distancia;

		heap_item (long vpoint_, double distancia_) : vpoint(vpoint_), distancia(distancia_) {}

		bool operator < (const heap_item& a) const {
              return distancia < a.distancia;
        }

	};

    Nodo* root;
	vector<T> dirs;
	double guide;

	void search_in_node (Nodo *node, T &to_find, int k, priority_queue<heap_item> &heap, void (*d_func)(T, T)) {
		if (node == nullptr) return;

		double distancia = d_func (dirs[node->vpoint], to_find);

		if (node->right == nullptr && node->left == nullptr) return;

		if (distancia < guide) {
			if (heap.size() == k) heap.pop ();
			
			heap.push(heap_item(node->vpoint, distancia));

			if (heap.size() == k) guide = heap.top().distancia;
		}

		if (distancia < node->radio) {
			if (distancia - guide <= node->radio) search_in_node(node->left, to_find, heap, d_func);

			if (distancia + guide >= node->radio) search_in_node(node->right, to_find, heap, d_func);
		}

		else {
			if (distancia + guide >= node->radio) search_in_node(node->right, to_find, heap, d_func);

			if (distancia - guide <= node->radio) search_in_node(node->left, to_find, heap, d_func);
		}
	}

public:
	Nodo* insert (int low, int up, void (* d_func)(T, T)) {
		if (low == up) return;

		Nodo *new_node = new Nodo;
		new_node->vpoint = low;

		if (up - low > 1) {
			// choose random point and then bring it to the front
			int tmp = rand() % up; // tengo dudas de esto
			swap(dirs[low], dirs[tmp]);

			int middle = (low + up) / 2;
			
			// partion of the vector
			part_by_distance (low, up, middle, d_func);

			new_node->radio = d_func(dirs[low], dirs[middle]);

			new_node->left = insert(low + 1, middle, d_func);
			new_node->right = insert(middle, up, d_func);
		}

		return new_node;
	}

	void part_by_distance(int low, int up, int middle, void (*d_func)(T, T)) {
		std::nth_element(
			dirs.begin() + low + 1,
			dirs.begin() + middle,
			dirs.begin() + up,
			[low, this] (const T& a, T& b) {
				return d_func (dirs[low], a) < d_func (dirs[low], b);
			}
        );
	}


	vector<T> search (T &to_find, int k, void (*d_func)(T, T)) {
		guide = numeric_limits<double>::max(); // set the guide to inf.
		
		vector<T> results;
		priority_queue<heap_item> heap;
		search_in_node (root, target, k, heap, void (*d_func)(long, long));
	
		while (heap.size() > 0) {
			results.push_back(dirs[heap.top().vpoint]);
			heap.pop();
		}

		reverse(results.begin(), results.end());

		return results;
	}



    VantagePointTree (vector<T> dirs_, void (* d_func)(T, T)) {
		dirs = dirs_;
        root = insert(0, dirs.size(), d_func);
    }
};
