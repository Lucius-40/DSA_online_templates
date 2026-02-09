#pragma once
#include<bits/stdc++.h>
#include "utils.hpp"

using namespace std ;
// run the batch file to execute

namespace Hash2Impl {

template<class K , class V>
class HashTable_Chaining{
    int size ;
    int elements ;
    int track_insert ;
    int track_delete ;
    int last_resize = 0 ;
    int total_collisions = 0 ;
    int total_hits = 0 ;
    int search_count = 0 ;
    vector<vector<pair<K,V>>> table ;
    int index(const K& key){
        return Hash2(key)%size ;// metro hash
    }

    void rehash(bool larger) {
        int newSize;
        if (larger) {
            newSize = nextPrime(size * 2); 
        } else {
            newSize = prevPrime(size / 2); 
        }

        vector<vector<pair<K,V>>> newTable(newSize);
        int prev_size = size ;
        size = newSize;
        last_resize = elements ;
        for (int i = 0; i < prev_size; i++) {
            for (const auto& kv : table[i]) {
                int newIdx = index(kv.first);
                newTable[newIdx].push_back(kv);
                if(newTable[newIdx].size() > 1)total_collisions++ ;
            }
        }
        table.swap(newTable);
        track_delete = 0 ;
        track_insert = 0 ;
        
    }

    public :
    HashTable_Chaining(){
        size = INITIAL_SIZE ;
        elements = 0 ;
        table.resize(INITIAL_SIZE);
        track_insert = 0 ;
        track_delete = 0 ;
    }

    void insert(const K& key, const V& value) {
        
        int idx = index(key);
        for (auto& kv : table[idx]) {
            
            if (kv.first == key) {
               return;
            }
        }
        if (!table[idx].empty()) {
            total_collisions++;
        }
        table[idx].push_back({key, value});
        elements++;
        track_insert ++ ;
        double load_factor = ((double)elements/ size);
        if(load_factor > LOAD_FACTOR_MAX and track_insert >= (last_resize/2) ){
            rehash(true);
        }
    }

    bool search(const K& key, V& outValue){
        int idx = index(key);
        int hits = 0;
        for (const auto& kv : table[idx]) {
            hits++;
            if (kv.first == key) {
                outValue = kv.second;
                total_hits += hits;
                search_count++;
                return true;
            }
        }
        return false;
    }

    void remove(const K& key) {
        int idx = index(key);
        for (auto it = table[idx].begin(); it != table[idx].end(); it++) {
            if (it->first == key) {
                table[idx].erase(it);
                elements-- ;
                track_delete ++ ;
                double load_factor = ((double)elements/size) ;
                if(load_factor < LOAD_FACTOR_MIN and track_delete >= (last_resize/2) and size > 13){
                    rehash(false);
                }
                return;
            }
        }
    }

    bool update(const K& key, const V& value) {
        int idx = index(key);
        for (auto& kv : table[idx]) {
            if (kv.first == key) {
                kv.second = value;
                return true;
            }
        }
        return false;
    }

    void display() {
        cout << "\nHash Table:\n" << endl;
        cout << "Table Size: " << size << " | Elements: " << elements << endl;
        cout << "Load Factor: " << ((double)elements / size) << endl;
        cout << "\n" << endl;
        
        int bucket_num = 0;
        for (int i = 0; i < size; i++) {
            if (!table[i].empty()) {
                cout << "Bucket " << i << ": ";
                for (const auto& kv : table[i]) {
                    cout << "(" << kv.first << ", " << kv.second << ") ";
                }
                cout << endl;
            }
        }
        cout << endl;
    }

    int getCollisions() const { return total_collisions; }
    double getAvgHits() const { return search_count > 0 ? (double)total_hits / search_count : 0.0; }
    void resetStats() { total_collisions = 0; total_hits = 0; search_count = 0; }

};



template <typename K, typename V>
class HashTable_DoubleHashing {
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
    vector<Entry> table;
    int prev(int n) const {
        if(n <= 3) 
            return 3 ;
        while (n > 2 && !isPrime(n)) 
            n--;
        if(n <= 3)
            return 3 ;
        else 
            return n;
    }

    int primaryHash(const K& key) const {
        return Hash2(key) % size; //  Metrohash
    }

    // int auxHash(const K& key) const {
    //     int R = prev(size);
    //     hash<K> hasher ;
    //     size_t hash_value = hasher(key);
    //     return R - (hash_value % R); 
    // }
    int auxHash(const K& key) const {
        int R = prev(size);
        uint64_t h = Hash1(key);
        h ^= (h >> 33);
        h *= 0xff51afd7ed558ccdULL;
        h ^= (h >> 33);
        return max(1, (int)(h % R));
    }

    int probeIndex(const K& key, int i) const {
        return (primaryHash(key) + i * auxHash(key)) % size;
    }

    void rehash(bool larger) {
        int newSize;
        if (larger) {
            newSize = nextPrime(size * 2); 
        } else {
            newSize = prevPrime(size / 2); 
        }
        vector<Entry> newTable(newSize);
        int prev_size = size;
        size = newSize;
        last_resize = elements;

        for (int i = 0; i < prev_size; i++) {
            if (table[i].occupied) {
                const K& key = table[i].key;
                const V& value = table[i].value;
                for (int j = 0; j < newSize; j++) {
                    int idx = probeIndex(key, j);  
                    if(j > 0) total_collisions++ ;
                    if (!newTable[idx].occupied) {
                        newTable[idx].key = key;
                        newTable[idx].value = value;
                        newTable[idx].occupied = true;
                        newTable[idx].deleted = false;
                        break;
                    }
                }
            }
        }
        table.swap(newTable);
        track_insert = 0;
        track_delete = 0;
    }

public:
    HashTable_DoubleHashing() {
        size = INITIAL_SIZE;
        elements = 0;
        track_insert = 0;
        track_delete = 0;
        last_resize = 0;
        table.resize(size);
    }

    void insert(const K& key, const V& value) {
        //bool flag = false ;
        for (int i = 0; i < size; i++) {
            int idx = probeIndex(key, i);
            if (table[idx].occupied && table[idx].key == key) {
                return; //dup
            }
            if (i > 0) total_collisions++ ;
            if (!table[idx].occupied || table[idx].deleted) {
                table[idx].key = key;
                table[idx].value = value;
                table[idx].occupied = true;
                table[idx].deleted = false;
                elements++;
                track_insert++;
                break;
            }
        }
        //if(flag) total_collisions ++ ;
        double load_factor = (double)elements / size;
        if (load_factor > LOAD_FACTOR_MAX && track_insert >= (last_resize / 2)) {
            rehash(true);
        }
    }

    bool search(const K& key, V& outValue) {
        for (int i = 0; i < size; i++) {
            int idx = probeIndex(key, i);
            if (!table[idx].occupied && !table[idx].deleted) {
                return false; // empty slot, stop
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

    void remove(const K& key) {
        for (int i = 0; i < size; i++) {
            int idx = probeIndex(key, i);
            if (!table[idx].occupied && !table[idx].deleted) {
                return; 
            }
            if (table[idx].occupied && table[idx].key == key) {
                table[idx].deleted = true;
                table[idx].occupied = false;
                elements--;
                track_delete++;
                double load_factor = (double)elements / size;
                if (load_factor < LOAD_FACTOR_MIN && track_delete >= (last_resize / 2) && size > INITIAL_SIZE) {
                    rehash(false);
                }
                return;
            }
        }
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
        std::cout << "\nHash Table (Double hashing):\n";
        std::cout << "Table size: " << size << " | elements: " << elements << "\n";
        std::cout << "Load factor: " << ((double)elements / size) << "\n\n";
        for (int i = 0; i < size; i++) {
            if (table[i].occupied) {
                std::cout << "Slot " << i << ": (" << table[i].key << ", " << table[i].value << ")\n";
            }
        }
        std::cout << std::endl;
    }

    int getCollisions() const { return total_collisions; }
    double getAvgHits() const { return search_count > 0 ? (double)total_hits / search_count : 0.0; }
    void resetStats() { total_collisions = 0; total_hits = 0; search_count = 0; }
};


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
    std::vector<Entry> table;

    // User-defined constants
    const int C1 = 5;  
    const int C2 = 3;

    int prev(int n) const {
        if (n <= 3) return 3;
        while (n > 2 && !isPrime(n)) n--;
        return (n <= 3) ? 3 : n;
    }

    int primaryHash(const K& key) const {
        return Hash2(key) % size; // e.g., MetroHash
    }

    int auxHash(const K& key) const {
        int R = prev(size);
        std::hash<K> hasher;
        size_t hash_value = hasher(key);
        return R - (hash_value % R);
    }

    // Custom probing sequence
    int probeIndex(const K& key, int i) const {
        return (primaryHash(key) + C1 * i * auxHash(key) + C2 * i * i) % size;
    }

    void rehash(bool larger) {
        int newSize;
        if (larger) {
            newSize = nextPrime(size * 2); 
        } else {
            newSize = prevPrime(size / 2); 
        }
        vector<Entry> newTable(newSize);
        int prev_size = size;
        size = newSize;
        last_resize = elements;

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
                        break;
                    }
                }
            }
        }
        table.swap(newTable);
        track_insert = 0;
        track_delete = 0;
    }

public:
    HashTable_CustomProbing() {
        size = INITIAL_SIZE;
        elements = 0;
        track_insert = 0;
        track_delete = 0;
        last_resize = 0;
        table.resize(size);
    }

    void insert(const K& key, const V& value) {
        //bool flag = false ;
        for (int i = 0; i < size; i++) {
            int idx = probeIndex(key, i);
            if (table[idx].occupied && table[idx].key == key) {
                return; // duplicate
            }
            if (i > 0) total_collisions++;
            if (!table[idx].occupied || table[idx].deleted) {
                table[idx].key = key;
                table[idx].value = value;
                table[idx].occupied = true;
                table[idx].deleted = false;
                elements++;
                track_insert++;
                break;
            }
        }
        //if(flag)total_collisions ++ ;
        double load_factor = (double)elements / size;
        if (load_factor > LOAD_FACTOR_MAX && track_insert >= (last_resize / 2)) {
            rehash(true);
        }
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

    void remove(const K& key) {
        for (int i = 0; i < size; i++) {
            int idx = probeIndex(key, i);
            if (!table[idx].occupied && !table[idx].deleted) {
                return;
            }
            if (table[idx].occupied && table[idx].key == key) {
                table[idx].deleted = true;
                table[idx].occupied = false;
                elements--;
                track_delete++;
                double load_factor = (double)elements / size;
                if (load_factor < LOAD_FACTOR_MIN && track_delete >= (last_resize / 2) && size > INITIAL_SIZE) {
                    rehash(false);
                }
                return;
            }
        }
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

} // namespace Hash2Impl
