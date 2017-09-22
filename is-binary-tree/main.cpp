/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node struct is defined as follows:
   struct Node {
      int data;
      Node* left;
      Node* right;
   }
*/
void check_r(Node* root, int &min, int &max, bool &result) {
    min = root->data < min ? root->data : min;
    max = root->data > max ? root->data : max;
    if (root->left) {
        int left_subtree_min = 100000, left_subtree_max = -100000;
        check_r(root->left, left_subtree_min, left_subtree_max, result);
        if (left_subtree_max >= root->data) {
            result = false;
            return;
        }


        min = std::min(min, left_subtree_min);
        min = std::min(min, left_subtree_max);
        max = std::max(max, left_subtree_min);
        max = std::max(max, left_subtree_max);
    }
    if (root->right) {
        int right_subtree_min = 100000, right_subtree_max = -100000;
        check_r(root->right, right_subtree_min, right_subtree_max, result);
        if (right_subtree_min <= root->data) {
            result = false;
            return;
        }

        min = std::min(min, right_subtree_min);
        min = std::min(min, right_subtree_max);
        max = std::max(max, right_subtree_min);
        max = std::max(max, right_subtree_max);
    }
}

bool checkBST(Node* root) {
    int subtree_min = 100000, subtree_max = -100000;
    bool result = true;
    check_r(root, subtree_min, subtree_max, result);
    return result;
}
