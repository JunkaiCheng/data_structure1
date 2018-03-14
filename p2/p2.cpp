//
//  main.cpp
//  p2
//
//  Created by Cheng on 2017/6/13.
//  Copyright © 2017年 Cheng. All rights reserved.
//

#include <iostream>
#include <cassert>
#include "recursive.h"
#include "p2.h"
using namespace std;


static int size_helper(list_t list, int i)
{
    if (list_isEmpty(list))
        return i;
    else
    {
        list=list_rest(list);
        return size_helper(list, i+1);
    }
}

int size(list_t list)
/*
 // EFFECTS: Returns the number of elements in "list".
 //          Returns zero if "list" is empty.
 */
{
    return size_helper(list, 0);
}




bool memberOf(list_t list, int val)
/*
 // EFFECTS: Returns true if the value "val" appears in "list".
 //          Returns false otherwise.
 */
{
    if (list_isEmpty(list))
        return false;
    else
    {
        if (list_first(list)==val)
            return true;
        else
        {
            list=list_rest(list);
            return memberOf(list, val);
        }
    }
}


static int dot_helper(list_t v1, list_t v2, int s)
{
    if (list_isEmpty(v1)||list_isEmpty(v2))
        return s;
    else
    {
        s=s+list_first(v1)*list_first(v2);
        v1=list_rest(v1);
        v2=list_rest(v2);
        return dot_helper(v1, v2, s);
    }
}

int dot(list_t v1, list_t v2)
/*
 // REQUIRES: Both "v1" and "v2" are non-empty
 //
 // EFFECTS: Treats both lists as vectors. Returns the dot
 //          product of the two vectors. If one list is longer
 //          than the other, ignore the longer part of the vector.
 */
{
    return dot_helper(v1, v2, 0);
}


static bool isIncreasing_helper (list_t v, int i)
{
    if (list_isEmpty(v))
        return true;
    else
    {
        if (list_first(v)<i)
            return false;
        else
        {
            return isIncreasing_helper(list_rest(v), list_first(v));
        }
    }
}


bool isIncreasing(list_t v)
/*
 // EFFECTS: Checks if the list of integers is increasing.
 //          A list is increasing if and only if no element
 //          is smaller than its previous element.
 //
 //          For example: (1, 1) and (1, 2, 3, 3, 5) are
 //          both increasing. (2, 1) and (1, 2, 3, 2, 5) are not.
 */
{
    
    return isIncreasing_helper(list_rest(v), list_first(v));
}


static list_t reverse_helper(list_t list, int n, list_t temp)
{
    if (n==0)
        return temp;
    else
    {
        temp=list_make(list_first(list), temp);
        
        return reverse_helper(list_rest(list), n-1, temp);
    }
}

list_t reverse(list_t list)
/*
 // EFFECTS: Returns the reverse of "list".
 //
 //          For example: the reverse of ( 3 2 1 ) is ( 1 2 3 ).
 */
{
    if (list_isEmpty(list)||list_isEmpty(list_rest(list)))
    {
        return list;
    }
    else
    {
        int n= size(list);
        return reverse_helper(list, n,list_make());
    }
    
    
}

static list_t append_helper(list_t first, list_t second)
{
    if (list_isEmpty(second))
        return first;
    else
    {
        first=list_make(list_first(second),first);
        second=list_rest(second);
        return append_helper(first, second);
    }
}

list_t append(list_t first, list_t second)
/*
 // EFFECTS: Returns the list (first second).
 //
 //          For example: append(( 2 4 6 ), ( 1 3 )) gives
 //          the list ( 2 4 6 1 3 ).
 */
{
    return reverse(append_helper(reverse(first), second));
}

static bool isArithmetic_helper(list_t v, int d)
{
    if (list_isEmpty(v)||list_isEmpty(list_rest(v)))
        return true;
    else
    {
        if(list_first(list_rest(v))-list_first(v)!=d)
            return false;
        else
            return isArithmetic_helper(list_rest(v),d);
    }
}

bool isArithmeticSequence(list_t v)
/*
 // EFFECTS: Checks if the list of integers forms an
 //          arithmetic sequence.
 //
 //          For example: (), (1), (1, 3, 5, 7), and (2, 8, 14, 20)
 //          are arithmetic sequences. (1, 2, 4), (1, 3, 3),
 //          and (2, 4, 8, 10) are not.
 */
{
    if (list_isEmpty(v)||list_isEmpty(list_rest(v)))
        return true;
    else
    {
        int d= list_first(list_rest(v))-list_first(v);
        return isArithmetic_helper(list_rest(v),d);
    }
}


static list_t filter_odd_helper(list_t list, list_t odd)
{
    if (list_isEmpty(list))
        return odd;
    else
    {
        if (list_first(list)%2==0)
            return filter_odd_helper(list_rest(list), odd);
        else
            return filter_odd_helper(list_rest(list), list_make(list_first(list), odd));
    }
}

list_t filter_odd(list_t list)
/*
 // EFFECTS: Returns a new list containing only the elements of the
 //          original "list" which are odd in value,
 //          in the order in which they appeared in list.
 //
 //          For example, if you apply filter_odd to the list
 //          ( 3 4 1 5 6 ), you would get the list ( 3 1 5 ).
 */
{
        return reverse(filter_odd_helper(list, list_make()));
}

static list_t filter_helper(list_t list, bool (*fn)(int), list_t filter)
{
    if (list_isEmpty(list))
        return filter;
    else
    {
        if (fn(list_first(list))==false)
            return filter_helper(list_rest(list), fn, filter);
        else
            return filter_helper(list_rest(list), fn, list_make(list_first(list), filter));
    }
}

list_t filter(list_t list, bool (*fn)(int))
/*
 // EFFECTS: Returns a list containing precisely the elements of "list"
 //          for which the predicate fn() evaluates to true, in the
 //          order in which they appeared in list.
 //
 //          For example, if predicate bool odd(int a) returns true
 //          if a is odd, then the function filter(list, odd) has
 //          the same behavior as the function filter_odd(list).
 */
{
    return reverse(filter_helper(list, fn, list_make()));
}


static list_t unique_helper(list_t rst, list_t list)
{
    
    if (list_isEmpty(list))
        return rst;
    else
    {
        int n=list_first(list);
        if (!memberOf(rst, n))
            rst=list_make(n,rst);
        return unique_helper(rst, list_rest(list));
    }
}

list_t unique(list_t list)
/*
 // EFFECTS: Returns a new list comprising of each unique element
 //          in "list". The order is determined by the first
 //          occurrence of each unique element in "list".
 //
 //          For example, if you apply unique to the list
 //          (1 1 2 1 3 5 5 3 4 5 4), you would get (1 2 3 5 4).
 //          If you apply unique to the list (0 1 2 3), you would
 //          get (0 1 2 3)
 */
{
    if(list_isEmpty(list)|| list_isEmpty(list_rest(list)))
        return list;
    else
        return reverse(unique_helper(list_make(list_first(list),list_make()), list_rest(list)));
}

static list_t insert_helper(list_t list, unsigned int n)
{
    if (n==0)
        return list;
    else
        return insert_helper(list_rest(list), n-1);
}

list_t insert_list(list_t first, list_t second, unsigned int n)
/*
 // REQUIRES: n <= the number of elements in "first".
 //
 // EFFECTS: Returns a list comprising the first n elements of
 //          "first", followed by all elements of "second",
 //          followed by any remaining elements of "first".
 //
 //          For example: insert(( 1 2 3 ), ( 4 5 6 ), 2)
 //          gives ( 1 2 4 5 6 3 ).
 */
{
    if (n==0)
        return append(second, first);
    else
    {
        second= append(chop(first, size(first)-n), second);
        return append(second, insert_helper(first, n));
    }
}


static list_t chop_helper(list_t list, unsigned int n)
{
    if (n==0)
        return reverse(list);
    else
        return chop_helper(list_rest(list), n-1);
}

list_t chop(list_t list, unsigned int n)
/*
 // REQUIRES: "list" has at least n elements.
 //
 // EFFECTS: Returns the list equal to "list" without its last n
 //          elements.
 */
{
    if (n==0)
        return list;
    else
        return chop_helper(reverse(list), n);
}



int tree_sum(tree_t tree)
/*
 // EFFECTS: Returns the sum of all elements in "tree".
 //          Returns zero if "tree" is empty.
 */

{
    if (tree_isEmpty(tree))
        return 0;
    else return tree_elt(tree)+tree_sum(tree_left(tree))+tree_sum(tree_right(tree));
    
}




bool tree_search(tree_t tree, int val)
/*
 // EFFECTS: Returns true if the value "val" appears in "tree".
 //          Returns false otherwise.
 */
{
    if (tree_isEmpty(tree))
        return false;
    else
    {
        if (tree_elt(tree)==val)
            return true;
        else return tree_search(tree_left(tree),val)||tree_search(tree_right(tree), val);
    }
}

int depth(tree_t tree)
/*
 // EFFECTS: Returns the depth of "tree", which equals the number of
 //          layers of nodes in the tree.
 //          Returns zero if "tree" is empty.
 //
 // For example, the tree
 //
 //                           4
 //                         /   \
 //                        /      \
 //                       2        5
 //                      / \      / \
 //                         3        8
 //                        / \      / \
 //                       6   7
 //                      / \ / \
 //
 // has depth 4.
 // The element 4 is on the first layer.
 // The elements 2 and 5 are on the second layer.
 // The elements 3 and 8 are on the third layer.
 // The elements 6 and 7 are on the fourth layer.
 //
 */
{
    if (tree_isEmpty(tree))
        return 0;
    else
    {
        if (depth(tree_left(tree))>=depth(tree_right(tree)))
            return 1+depth(tree_left(tree));
        else
            return 1+depth(tree_right(tree));
    }
}




int tree_max(tree_t tree)
/*
 // REQUIRES: "tree" is non-empty.
 //
 // EFFECTS: Returns the largest element in "tree".
 */
{
    if (tree_isEmpty(tree_left(tree))&&tree_isEmpty(tree_right(tree)))
        return tree_elt(tree);
    else
    {
        if (!(tree_isEmpty(tree_left(tree)))&&!(tree_isEmpty(tree_right(tree))))
        {
            if ((tree_max(tree_left(tree))>=tree_elt(tree))&&(tree_max(tree_left(tree))>=tree_max(tree_right(tree))))
                return tree_max(tree_left(tree));
            if ((tree_max(tree_right(tree))>=tree_elt(tree))&&(tree_max(tree_right(tree))>=tree_max(tree_left(tree))))
                return tree_max(tree_right(tree));
            else
                return tree_elt(tree);
        }
        if (!(tree_isEmpty(tree_left(tree)))&&(tree_isEmpty(tree_right(tree))))
        {
            if (tree_max(tree_left(tree))>=tree_elt(tree))
                return tree_max(tree_left(tree));
            else return tree_elt(tree);
        }
        else
        {
            if (tree_max(tree_right(tree))>=tree_elt(tree))
                return tree_max(tree_right(tree));
            else return tree_elt(tree);
        }
    }
}



list_t traversal(tree_t tree)
/*
 // EFFECTS: Returns the elements of "tree" in a list using an
 //          in-order traversal. An in-order traversal prints
 //          the "left most" element first, then the second-left-most,
 //          and so on, until the right-most element is printed.
 //
 //          For any node, all the elements of its left subtree
 //          are considered as on the left of that node and
 //          all the elements of its right subtree are considered as
 //          on the right of that node.
 //
 // For example, the tree:
 //
 //                           4
 //                         /   \
 //                        /      \
 //                       2        5
 //                      / \      / \
 //                         3
 //                        / \
 //
 // would return the list
 //
 //       ( 2 3 4 5 )
 //
 // An empty tree would print as:
 // 
 //       ( )
 //
 */
{
    if (tree_isEmpty(tree))
        return list_make();
    else
        return append(append(traversal(tree_left(tree)), list_make(tree_elt(tree),list_make())), traversal(tree_right(tree)));
}

static bool lt(int a, int b)
{
    if (a>=b)
        return true;
    else
        return false;
}

static bool st(int a, int b)
{
    if (a<=b)
        return true;
    else
        return false;
}


static bool tree_hmp_helper(tree_t tree, bool (*fn)(int, int))
{
    if (tree_isEmpty(tree)||((tree_isEmpty(tree_left(tree)))&&(tree_isEmpty(tree_right(tree)))))
        return true;
    if (!(tree_isEmpty(tree_left(tree)))&&(tree_isEmpty(tree_right(tree))))
    {
        if (fn(tree_elt(tree_left(tree)),tree_elt(tree)))
            return tree_hmp_helper(tree_left(tree), fn);
        else
            return false;
    }
    if (!(tree_isEmpty(tree_right(tree)))&&(tree_isEmpty(tree_left(tree))))
    {
        if (fn(tree_elt(tree_right(tree)),tree_elt(tree)))
            return tree_hmp_helper(tree_right(tree), fn);
        else
            return false;
    }
    else
    {
        if (fn(tree_elt(tree_left(tree)),tree_elt(tree))||fn(tree_elt(tree_right(tree)),tree_elt(tree)))
            return tree_hmp_helper(tree_left(tree), fn)||tree_hmp_helper(tree_right(tree), fn);
        else
            return false;
    }
}

bool tree_hasMonotonicPath(tree_t tree)
/*
 // EFFECTS: Returns true if and only if "tree" has at least one
 //          root-to-leaf path such that all the elements along the
 //          path form a monotonically increasing or decreasing
 //          sequence.
 //
 //          A root-to-leaf path is a sequence of elements in a tree
 //          starting with the root element and proceeding downward
 //          to a leaf (an element with no children).
 //
 //          An empty tree has no root-to-leaf path.
 //
 //          A monotonically increasing (decreasing) sequence is a
 //          sequence of numbers where no number is smaller (larger)
 //          than its previous number.
 //
 // For example, the tree:
 //
 //                           4
 //                         /   \
 //                        /
 //                       8
 //                      / \
 //                     3   16
 //                    / \  / \
 //
 // has two root-to-leaf paths: 4->8->3 and 4->8->16.
 // Since the numbers on the path 4->8->16 form a monotonically
 // increasing sequence, the function should return true.
 // If we change 8 into 20, there is no such a path.
 // Thus, the function should return false.
 */

{
    if (tree_isEmpty(tree))
        return false;
    else
    {
        bool b1=0;
        bool b2=0;
        bool b3=0;
        bool b4=0;
        tree_t l= tree_left(tree);
        tree_t r=tree_right(tree);
        if (!(tree_isEmpty(l))&&(tree_elt(l)>=tree_elt(tree)))
            b1= tree_hmp_helper(l, lt);
        if (!(tree_isEmpty(l))&&(tree_elt(l)<=tree_elt(tree)))
            b2= tree_hmp_helper(l, st);
        if (!(tree_isEmpty(r))&&(tree_elt(r)>=tree_elt(tree)))
            b3= tree_hmp_helper(r, lt);
        if (!(tree_isEmpty(r))&&(tree_elt(r)<=tree_elt(tree)))
            b4= tree_hmp_helper(r, st);

        if (tree_isEmpty(r)&&tree_isEmpty(l))
            return true;
        return (b1||b2||b3||b4);
    }
    
}


bool tree_allPathSumGreater(tree_t tree, int sum)
/*
 // EFFECTS: Returns true if and only if for each root-to-leaf
 //          path of "tree", the sum of all elements along the path
 //          is greater than "sum".
 //
 //          A root-to-leaf path is a sequence of elements in a tree
 //          starting with the root element and proceeding downward
 //          to a leaf (an element with no children).
 //
 //          An empty tree has no root-to-leaf path.
 //
 // For example, the tree:
 //
 //                           4
 //                         /   \
 //                        /     \
 //                       1       5
 //                      / \     / \
 //                     3   6
 //                    / \ / \
 //
 // has three root-to-leaf paths: 4->1->3, 4->1->6 and 4->5.
 // Given sum = 9, the path 4->5 has the sum 9, so the function
 // should return false. If sum = 7, since all paths have the sums
 // greater than 7, the function should return true.
 // 
 */
{
    if (tree_isEmpty(tree))
        return false;
    else
    {
        if (tree_isEmpty(tree_left(tree))&&tree_isEmpty(tree_right(tree))&&(tree_elt(tree)>sum))
            return true;
        if (tree_isEmpty(tree_left(tree))&&tree_isEmpty(tree_right(tree))&&(tree_elt(tree)<=sum))
            return false;
        if (tree_isEmpty(tree_left(tree))&&!(tree_isEmpty(tree_right(tree))))
            return tree_allPathSumGreater(tree_right(tree),sum-tree_elt(tree));
        if (!(tree_isEmpty(tree_left(tree)))&&(tree_isEmpty(tree_right(tree))))
            return tree_allPathSumGreater(tree_left(tree),sum-tree_elt(tree));
        else
        {
            return (tree_allPathSumGreater(tree_left(tree),sum-tree_elt(tree)))&&(tree_allPathSumGreater(tree_right(tree),sum-tree_elt(tree)));
        }
        
    }
}

bool covered_by(tree_t A, tree_t B)
/*
 // EFFECTS: Returns true if tree A is covered by tree B.
 */
{
    if (tree_isEmpty(A))
        return true;
    if ((!tree_isEmpty(A))&&tree_isEmpty(B))
        return false;
    else
    {
        if (tree_elt(A)==tree_elt(B))
            return (covered_by(tree_left(A), tree_left(B)))&&(covered_by(tree_right(A), tree_right(B)));
        else
            return false;
    }
}

bool contained_by(tree_t A, tree_t B)
/*
 // EFFECTS: Returns true if tree A is covered by tree B
 //          or any complete subtree of B.
 */
{
    if (covered_by(A,B))
        return true;
    if (tree_isEmpty(B))
        return false;
    else
        return contained_by(A, tree_left(B))||contained_by(A, tree_right(B));
}

tree_t insert_tree(int elt, tree_t tree)
/*
 // REQUIRES: "tree" is a sorted binary tree.
 //
 // EFFECTS: Returns a new tree with elt inserted at a leaf such that
 //          the resulting tree is also a sorted binary tree.
 //
 // For example, inserting 1 into the tree:
 //
 //                           4
 //                         /   \
 //                        /      \
 //                       2        5
 //                      / \      / \
 //                         3
 //                        / \
 //
 // would yield
 //                           4
 //                         /   \
 //                        /      \
 //                       2        5
 //                      / \      / \
 //                     1   3
 //                    / \ / \
 // 
 */
{
    if (tree_isEmpty(tree))
        return tree_make(elt, tree_make(), tree_make());
    else
    {
        if (elt<tree_elt(tree))
            return tree_make(tree_elt(tree),insert_tree(elt,tree_left(tree)), tree_right(tree));
        else
            return tree_make(tree_elt(tree),tree_left(tree),insert_tree(elt, tree_right(tree)));
    }
    
}



















