#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define HASH_TABLE_SIZE 2000000000
#define TOKEN_LEN 50
#define NUMTOKENS 100 // number of elements / strings in the hash table

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

  if(ll == NULL) {
    printf("\nLinked List doesn't exist\n");
    return ;
  }


  if (ll->head == NULL ) {
    printf("\nZero elements in linked list....exiting...");
    exit(1);
  }
  else
  {
    struct node* ptr = ll->head;
    while ( ptr != NULL) {
      printf("%s ", ptr->token);
      ptr = ptr->next;
    }
  }
  printf("\n");
}


// only interface with this function to create a new linked list
// returns pointer to struct, store that for future reference
struct LinkedList* _new_ll_head ( )
{

  struct LinkedList* ll = malloc(sizeof(struct LinkedList));
  ll->head = NULL;
  ll->cur = NULL;
  ll->len = 0;
  return ll;
}

struct HashTable {
  struct LinkedList* arr[HASH_TABLE_SIZE];

  long int present_hashes[NUMTOKENS];
  int present_hashes_index;
};

struct HashTable* get_hash_table (  ){
  // creates instance of hash table
  struct HashTable* ht = malloc(sizeof(struct HashTable));

  // intialiazes hash table with *node
  memset(ht->arr, 0, HASH_TABLE_SIZE);
  memset(ht->present_hashes, 0, NUMTOKENS);

  ht->present_hashes_index = 0;

  return ht;
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
  long int key_hash = hash(key);

  if(ht->arr[key_hash] == NULL){
    struct LinkedList* ll = _new_ll_head();
    ht->arr[key_hash] = ll;
    add_node(key, ht->arr[key_hash]);
    ht->arr[key_hash]->len++;

    ht->present_hashes[ht->present_hashes_index] = key_hash;
    ht->present_hashes_index++;
  }
  else if(ht->arr[key_hash]->head != NULL) {
    add_node(key, ht->arr[key_hash]);
    ht->arr[key_hash]->len++;

    ht->present_hashes[ht->present_hashes_index] = key_hash;
    ht->present_hashes_index++;
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

  printf("\nDeleting key => '%s'", key_to_delete);

  long int key_hash = hash(key_to_delete);


if(ht->arr[key_hash] == NULL) {
  printf("\nHash not found in table...");
  return ;
}

  if ( ht->arr[key_hash]->head != NULL && ht->arr[key_hash]->len == 1)
  {

    // directly nullify linked list belonging to specified key
    ht->arr[key_hash] = NULL;

//////////////////////////////////
    for ( int i =0 ; i < 100; i ++ )
    {
      if(  ht->present_hashes[i]  == key_hash)  {
        ht->present_hashes[i] = 0;
      }
    }

    printf("\nKey => '%s' successfully deleted", key_to_delete);
    ////////////////////
  }
  else if(ht->arr[key_hash]->head != NULL && ht->arr[key_hash]->len > 1){

    // need to delete from linked list since there are  > 1 keys in the hash value
    if (delete_from_ll(ht->arr[key_hash], key_to_delete) == 1){
      printf("\nDeleted key => %s from table", key_to_delete);
      return;
    }
    else{
      printf("\nCouldn't find key => %s in table", key_to_delete);
      return ;
    }
  }


}

void display_hash_table ( struct HashTable* ht)
{

  printf("\n\n");
  printf("Hash Table\n");
  printf("--------------------\n");
  for ( int i=0 ;i<100;i++)
  {

    if( ht->present_hashes[i] != 0) {

      printf("%lld", ht->present_hashes[i]);
      printf(" ==> ");
      display_linkedList(ht->arr[ht->present_hashes[i]]);
    }

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

  hash_table_insert(ht, "hello");
  hash_table_insert(ht, "my");
  hash_table_insert(ht, "sweet");
  hash_table_insert(ht, "senpai");


  // display_linkedList(ht->arr[hash("hello")]);
  // display_linkedList(ht->arr[hash("my")]);
  // display_linkedList(ht->arr[hash("sweet")]);
  // display_linkedList(ht->arr[hash("senpai")]);

  display_hash_table(ht);


  // printf("\n\n\ngoing under now\n\n\n");

  // printf("\n%d", ht->arr[hash("hello")]->len);
  // printf("\n%d", ht->arr[hash("my")]->len);
  // printf("\n%d", ht->arr[hash("sweet")]->len);
  // printf("\n%d", ht->arr[hash("senpai")]->len);


  hash_table_delete(ht, "my");


display_hash_table(ht);
  //
  // display_linkedList(ht->arr[hash("hello")]);
  // display_linkedList(ht->arr[hash("my")]);
  // display_linkedList(ht->arr[hash("sweet")]);
  // display_linkedList(ht->arr[hash("senpai")]);

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
