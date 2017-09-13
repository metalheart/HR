/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node struct is defined as follows:
   struct Node {
      int data;
      Node* left;
      Node* right;
   }
*/
   void checkTree(Node* root, int value, bool isLeft, bool& ok) {
       if (root) {
           if (root->left) {
               if (root->data >= root->right->data) {
                   ok = false;
                   return;
               } else {
                   checkTree(root->right, root->data, false, ok);
               }
           }
           
           if (root->right) { 
               if (root->data <= root->left->data) {
                   ok = false;
                   return;
               } else {
                   checkTree(root->left, root->data, true, ok);
               }
           }
       }
   }

   bool checkBST(Node* root) {
      /*std::list<Node*> nodes = {root};
       while(!nodes.empty()) {
           std::list<Node*> new_nodes;
           for (const auto& n : nodes) {
               if (n->left) {
                   if (n->left->data > n->data) return false;
                   new_nodes.push_back(n->left);
               }
               if (n->right) {
                   if (n->right->data < n->data) return false;
                   new_nodes.push_back(n->right);
               }
           }
           
           nodes = new_nodes;
       }
       
       return true;*/
       bool ok = true;
       checkTree(root, 0, ok);
       return ok;
   }

