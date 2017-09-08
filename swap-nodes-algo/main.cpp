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

void build_tree(node_sp& root, std::list<std::pair<int,int>>& nodes, int level) {
    if (nodes.empty()) {
        return;
    }

    const std::pair<int, int> n = nodes.front();
    nodes.pop_front();

    if (n.first >= 0) {
        root->children[node::Left] = make_shared<node>(n.first);
        root->children[node::Left]->level = level + 1;
        build_tree(root->children[node::Left], nodes, level + 1);
    }
    if (n.second >= 0) {
        root->children[node::Right] = make_shared<node>(n.second);
        root->children[node::Right]->level = level + 1;
        build_tree(root->children[node::Right], nodes, level + 1);
    }

}

void swap_bfs(node_sp& root, int level) {
    int cur_level = 1;
    list<node_sp> nodes = {root};

    do {
        if (level == cur_level) {
            for (const auto& n : nodes) {
                std::swap(n->children[0], n->children[1]);
            }

            break;
        }

        list<node_sp> new_nodes;
        for (const auto& n : nodes) {
            if (n->children[0]) new_nodes.push_back(n->children[0]);
            if (n->children[1]) new_nodes.push_back(n->children[1]);
        }

        nodes = new_nodes;

        ++ cur_level;
    } while(1);
}

void printLevelOrder(const node_sp& root) {
    if (!root) return;
    queue<node_sp> nodesQueue;
    int nodesInCurrentLevel = 1;
    int nodesInNextLevel = 0;
    nodesQueue.push(root);
    while (!nodesQueue.empty()) {
        node_sp currNode = nodesQueue.front();
        nodesQueue.pop();
        nodesInCurrentLevel--;
        if (currNode) {
            cout << currNode->data << " ";
            nodesQueue.push(currNode->children[0]);
            nodesQueue.push(currNode->children[1]);
            nodesInNextLevel += 2;
        }
        if (nodesInCurrentLevel == 0) {
            cout << endl;
            nodesInCurrentLevel = nodesInNextLevel;
            nodesInNextLevel = 0;
        }
    }
}

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */

    std::ifstream in("./in.txt");
    std::streambuf *cinbuf = std::cin.rdbuf(); //save old buf
    std::cin.rdbuf(in.rdbuf()); //redirect std::cin to in.txt!

    int N;
    cin >> N;
    std::list<std::pair<int,int>> nodes;
    for (int i = 0; i < N; ++i) {
        std::pair<int,int> p;
        cin >> p.first;
        cin >> p.second;

        nodes.push_back(p);
    }

    int T;
    cin >> T;
    vector<int> K(T);
    copy(istream_iterator<int>(cin), istream_iterator<int>(), K.begin());

    node_sp root = make_shared<node>(1);

    build_tree(root, nodes, 1);

    for (const auto &k : K) {
        printLevelOrder(root);
        swap_bfs(root, k);
        cout << endl;
    }

    return 0;
}