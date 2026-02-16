#include<bits/stdc++.h> 
#include"hash_table/utils.hpp"
using namespace std ;

template <typename K, typename V>
class CustomProbing1 {
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
        return Hash1(key) % size; // e.g., MetroHash
    }

    // int auxHash(const K& key) const {
    //     int R = prev(size);
        
    //     int hash_value = Hash1(key)%R;
    //     return R - (hash_value % R);
    // }
    int auxHash(const K& key) const {
        int R = prev(size);
        uint64_t h = Hash1(key);
        h = (h * 31 + 17) * 2654435761ULL;  
        return max(1, (int)(h % R));
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
    CustomProbing1(int n = INITIAL_SIZE) {
        size = n;
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
        cout << endl;
    }

    int getCollisions() const { return total_collisions; }
    double getAvgHits() const { return search_count > 0 ? (double)total_hits / search_count : 0.0; }
    void resetStats() { total_collisions = 0; total_hits = 0; search_count = 0; }
};



template <typename K, typename V>
class CustomProbing2 {

    
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
    CustomProbing2(int n = INITIAL_SIZE) {
        size = n;
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
       
        for (int i = 0; i < size; i++) {
            if (table[i].occupied) {
                cout<< "(" << table[i].key << ", " << table[i].value << ")\n";
            }
        }
        cout <<endl;
    }

    int getCollisions() const { return total_collisions; }
    double getAvgHits() const { return search_count > 0 ? (double)total_hits / search_count : 0.0; }
    void resetStats() { total_collisions = 0; total_hits = 0; search_count = 0; }
};

int main(){
    cin.tie(nullptr);
    int N , Q ;
    cin >> N >> Q ;

    CustomProbing1 <int , CustomProbing2<int, string> *> table(N) ;
    for(int i = 0 ; i < Q ; i++){
        string line ;
        getline(cin >> ws , line);
        string action ;
        istringstream iss(line);
        iss >> action ;
        if(action == "INSERT"){
            int a ,b ;
            string c ;
            iss >> a >> b >> c ;
            CustomProbing2<int, string>* temp = nullptr;
            bool exists = table.search(a, temp);
            if(!exists){
                temp = new CustomProbing2<int, string>(N);
                table.insert(a, temp);
            }
            temp->insert(b,c);
        }
 
        else if (action == "DELETE"){
            int group, user ;
            iss >> group >> user ;
            CustomProbing2<int, string>* temp = nullptr ;
            bool exists = table.search(group, temp);
            if(exists){
                string perm ;
                bool exists =temp->search(user, perm);
                if(exists){
                    cout << "("<<user << " , "<<perm <<") deleted\n";
                }
                temp->remove(user);
            }
        }
        else if (action == "SEARCH"){
            int group , user ;
            iss >> group ;
            CustomProbing2<int, string>* temp = nullptr ;
            bool exists = table.search(group, temp);
            if(!exists){cout << "group does not exist \n";}
            if(iss >> user){
                string perm ;
                bool flag = temp->search(user,perm);
                if(flag){
                    cout << perm <<endl ;
                }
                else {
                    cout << "User not found \n";
                }
            }
            else {
                temp->display();
            }
        }
    }
}