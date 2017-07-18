#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<pthread.h>
struct msg{
	char text[100];
	int msg_id;
};
FILE *fp=fopen("C:/Users/Gali Tharun/Documents/Visual Studio 2013/Projects/user1.txt", "wb+");
FILE *fp1 = fopen("C:/Users/Gali Tharun/Documents/Visual Studio 2013/Projects/user2.txt", "rb");
void *read_operation(void* )
{
	msg *new_msg = (msg*)calloc(1, sizeof(msg));
	while (1)
	{
		while (fread(new_msg, sizeof(msg), 1, fp1)==0)
		{
		}
		printf("Tharun:%s\n", new_msg->text);
	}
}
void *write_operation(void *)
{
	while (true)
	{
		msg *new_msg = (msg*)calloc(1, sizeof(msg));
		scanf("%s", new_msg->text);
		fwrite(new_msg, sizeof(msg), 1, fp);
		fflush(fp);
	}
	return NULL;
}
int main()
{
	pthread_t ReadThread, WriteThread;
	pthread_create(&WriteThread, NULL, write_operation, NULL);
	pthread_create(&ReadThread, NULL, read_operation, NULL);
	pthread_join(ReadThread, NULL);
	pthread_join(WriteThread, NULL);
	return 0;
}