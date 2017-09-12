#include <cmath>
#include <cstdio>
#include <vector>
#include <list>
#include <iostream>
#include <algorithm>
#include <memory>
#include <iterator>
#include <fstream>
#include <iomanip>
#include <queue>

using namespace std;

struct node;

using node_up = std::unique_ptr<node>;
using node_sp = std::shared_ptr<node>;

struct node {
    enum Side {
        Left = 0,
        Right = 1
    };

    node() : node(0) {}
    explicit node(int data) : data(data), level(1) {}

    bool is_leaf() const { return !left && !right; }

    Side which_side(int data) {
       return this->data >= data ? Right : Left;
    }

    int data;
    int level;

    node_sp children[2];
};

void traverse_inorder(node_sp& root) {
    if (!root) return;
    traverse_inorder(root->children[0]);
    std::cout << root->data << " ";
    traverse_inorder(root->children[1]);
}

void build_bfs(node_sp& root, std::list<std::pair<int,int>>& nodeIdexes, int& depth) {
    list<node_sp> nodes = {root};

    depth = 1;

    while (!nodeIdexes.empty() && !nodes.empty()) {
        list<node_sp> new_nodes;
        for (auto& n : nodes) {
            const auto &e = nodeIdexes.front();
            nodeIdexes.pop_front();

            if (e.first != -1) {
                n->children[0] = std::make_shared<node>(e.first);
                new_nodes.push_back(n->children[0]);
            }
            if (e.second != -1) {
                n->children[1] = std::make_shared<node>(e.second);
                new_nodes.push_back(n->children[1]);
            }
        }

        depth += !new_nodes.empty();

        nodes = new_nodes;
    };
}

void swap_bfs(node_sp& root, int K) {
    int cur_level = 1;
    list<node_sp> nodes = {root};

    do {
        if ((cur_level % K) == 0) {
            for (const auto& n : nodes) {
                std::swap(n->children[0], n->children[1]);
            }
        }

        list<node_sp> new_nodes;
        for (const auto& n : nodes) {
            if (n->children[0]) new_nodes.push_back(n->children[0]);
            if (n->children[1]) new_nodes.push_back(n->children[1]);
        }

        nodes = new_nodes;

        ++ cur_level;
    } while(!nodes.empty());
}

struct Trunk
{
    Trunk *prev;
    string str;

    Trunk(Trunk *prev, string str)
    {
        this->prev = prev;
        this->str = str;
    }
};

// Helper function to print branches of the binary tree
void showTrunks(Trunk *p)
{
    if (p == nullptr)
        return;

    showTrunks(p->prev);

    cout << p->str;
}

void printTree(const node_sp& root, Trunk *prev, bool isLeft)
{
    if (root == nullptr)
        return;

    string prev_str = "	";
    Trunk *trunk = new Trunk(prev, prev_str);

    printTree(root->children[0], trunk, true);

    if (!prev)
        trunk->str = "---";
    else if (isLeft)
    {
        trunk->str = ".---";
        prev_str = "   |";
    }
    else
    {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    cout << root->data << endl;

    if (prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->children[1], trunk, false);
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    std::ifstream in("./in.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

    int N;
    cin >> N;
    std::list<std::pair<int,int>> nodeIdexes;

    for (int i = 0; i < N; ++i) {
        std::pair<int,int> p;
        cin >> p.first;
        cin >> p.second;

        nodeIdexes.push_back(p);
    }

    int T;
    cin >> T;
    vector<int> K(T);
    copy(istream_iterator<int>(cin), istream_iterator<int>(), K.begin());

    node_sp root = make_shared<node>(1);

    int depth;
    build_bfs(root, nodeIdexes, depth);

    for (const auto &k : K) {
        //printTree(root, nullptr, false);
        swap_bfs(root, k);
        traverse_inorder(root);
        cout << endl;
    }

    return 0;
}