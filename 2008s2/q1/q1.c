// check whether a tree is a binary search tree (BST)
int isBST(Tree t)
{
	//Check if it's empty
	int bool = 1;
	if (t == NULL){ // No tree
		bool = 1;
	} else if (t->left == NULL && t->right == NULL){ //1 level
		bool = 1;
	} else {
		char root = t->data;

		Tree currleft = t->left;
		while (t->left != NULL){		//Checking all left children
			while (currleft->right !=NULL){
				if (currleft->right->data < currleft->data || currleft->right->data > root){
					bool = 0;
					break;
				}
				currleft = currleft->right;
			}
			if (t->left->data > t->data){
				bool = 0;
				break;
			}
			t = t->left;
			currleft = t;
		}
		Tree currright = t->right;
		while (t->right != NULL){		//Checking all right children
			while (currright->left != NULL){
				if (currright->left->data > currright->data || currright->left->data < root){
					bool = 0;
					break;
				}
				currright = currright->left;
			}
			if (t->right->data < t->data){
				bool = 0;
				break;
			}
			t = t->right;
			currright = t;
		}
	}
	return bool;
}
