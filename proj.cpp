#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include <map>
#include <set>
using namespace std;

struct slot
{
	char *value;
	int row;
	struct slot *next;
};

struct bucket
{
	int num;
	struct slot *head;
};

int hash33(char *key)
{
	int i, k;
	unsigned int hv = 0;
	k = strlen(key);
	for(i = 0; i < k; ++i)
	{
		hv = (hv<<5)+hv+key[i];
	}
	hv = hv % 10;
	return hv;

}

int main()
{
	/*create hash tables*/
	FILE *fbookr = fopen("books.txt", "r");
	FILE *fsellr = fopen("sellRecord.txt", "r");
	FILE *fb1 = fopen("books_isbn.txt", "w+");
	FILE *fb2 = fopen("books_author.txt", "w+");
	FILE *fb3 = fopen("books_title.txt", "w+");
	FILE *fb4 = fopen("books_price.txt", "w+");
	FILE *fb5 = fopen("books_subject.txt", "w+");
	FILE *fs1 = fopen("sellRecord_uid.txt", "w+");
	FILE *fs2 = fopen("sellRecord_no.txt", "w+");
	FILE *fs3 = fopen("sellRecord_isbn_no.txt", "w+");

	struct bucket *b_isbn = (struct bucket *)malloc(sizeof(struct bucket) * 10);
	struct bucket *b_auth = (struct bucket *)malloc(sizeof(struct bucket) * 10);
	struct bucket *b_title = (struct bucket *)malloc(sizeof(struct bucket) * 10);
	struct bucket *b_price = (struct bucket *)malloc(sizeof(struct bucket) * 10);
	struct bucket *b_sub = (struct bucket *)malloc(sizeof(struct bucket) * 10);
	struct bucket *s_uid = (struct bucket *)malloc(sizeof(struct bucket) * 10);
	struct bucket *s_no = (struct bucket *)malloc(sizeof(struct bucket) * 10);
	struct bucket *s_isbn = (struct bucket *)malloc(sizeof(struct bucket) * 10);
	
	map<string, vector<string> > book;
	map<string, vector<string> > sell;
	
	string book_attr[] = {"isbn", "author", "title", "price", "subject"};
	string sell_attr[] = {"uid", "no", "isbn_no"};
	set<string> bookset(book_attr, book_attr+5);
	set<string> sellset(sell_attr, sell_attr+3);
	if(sellset.find("isbn_no") != sellset.end())
	  cout << "yes\n";
	else
	  cout << "no\n";

	//initialize all hash tables
	for(int i = 0; i < 10; ++i)
	{
		b_isbn[i].head = NULL;
		b_isbn[i].num = 0;
		b_auth[i].head = NULL;
		b_auth[i].num = 0;
		b_title[i].head = NULL;
		b_title[i].num = 0;
		b_price[i].head = NULL;
		b_price[i].num = 0;
		b_sub[i].head = NULL;
		b_sub[i].num = 0;
		s_uid[i].head = NULL;
		s_uid[i].num = 0;
		s_no[i].head = NULL;
		s_no[i].num = 0;
		s_isbn[i].head = NULL;
		s_isbn[i].num = 0;
	}

	//hash tables for books
	char tmp[150], token[100];
	int len, i, j = 0, bucket, row = 0;
	fgets(tmp, sizeof(tmp), fbookr);
	while(fgets(tmp, sizeof(tmp), fbookr) != NULL)
	{
		row++;
		len = strlen(tmp);
		//isbn
		for(i = 0; i < len; ++i)
		{
			if(tmp[i] == '|')
			{
				token[j] = '\0';
				//for database table
				book["isbn"].push_back(string(token));
				//for hash table
				bucket = hash33(token);
				char *value = (char *)malloc(sizeof(char) * strlen(token) + 1);
				for(int k = 0; k <= strlen(token); ++k)
				  value[k] = token[k];
				struct slot *new_slot = (struct slot *)malloc(sizeof(struct slot));
				new_slot->value = value;
				new_slot->row = row;
				new_slot->next = b_isbn[bucket].head;
				b_isbn[bucket].head = new_slot;
				b_isbn[bucket].num++;
				j = 0;
				i++;
				break;
			}
			else
				token[j++] = tmp[i];
		}

		//author
		for(; i < len; ++i)
		{
			if(tmp[i] == '|')
			{
				token[j] = '\0';
				//for database table
				book["author"].push_back(string(token));
				//for hash table
				bucket = hash33(token);
				char *value = (char *)malloc(sizeof(char) * strlen(token) + 1);
				for(int k = 0; k <= strlen(token); ++k)
				  value[k] = token[k];
				struct slot *new_slot = (struct slot *)malloc(sizeof(struct slot));
				new_slot->value = value;
				new_slot->row = row;
				new_slot->next = b_auth[bucket].head;
				b_auth[bucket].head = new_slot;
				b_auth[bucket].num++;
				j = 0;
				i++;
				break;
			}
			else
				token[j++] = tmp[i];
		}
		
		//title
		for(; i < len; ++i)
		{
			if(tmp[i] == '|')
			{
				token[j] = '\0';
				//for database table
				book["title"].push_back(string(token));
				//for hash table
				bucket = hash33(token);
				char *value = (char *)malloc(sizeof(char) * strlen(token) + 1);
				for(int k = 0; k <= strlen(token); ++k)
				  value[k] = token[k];
				struct slot *new_slot = (struct slot *)malloc(sizeof(struct slot));
				new_slot->value = value;
				new_slot->row = row;
				new_slot->next = b_title[bucket].head;
				b_title[bucket].head = new_slot;
				b_title[bucket].num++;
				j = 0;
				i++;
				break;
			}
			else
				token[j++] = tmp[i];
		}
		
		//price
		for(; i < len; ++i)
		{
			if(tmp[i] == '|')
			{
				token[j] = '\0';
				//for database table
				book["price"].push_back(string(token));
				//for hash table
				bucket = hash33(token);
				char *value = (char *)malloc(sizeof(char) * strlen(token) + 1);
				for(int k = 0; k <= strlen(token); ++k)
				  value[k] = token[k];
				struct slot *new_slot = (struct slot *)malloc(sizeof(struct slot));
				new_slot->value = value;
				new_slot->row = row;
				new_slot->next = b_price[bucket].head;
				b_price[bucket].head = new_slot;
				b_price[bucket].num++;
				j = 0;
				i++;
				break;
			}
			else
				token[j++] = tmp[i];
		}
		
		//subject
		for(; i < len; ++i)
		{
			if(tmp[i] <= 13)
			{
				token[j] = '\0';
				//for database table
				book["subject"].push_back(string(token));
				//for hash table
				bucket = hash33(token);
				char *value = (char *)malloc(sizeof(char) * strlen(token) + 1);
				for(int k = 0; k <= strlen(token); ++k)
				  value[k] = token[k];
				struct slot *new_slot = (struct slot *)malloc(sizeof(struct slot));
				new_slot->value = value;
				new_slot->row = row;
				new_slot->next = b_sub[bucket].head;
				b_sub[bucket].head = new_slot;
				b_sub[bucket].num++;
				//printf("len : %d, %d\n", tmp[strlen(tmp)-2], tmp[strlen(tmp)-1]);
				j = 0;
				i++;
				break;
			}
			else
				token[j++] = tmp[i];
		}
	}

	//hash tables for sellRecord
	row = 0;
	fgets(tmp, sizeof(tmp), fsellr);
	while(fgets(tmp, sizeof(tmp), fsellr) != NULL)
	{
		row++;
		len = strlen(tmp);
		//uid
		for(i = 0; i < len; ++i)
		{
			if(tmp[i] == '|')
			{
				token[j] = '\0';
				//for database table
				sell["uid"].push_back(string(token));
				//for hash table
				bucket = hash33(token);
				char *value = (char *)malloc(sizeof(char) * strlen(token) + 1);
				for(int k = 0; k <= strlen(token); ++k)
				  value[k] = token[k];
				struct slot *new_slot = (struct slot *)malloc(sizeof(struct slot));
				new_slot->value = value;
				new_slot->row = row;
				new_slot->next = s_uid[bucket].head;
				s_uid[bucket].head = new_slot;
				s_uid[bucket].num++;
				j = 0;
				i++;
				break;
			}
			else
				token[j++] = tmp[i];
		}
		//no
		for(; i < len; ++i)
		{
			if(tmp[i] == '|')
			{
				token[j] = '\0';
				//for database table
				sell["no"].push_back(string(token));
				//for hash table
				bucket = hash33(token);
				char *value = (char *)malloc(sizeof(char) * strlen(token) + 1);
				for(int k = 0; k <= strlen(token); ++k)
				  value[k] = token[k];
				struct slot *new_slot = (struct slot *)malloc(sizeof(struct slot));
				new_slot->value = value;
				new_slot->row = row;
				new_slot->next = s_no[bucket].head;
				s_no[bucket].head = new_slot;
				s_no[bucket].num++;
				j = 0;
				i++;
				break;
			}
			else
				token[j++] = tmp[i];
		}
		//isbn_no
		for(; i < len; ++i)
		{
			if(tmp[i] <= 13)
			{
				token[j] = '\0';
				//for database table
				sell["isbn_no"].push_back(string(token));
				//for hash table
				bucket = hash33(token);
				char *value = (char *)malloc(sizeof(char) * strlen(token) + 1);
				for(int k = 0; k <= strlen(token); ++k)
				  value[k] = token[k];
				struct slot *new_slot = (struct slot *)malloc(sizeof(struct slot));
				new_slot->value = value;
				new_slot->row = row;
				new_slot->next = s_isbn[bucket].head;
				s_isbn[bucket].head = new_slot;
				s_isbn[bucket].num++;
				//printf("len : %d, %d\n", tmp[strlen(tmp)-2], tmp[strlen(tmp)-1]);
				j = 0;
				i++;
				break;
			}
			else
				token[j++] = tmp[i];
		}

	}
	
	for(int i = 0; i < 10; ++i)
	{
		//print the isbn hash table
		fprintf(fb1, "Bucket %d\t", i);
		struct slot *ptr = b_isbn[i].head;
		for(int j = 0; j < b_isbn[i].num; ++j)
		{
			if(j != b_isbn[i].num-1)
			  fprintf(fb1, "<%s>, ", ptr->value);
			else
			  fprintf(fb1, "<%s>", ptr->value);
			ptr = ptr->next;
		}
		fprintf(fb1, "\n");

		//print the author hash table
		fprintf(fb2, "Bucket %d\t", i);
		ptr = b_auth[i].head;
		for(int j = 0; j < b_auth[i].num; ++j)
		{
			if(j != b_auth[i].num-1)
			  fprintf(fb2, "<%s>, ", ptr->value);
			else
			  fprintf(fb2, "<%s>", ptr->value);
			ptr = ptr->next;
		}
		fprintf(fb2, "\n");
		
		//print the title hash table
		fprintf(fb3, "Bucket %d\t", i);
		ptr = b_title[i].head;
		for(int j = 0; j < b_title[i].num; ++j)
		{
			if(j != b_title[i].num-1)
			  fprintf(fb3, "<%s>, ", ptr->value);
			else
			  fprintf(fb3, "<%s>", ptr->value);
			ptr = ptr->next;
		}
		fprintf(fb3, "\n");
	
		//print the price hash table
		fprintf(fb4, "Bucket %d\t", i);
		ptr = b_price[i].head;
		for(int j = 0; j < b_price[i].num; ++j)
		{
			if(j != b_price[i].num-1)
			  fprintf(fb4, "<%s>, ", ptr->value);
			else
			  fprintf(fb4, "<%s>", ptr->value);
			ptr = ptr->next;
		}
		fprintf(fb4, "\n");

		//print the subject hash table
		fprintf(fb5, "Bucket %d\t", i);
		ptr = b_sub[i].head;
		for(int j = 0; j < b_sub[i].num; ++j)
		{
			if(j != b_sub[i].num-1)
			  fprintf(fb5, "<%s>, ", ptr->value);
			else
			  fprintf(fb5, "<%s>", ptr->value);
			ptr = ptr->next;
		}
		fprintf(fb5, "\n");
		
		//print the sell_uid hash table
		fprintf(fs1, "Bucket %d\t", i);
		ptr = s_uid[i].head;
		for(int j = 0; j < s_uid[i].num; ++j)
		{
			if(j != s_uid[i].num-1)
			  fprintf(fs1, "<%s>, ", ptr->value);
			else
			  fprintf(fs1, "<%s>", ptr->value);
			ptr = ptr->next;
		}
		fprintf(fs1, "\n");
		
		//print the sell_no hash table
		fprintf(fs2, "Bucket %d\t", i);
		ptr = s_no[i].head;
		for(int j = 0; j < s_no[i].num; ++j)
		{
			if(j != s_no[i].num-1)
			  fprintf(fs2, "<%s>, ", ptr->value);
			else
			  fprintf(fs2, "<%s>", ptr->value);
			ptr = ptr->next;
		}
		fprintf(fs2, "\n");
		
		//print the sell_isbn hash table
		fprintf(fs3, "Bucket %d\t", i);
		ptr = s_isbn[i].head;
		for(int j = 0; j < s_isbn[i].num; ++j)
		{
			if(j != s_isbn[i].num-1)
			  fprintf(fs3, "<%s>, ", ptr->value);
			else
			  fprintf(fs3, "<%s>", ptr->value);
			ptr = ptr->next;
		}
		fprintf(fs3, "\n");
	}
	fclose(fb1);
	fclose(fb2);
	fclose(fb3);
	fclose(fb4);
	fclose(fb5);
	fclose(fs1);
	fclose(fs2);
	fclose(fs3);

	//process command
	vector<string> attrs;
	vector<string> tables;
	bool distinct, no_con;
	char ch;
	while(1)
	{
		no_con = false;
		distinct = false;
		scanf("%s", tmp);
		if(tmp[0] == '0')
		  break;
		
		//read in the query
		if(strcmp(tmp, "SELECT") == 0)
		{
			cin >> tmp;
			if(strcmp(tmp, "DISTINCT") == 0)
			{
				distinct = true;
				cin >> tmp;
			}
			//read all the query attributes
			while(1)
			{
				if(strcmp(tmp, "FROM") == 0)
				  break;
				attrs.push_back(string(tmp));
				cin >> tmp;
			}
			//read all query tables
			while(1)
			{
				scanf("%s", tmp);
				if(strcmp(tmp, "WHERE") == 0)
				  break;
				
				if(tmp[strlen(tmp)-1] == ',')
				{
					tmp[strlen(tmp)-1] = '\0';
					tables.push_back(string(tmp));	
				}
				else if(tmp[strlen(tmp)-1] == ';')	//end of line
				{
					no_con = true;
					tmp[strlen(tmp)-1] = '\0';
					tables.push_back(string(tmp));
					break;
				}
				else
				  tables.push_back(string(tmp));
			}
			//read all the query WHERE condition (if any)
		}
		else
		  printf("Invalid command.\n");
		
		//process the query
		for(int i = 0; i < tables.size(); ++i)
		  cout << tables.at(i) << endl;
	}

	return 0;
}
