/*#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
#define PRIME 1009 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t queue_full=PTHREAD_COND_INITIALIZER;
pthread_cond_t queue_empty=PTHREAD_COND_INITIALIZER;
int counter = 0;
typedef struct record{
	char* key;
	char* value;
}record;
struct queue{
	record data;
	queue *next;
};
typedef struct hash_table{
	record rec;
	hash_table* next;
}hash_table;

hash_table** table = (hash_table**)calloc(150, sizeof(hash_table*));


int hash_function(char* str){
	long long int hash = 0;
	int i = 0;
	for (; str[i] != '\0'; i++){
		hash += str[i] * (PRIME + i);
	}
	return hash % 150;
}


void add_to_hashtable(hash_table** ht, int hash_value, record rec){
	hash_table* created = (hash_table*)malloc(sizeof(hash_table));
	created->rec = rec;
	created->next = NULL;
	if (ht[hash_value] == NULL){
		ht[hash_value] = created;
	}
	else{
		hash_table *temp;
		for (temp = ht[hash_value]; temp->next != NULL; temp = temp->next);
		temp->next = created;
	}

}

void insertRecord(hash_table** table, record rc){
	
	int hash_value = hash_function(rc.key);
	add_to_hashtable(table, hash_value, rc);
}

void display(hash_table** table){
	for (int i = 0; i < 150; i++){
		hash_table* temp;
		temp = table[i];
		if (temp == NULL){
			printf("NO RECORD:%d\n", i);
		}
		else{
			for (; temp != NULL; temp = temp->next){
				printf("{%s : %s}\n", temp->rec.key, temp->rec.value);
			}
		}
	}
}

void displayRecord(hash_table** table, char* str){
	int h_value = hash_function(str);
	hash_table* temp;
	temp = table[h_value];
	if (temp == NULL)
	{
		printf("NOT FOUND\n");
	}
	else{
		for (; temp != NULL; temp = temp->next){
			if (strcmp(temp->rec.key, str) == 0){
				printf("{%s : %s}\n", temp->rec.key, temp->rec.value);
			}
		}
	}
}


void removeRecord(hash_table** table, char* str){
	int h_value = hash_function(str);

	if (strcmp(table[h_value]->rec.key, str) == 0){
		table[h_value] = table[h_value]->next;
	}
	else{
		hash_table* temp;
		hash_table* prev;
		for (temp = table[h_value]; (strcmp(table[h_value]->rec.key, str) != 0); temp = temp->next);
		for (prev = table[h_value]; prev->next != temp; prev = prev->next);
		prev->next = temp->next;
		free(temp);
	}

}

queue *head;
queue *createNode(char* key, char *value)
{
	queue *node = (queue*)malloc(sizeof(queue));
	record rc;
	rc.key = key;
	rc.value = value;
	node->data = rc;
	node->next = NULL;
	return node;
}
void enque()
{
	pthread_mutex_lock(&mutex);
	if (counter == 20){
		pthread_cond_wait(&queue_empty, &mutex);
	}
	char *key="hello123";
	char *value = "bye123";
	
	queue *temp = createNode(key, value);
	queue *current = head;
	if (head == NULL)
	{
		head = temp;
	}
	else{
		while (current->next != NULL)
		{
			current = current->next;
		}
		current->next = temp;
	}
	counter++;
	pthread_cond_signal(&queue_full);
	pthread_mutex_unlock(&mutex);
}
void deque()
{
	pthread_mutex_lock(&mutex);
	while (true)
	{
		if (counter < 1)
		{
			pthread_cond_wait(&queue_full, &mutex);
		}


		printf("entered De\n");
		record d = head->data;
		head = head->next;
		insertRecord(table, d);
		counter--;
	}
	pthread_cond_signal(&queue_empty);
	pthread_mutex_unlock(&mutex);
}


void *proThread(void *x)
{
	enque();
	return NULL;
}
void *conThread(void *args)
{
	deque();
	return NULL;
}
int main()
{
	
	int t = 100;
	pthread_t proThread1, conThread1, conThread2, conThread3;
	while (t!=0)
	{
		pthread_create(&proThread1, NULL,proThread, NULL);
		pthread_create(&conThread1, NULL,conThread,NULL);
		pthread_create(&conThread2, NULL, conThread,NULL); 
		pthread_create(&conThread3, NULL, conThread,NULL);
		t--;
	}

}
*/