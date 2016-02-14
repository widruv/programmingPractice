#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct stack{
	char address[71];
	struct stack *next;
} STACK;

void push(STACK **, char *);
char* pop(STACK**);
char pop_char[71];

int main(int argc, char**argv)
{
	char input[100];
	char current_address[71];
	char* temp;
	char* command;
	char init_address[]="http://www.acm.org/";
	char back[] = "BACK";
	char forward[] = "FORWARD";
	char visit[] = "VISIT";
	char quit[] = "QUIT";

	strncpy(current_address, init_address, sizeof(current_address)-1);
	current_address[sizeof(current_address)-1]='\0';

	STACK *back_head;
	STACK *forward_head;
	back_head = (STACK*)malloc(sizeof(STACK));
	back_head->next= NULL;
	forward_head = (STACK*)malloc(sizeof(STACK));
	forward_head->next= NULL;

	while(1)
	{
		char *input_address;
		fflush(stdin);
		fgets(input,sizeof(input),stdin);
		input[strlen(input)-1]='\0';

		command = strtok(input," ");
		input_address = strtok(NULL," ");

		if(!strncmp(back,command,sizeof(back)))
		{
			if(isEmpty(back_head)==0)
				printf("Ignored\n");
			else
			{
				push(&forward_head,current_address);
				temp = pop(&back_head);
				strncpy(current_address,temp,sizeof(current_address)-1);
				current_address[sizeof(current_address)-1]='\0';
				printf("%s\n",current_address);
			}
		}
		else if(!strncmp(forward,command,sizeof(forward)))
		{
			if(isEmpty(forward_head)==0)
				printf("Ignored\n");
			else
			{
				push(&back_head,current_address);
				temp = pop(&forward_head);
				strncpy(current_address,temp,sizeof(current_address)-1);
				current_address[sizeof(current_address)-1]='\0';
				printf("%s\n",current_address);
			}
		}
		else if(!strncmp(visit,command,sizeof(visit)))
		{
			if(strlen(input_address)>71)
				printf("Ignored\n");
			else
			{
				push(&back_head,current_address);
				printf("%s\n",input_address);
				strncpy(current_address, input_address,sizeof(current_address)-1);
				current_address[sizeof(current_address)-1]='\0';
				while(isEmpty(forward_head)==1)
					pop(&forward_head);
			}
		}
		else if(!strncmp(quit,command,sizeof(quit)))
		{
			while(isEmpty(forward_head)==1)
					pop(&forward_head);
			while(isEmpty(back_head)==1)
					pop(&back_head);
			free(back_head);
			free(forward_head);
			break;
		}
		else
		{
			printf("Ignored\n");
		}

	}
	return 0;
}



void push(STACK **head, char* address)
{
	STACK *node = (STACK*)malloc(sizeof(STACK));
	strncpy(node->address,address,sizeof(node->address)-1);
	node->address[sizeof(node->address)-1]='\0';
	node->next = *head;
	*head = node;
}

char* pop(STACK **head)
{
	STACK *top = *head;
	strncpy(pop_char,top->address,sizeof(pop_char)-1);
	pop_char[sizeof(pop_char)-1]='\0';
	*head = top->next;
	free(top);

	return pop_char;
}

int isEmpty(STACK *head)
{
	if(head->next==NULL)
		return 0;
	else
		return 1;
}
