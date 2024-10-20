#include <iostream>

using namespace std;

template <typename T> struct Node {
    T data;
    Node* next;
    Node(T data) {
        cout << "Create new node" << endl;
        this->data = data;
        this->next = nullptr;
    }
};

template <typename T> struct LinkedList {
    struct iterator {
        Node<T>* current;

        iterator(Node<T>* node) { this->current = node; }

        void operator++() { this->current = this->current->next; }

        bool operator==(const iterator& other) {
            return this->current == other.current;
        }

        bool operator!=(const iterator& other) {
            return this->current != other.current;
        }

        T& operator*() { return this->current->data; }

        bool is_end() { return this->current == nullptr; }
    };

    // properties
    Node<T>* head;
    uint32_t size;

    // methods
    LinkedList() {
        cout << "Create linked list" << endl;
        head = new Node<T>(0);
        size = 0;
    }

    bool is_empty() const { return size == 0; }

    void push_back(T data) {
        Node<T>* iter = head;

        while (iter->next != nullptr) {
            iter = iter->next;
        }

        Node<T>* new_node = new Node<T>(data);
        iter->next = new_node;
        this->size += 1;
    }

    void push_front(T data) {
        Node<T>* new_node = new Node<T>(data);

        new_node->next = head->next;
        head->next = new_node;
        this->size += 1;
    }

    bool insert(T data, uint32_t index) {
        if (index > size) {
            cerr << "Invalid index: " << index << endl;
            return false;
        }

        Node<T>* iter = head;
        while (index) {
            iter = iter->next;
            index -= 1;
        }

        Node<T>* new_node = new Node<T>(data);
        new_node->next = iter->next;
        iter->next = new_node;

        this->size += 1;
        return true;
    }

    bool erase(uint32_t index) {
        if (index >= size) {
            cerr << "Invalid index: " << index << endl;
            return false;
        }

        Node<T>* iter = head;
        while (index) {
            iter = iter->next;
            index -= 1;
        }

        // for delete later
        Node<T>* removed_node = iter->next;

        iter->next = iter->next->next;
        this->size -= 1;

        // free it goddammit
        delete removed_node;

        return true;
    }

    iterator begin() const { return iterator(head->next); }
    iterator end() const { return iterator(nullptr); }

    void dump_list() const {
        cout << "List:";
#if 0
        Node<T>* iter = head;
        while (iter->next != nullptr) {
            iter = iter->next;
            cout << " " << iter->data;
        }
#else
        for (LinkedList<T>::iterator iter = begin(); iter != end(); ++iter) {
            cout << " " << *iter;
        }
#endif
        cout << "\n";
    }
};

int main(int argc, char* argv[]) {
    LinkedList<int> list;

    list.push_back(5);
    list.push_back(6);
    list.push_back(7);

    list.push_front(10);
    list.insert(99, 1);

    list.dump_list();

    return 0;
}
