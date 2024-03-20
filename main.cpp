#include <BinaryTree.hpp>
#include <ArrayList.hpp>
#include <LinkedList.hpp>
#include <CircleLinkedList.hpp>
#include <SinglyLinkedList.hpp>
#include <SinglyCircleLinkedList.hpp>
#include <Stack.hpp>
#include <Queue.hpp>
#include <Deque.hpp>


void test01()
{
    mystd::BinaryTree<int> bt;
    int arr[] = {7, 9, 4, 2, 5, 8, 11, 1, 3, 10, 12};
    int len = sizeof arr/sizeof arr[0];
    for (int i = 0; i < len; ++i) {
        bt.add(arr[i]);
    }

    if (!bt.isEmpty()) {
        bt.preOrderTraverse();
        std::cout << std::endl;
        bt.inOrderTraverse();
        std::cout << std::endl;
        bt.postOrderTraverse();
        std::cout << std::endl;
        bt.levelOrderTraverse();
    }

    std::cout << std::endl << bt.size() << std::endl;
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

int main()
{
    test01();
    return 0;
}
