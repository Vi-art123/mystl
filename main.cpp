#include <binarytree.hpp>
#include <ArrayList.hpp>
#include <LinkedList.hpp>


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
    mystd::LinkedList<int> ll;
    int arr[] = {7, 9, 4, 2, 5, 8, 11, 1, 3, 10, 12};
    int len = sizeof arr/sizeof arr[0];
    for (int i = 0; i < len; ++i) {
        ll.push_back(arr[i]);
    }

//    ll.pop_back();
//    ll.set(8, 6);
//    ll.add(8, 6);
//    ll.reverse();
    ll.to_string();
//    std::cout << ll.get(9) << std::endl;
}

int main()
{
//    test01();
    test02();
    test03();
    return 0;
}
