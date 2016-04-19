// find longest ascending sublist
// return pointer to node at start of sublist
List flas(List L)
{
	int count = 0;
	int max = 0;
	int temp = 0;
	Node *currlong = NULL;
	Node *templong = NULL;
	if (L == NULL){
		return L;
	} else if (L->next == NULL){
		return L->next;
	} else { 
		while (L->next->next != NULL){
			Node *curr = L;
			if (L->next->data > L->data){
				//handle
				if (count == 0 && currlong == NULL){
					currlong = curr;
				} else if (count == 0 && currlong !=NULL){
					templong = curr;
					Node *n = templong;
					while (templong->next != NULL){
						if (n->next->data > n->data){
							temp++;
						}
						n = n->next;
					}
				}
				count++;
			}
			if (max < count){
				max = count; 
			}
			if (temp > max){
				currlong = templong;
			}
			count = 0;
			L = L->next;
		}
	}
	return currlong; /// causes a segfault
}
