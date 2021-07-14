#include "doctest.h"
#include "BinaryTree.hpp"
#include <iostream>
#include <vector>
using namespace std;
using namespace ariel;


TEST_CASE("Check Output"){
    BinaryTree<int> tree;
    CHECK_NOTHROW(tree.add_root(1));
    CHECK_NOTHROW(cout << tree << endl;);

}

TEST_CASE("Replacements") {
    SUBCASE("BinaryTree<int>"){
        BinaryTree<int> tree;
        CHECK_NOTHROW(tree.add_root(1));
        SUBCASE("Root replacement"){
            CHECK_NOTHROW(tree.add_root(1));
            CHECK_NOTHROW(tree.add_root(2));
        }
        SUBCASE("Left replacement"){
            CHECK_NOTHROW(tree.add_left(1,2));
            CHECK_NOTHROW(tree.add_left(2,3));
        }
        SUBCASE("Right replacement"){
            CHECK_NOTHROW(tree.add_right(1,4));
            CHECK_NOTHROW(tree.add_right(4,5));
        }  
    }
    SUBCASE("BinaryTree<double>"){
        BinaryTree<double> tree;
        CHECK_NOTHROW(tree.add_root(1.1));
        SUBCASE("Root replacement"){
            CHECK_NOTHROW(tree.add_root(1.1));
            CHECK_NOTHROW(tree.add_root(2.2));
        }
        SUBCASE("Left replacement"){
            CHECK_NOTHROW(tree.add_left(1.1,2.2));
            CHECK_NOTHROW(tree.add_left(2.2,3.3));
        }
        SUBCASE("Right replacement"){
            CHECK_NOTHROW(tree.add_right(1.1,4.4));
            CHECK_NOTHROW(tree.add_right(4.4,5.5));
        }  
    }
    SUBCASE("BinaryTree<char>"){
        BinaryTree<char> tree;
        CHECK_NOTHROW(tree.add_root('a'));
        SUBCASE("Root replacement"){
            CHECK_NOTHROW(tree.add_root('a'));
            CHECK_NOTHROW(tree.add_root('b'));
        }
        SUBCASE("Left replacement"){
            CHECK_NOTHROW(tree.add_left('a','b'));
            CHECK_NOTHROW(tree.add_left('b','c'));
        }
        SUBCASE("Right replacement"){
            CHECK_NOTHROW(tree.add_right('a','d'));
            CHECK_NOTHROW(tree.add_right('d','e'));
        }  
    }         
}

TEST_CASE("The first input does not exist in the tree") {
    SUBCASE("BinaryTree<int>"){
        SUBCASE("There is no element (root) in the tree"){
            BinaryTree<int> tree;
            for(int a1 = -10; a1 <= 10; a1++) {
                for(int a2 = -10; a2 <= 10; a2++) {
                    CHECK_THROWS(tree.add_left(a1,a2));
                    CHECK_THROWS(tree.add_right(a1,a2));
                }
            } 
        }
        SUBCASE("There are elements in the tree but not the first input"){
            BinaryTree<int> tree;
            CHECK_NOTHROW(tree.add_root(11));
            for(int a1 = -10; a1 <= 10; a1++) {
                for(int a2 = -10; a2 <= 10; a2++) {
                    CHECK_THROWS(tree.add_left(a1,a2));
                    CHECK_THROWS(tree.add_right(a1,a2));
                }
            } 
        }
    }
    SUBCASE("BinaryTree<double>"){
        SUBCASE("There is no element (root) in the tree"){
            BinaryTree<double> tree;
            for(int a1 = -1; a1 <= 10; a1++) {
                for(int a2 = -1; a2 <= 10; a2++) {
                    double d1=a1*10+a2;
                    d1=d1/10;
                    double d2=a2*10+a1;
                    d2=d2/10;
                    CHECK_THROWS(tree.add_left(a1,a2));
                    CHECK_THROWS(tree.add_right(a1,a2));
                }
            }
        }
        SUBCASE("There are elements in the tree but not the first input"){
            BinaryTree<double> tree;
            CHECK_NOTHROW(tree.add_root(11.1));
            for(int a1 = -1; a1 <= 10; a1++) {
                for(int a2 = -1; a2 <= 10; a2++) {
                    double d1=a1*10+a2;
                    d1=d1/10;
                    double d2=a2*10+a1;
                    d2=d2/10;
                    CHECK_THROWS(tree.add_left(a1,a2));
                    CHECK_THROWS(tree.add_right(a1,a2));
                }
            }
        }         
    }
    SUBCASE("BinaryTree<string>"){
        BinaryTree<string> tree;
        SUBCASE("There is no element (root) in the tree"){
            CHECK_THROWS(tree.add_left("ab","cd"));
            CHECK_THROWS(tree.add_right("ab","cd"));
        }
        SUBCASE("There are elements in the tree but not the first input"){
            CHECK_NOTHROW(tree.add_root("abcd"));
            CHECK_THROWS(tree.add_left("ab","cd"));
            CHECK_THROWS(tree.add_right("ab","cd"));
        }

    }
    SUBCASE("BinaryTree<char>"){
        BinaryTree<char> tree;
        for(char c1 = 'a'; c1 <= 'z'; c1++) {
            for(char c2 = 'a'; c2 <= 'z'; c2++) {
                CHECK_THROWS(tree.add_left(c1,c2));
                CHECK_THROWS(tree.add_right(c1,c2));
            }
        }
    }
    SUBCASE("BinaryTree<char>"){
        BinaryTree<bool> tree;
        CHECK_THROWS(tree.add_left(true,false));
        CHECK_THROWS(tree.add_right(true,false));
        CHECK_THROWS(tree.add_left(false,false));
        CHECK_THROWS(tree.add_right(false,false));
        CHECK_THROWS(tree.add_left(false,true));
        CHECK_THROWS(tree.add_right(false,true));
        CHECK_THROWS(tree.add_left(true,true));
        CHECK_THROWS(tree.add_right(true,true));
    }

}


TEST_CASE("Check iterators"){
    SUBCASE("BinaryTree<int>"){
        BinaryTree<int> tree;
        CHECK_NOTHROW(tree.add_root(1));
        CHECK_NOTHROW(tree.add_left(1, 9).add_left(9, 4).add_right(9, 5).add_right(1, 3).add_left(1, 2));
        SUBCASE("PreOrder -> (parent - left - right) "){
            unsigned int i=0; // move over the result vector
            vector <int> result_vector={1,2,4,5,3};
            for (auto it=tree.begin_preorder(); it!=tree.end_preorder(); ++it) {
                CHECK((*it)==result_vector[i]);
                i++;
            }
        }
        SUBCASE("InOrder -> (left - parent - right) "){
            unsigned int i=0; // move over the result vector
            vector <int> result_vector={4,2,5,1,3};
            for (auto it=tree.begin_inorder(); it!=tree.end_inorder(); ++it) {
                CHECK((*it)==result_vector[i]);
                i++;
            }
        }
        SUBCASE("PostOrder -> (left - right -parent) "){
            unsigned int i=0; // move over the result vector
            vector <int> result_vector={4,5,2,3,1};
            for (auto it=tree.begin_postorder(); it!=tree.end_postorder(); ++it) {
                CHECK((*it)==result_vector[i]);
                i++;
            }
        }
    }
    SUBCASE("BinaryTree<double>"){
        BinaryTree<double> tree;
        CHECK_NOTHROW(tree.add_root(1.1));
        CHECK_NOTHROW(tree.add_left(1.1, 9.2).add_left(9.2, 4.3).add_right(9.2, 5.4).add_right(1.1, 3.5).add_left(1.1, 2.6));
        SUBCASE("PreOrder -> (parent - left - right) "){
            unsigned int i=0; // move over the result vector
            vector <double> result_vector={1.1,2.6,4.3,5.4,3.5};
            for (auto it=tree.begin_preorder(); it!=tree.end_preorder(); ++it) {
                CHECK((*it)==result_vector[i]);
                i++;
            }
        }
        SUBCASE("InOrder -> (left - parent - right) "){
            unsigned int i=0; // move over the result vector
            vector <double> result_vector={4.3,2.6,5.4,1.1,3.5};
            for (auto it=tree.begin_inorder(); it!=tree.end_inorder(); ++it) {
                CHECK((*it)==result_vector[i]);
                i++;
            }
        }
        SUBCASE("PostOrder -> (left - right -parent) "){
            unsigned int i=0; // move over the result vector
            vector <double> result_vector={4.3,5.4,2.6,3.5,1.1};
            for (auto it=tree.begin_postorder(); it!=tree.end_postorder(); ++it) {
                CHECK((*it)==result_vector[i]);
                i++;
            }
        }

    }
    SUBCASE("BinaryTree<string>"){
        BinaryTree<string> tree;
        CHECK_NOTHROW(tree.add_root("1"));
        CHECK_NOTHROW(tree.add_left("1", "9").add_left("9", "4").add_right("9", "5").add_right("1", "3").add_left("1", "2"));
        SUBCASE("PreOrder -> (parent - left - right) "){
            unsigned int i=0; // move over the result vector
            vector <string> result_vector={"1","2","4","5","3"};
            for (auto it=tree.begin_preorder(); it!=tree.end_preorder(); ++it) {
                CHECK((*it)==result_vector[i]);
                i++;
            }
        }
        SUBCASE("InOrder -> (left - parent - right) "){
            unsigned int i=0; // move over the result vector
            vector <string> result_vector={"4","2","5","1","3"};
            for (auto it=tree.begin_inorder(); it!=tree.end_inorder(); ++it) {
                CHECK((*it)==result_vector[i]);
                i++;
            }
        }
        SUBCASE("PostOrder -> (left - right -parent) "){
            unsigned int i=0; // move over the result vector
            vector <string> result_vector={"4","5","2","3","1"};
            for (auto it=tree.begin_postorder(); it!=tree.end_postorder(); ++it) {
                CHECK((*it)==result_vector[i]);
                i++;
            }
        }
    }
        SUBCASE("BinaryTree<char>"){
        BinaryTree<char> tree;
        CHECK_NOTHROW(tree.add_root('a'));
        CHECK_NOTHROW(tree.add_left('a', 'h').add_left('h', 'd').add_right('h', 'e').add_right('a', 'c').add_left('a', 'b'));
        SUBCASE("PreOrder -> (parent - left - right) "){
            unsigned int i=0; // move over the result vector
            vector <char> result_vector={'a','b','d','e','c'};
            for (auto it=tree.begin_preorder(); it!=tree.end_preorder(); ++it) {
                CHECK((*it)==result_vector[i]);
                i++;
            }
        }
        SUBCASE("InOrder -> (left - parent - right) "){
            unsigned int i=0; // move over the result vector
            vector <char> result_vector={'d','b','e','a','c'};
            for (auto it=tree.begin_inorder(); it!=tree.end_inorder(); ++it) {
                CHECK((*it)==result_vector[i]);
                i++;
            }
        }
        SUBCASE("PostOrder -> (left - right -parent) "){
            unsigned int i=0; // move over the result vector
            vector <char> result_vector={'d','e','b','c','a'};
            for (auto it=tree.begin_postorder(); it!=tree.end_postorder(); ++it) {
                CHECK((*it)==result_vector[i]);
                i++;
            }
        }
    }

}





