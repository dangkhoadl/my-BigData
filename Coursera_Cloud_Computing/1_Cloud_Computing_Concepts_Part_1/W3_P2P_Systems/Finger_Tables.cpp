

// Algo
// 			successor( (n + 2^i) mod 2^m )

class Chord {
private:
    // Chord config Parameters
    int m;
    vector<int> nodes;

    // Finger tables
    //      node_id: 
    //          (0, next_node)
    //          (1, next_node)
    //               ...
    //          (m-1, next_node)
    unordered_map<int, map<int,int>> finger_table;
private:
    inline int pow2(int k) {
        return (1 << k);
    }
    int hash(int n, int i) {
        return (n + pow2(i)) % pow2(m);
    }
    int succ(int hash_val) { // O(log(n))
        auto it = upper_bound(nodes.begin(), nodes.end(), hash_val);

        // If hash_val == node: return node
        if(it != nodes.begin() && *prev(it) == hash_val) return hash_val;

        // Else Return successor
        return it == nodes.end() ? nodes[0] : *it;
    }
public:
    // Config
    Chord(vector<int> nodes, int m) : nodes(nodes), m(m) {
        // Sort Nodes increasing
        sort(this->nodes.begin(), this->nodes.end());

        // build Finger table
        this->finger_table.clear();
        this->build_finger_table();
    }
    void build_finger_table() {
        for(const auto &node: nodes) {
            map<int, int> entry;
            int next_node;

            for(int i=0; i<m; ++i) {
                next_node = succ(hash(node, i)); 
                entry[i] = next_node;
            }

            finger_table[node] = entry;
        }
    }
};
