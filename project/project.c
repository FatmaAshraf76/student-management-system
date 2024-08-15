#include <stdio.h>
#include <stdlib.h>

#define TRUE 1
#define FALSE 0

struct student
{
	int id;
	char name[50];
	int age;
	float gpa;
};

struct node
{
	struct student data;
	struct node *next;
};

struct node *head=NULL;

void addStudent(const struct student *const ptr);
void updateStudent(int id);
void displayStudents(void);
float calculateAverageGPA(void);
void deleteStudent(int id);
void searchStudentByID(int id);
void searchHighestGPA(void);
int isfound(int id);

int main(void)
{
	while(1)
	{
		setvbuf(stdout, NULL, _IONBF, 0);
		setvbuf(stderr, NULL, _IONBF, 0);
		int num=0;
		int id=0;
		struct student new_student;
    	printf("\n 1->addStudent \n 2->displayStudents \n 3->searchStudentByID \n 4->updateStudent \n 5->deleteStudent \n 6->calculateAverageGPA \n 7->searchHighestGPA \n else->break \n");
    	scanf("%d",&num);
    	switch(num)
    	{
    	case 1: printf("enter the new student details(id ,name ,age ,gpa)\n");
    		    scanf("%d",&new_student.id);
    		    scanf("%s ",new_student.name);
    		    scanf("%d",&new_student.age);
    		    scanf("%f",&new_student.gpa);
    		    addStudent(&new_student);
    	 break;
    	case 2: displayStudents();
    	 break;
    	case 3: printf("enter the student id :");
	            scanf("%d",&id);
    		    searchStudentByID(id);
    	 break;
    	case 4: printf("enter the student id :");
    	        scanf("%d",&id);
    		    updateStudent(id);
    	 break;
    	case 5: printf("enter the student id :");
                scanf("%d",&id);
    		    deleteStudent(id);
    	 break;
    	case 6: printf("the average GPA: %f",calculateAverageGPA());
    	 break;
    	case 7: searchHighestGPA();
    	 break;
    	default: printf("EXIT \n");
    	return 0;
    	}
	}
}

void searchStudentByID(int id)
{
	if(head==NULL)         //is empty
	{
		printf("the student was not found and the list is empty\n");
	}
	struct node *current = head;
	while(current != NULL)
	{
		if(current->data.id == id)
		{
			printf("the student details\n");
			printf("***************************************\n");
			printf("name: %s \n ",current->data.name);
			printf(" id: %d \n",current->data.id);
			printf(" age: %d \n",current->data.age);
			printf(" gpa: %f \n",current->data.gpa);
			printf("***************************************\n");
			return ;
		}
		current = current->next;
	}
	printf("the student was not found\n");

}

int isfound(int id)
{
	if(head==NULL)         //is empty
	{
		return FALSE;
	}
	struct node *current = head;
	while(current != NULL)
	{
		if(current->data.id == id)
		{
			return TRUE;
		}
		current = current->next;
	}
	return FALSE;
}

void addStudent(const struct student *const ptr)
{
	int id=ptr->id;
	if(!isfound(id))
	{
		struct node *newnode=(struct node*) malloc(sizeof(struct node));
		newnode->data=*ptr;
		newnode->next = NULL;
		if (newnode==NULL)
		{
			printf("error memory is already full\n");
			return;
		}
		else
		{
			struct node *current = NULL;
			if(head==NULL)               //is empty
			{
				head=newnode;
				return;
			}
			current = head;
			while(current->next != NULL)
			{
				current = current->next;
			}
			current->next = newnode;
		}
	}
	else
	{
		printf(" error the student's ID already exists\n");
		return;
	}
}

void displayStudents(void)
{
	struct node *ptr = head;
	if(head==NULL)         //is empty
	{
		 printf("no students are present\n");
		return ;
	}
	printf("***************************************\n");
	while(ptr != NULL)
	{
		printf("name: %s \n ",ptr->data.name);
		printf(" id: %d \n",ptr->data.id);
		printf(" age: %d \n",ptr->data.age);
		printf(" gpa: %f \n",ptr->data.gpa);
		printf("***************************************\n");
		ptr = ptr->next;
	}
}

void updateStudent(int id)
{
	if(!isfound(id))
	{
		printf("the student was not found\n");
		return;
	}
	struct node *current = head;
	while(current != NULL)
	{
		if(current->data.id == id)
		{
			printf("please enter the new data(name, age, gpa) \n");
			scanf("%s ",current->data.name);
			scanf("%d",&current->data.age);
			scanf("%f",&current->data.gpa);
			return;
		}
		current = current->next;
	}
}

float calculateAverageGPA(void)
{
	float averageGPA=0,totalGPA=0,noOfStudents=0;
	if(head==NULL)         //is empty
	{
		return 0;
	}
	struct node *current = head;
	while(current != NULL)
	{
		totalGPA+=current->data.gpa;
		noOfStudents++;
		current = current->next;
	}
	averageGPA=totalGPA/noOfStudents;
	return averageGPA;
}

void searchHighestGPA(void)
{
	float max=0;
	int id;
	if(head==NULL)         //is empty
	{
		printf("there are no students\n");
		return;
	}
	struct node *current = head;
	while(current != NULL)
	{
		if(current->data.gpa >max)
		{
			max=current->data.gpa;
			id=current->data.id;
		}
		current = current->next;
	}
	searchStudentByID(id);
}

void deleteStudent(int id)
{
	// pointer to loop in linked list
	struct node *current = head;
	struct node *prev = NULL;
	// pointer to point the node that will be deleted
	struct node * delete_node = NULL;
	if(head==NULL)         //is empty
	{
		printf("there are no students\n");
		return;
	}
	if(!isfound(id))                 //if id not found
	{
		printf("the student was not found\n");
		return;
	}
	if(head->data.id == id)   //check the first student
	{
		delete_node = head;
		head = head->next;
		free(delete_node);
		printf("the student is deleted successfully \n");
		return;
	}
	current = head->next;
	prev = head;
	while(current != NULL)    //check the rest of students
	{
		if(current->data.id==id)
		{
			delete_node = current;
			prev->next = current->next;
			free(delete_node);
			printf("the student is deleted successfully \n");
			return;
		}
		current = current->next;
	}
}
