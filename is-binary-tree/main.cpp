/* Hidden stub code will pass a root argument to the function below. Complete the function to solve the challenge. Hint: you may want to write one or more helper functions.  

The Node struct is defined as follows:
   struct Node {
      int data;
      Node* left;
      Node* right;
   }
*/
   void checkTree(Node* root, int& min, int &max, bool& ok) {
       if (root) {
           min = root->data < min ? root->data : min;
           max = root->data > max ? root->data : max;
           
           int new_min = 1000000, new_max = 0;
           
           if (root->left) {
               checkTree(root->left, new_min, new_max, ok);
               ok = ok && new_max < root->data;
               
           }
           
           if (root->right) {
               checkTree(root->right, new_min, new_max, ok);
               ok = ok && new_max > root->data;
           
           }

           min = new_min < min ? new_min : min;
           max = new_max > max ? new_max : max;
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
       int min = 10000000, max = 0;
       checkTree(root, min, max, ok);
       return ok;
   }

