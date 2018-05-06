

// Algo
// 			successor( (n + 2^i) mod 2^m )

int consistent_hash(int n, int i, int m) {
    return ((n + static_cast<int>(pow(2,i))) % static_cast<int>(pow(2,m)));
}
int succ(int id, int hashVal, vector<int> nodes) {
    for(int i=0; i<nodes.size()-1; ++i) {
        if(hashVal>nodes[i] && hashVal<=nodes[i+1] && id!=nodes[i+1]) {
            return nodes[i+1];
        }
    }
    if(nodes[0] != id) {
        return nodes[0];
    }
    return nodes[1];
}

// Build finger tables
unordered_map<int, map<int,int>> build(int m, vector<int> nodes) {
    unordered_map<int, map<int,int>> tables;

    // Sort
    sort(nodes.begin(), nodes.end()); 

    for(int t=0; t<nodes.size(); ++t) {
        map<int, int> table;
        for(int i=0; i<m; ++i) {
            table.insert({i, succ(nodes[t], consistent_hash(nodes[t], i, m), nodes)});
        }
        tables.insert({nodes[t], table});
    }

    return tables;
}
