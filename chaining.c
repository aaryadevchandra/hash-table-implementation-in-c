#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define HASH_TABLE_SIZE 2000000000
#define TOKEN_LEN 50

//dynamically making linked lists
struct node {
   char token[TOKEN_LEN];
   struct node* next;
};

struct LinkedList {
  struct node* head;
  struct node* cur;
  int len;
};

// also have to pass the instance of linked list since there are multiple
void add_node( char token[], struct LinkedList* ll)
{
  if(ll->head == NULL){
    struct node* nn = malloc(sizeof(struct node));
    strcpy(nn->token, token);
    nn->next = NULL;
    ll->head = nn;
    ll->cur = nn;
    nn = NULL;
  }
  else{
    struct node* nn = malloc(sizeof(struct node));
    strcpy(nn->token, token);
    nn->next = NULL;
    ll->cur->next = nn;
    ll->cur = nn;
    nn = NULL;
  }
}

void display_linkedList ( struct LinkedList* ll ){
  if (ll->head == NULL ) {
    printf("\nZero elements in linked list....exiting...");
    exit(1);
  }
  else
  {
    struct node* ptr = ll->head;
    while ( ptr != NULL) {
      printf("%s, ", ptr->token);
      ptr = ptr->next;
    }
  }
  printf("\n\n");
}


// only interface with this function to create a new linked list
// returns pointer to struct, store that for future reference
struct LinkedList* _new_ll_head ( )
{

  struct LinkedList* ll = malloc(sizeof(struct LinkedList));
  ll->head = NULL;
  ll->cur = NULL;

  return ll;
}

struct HashTable {
  struct LinkedList* arr[HASH_TABLE_SIZE];
};

struct HashTable* get_hash_table (  ){
  // creates instance of hash table
  struct HashTable* ht = malloc(sizeof(struct HashTable));


  // intialiazes hash table with *node
  memset(ht->arr, 0, HASH_TABLE_SIZE);
}


long hash(char* key) {
	long hashVal = 0;
	while (*key != '\0') {
		hashVal = (hashVal << 4) + *(key++);
		long g = hashVal & 0xF0000000L;
		if (g != 0) hashVal ^= g >> 24;
		hashVal &= ~g;
	}
	return hashVal;
}

void hash_table_insert(struct HashTable* ht, char key[])
{

  if(ht->arr[hash(key)] == NULL){
    struct LinkedList* ll = _new_ll_head();
    ht->arr[hash(key)] = ll;
    add_node(key, ht->arr[hash(key)]);
    ht->arr[hash(key)]->len++;
  }
  else if(ht->arr[hash(key)]->head != NULL) {
    add_node(key, ht->arr[hash(key)]);
    ht->arr[hash(key)]->len++;
  }

}


int delete_from_ll( struct LinkedList* ll, char key[] )
{
  struct node* ptr = ll->head;

  while(ptr != NULL)
  {
    // if match
    if( !strcmp(ptr->next->token, key)) {
      ptr->next = ptr->next->next;
      return 1;
    }
    ptr = ptr->next;
  }
  return -1;
}



// delete from HashTable

void hash_table_delete(struct HashTable* ht, char key_to_delete[])
{

  if ( ht->arr[hash(key_to_delete)]->head != NULL && ht->arr[hash(key_to_delete)]->len == 1)
  {
    // directly nullify linked list belonging to specified key
    ht->arr[hash(key_to_delete)] = NULL;
  }
  else if(ht->arr[hash(key_to_delete)]->head != NULL && ht->arr[hash(key_to_delete)]->len > 1){
    // need to delete from linked list since there are  > 1 keys in the hash value
    delete_from_ll(ht->arr[hash(key_to_delete)], key_to_delete);
  }
  else {
    printf("\nkey %s doesn't exist in hash table", key_to_delete);
    return ;
  }


}






int main()
 {
   // instantiate linked list instead of node
   // let node instantiation be handled internally in linked list


   // _new_ll returns a new instance of a linked list
   // struct node* ll1 = _new_ll();


   // initializing hash table
   struct HashTable* ht = get_hash_table();



   // yay works
//    printf("%p\n", ht->arr[hash("hello")]);
//    hash_table_insert(ht, "hello");
//    hash_table_insert(ht, "hello");
//    printf("%p\n", ht->arr[hash("hello")]);
// display_linkedList(ht->arr[hash("hello")]);
//    hash_table_delete(ht, "hello");
//
//    display_linkedList(ht->arr[hash("hello")]);


//    struct LinkedList* ll = _new_ll_head();
//
//    add_node("hello", ll);
//    add_node("my", ll);
//    add_node("sweet", ll);
//    add_node("senpai", ll);
//
//    display_linkedList(ll);
//
//    delete_from_ll(ll, "sweet");
//
//
// display_linkedList(ll);






 }
