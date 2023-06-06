#include<iostream>
#include<unordered_set>
using namespace std;
template <class T>
class shared_pointer{
    public:
    shared_pointer* prev;
    shared_pointer* next;
    T* object;
    // construct with object
    shared_pointer():shared_pointer(nullptr){
    }
    shared_pointer(T* _object):object(_object){
        prev = next = nullptr;
    }
    // construct other ptr
    shared_pointer(shared_pointer<T> &ptr){
        ptr_insert(ptr);
    }
    int use_count(){
        shared_pointer* p = prev, *n = next;
        if(!object)return 0;
        int cnt = 1;
        while(p){
            cnt += 1;
            p = p->prev;
        }
        while(n){
            cnt += 1;
            n = n->next;
        }
        return cnt;
    }
    ~shared_pointer(){
        remove_ptr();
    }
    T* get(){
        return object;
    }
    void remove_ptr(){
        if(object && !prev && !next){
            delete object;
        }
        object = nullptr;
        if(prev){
            prev->next = next;
        }
        if(next){
            next->prev = prev;
        }
    }
    shared_pointer& operator=(shared_pointer<T> &rhs){
        remove_ptr();
        if(rhs.object != nullptr){
            ptr_insert(rhs);
        }
        return *this;
    }
    void ptr_insert(shared_pointer<T> &ptr){
        object = ptr.object;
        if(ptr.next == nullptr){
            ptr.next = this;
            prev = &ptr;
            next = nullptr;
        }
        else{
            next = ptr.next;
            next->prev = this;
            ptr.next = this;
        }
    }

    // Overload * operator
    T& operator*()
    {
        return *object; // dealt with *ptr1 = 100 case
    }

    // Overload -> operator
    T* operator->()
    {
        return object;
    }

};
int main(){
    /*
    shared_pointer<int> T(new int(1));
    cout << &T << endl;
    cout << T.get() << endl;
    int* tmp = T.get();
    cout << "tmp: "<< *tmp << endl;
    //cout << T << endl;
    shared_pointer<int> T2(T);
    shared_pointer<int> T3(T);
    cout << "cnt: " << T.ptr_count() << endl;
    cout << "T1:" << *(T.object) << endl;
    cout << "T2:" << *(T2.object) << endl;
    cout << "T3:" << *(T3.object) << endl;
    T2.~shared_pointer();
    cout << "T1:" << *(T.object) << endl;
    T2.remove_ptr();
    //cout << *(T2.object) << endl;
    //cout << T2.get() << endl;
    cout << "T3:" << *(T3.object) << endl;
    T.remove_ptr();
    //T3.remove_ptr();
    T = T3;
    cout << T.ptr_count() << endl;
    T3.remove_ptr();
    T.remove_ptr();
    cout << "T1:" << *(T.object) << endl;
    cout << "tmp: "<< *tmp << endl;
    */
    shared_pointer<int> ptr(nullptr);
     // ptr1 pointing to an integer.
    shared_pointer<int> ptr1(new int(151)); // memory: stack
    cout << "--- Shared pointers ptr1 ---\n";
    *ptr1 = 100;
    cout << " ptr1's value : " << *ptr1 << endl;
    cout << " ptr1's Address pointed : " << ptr1.get() << endl;
    cout << " ptr1's Counter Value : " << ptr1.use_count() << endl;

    {
        // ptr2 pointing to same integer
        // which ptr1 is pointing to
        // Shared pointer reference counter
        // should have increased now to 2.
        shared_pointer<int> ptr2 = ptr1; // memory: stack
        cout << "--- Shared pointers ptr1, ptr2 ---\n";
        cout << " ptr1's value : " << *ptr1 << endl;
        cout << " ptr1's Address pointed : " << ptr1.get() << endl;
        cout << " ptr1's Counter Value : " << ptr1.use_count() << endl;
        cout << " ptr2's value : " << *ptr2 << endl;
        cout << " ptr2's Address pointed : " << ptr2.get() << endl;
        cout << " ptr2's Counter Value : " << ptr2.use_count() << endl;

        {
            // ptr3 pointing to same integer
            // which ptr1 and ptr2 are pointing to.
            // Shared pointer reference counter
            // should have increased now to 3.
            shared_pointer<int> ptr3(ptr2); // memory: stack
            cout << "--- Shared pointers ptr1, ptr2, ptr3 ---\n";
            cout << " ptr1's value : " << *ptr1 << endl;
            cout << " ptr1's Address pointed : " << ptr1.get() << endl;
            cout << " ptr1's Counter Value : " << ptr1.use_count() << endl;
            cout << " ptr2's value : " << *ptr2 << endl;
            cout << " ptr2's Address pointed : " << ptr2.get() << endl;
            cout << " ptr2's Counter Value : " << ptr2.use_count() << endl;
            cout << " ptr3's value : " << *ptr3 << endl;
            cout << " ptr3's Address pointed : " << ptr3.get() << endl;
            cout << " ptr3's Counter Value : " << ptr3.use_count() << endl;

            {
                shared_pointer<int> ptr4;  // memory: stack
                ptr4 = ptr3;
                cout << "--- Shared pointers ptr1, ptr2, ptr3, ptr4 ---\n";
                cout << " ptr1's value : " << *ptr1 << endl;
                cout << " ptr1's Address pointed : " << ptr1.get() << endl;
                cout << " ptr1's Counter Value : " << ptr1.use_count() << endl;
                cout << " ptr2's value : " << *ptr2 << endl;
                cout << " ptr2's Address pointed : " << ptr2.get() << endl;
                cout << " ptr2's Counter Value : " << ptr2.use_count() << endl;
                cout << " ptr3's value : " << *ptr3 << endl;
                cout << " ptr3's Address pointed : " << ptr3.get() << endl;
                cout << " ptr3's Counter Value : " << ptr3.use_count() << endl;
                cout << " ptr4's value : " << *ptr4 << endl;
                cout << " ptr4's Address pointed : " << ptr4.get() << endl;
                cout << " ptr4's Counter Value : " << ptr4.use_count() << endl;
            }
        }

        // ptr3, ptr4 is out of scope.
        // It would have been destructed.
        // So shared pointer reference counter
        // should have decreased now to 2.
        cout << "--- Shared pointers ptr1, ptr2 ---\n";
        cout << " ptr1's value : " << *ptr1 << endl;
        cout << " ptr1's Address pointed : " << ptr1.get() << endl;
        cout << " ptr1's Counter Value : " << ptr1.use_count() << endl;
        cout << " ptr2's value : " << *ptr2 << endl;
        cout << " ptr2's Address pointed : " << ptr2.get() << endl;
        cout << " ptr2's Counter Value : " << ptr2.use_count() << endl;
    }

    // ptr2 is out of scope.
    // It would have been destructed.
    // So shared pointer reference counter
    // should have decreased now to 1.
    cout << "--- Shared pointers ptr1 ---\n";
    cout << " ptr1's value : " << *ptr1 << endl;
    cout << " ptr1's Address pointed : " << ptr1.get() << endl;
    cout << " ptr1's Counter Value : " << ptr1.use_count() << endl;

    return 0;
}
