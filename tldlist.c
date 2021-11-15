#include "date.h"
#include "tldlist.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>


 TLDNode *create_tldnode(char *tldName); // create an empty node
 int add_tldnode(TLDList *tld, char *tldname, TLDNode *node); // add nodes to the tldlist
 TLDNode *find_the_last_node(TLDNode *node); // determine the last node
 int find_node_height(TLDNode *node); // get the height of a node /left or right
 int get_height_difference(TLDNode *node); // get heigt difference between right and left subtrees
 void balance_the_node(TLDNode *node); // balancing the node after add_tldnode()
 TLDNode *balance_ll(TLDNode *node); // left -left rotation 
 TLDNode *balance_lr(TLDNode *node); // left-right rotation
 TLDNode *balance_rr(TLDNode *node); // right - right rotation
 TLDNode *balance_rl(TLDNode *node); // right - left rotation

typedef struct tldlist{
    /* counts the number successful tldlist_add()'s 
    since creation of the  tldlist */
    long count; 

    //Begin and end date constraints
    Date *begin;
    Date *end;

    //a tldlist has a root node
    TLDNode  *root;
} TLDList;

typedef struct tldnode{
/*  counts the number of times that a log entry for the
  corresponding tld was added to the list
 */
    long count;

    // tld_name  associated with the node
    char *tld_name;

    //can have right and left node and a parentnode thats not the root node
    TLDNode *parent; 
    TLDNode *right; 
    TLDNode *left; 

} TLDNode;

typedef struct tlditerator{
                  TLDNode *nodes;
            } TLDIterator;

TLDList *tldlist_create(Date *begin, Date *end){
    
    TLDList *newtld = malloc(sizeof(TLDList));

   
     
    if(newtld !=NULL){
        
        newtld->count = 0;
        newtld->begin = begin;
        newtld->end = end;
        newtld->root = NULL;

        return newtld;
    }else{
        //printf("tldlist creation failed");
        free(newtld);
        return NULL;
    } 
    
    
     
}



void tldlist_destroy(TLDList *tld){
    if(tld != NULL){

        TLDIterator *iterator = tldlist_iter_create(tld);

        TLDNode *temp_node; 

        while((temp_node = tldlist_iter_next(iterator)) !=NULL){
            free(temp_node->tld_name); // destroy the tldname associated with the tld
            free(temp_node); //destroy the tldnode
            
        }
        free(tld);  // destroy the tld
        tldlist_iter_destroy(iterator); // destroy the iterator 

    }
    
}

int tldlist_add(TLDList *tld, char *hostname, Date *d){
    // check if  date  falls in the begin and end dates associated with the list
   // printf("The Host Name is %s \n", hostname);
    if(date_compare(tld->begin, d) > 0 || date_compare(tld->end, d) < 0 ){
        // if the beginning date is past the date given or end date is before the date given
        return 0;
    }else{
    // returns a pointer to the last occurrence of the dot character to get the tldname eg returns .com, .uk etc
    char *tldtemp= strrchr(hostname, '.') + 1; // +1 removes the dot
    
    for(int i = 0; (tldtemp[i] != '\0'); i++){ // converts every charater of the tldname to lowercase
            tldtemp[i] = tolower(tldtemp[i]);  
    }
    char *tldname = malloc(sizeof(tldtemp));
    strcpy(tldname, tldtemp); //copies the tldTemp  to tldName
   // printf("The Host Name is %s \n", tldtemp);
    tld->count ++;
    return 1;
    }
   
}

long tldlist_count(TLDList *tld){

    return tld->count;
}

TLDNode *find_the_last_node(TLDNode *node){
    // recursively traverse the root node to find the last node
    if(node !=NULL){
        TLDNode *templeft = find_the_last_node(node->left);
        TLDNode *tempright = find_the_last_node(node->right);
        if(templeft !=NULL){// still not the last left node
            return templeft;
        }else if(tempright !=NULL){ // still not the last right node
            return tempright;
        }
        else{
            return node; // this is the last node
        }
    }else {
        return node; // this is the last node
    }
}

TLDIterator *tldlist_iter_create(TLDList *tld){
    TLDIterator *iterator = malloc(sizeof(TLDIterator));
    if(iterator !=NULL){
        iterator->nodes = find_the_last_node(tld->root);
        return iterator;
    }else{
        tldlist_iter_destroy(iterator);
        return NULL;
    }

}



void tldlist_iter_destroy(TLDIterator *iter) {
	free(iter->nodes); // destroy the nodes
	free(iter); // destroy the iterator
}

char *tldnode_tldname(TLDNode *node) {
	return node->tld_name;
}
long tldnode_count(TLDNode *node){
    return node->count;
}


TLDNode *tldlist_iter_next(TLDIterator *iterator) {
	TLDNode *temp = iterator->nodes;

    //printf("We are here");

	if (temp != NULL)
	{
		// check if node in iterator has a parent, if not then it is the root node
		if (iterator->nodes->parent != NULL) {
			TLDNode *tempright = iterator->nodes->parent->right;
			if (tempright != iterator->nodes && tempright != NULL){
				iterator->nodes = find_the_last_node(iterator->nodes->parent->right);
            }
			else{
				iterator->nodes = iterator->nodes->parent;
            }
		}
		else {
			iterator->nodes = NULL; // set the iterator node storage to null
			return temp; // returns the node if it is the root node of the tree
		}

	}
	else{
        return NULL;
    }
    return temp;
}

// Inserting nodes into the  TLDlist based on the tldname

/*Binary Search tree rules 
*The left subtree of a node contains only nodes with keys lesser than the node's key
* The right subtree of a node contains only nodes with keys greater than the node’s key
* The left and right subtree each must also be a binary search tree.
*/

TLDNode *create_tldnode(char *tld_name){ // creating an empty node

TLDNode *node = malloc(sizeof(TLDNode));
if(node !=NULL){
    node->parent = NULL; // New node so, no parent
    node->right = NULL; // empty node has no right or left node
    node->left  = NULL; 
    node->count = 1; // initialize the count 
    node->tld_name = tld_name; // the first tld added to the node
}else{  // memory allocation for the node has failed
    free(node); // free the node
    return NULL;
    
}
return node;

}



int add_tldnode(TLDList *tld, char *tld_name, TLDNode *node){
    if(node != NULL){  
        
        int compare_tld_names = strcmp(tld_name, node->tld_name);
        if(compare_tld_names< 0){ // comparing the size of the two tld names
            // if the tldname is smaller than the tld in the list - go left node rule no 1

            if(node->left != NULL){
                // add the node to the left node of the next node
                return add_tldnode(tld, tld_name, node->left); 
            }else {
                // create a new node
                TLDNode *temp_left =  create_tldnode(tld_name); // create new node 
                temp_left->parent = node;  // the current node becomes the parent node
                node->left        =  temp_left; // the temp node becomes the current node left node
            // balancing the  node
            balance_the_node(node->left);


           return 0;
            }

        }else if (compare_tld_names>0){
             // if the tldname is larger than the tld in the list - go right node rule no 2

             if(node->right !=NULL){
                 // // add the node to the right node of the next node
                 return add_tldnode(tld, tld_name, node->right);
             }else{
                 TLDNode *temp_right = create_tldnode(tld_name); // create a new node
                 temp_right->parent = node; // current node becomes the parent node
                 node->right        = temp_right; // the temp node becomes the right node of thr curret node
            // balance the node
            balance_the_node(node->right);
            
            return 0;
             }
       
        }else { // the tld_name already exists so no need to duplicate
            node->count++; // increase the counter to show the tld was counted
            free(tld_name); // free the memory allocated to the tld name
            return 0;
        }
    }else{
        // the node does not exist 
        TLDNode *temp_node = create_tldnode(tld_name);
        temp_node->parent = NULL; // this is the first node so it has no parent
        tld->root = temp_node; // this node becomes the root of the tldlist 
        return 0;
    }
    return 1;
}






/* 
* This section covers 
* BALANCING THE BINARY SEARCH TREE AFTER ADDING A NODE 
* Means maintaining the height of the left and right subtree are about the same
* 
*/
int find_node_height(TLDNode *node){
    if(node != NULL ){
        // recursively determine the height of the current node

        int left_node_height = find_node_height(node->left);
        int right_node_height = find_node_height(node->right);
        if(left_node_height > right_node_height){
            return left_node_height+1;
        }else{
                return right_node_height+1;
        }
    }else{
        return 0;
    }

}

/*
*balanced node if the balance factor  is -1 , 0 , or 1
* left heavy node -  balance factor of -1
*right heavy node balance factor of +1

*/

int get_height_difference(TLDNode *node){ // get the balance factor of the node 
    int left_height; 
    int right_height;
    int height_difference;


    if(node != NULL){
        left_height = find_node_height(node->left);
        right_height = find_node_height(node->right);
        height_difference = left_height - right_height;
        return height_difference;
    }else{
         height_difference = 0;
        
    }
   return  height_difference;
}

void balance_the_node(TLDNode *node){
    int height_difference = get_height_difference(node);
    if(node !=NULL){
        if(height_difference >1){
        int compare_height = get_height_difference(node->left);
        if(compare_height > 0 ){
            // left-left
            node = balance_ll(node);
        }else{
            // left-right
            node = balance_lr(node);
        }
    }else if(height_difference < -1){ 
         int compare_height = get_height_difference(node->right);
         if(compare_height>0){
             //right - left
             node = balance_rl(node);
         }else{
             //right-right
             node = balance_rr(node);
         }

    }

    }

}
 // left-left rotatition 
 TLDNode  *balance_ll(TLDNode *node){
     TLDNode *new_node = node->left;
     node->left        = new_node->right;  
     new_node->right    = node;
     return new_node;
 }

// left-right rotation
 TLDNode *balance_lr(TLDNode *node){
     TLDNode *new_node = node->left;
     node->left          = balance_rr(new_node);

     return balance_ll(node);
 }
 
 // right-right rotation
   TLDNode *balance_rr(TLDNode *node){
     TLDNode *new_node = node->right;
     node->right      = new_node->left;
     new_node->left    = node;

     return new_node;

 }

// Right -left  rotation
 TLDNode *balance_rl(TLDNode *node){
     TLDNode *new_node = node->right;
     node->right = balance_ll(new_node);
     return balance_rr(node);
 }

