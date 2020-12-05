#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
#include <priority_queue>

template <typename T>
class VantagePointTree
{
    struct Nodo {
        long vpoint;
        unsigned double radio;                
        Nodo * left;
        Nodo * right;
		
		Nodo () : vpoint(0), radio(0), left(0), rigth(0) {}
	};

    Nodo* root;
	vector<long> dirs;

public:
	Nodo* insert (int down, int up, void (* d_func)(long, long)) {
		if (down == up) return;

		Nodo *new_node = new Nodo;
		new_node->vpoint = down;

		if (up - low > 1) {
			// choose random point and then bring it to the front
			int tmp = rand() % up; // tengo dudas de esto
			swap(dirs[low], dirs[tmp]);

			int middle = (low + up) / 2;

			part_by_distance (low, up, middle, d_func);

			new_node->radio = d_func(dirs[low], dirs[middle]);

			new_node->left = insert(down + 1, middle, d_func);
			new_node->right = insert(middle, up, d_func);
		}

		return new_node;
	}

	vector<long> (int low, int up, int middle, void (*d_func)(long, long)) {
		std::nth_element(
			dirs.begin() + low + 1,
			dirs.begin() + middle,
			dirs.begin() + up,
			[low, this] (const T& a, T& b) {
				return d_func (dirs[low], a) < d_func (dirs[low], b);
			}
        );
	}


	vector<long> all_distances(long vp, vector<long> dirs, void (* d_func)(long, long)) {
            vector<long> distances;
            for (auto d: dirs){
                distances.push_back((long) d_func(vp, d));
            }
            return distances;
    }


	void search (Nodo *node, T &to_find, int i, std::priority_queue& heap) {
		if
	}



    VantagePointTree (vector<long> dirs_, void (* d_func)(long, long)) {
		dirs = dirs_;
        root = insert(0, dirs.size(), d_func);
    }
};
