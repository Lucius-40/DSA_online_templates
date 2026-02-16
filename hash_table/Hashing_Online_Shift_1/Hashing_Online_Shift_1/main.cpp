#include "hashTable/utils.hpp"
#include<bits/stdc++.h>

using namespace std ;

template <typename K, typename V>
class HashTable_CustomProbing {

    
    struct Entry {
        K key;
        V value;
        bool occupied;
        bool deleted;
        Entry(){
            occupied = false ;
            deleted = false ;
        }
    };


    int size;
    int elements;
    int track_insert;
    int track_delete;
    int last_resize;
    int total_collisions = 0;
    int total_hits = 0;
    int search_count = 0;
    int P_MAX ;
    int max_probe ;
    std::vector<Entry> table;

    // User-defined constants
   

    int prev(int n) const {
        if (n <= 3) return 3;
        while (n > 2 && !isPrime(n)) n--;
        return (n <= 3) ? 3 : n;
    }

    int primaryHash(const K& key) const {
        // return Hash2(key) % size; // e.g., MetroHash
        return key ;
    }


    // Custom probing sequence
    int probeIndex(const K& key, int i) const {
        return (primaryHash(key) + (i * i)) % size;
    }

    /*
    Table Size: <old_size> 
Active Processes: <occupied_count> 
Load Factor: <load_factor> 
Max Probe Sequence: <max_probe_count> 
--- Rehash Triggered: AFTER --- 
Table Size: <new_size> 
Active Processes: <occupied_count> 
Load Factor: <load_factor> 
Max Probe Sequence: <max_probe_count>
    */
    void rehash(bool larger , pair<int,int> data = {-1,-1}) {
        if(larger){
            cout << "--- Rehash Triggered: BEFORE --- "<<endl ;
            cout << "Table Size : "<< size << endl ;
            cout << "Active Processes :"<< elements ;
            cout <<"\nLoad Factor : "<< (double)elements/size <<endl ;
            cout <<"Max probe sequence : "<< P_MAX << endl ;

        }
        else {
            cout << "FREE "<<data.first<<": Freed from index "<< data.second <<endl ;
            cout << "--- Rehash Triggered: BEFORE --- "<<endl ;
            cout << "Table Size : "<< size << endl ;
            cout << "Active Processes :"<< elements ;
            cout <<"\nLoad Factor : "<< (double)elements/size <<endl ;
            cout <<"Max probe sequence : "<< max_probe << endl ;
        }
        int newSize;
        if (larger) {
            newSize = nextPrime(size * 2); 
        } else {
            newSize = prev(ceil((double)size / 2)); 
        }
        vector<Entry> newTable(newSize);
        int prev_size = size;
        size = newSize;
        last_resize = elements;
        max_probe = 1 ;

        for (int i = 0; i < prev_size; i++) {
            
            if (table[i].occupied) {
                const K& key = table[i].key;
                const V& value = table[i].value;
                for (int j = 0; j < newSize; j++) {
                    int idx = probeIndex(key, j);
                    if(j > 0)total_collisions++ ;
                    if (!newTable[idx].occupied) {
                        newTable[idx].key = key;
                        newTable[idx].value = value;
                        newTable[idx].occupied = true;
                        newTable[idx].deleted = false;
                        max_probe = max(max_probe, j+ 1);
                        break;
                    }
                }
            }
        }
        table.swap(newTable);
        track_insert = 0;
        track_delete = 0;

        
            cout << "--- Rehash Triggered: AFTER --- "<<endl ;
            cout << "Table Size : "<< size << endl ;
            cout << "Active Processes :"<< elements ;
            cout <<"\nLoad Factor : "<< (double)elements/size <<endl ;
            cout <<"Max probe sequence : "<< max_probe << endl ;
        
    }

public:
    HashTable_CustomProbing(int P=5, int n =INITIAL_SIZE) {
        size = n;
        elements = 0;
        track_insert = 0;
        track_delete = 0;
        last_resize = 0;
        table.resize(size);
        P_MAX= P ;
        max_probe = 1 ;
    }

    vector<int> insert(const K& key, const V& value) {
        //bool flag = false ;
        for (int i = 0; i < size; i++) {
            
            int idx = probeIndex(key, i);
            if (table[idx].occupied && table[idx].key == key) {
                return {0,0,0}; // duplicate
            }
            if (i > 0) total_collisions++;
            if (!table[idx].occupied || table[idx].deleted) {
                table[idx].key = key;
                table[idx].value = value;
                table[idx].occupied = true;
                table[idx].deleted = false;
                elements++;
                track_insert++;
                max_probe = max(max_probe, i+1 );
                cout << "ALLOCATE "<<key<<": inserted at index  "<< idx <<" probes : "<<i+1 <<endl ;
                if(max_probe > P_MAX) rehash(true);
                return {1, i+1 , idx};
                
            }
        }
        //if(flag)total_collisions ++ ;
        // double load_factor = (double)elements / size;
        // if (load_factor > LOAD_FACTOR_MAX && track_insert >= (last_resize / 2)) {
        //     rehash(true);
        // }
        return {0,0,0};
    }

    bool search(const K& key, V& outValue) {
        for (int i = 0; i < size; i++) {
            int idx = probeIndex(key, i);
            if (!table[idx].occupied && !table[idx].deleted) {
                return false;
            }
            if (table[idx].occupied && table[idx].key == key) {
                total_hits += (i + 1);
                search_count++;
                outValue = table[idx].value;
                return true;
            }
        }
        return false;
    }

    int remove(const K& key) {
        for (int i = 0; i < size; i++) {
            int idx = probeIndex(key, i);
            if (!table[idx].occupied && !table[idx].deleted) {
                return -1;
            }
            if (table[idx].occupied && table[idx].key == key) {
                table[idx].deleted = true;
                table[idx].occupied = false;
                elements--;
                track_delete++;
                double load_factor = (double)elements / size;
                if (load_factor < LOAD_FACTOR_MIN && track_delete >= 5 and size > INITIAL_SIZE) {
                    rehash(false, {(int)key , idx});
                    return -2 ;
                }
                return idx ;
            }
        }
        return -1 ;
    }

    bool update(const K& key, const V& value) {
        for (int i = 0; i < size; i++) {
            int idx = probeIndex(key, i);
            if (!table[idx].occupied && !table[idx].deleted) {
                return false;
            }
            if (table[idx].occupied && table[idx].key == key) {
                table[idx].value = value;
                return true;
            }
        }
        return false;
    }

    void display() {
        cout << "\nHash Table (Custom Probing):\n";
        cout << "Table size: " << size << " | elements: " << elements << "\n";
        cout << "Load factor: " << ((double)elements / size) << "\n\n";
        for (int i = 0; i < size; i++) {
            if (table[i].occupied) {
                cout << "Slot " << i << ": (" << table[i].key << ", " << table[i].value << ")\n";
            }
        }
        cout <<endl;
    }

    int getCollisions() const { return total_collisions; }
    double getAvgHits() const { return search_count > 0 ? (double)total_hits / search_count : 0.0; }
    void resetStats() { total_collisions = 0; total_hits = 0; search_count = 0; }
};

int main(){
    freopen("input2.txt", "r", stdin);
    freopen("output.txt", "w",stdout);
    int N , P_MAX , Q ;
    cin >> N >> P_MAX>> Q ;
    HashTable_CustomProbing <int, int> table(P_MAX, N) ;
    for(int i =0 ; i < Q ; i++){
        string input ;int id ;
        cin >> input >>id;
        if(input == "ALLOCATE"){
            table.insert(id, id);
        }
        else {
            int res = table.remove(id);
            if(res >= 0){
                cout << "FREE "<<id<<": Freed from index "<< res <<endl ;
            }
        }
    }

}