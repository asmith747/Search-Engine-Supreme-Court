#ifndef AVLTREE_H
#define AVLTREE_H

#include <iostream>
#include "indexinterface.h"
#include <ostream>
#include <fstream>
#include <vector>
#include "data.h"

using namespace std;

template <typename T>
class AVLTree
{
  public:

    AVLTree( )
    {
        root = NULL;
    }

    AVLTree( const AVLTree & right)
    {
        root = NULL;
        *this = right;
    }

    ~AVLTree( )
    {
        makeEmpty( );
    }

    bool contains( const T x ) const
    {
        return contains( x, root );
    }

    int getSize(){
        size = 0;
        return getSize(0, root);
    }

    void getData(T word)
    {
        getData(word, root);
    }

    vector<T> printCommon()
    {
        return printCommon(root, 0);
    }

    void clear(){
        clear(root);
    }

    T getTop(T word){
        return getTop(word, root);
    }

    T& update(T x)
    {
        return update(x, root);
    }

    bool isEmpty( ) const
    {
        return root == NULL;
    }

    void printOut(ofstream& out)
    {
        printOut(out, root);
    }

    void makeEmpty( )
    {
        makeEmpty( root );
    }


    void insert( const T & x )
    {
        insert( x, root );
    }


  private:
    Data nul;
    vector<T> common;
    int size = 0;
    vector<T> top;
    struct AVLNode
    {
        AVLNode( const T & theElement, AVLNode *lt, AVLNode *rt, int h = 0 )
        {
            element = theElement;
            left = lt;
            right = rt;
            height = h;
        }
        T element;
        AVLNode   *left;
        AVLNode   *right;
        int height;
    };

    AVLNode *root;

    void insert( const T & x, AVLNode * & t )
    {
        if( t == NULL )
            t = new AVLNode( x, NULL, NULL );
        else if( x < t->element )
        {
            insert( x, t->left );
            if( height( t->left ) - height( t->right ) == 2 ){
                if( x < t->left->element )
                    rotateWithLeftChild( t );
                else
                    doubleWithLeftChild( t );
            }
        }
        else if( t->element < x )
        {
            insert( x, t->right );
            if( height( t->right ) - height( t->left ) == 2 ){
                if( t->right->element < x )
                    rotateWithRightChild( t );
                else
                    doubleWithRightChild( t );
            }
        }
        else{

        }

        t->height = max( height( t->left ), height( t->right ) ) + 1;
    }



    bool contains( const T x, AVLNode *t ) const
    {
        if( t == NULL )
            return false;
        else if( x < t->element )
            return contains( x, t->left );
        else if( t->element < x )
            return contains( x, t->right );
        else{
            return true;    // Match
        }
    }

    T& update(T x, AVLNode *t )
    {
        if( x < t->element )
            return update( x, t->left );
        else if( t->element < x )
            return update( x, t->right );
        else{
            return t->element;    // Match
        }
    }


    /**
     * Internal method to make subtree empty.
     */
    //NOT GIVEN
    void makeEmpty(AVLNode * & t )
    {
        if( t != NULL )
        {
            makeEmpty( t->left );
            makeEmpty( t->right );
            delete t;
        }
        t = NULL;
    }

    void printOut(ofstream& out, AVLNode *t)
    {
        if( t != NULL )
        {
            printOut( out, t->left );
            out << t->element;
            printOut( out, t->right );
        }
    }

    void clear(AVLNode ** t)
    {
        if(t!=nullptr){
            clear(t->left);
            clear(t->right);
            delete t;
        }
        t=nullptr;
    }

    vector<T> printCommon(AVLNode *t, int ind)
    {
        if(ind == 0)
            common.clear();
        vector<T> temp;
        if( t != NULL )
        {
             temp = printCommon(t->left, 1);
             common.push_back(t->element);
             temp = printCommon(t->right, 1);
        }
        if(ind == 0)
            return common;
        else
            return temp;
    }


    int getSize(int beg, AVLNode *t)
    {
        if( t != NULL )
        {
            size++;
            getSize(1, t->left);
            getSize(1, t->right );
        }
        if(beg==0)
            return size;
    }

    void getData(T word, AVLNode *t)
    {
        if( t == NULL )
            cout << "Word not found\n";
        else if( word < t->element )
            return getData( word, t->left );
        else if( t->element < word )
            return getData( word, t->right );
        else{
            cout << t->element<< endl;
        }
    }

    T getTop(T word, AVLNode *t)
    {
        if( t == NULL ){
            cout << "Word not found\n";
            return nul;
        }
        else if(word < t->element )
            return getTop(word, t->left );
        else if( t->element < word )
            return getTop(word, t->right );
        else{
            return t->element;
        }
    }

    int height( AVLNode *t ) const
    {
        return t == NULL ? -1 : t->height;
    }

    int max( int lhs, int rhs ) const
    {
        return lhs > rhs ? lhs : rhs;
    }

    void rotateWithLeftChild( AVLNode * & k2 )
    {
        AVLNode *k1 = k2->left;
        k2->left = k1->right;
        k1->right = k2;
        k2->height = max( height( k2->left ), height( k2->right ) ) + 1;
        k1->height = max( height( k1->left ), k2->height ) + 1;
        k2 = k1;
    }

    void rotateWithRightChild( AVLNode * & k1 )
    {
        AVLNode *k2 = k1->right;
        k1->right = k2->left;
        k2->left = k1;
        k1->height = max( height( k1->left ), height( k1->right ) ) + 1;
        k2->height = max( height( k2->right ), k1->height ) + 1;
        k1 = k2;
    }

    void doubleWithLeftChild(AVLNode * & k3 )
    {
        rotateWithRightChild( k3->left );
        rotateWithLeftChild( k3 );
    }

    void doubleWithRightChild(AVLNode * & k1 )
    {
        rotateWithLeftChild(k1->right);
        rotateWithRightChild(k1);
    }
};

#endif
