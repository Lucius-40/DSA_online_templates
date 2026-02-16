#pragma once

#include<bits/stdc++.h>
#include "hash_functions/metroHash/metrohash64.h"
#include "hash_functions/MurMur hash/MurmurHash3.h"

using namespace std ;

#define INITIAL_SIZE 13
#define LOAD_FACTOR_MAX 0.5
#define LOAD_FACTOR_MIN 0.2
#define HASH_SEED 42

bool isPrime(int n) {
    if (n < 2) return false;
    for (int i = 2; i*i <= n; i++)
        if (n % i == 0) return 0;
    return true;
}

int nextPrime(int n) {
    while (!isPrime(n)) n++;
    return n;
}

int prevPrime(int n) {
    if(n <= INITIAL_SIZE) 
        return INITIAL_SIZE ;
    while (n > 2 && !isPrime(n)) 
        n--;
    if(n <= INITIAL_SIZE)
        return INITIAL_SIZE ;
    else 
        return n;
}




vector<string> generate_unique_words(int count = 10000, int length = 10) {
    static bool seeded = false;
    if (!seeded) {
        srand(42);
        seeded = true;
    }
    
    set<string> unique_set;
    while ((int)unique_set.size() < count) {
        string s;
        for (int i = 0; i < length; i++)
            s.push_back('a' + rand() % 26);
        unique_set.insert(s); // Duplicates automatically ignored
    }
    
    return vector<string>(unique_set.begin(), unique_set.end());
}



// Hash1 using XXHash64
// template<typename T>
// uint64_t Hash1(const T& k) {
//     return XXHash64::hash(&k, sizeof(T), HASH_SEED);
// }

// Specialization for string
// template<>
// inline uint64_t Hash1<string>(const string& k) {
//     return XXHash64::hash(k.c_str(), k.length(), HASH_SEED);
// }


// Hash1 using MetroHash64
template<typename T>
uint64_t Hash1(const T& k) {
    uint64_t hashValue;
    MetroHash64::Hash(reinterpret_cast<const uint8_t*>(&k), sizeof(T),
                      reinterpret_cast<uint8_t*>(&hashValue), HASH_SEED);
    return hashValue;
}

// Specialization for string
template<>
inline uint64_t Hash1<string>(const string& k) {
    uint64_t hashValue;
    MetroHash64::Hash(reinterpret_cast<const uint8_t*>(k.c_str()), k.length(),
                      reinterpret_cast<uint8_t*>(&hashValue), HASH_SEED);
    return hashValue;
}


// Hash2 using MurmurHash3
template<typename T>
uint64_t Hash2(const T& k) {
    uint64_t hashValue[2];  // MurmurHash3_x64_128 produces 128 bits
    MurmurHash3_x64_128(&k, sizeof(T), HASH_SEED, hashValue);
    return hashValue[0];  // Return first 64 bits
}

// Specialization for string
template<>
inline uint64_t Hash2<string>(const string& k) {
    uint64_t hashValue[2];  // MurmurHash3_x64_128 produces 128 bits
    MurmurHash3_x64_128(k.c_str(), k.length(), HASH_SEED, hashValue);
    return hashValue[0];  // Return first 64 bits
}