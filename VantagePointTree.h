#include <iostream>
#include <vector>
template <typename T>
class VantagePointTree
{
    struct Nodo {

        vector<long>puntos_id;
        long vp;
        unsigned int radio;                
        Nodo * left;
        Nodo * right;

        void insert (vector<long> dirs, void (* d_func)(long, long)) {
            if (dirs.empty()) return;
            this->puntos_id = dirs;
            
            size_t n = dirs.size();
            this->vp = dirs[rand() % n];
            auto distances = all_distances(root->vp, dirs, d_func);
            long suma = 0;
            for (auto d: distances)
                suma += d;
            this->radio = suma/n;
            
            vector<long> left_point;
            vector<long> right_point;
            for (int i = 0; i < n; i++) {
                if (distances[i] < radio){
                    left_point->puntos_id.push_back(dirs[i]);
                } else {
                    right_point->puntos_id.push_back(dirs[i]);
                }
            }

            Nodo* left = new Nodo();
            left->insert(left_point, d_func);
            this->left = left;

            Nodo* right = new Nodo();
            right->insert(right_point, d_func);
            this->right = right;
        }
        vector<long> all_distances(long vp, vector<long> dirs, void (* d_func)(long, long)) {
            vector<long> distances;
            for (auto d: dirs){
                distances.push_back((long) d_func(vp, d));
            }
            return distances;
        }

    };


        


    Nodo* root;

public:

    VantagePointTree (vector<long> dirs, void (* d_func)(long, long)) {
        root->insert(dirs, d_func);
    }
};