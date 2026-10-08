// HashMap.cpp — a hash table with separate chaining and automatic rehashing.
//
// Why this file exists: hashing is the missing classic in this collection.
// Two strings can land in the same bucket (a collision) and the table stays
// fast by relinking lists, not by moving everything around.

#include <iostream>
#include <string>
#include <functional>   // only used for std::hash, not a container

template <typename K, typename V>
class HashMap {
private:
    struct Node {
        K key;
        V value;
        Node* next;
        Node(const K& k, const V& v) : key(k), value(v), next(NULL) {}
    };

    Node** buckets;          // raw array of bucket heads, no STL containers
    size_t bucketCount;
    size_t itemCount;

    // index inside the bucket array for a key
    size_t indexFor(const K& key, size_t tableSize) const {
        return std::hash<K>()(key) % tableSize;
    }

    // double the table and move every node — called when load gets too high
    void rehash() {
        size_t oldCount = bucketCount;
        Node** oldBuckets = buckets;

        bucketCount = oldCount * 2;
        buckets = new Node*[bucketCount]();
        itemCount = 0;                     // insert() counts them again

        for (size_t i = 0; i < oldCount; i++) {
            Node* cur = oldBuckets[i];
            while (cur != NULL) {
                insert(cur->key, cur->value);
                Node* dead = cur;
                cur = cur->next;
                delete dead;
            }
        }
        delete[] oldBuckets;
        std::cout << "[rehash] table grew to " << bucketCount << " buckets\n";
    }

public:
    HashMap(size_t startSize = 8) : bucketCount(startSize), itemCount(0) {
        buckets = new Node*[bucketCount]();   // () zeroes the pointers
    }

    ~HashMap() {
        for (size_t i = 0; i < bucketCount; i++) {
            Node* cur = buckets[i];
            while (cur != NULL) {
                Node* dead = cur;
                cur = cur->next;
                delete dead;
            }
        }
        delete[] buckets;
    }

    // insert or update — same key twice keeps only the newest value
    void insert(const K& key, const V& value) {
        if (itemCount + 1 > bucketCount * 3 / 4)   // load factor 0.75
            rehash();

        size_t i = indexFor(key, bucketCount);
        Node* cur = buckets[i];
        while (cur != NULL) {
            if (cur->key == key) {                 // key exists: update
                cur->value = value;
                return;
            }
            cur = cur->next;
        }
        Node* n = new Node(key, value);            // new key: push to front
        n->next = buckets[i];
        buckets[i] = n;
        itemCount++;
    }

    // get into `out`; returns false if the key is missing
    bool get(const K& key, V& out) const {
        Node* cur = buckets[indexFor(key, bucketCount)];
        while (cur != NULL) {
            if (cur->key == key) {
                out = cur->value;
                return true;
            }
            cur = cur->next;
        }
        return false;
    }

    bool contains(const K& key) const {
        V tmp;
        return get(key, tmp);
    }

    // true if something was actually removed
    bool remove(const K& key) {
        size_t i = indexFor(key, bucketCount);
        Node* cur = buckets[i];
        Node* prev = NULL;
        while (cur != NULL) {
            if (cur->key == key) {
                if (prev == NULL)
                    buckets[i] = cur->next;
                else
                    prev->next = cur->next;
                delete cur;
                itemCount--;
                return true;
            }
            prev = cur;
            cur = cur->next;
        }
        return false;
    }

    size_t size() const { return itemCount; }

    // print each bucket so collisions are visible
    void display() const {
        for (size_t i = 0; i < bucketCount; i++) {
            std::cout << "bucket " << i << ":";
            Node* cur = buckets[i];
            if (cur == NULL) { std::cout << " (empty)\n"; continue; }
            while (cur != NULL) {
                std::cout << " [" << cur->key << " -> " << cur->value << "]";
                cur = cur->next;
            }
            std::cout << "\n";
        }
    }
};

int main() {
    HashMap<std::string, int> scores;

    // 1. plain insert + get
    scores.insert("ali", 90);
    scores.insert("sara", 95);
    scores.insert("umer", 88);

    int v = 0;
    if (scores.get("sara", v))
        std::cout << "sara scored " << v << "\n";

    // 2. updating an existing key keeps only the newest value
    scores.insert("ali", 93);
    scores.get("ali", v);
    std::cout << "ali's updated score: " << v << "\n";

    // 3. missing keys fail cleanly instead of inventing values
    if (!scores.get("zara", v))
        std::cout << "zara: not found\n";

    // 4. remove works, removing twice reports false the second time
    std::cout << "removed umer: " << (scores.remove("umer") ? "yes" : "no") << "\n";
    std::cout << "removed umer again: " << (scores.remove("umer") ? "yes" : "no") << "\n";

    // 5. rehash demo — small table, many inserts, watch it grow
    HashMap<std::string, int> tiny(4);
    std::string words[] = {"ai", "ml", "data", "code", "prompt", "agent",
                           "model", "token", "vector", "graph", "search", "index"};
    for (int i = 0; i < 12; i++)
        tiny.insert(words[i], i * 10);
    std::cout << "tiny holds " << tiny.size() << " items after rehashing:\n";
    tiny.display();

    // 6. a real use: counting word frequency
    HashMap<std::string, int> freq;
    std::string sentence[] = {"the", "model", "reads", "the", "prompt",
                              "the", "model", "answers"};
    for (int i = 0; i < 8; i++) {
        int c = 0;
        freq.get(sentence[i], c);      // 0 if unseen
        freq.insert(sentence[i], c + 1);
    }
    freq.get("the", v);   std::cout << "'the' appears " << v << " times\n";
    freq.get("model", v); std::cout << "'model' appears " << v << " times\n";

    return 0;
}
