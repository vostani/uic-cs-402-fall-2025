#include <vector>
#include <string>
#include <bits/stdc++.h>

// be sure to change FIRSTNAME and LASTNAME with your own first and last name
#include "Sreten_Kljaic_project3.h"

using namespace std;

/****************
 * INSTRUCTIONS *
 ****************
 *
 * - Replace all instances of "Firstname_Lastname" with your firstname and
 *   your last name. This include the .h and .cpp files, along with the
 *   header guards at the top of the .h file.
 *
 * - Implement solutions to the problems described below.
 *   You must follow the specifications as written below.
 *
 * - Certain function signatures may not be modified (as it will affect auto
 *   grading). These functions will be specified.
 *
 * - You are allowed to add helper functions. Be sure to add the appropriate
 *   function prototypes in "Fistname_Lastname_project3.h."
 *
 * - If you are working in a group, please modify the comments directly below.
 *   
 * - IMPORTANT: If you are working in a group, every member is expected to submit their
 *   source code individually.
 *
 */


/*** GROUP PROJECT ***/
// Please list ALL of your other group members as comments below.
//   Member 1
//   Member 2


/* Problem 1: "Weird" Tree Traversal (Trees)
 *
 * 25 Points
 *
 * In this problem, you are asked to implement what I am calling "weird"
 * traversal on a tree.
 *
 * Definition: A weird traversal on an arbitrary rooted tree (i.e., a node can have
 * any number of children) proceeds as follows.
 *
 *   - First, the traversal visits all even layers in level-order, where we
 *     define the root to be layer 0, its children as layer 1, etc. "Level-
 *     order" here means visiting the nodes in layer i from left to right, 
 *     followed by nodes in layer i+2 from left to right (for even i). In
 *     other words, this traversal, starting from the root, visits all even
 *     layers in level-order (top to bottom, left to right).
 *
 *   - Once all even layers have been visited, all of the odd layers are then
 *     visited, bottom to top and right to left. In other words, this traversal
 *     visits the deepest odd layer first, from right most node to left most node,
 *     then proceeds back up, with the children of the root visited last.
 * 
 * Problem 
 *  - Given a pointer to the root of a Tree (specified as a TreeNode in
 *    the header file), output a vector of integers which represents the 
 *    weird-traversal of the tree.
 *
 * Grading
 *  - This problem is easily solvable using 2 traversals. This will only give
 *    you 15 points. To get full marks, you must solve this problem doing
 *    a single traversal of the tree.
 *      - Note this also means you cannot copy this tree into a different
 *        representation, as this would be at least 2 traversals to solve
 *        the problem (one to put the tree into a different format, then
 *        another traversal to perform weird-traversal).
 * 
 * Assumptions
 *  - Each node in the tree has a unique integer id. However, you cannot
 *    assume that the root is id 0, its first child has id 1, etc. The
 *    ids in the tree are only guaranteed to be unique.
 *  - The tree is in the first-child, next-sibling representation. That is,
 *    a node in a tree only has 2 pointers: one to its first (i.e., left-
 *    most) child, and one to its first (i.e., right) sibling.
 *
 * Examples
 *  - Tree in first-child, next-sibling representation. Consider the following
 *    tree:
 *       0
 *     / | \
 *    1  2  3
 *      /    \
 *     4      5
 *   / | \   /||\
 *  6  7 8  9 ab c
 *
 *    The first-child, next-sibling representation turns this tree into an equivalent
 *    binary tree, where a left branch is the first child in the above tree, and a
 *    right branch is the next sibling in the above tree:
 *               0
 *             /
 *           1
 *             \
 *             [  2  ]
 *            /      \
 *           4       3
 *          /       /
 *         6       5
 *          \     /
 *           7   9
 *            \   \
 *             8   a
 *                  \
 *                   b
 *                    \
 *                     c
 *
 * - Weird-traversal of above tree, given pointer to root labeled "a":
 *   [0, 4, 5, c, b, a, 9, 8, 7, 6, 3, 2, 1]
 *
 * - Other weird-traversal examples
 *    (a)    1   -> [1, 3, 2]
 *         /  \
 *        2    3
 *
 *    (b) -1    -> [-1, 3, 6, -9, 7, 2]
 *        / \
 *      2    7
 *       \  / \
 *       3 6  -9
 */

// Do not modify this function signature.
vector<int> weird_traversal(TreeNode* root) {
    if (!root) return {};

    vector<int> evenLevels;
    deque<vector<int>> oddLevelsStack; 

    queue<pair<TreeNode*, int>> q;
    q.emplace(root, 0);

    while (!q.empty()) {
        int levelSize = q.size();
        vector<int> currentLevel;
        int depth = q.front().second;

        for (int i = 0; i < levelSize; ++i) {
            auto [node, _] = q.front(); q.pop();
            currentLevel.push_back(node->id);

            TreeNode* child = node->first_child;
            while (child) {
                q.emplace(child, depth + 1);
                child = child->next_sibling;
            }
        }

        reverse(currentLevel.begin(), currentLevel.end());

        if (depth % 2 == 0) {
            evenLevels.insert(evenLevels.end(),
                              currentLevel.begin(), currentLevel.end());
        } else {
            oddLevelsStack.push_front(std::move(currentLevel));
        }
    }

    vector<int> result = std::move(evenLevels);
    for (auto& lev : oddLevelsStack) {
        result.insert(result.end(), lev.begin(), lev.end());
    }
    return result;
}



/* Problem 2: Bits-to-Tree (Trees)
 *
 * 25 Points
 *
 * In this problem, you are given a vector of bits which represents 
 * a DFS traversal of a tree with the following properties:
 *  1. Non-empty: the tree always has at least 1 node (the root).
 *  2. Unlabeled: the nodes in the tree are not labeled.
 *  3. Ordered: the children of each noded are ordered from left to right.
 *
 * Your goal is to reconstruct the tree given the vector of bits, using
 * the TreeNode struct. The bits in the vector correspond to a DFS
 * traversal in the following way:
 *  - A '1' represents a "down" traversal; and
 *  - A '0' represents a "up" traversal.
 * Moreover, this DFS traversal visits each child in left-to-right order.
 *
 * Helpful Properties of this Problem
 *  - For a tree with n nodes, the input "bits" is valid if and only if
 *      - bits has exactly n-1 1's and n-1 0's;
 *      - bits has even length (i.e., = 2(n-1)); and
 *      - For any prefix of bits (i.e., bits[0,..,i]), #0s <= #1s
 *
 * Other Considerations
 *  - The tree is guaranteed to be non-empty. What type of input would lead
 *    to a tree that is a single root node?
 *  - Defining a helper function for this problem could be useful.
 *
 * Grading
 *  - The returned pointer must be the root of the tree you have reconstructed,
 *    or the nullptr if 'bits' is not a valid encoding.
 *  - Additionally, label each node from 0 to n-1, where the ID of the node
 *    corresponds to its ordering during the pre-order DFS traversal.
 *  - Using your own TreeNode type which represents a tree in a format other
 *    than specified to construct your solution will only yield 15 points. For
 *    full marks, directly construct your tree using the TreeNode struct.
 * 
 * Examples
 *  - [1, 0] ->  0
 *              /
 *             1
 *
 *  - [1, 0, 1, 0, 1, 1, 0, 1, 0, 0]
 *      -> (in a format where each node has a vector of children)
 *                0
 *              / | \
 *             1  2   3
 *                   | \
 *                   4  5
 *      -> (in the required first-child, next sibling format)
 *               0
 *              /
 *             1
 *             \
 *              2
 *               \
 *                3
 *               /
 *              4
 *               \
 *                5
 */

// Do not modify this fuction signature
TreeNode* bits_to_tree(const vector<bool>& bits) {
    int n = bits.size();
    if (n % 2 != 0) return nullptr;                
    int nodes = n / 2 + 1;                         
    if (nodes == 0) return nullptr;                

    int count1 = 0;
    int balance = 0;
    for (bool b : bits) {
        if (b) {
            ++count1;
            ++balance;
        } else {
            --balance;
        }
        if (balance < 0) return nullptr;
    }
    if (balance != 0 || count1 != nodes - 1) return nullptr;

    vector<TreeNode*> stack;
    int id = 0;

    if (bits.empty()) {
        TreeNode* root = new TreeNode;
        root->id = 0;
        return root;
    }

    TreeNode* root = new TreeNode;
    root->id = id++;
    stack.push_back(root);

    for (bool bit : bits) {
        if (bit) {
            TreeNode* newNode = new TreeNode;
            newNode->id = id++;
            TreeNode* parent = stack.back();
            if (parent->first_child == nullptr) {
                parent->first_child = newNode;
            } else {
                TreeNode* child = parent->first_child;
                while (child->next_sibling != nullptr) {
                    child = child->next_sibling;
                }
                child->next_sibling = newNode;
            }

            stack.push_back(newNode);
        } else {
            if (stack.empty()) return nullptr;
            stack.pop_back();
        }
    }

    return root;
}


/* Problem 3: Light Post Problem (Trees + Dynamic Programming)
 *
 * 25 points
 *
 * This problem is an extension of the Binary Tree Cameras problem from LeetCode 
 * we did in class (https://leetcode.com/problems/binary-tree-cameras/description/).
 *
 * Problem: You are given an "unrooted" tree (i.e., an undirected graph with no 
 * cycles and exactly n-1 edges for n nodes). Any node could be picked arbitrarily
 * as the root. Moreover, this is a general tree in that a node can have any
 * number of children.
 *
 * You need to select a subset of nodes to place light towers to illuminate all
 * nodes. When a light tower is placed on a node, it illuminates:
 *  - The node the light tower is placed on; and
 *  - All neighbors of that node (i.e., all children and its parent).
 * Additionally, each node has a cost associated with placing a light tower on it.
 *
 * Your objective is to illuminate all nodes in the graph such that the cost
 * of the placed light towers is minimized. 
 *
 * The output of your solution will be a pair<int, vector<Node>>. The first
 * element of the pair is the cost of the 
 *
 * Assumptions
 *  - The given graph has nodes uniquely labeled from 0 to n-1.
 *  - The function has 3 input parameters:
 *      - int n: number of Nodes in the graph.
 *      - vector<Edge>& edges: list of edges in the graph.
 *      - vector<int>& costs: vector of costs such that node i has cost 
 *        costs[i].
 *  - The function outputs a pair of type <int, vector<Node>> with the
 *    following properties:
 *      - pair.first is an integer representing the minimum computed cost
 *      - pair.second is a vector of integers representing the ids of each
 *        node which has a light post placed on it (in other words, this
 *        is your subset of nodes you have chosen to minimize the costs).
 *  - edges will be a valid tree (though it will not have a root).
 *
 * Additional Information
 *  - There is a "Node" struct defined in the header file which you may use
 *    in your implementation if you think it will be helfpul.
 *  - Think about if it matters which node you choose as the root
 *
 * Grading
 *  - Your algorithm must run in poolynoimial time in the size of the input.
 * 
 * Examples
 *  - (n=1, edges = {}, costs = {5}) -> { 5, {0}}
 *  - (n=2, edges = { (0,1) }, costs = {1,2}) -> { 1, {0}}
 *  - (n=3, edges = { (0,1), (0,2) }, costs = {50, 2, 3}) -> {5, {1,2}}
 */

// Do not modify this function signature
pair<int, vector<int>> light_post_problem(int n, const vector<Edge>& edges, const vector<int>& costs) {
    if (n == 0) return {0, {}};
    
    vector<vector<int>> adj(n);
    for (const auto& e : edges) {
        adj[e.u].push_back(e.v);
        adj[e.v].push_back(e.u);
    }
    
    vector<vector<long long>> dp(n, vector<long long>(3, 0));
    vector<vector<vector<int>>> choice(n, vector<vector<int>>(3));
    
    vector<int> parent(n, -1);
    
    function<void(int, int)> dfs1 = [&](int u, int par) {
        parent[u] = par;
        vector<int> children;
        for (int v : adj[u]) {
            if (v != par) {
                children.push_back(v);
                dfs1(v, u);
            }
        }
        
        // dp[u][0]
        long long cost0 = costs[u];
        vector<int> sel0;
        for (int child : children) {
            if (dp[child][1] <= dp[child][2]) {
                cost0 += dp[child][1];
                sel0.insert(sel0.end(), choice[child][1].begin(), choice[child][1].end());
            } else {
                cost0 += dp[child][2];
                sel0.insert(sel0.end(), choice[child][2].begin(), choice[child][2].end());
            }
        }
        dp[u][0] = cost0;
        sel0.push_back(u);
        choice[u][0] = sel0;
        
        // dp[u][2]
        long long cost2 = 0;
        vector<int> sel2;
        for (int child : children) {
            cost2 += dp[child][1];
            sel2.insert(sel2.end(), choice[child][1].begin(), choice[child][1].end());
        }
        dp[u][2] = cost2;
        choice[u][2] = sel2;
        
        // dp[u][1]
        long long cost1 = LLONG_MAX / 2;
        vector<int> sel1;
        for (int cov_child : children) {
            long long cur = 0;
            vector<int> cur_sel;
            cur += dp[cov_child][0];
            cur_sel.insert(cur_sel.end(), choice[cov_child][0].begin(), choice[cov_child][0].end());
            for (int child : children) {
                if (child == cov_child) continue;
                if (dp[child][1] <= dp[child][2]) {
                    cur += dp[child][1];
                    cur_sel.insert(cur_sel.end(), choice[child][1].begin(), choice[child][1].end());
                } else {
                    cur += dp[child][2];
                    cur_sel.insert(cur_sel.end(), choice[child][2].begin(), choice[child][2].end());
                }
            }
            if (cur < cost1) {
                cost1 = cur;
                sel1 = cur_sel;
            }
        }
        if (children.empty()) {
            cost1 = LLONG_MAX / 2;
        }
        dp[u][1] = cost1;
        choice[u][1] = sel1;
    };
    
    int root = 0;
    dfs1(root, -1);
    
    long long min_cost = LLONG_MAX;
    vector<int> best_sel;
    
    // Case 1
    if (dp[root][0] < min_cost) {
        min_cost = dp[root][0];
        best_sel = choice[root][0];
    }
    
    // Case 2
    if (dp[root][1] < min_cost) {
        min_cost = dp[root][1];
        best_sel = choice[root][1];
    }
    
    // Case 3
    long long cost3 = dp[root][2] + costs[root];
    vector<int> sel3 = choice[root][2];
    sel3.push_back(root);
    if (cost3 < min_cost) {
        min_cost = cost3;
        best_sel = sel3;
    }
    
    sort(best_sel.begin(), best_sel.end());
    
    return {(int)min_cost, best_sel};
}

/* Problem 4: Smallest Subset Sum (Dynamic Programming)
 * 
 * 25 points
 *
 * In this problem, you will tackle the classic subset sum problem, but with a twist.
 *
 * Subset Sum Overview: First, recall the subset sum problem. 
 *  - Input: A list of n positive integers A = {a_1, ..., a_n} and a target value T.
 *  - Output: true if there exists a set S, which is a subset of {1,...,n} such that
 *      sum(A[i], i in S) = T, false otherwise.
 *    Equivalently written in C++:
 *      int sum = 0;
 *      for(i in S): sum += A[i];
 *      return (sum == T);
 *
 * Basic Dynamic Programming Algorithm; Runtime: O(nT)
 *  - We can solve the above formulation of the subset sum problem using
 *    a table of booleans M of dimensions M [1..n][0..T]. For every i=1 to
 *    n and j=0 to T, set M[i][j] = true if and only if a target sum of
 *    j can be formed from a subset of {a_1, ..., a_i} (and false otherwise).
 *      - Base cases:
 *          - M[i][0] = true for all i=1 to n (empty set has zero sum).
 *          - M[1][a_1] = true (singleton case).
 *          - M[1][j] = false for all j != a_1.
 *      - Induction: for i > 1
 *          M[i][j] = true if 
 *              M[i-1][j] = true || (j >= a_i) && (M[i-1][j-a_i] = true)
 *          (false otherwise)
 *  - Then, M[n][T] is the answer to the problem (i.e., if it is true then
 *    there exists a subset satisfying the subset sum property).
 *
 * Smallest Subset Sum: In this problem, you are tasked with solving the subset
 * sum problem, but with the following twists: 
 *  1. You must return the subset S such that sum(A[i], i in S) = T.
 *  2. S must be the smallest possible subset satisfying 1 above.
 *  3. S must be the lexicographically first subset (as there could be multiple
 *     smallest subsets).
 * Consider the following example to help your understanding:
 *  - Input: A = {1, 1, 2, 3, 1, 4}, T = 5
 *  - There are 8 possible subsets for the target sum:
 *      1. {A[1], A[2], A[3], A[5]} = {1, 1, 2, 1}
 *      2. {A[1], A[2], A[4]} = {1, 1, 3}
 *      3. {A[1], A[4], A[5]} = {1, 3, 1}
 *      4. {A[1], A[6]} = {1, 4}
 *      5. {A[2], A[4], A[5]} = {1, 3, 1}
 *      6. {A[2], A[6]} = {1, 4}
 *      7. {A[3], A[4]} = {2, 3}
 *      8. {A[5], A[6]} = {1, 4}
 *    Subsets 4, 6, 7, 8 are all of size 2, so they are the smallest ones.
 *  - Output: S = {1, 6}
 *      Reason: A[1]+A[6] == 5 
 *              && S.size() == 2 
 *              && {1,6} is lexicographically smaller than {2,6}, {3,4}, and {5,6}
 *              (note this is left-right ordering of the vector).
 *  
 * Assumptions
 *  - The function has 3 input parameters
 *      - unsigned int n: number of elements in the vector 'values'.
 *      - unsigned int t: target sum (assumed >= 1).
 *      - vector<pair<unsigned int, string>>& values: vector of pairs with 
 *        the following properties: for i=0 to n-1, p = values[i]:
 *          - p.first = A[i+1] (the vector of values to be summed to target t).
 *            Always assumed to be >= 1.
 *          - p.second = just some string that is tied to the value A[i+1].
 *  - The function outputs a vector<pair<unsigned int, string>> with the following
 *    properties: let out be this vector
 *      unsigned int sum = 0;
 *      vector<unsigned int> order;
 *      for(i = 0; i < out.size(); ++i) {
 *          unsigned int idx = out[i].first;
 *          sum += values[idx].first;
 *          out[i].second == values[idx].second; // the strings match as well!
 *          order.push_back(idx);
 *      }
 *      sum == t; // should be true!
 *      order is lexicographic minimum subset
 *
 * Other Information
 *  - The strings in pair<unsigned int, string> here are to help distinguish elements of
 *    the set from each other, since integers within the set are not assumed to be unique.
 *    For exmple, if we modify the above example to
 *      values = { {1, "dog"}, {1, "cat"}, {2, "bird"}, {3, "mouse"}, {1, "snake"}, {4, "fish"} }
 *    Then setting t = 5, the returned answer would be
 *      out = { {1, "dog"}, {4, "fish"} }.
 *
 * Grading
 *  - Your solution must be asymptotically equivalent to the basic subset sum problem.
 *    That is, you must run in time O(nT). Note this means that you cannot enumerate
 *    all possible subsets! Doing so will only give you a maximum of 5 points.
 *  - A maximum of 15 points will be given to those who return a minimum sized solution, but
 *    not the lexicographically smallest one.
 */

// Do not modify this function signature
vector<pair<unsigned int,string>> smallest_subset_sum(unsigned int n, unsigned int t, const vector<pair<unsigned int, string>>& values) {
    std::vector<std::vector<unsigned int>> dp(n + 1, std::vector<unsigned int>(t + 1, UINT_MAX));
    std::vector<std::vector<int>> prev(n + 1, std::vector<int>(t + 1, -1));

    for (unsigned int i = 0; i <= n; ++i) {
        dp[i][0] = 0;
    }

    for (unsigned int i = 1; i <= n; ++i) {
        unsigned int val = values[i - 1].first;
        for (unsigned int j = 0; j <= t; ++j) {
            dp[i][j] = dp[i - 1][j];
            prev[i][j] = -1;

            if (j >= val && dp[i - 1][j - val] != UINT_MAX) {
                unsigned int candidate_size = dp[i - 1][j - val] + 1;
                if (candidate_size < dp[i][j]) {
                    dp[i][j] = candidate_size;
                    prev[i][j] = i - 1;
                }
            }
        }
    }

    if (dp[n][t] == UINT_MAX) {
        return {};
    }

    std::vector<pair<unsigned int, string>> result;
    unsigned int curr_sum = t;
    int curr_i = n;

    while (curr_sum > 0) {
        bool found = false;
        for (int k = curr_i - 1; k >= 0; --k) {
            unsigned int val = values[k].first;
            if (curr_sum >= val && dp[k][curr_sum - val] != UINT_MAX &&
                dp[k + 1][curr_sum] == dp[k][curr_sum - val] + 1) {
                result.emplace_back(k, values[k].second);
                curr_sum -= val;
                curr_i = k;
                found = true;
                break;
            }
        }
        if (!found) {
            return {};
        }
    }

    std::reverse(result.begin(), result.end());
    return result;
}


int main() {
    return 0;
}

