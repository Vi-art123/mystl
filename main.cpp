#include <AVLTree.hpp>
#include <RBTree.hpp>
#include <CircleLinkedList.hpp>
#include <SinglyLinkedList.hpp>
#include <SinglyCircleLinkedList.hpp>
#include <Stack.hpp>
#include <Queue.hpp>
#include <Deque.hpp>
#include <ListSet.hpp>
#include <TreeSet.hpp>
#include <map>


void test01()
{
    mystd::RBTree<int> bst;
    // int arr[] = {7, 9, 4, 2, 5, 8, 11, 1, 3, 10, 12};
//    int arr[] = {7, 9, 4, 2, 5, 8, 11, 1, 3};
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int len = sizeof arr/sizeof arr[0];
    for (int i = 0; i < len; ++i) {
        bst.add(arr[i]);
//        bst.to_string();
//        std::cout << "---------------------------------" << std::endl;
    }
#if 1
    bst.to_string();
    std::cout << "---------------------------------" << std::endl;
    for (int i = 0; i < len; ++i) {
        bst.remove(arr[i]);
        bst.to_string();
        std::cout << "---------------------------------" << std::endl;
    }
#endif
    std::cout << std::endl;
    std::cout << "size=" << bst.size() << std::endl;
    std::cout << "height=" << bst.height() << std::endl;

//    bst.invertTree();
//    bst.to_string();
}

void test02()
{
    mystd::ArrayList<int> al;
    int arr[] = {7, 9, 4, 2, 5, 8, 11, 1, 3, 10, 12};
    int len = sizeof arr/sizeof arr[0];
    for (int i = 0; i < len; ++i) {
        al.push_back(arr[i]);
    }

//    al.pop_back();
//    al.set(8, 6);
//    al.add(8, 6);
    al.to_string();
//    std::cout << al.get(9) << std::endl;
}

void test03()
{
    mystd::CircleLinkedList<int> ll;
    int arr[] = {7, 9, 4, 2, 5, 8, 11, 1, 3, 10, 12};
    int len = sizeof arr/sizeof arr[0];
    for (int i = 0; i < len; ++i) {
        ll.push_back(arr[i]);
    }

    {
        decltype(ll) list = ll;
        ll.to_string();
    }

//    ll.pop_back();
//    ll.set(8, 6);
//    ll.add(8, 6);
//    ll.to_string();
//    ll.reverse();
//    ll.add(0, 6);
//    ll.pop_back();
    ll.to_string();
//    std::cout << ll.get(9) << std::endl;
}

void test04()
{
    mystd::Stack<int> stack;
    int arr[] = {7, 9, 4, 2, 5, 8, 11, 1, 3, 10, 12};
    int len = sizeof arr/sizeof arr[0];
    for (int i = 0; i < len; ++i) {
        stack.push(arr[i]);
    }

    stack.pop();
    stack.to_string();
    std::cout << stack.top() << std::endl;
}

void test05()
{
    mystd::Queue<int> queue;
    int arr[] = {7, 9, 4, 2, 5, 8, 11, 1, 3, 10, 12};
    int len = sizeof arr/sizeof arr[0];
    for (int i = 0; i < len; ++i) {
        queue.enQueue(arr[i]);
    }

    queue.deQueue();
    queue.to_string();
    std::cout << queue.front() << std::endl;
}

void test06()
{
    mystd::TreeSet<int> set;
    int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 9};
    int len = sizeof arr/sizeof arr[0];
    for (int i = 0; i < len; ++i) {
        set.add(arr[i]);
    }

    set.traversal();
}

int main()
{
    test01();
    return 0;
}
