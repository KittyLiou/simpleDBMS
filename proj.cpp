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

int hash33(const char *key)
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

string belong_table(map<string, set<string> > sets, string s)
{
	if(sets["books"].find(s) != sets["books"].end())
	  return string("books");
	if(sets["sellRecord"].find(s) != sets["sellRecord"].end())
	  return string("sellRecord");
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
	
	map<string, struct bucket *> hash_table;
	hash_table["isbn"] = (struct bucket *)malloc(sizeof(struct bucket) * 10);
	hash_table["author"] = (struct bucket *)malloc(sizeof(struct bucket) * 10);
	hash_table["title"] = (struct bucket *)malloc(sizeof(struct bucket) * 10);
	hash_table["price"] = (struct bucket *)malloc(sizeof(struct bucket) * 10);
	hash_table["subject"] = (struct bucket *)malloc(sizeof(struct bucket) * 10);
	hash_table["uid"] = (struct bucket *)malloc(sizeof(struct bucket) * 10);
	hash_table["no"] = (struct bucket *)malloc(sizeof(struct bucket) * 10);
	hash_table["isbn_no"] = (struct bucket *)malloc(sizeof(struct bucket) * 10);
	
	map<string, map<string, vector<string> > > tables;
	map<string, int> table_row_num;
	
	string book_attr[] = {"isbn", "author", "title", "price", "subject"};
	string sell_attr[] = {"uid", "no", "isbn_no"};
	map<string, set<string> > sets;
	sets["books"]=  set<string>(book_attr, book_attr+5);
	sets["sellRecord"]=  set<string>(sell_attr, sell_attr+3);

	//initialize all hash tables
	for(int i = 0; i < 10; ++i)
	{
		hash_table["isbn"][i].head = NULL;
		hash_table["isbn"][i].num = 0;
		hash_table["author"][i].head = NULL;
		hash_table["author"][i].num = 0;
		hash_table["title"][i].head = NULL;
		hash_table["title"][i].num = 0;
		hash_table["price"][i].head = NULL;
		hash_table["price"][i].num = 0;
		hash_table["subject"][i].head = NULL;
		hash_table["subject"][i].num = 0;
		hash_table["uid"][i].head = NULL;
		hash_table["uid"][i].num = 0;
		hash_table["no"][i].head = NULL;
		hash_table["no"][i].num = 0;
		hash_table["isbn_no"][i].head = NULL;
		hash_table["isbn_no"][i].num = 0;
	}

	//hash tables for books
	char tmp[150], token[100];
	int len, i, j = 0, bucket, row = 0;
	fgets(tmp, sizeof(tmp), fbookr);
	while(fgets(tmp, sizeof(tmp), fbookr) != NULL)
	{
		if(tmp[0] <= 13)	//used to exclude blank line at the end of file
		  break;
		row++;
		len = strlen(tmp);
		//isbn
		for(i = 0; i < len; ++i)
		{
			if(tmp[i] == '|')
			{
				token[j] = '\0';
				//for database table
				tables["books"]["isbn"].push_back(string(token));
				//for hash table
				bucket = hash33(token);
				char *value = (char *)malloc(sizeof(char) * strlen(token) + 1);
				for(int k = 0; k <= strlen(token); ++k)
				  value[k] = token[k];
				struct slot *new_slot = (struct slot *)malloc(sizeof(struct slot));
				new_slot->value = value;
				new_slot->row = row;
				new_slot->next = hash_table["isbn"][bucket].head;
				hash_table["isbn"][bucket].head = new_slot;
				hash_table["isbn"][bucket].num++;
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
				tables["books"]["author"].push_back(string(token));
				//for hash table
				bucket = hash33(token);
				char *value = (char *)malloc(sizeof(char) * strlen(token) + 1);
				for(int k = 0; k <= strlen(token); ++k)
				  value[k] = token[k];
				struct slot *new_slot = (struct slot *)malloc(sizeof(struct slot));
				new_slot->value = value;
				new_slot->row = row;
				new_slot->next = hash_table["author"][bucket].head;
				hash_table["author"][bucket].head = new_slot;
				hash_table["author"][bucket].num++;
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
				tables["books"]["title"].push_back(string(token));
				//for hash table
				bucket = hash33(token);
				char *value = (char *)malloc(sizeof(char) * strlen(token) + 1);
				for(int k = 0; k <= strlen(token); ++k)
				  value[k] = token[k];
				struct slot *new_slot = (struct slot *)malloc(sizeof(struct slot));
				new_slot->value = value;
				new_slot->row = row;
				new_slot->next = hash_table["title"][bucket].head;
				hash_table["title"][bucket].head = new_slot;
				hash_table["title"][bucket].num++;
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
				tables["books"]["price"].push_back(string(token));
				//for hash table
				bucket = hash33(token);
				char *value = (char *)malloc(sizeof(char) * strlen(token) + 1);
				for(int k = 0; k <= strlen(token); ++k)
				  value[k] = token[k];
				struct slot *new_slot = (struct slot *)malloc(sizeof(struct slot));
				new_slot->value = value;
				new_slot->row = row;
				new_slot->next = hash_table["price"][bucket].head;
				hash_table["price"][bucket].head = new_slot;
				hash_table["price"][bucket].num++;
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
				tables["books"]["subject"].push_back(string(token));
				//for hash table
				bucket = hash33(token);
				char *value = (char *)malloc(sizeof(char) * strlen(token) + 1);
				for(int k = 0; k <= strlen(token); ++k)
				  value[k] = token[k];
				struct slot *new_slot = (struct slot *)malloc(sizeof(struct slot));
				new_slot->value = value;
				new_slot->row = row;
				new_slot->next = hash_table["subject"][bucket].head;
				hash_table["subject"][bucket].head = new_slot;
				hash_table["subject"][bucket].num++;
				j = 0;
				i++;
				break;
			}
			else
				token[j++] = tmp[i];
		}
	}
	table_row_num["books"] = row;

	//hash tables for sellRecord
	row = 0;
	fgets(tmp, sizeof(tmp), fsellr);
	while(fgets(tmp, sizeof(tmp), fsellr) != NULL)
	{
		if(tmp[0] <= 13)	//used to exclude blank line at the end of file
		  break;
		row++;
		len = strlen(tmp);
		//uid
		for(i = 0; i < len; ++i)
		{
			if(tmp[i] == '|')
			{
				token[j] = '\0';
				//for database table
				tables["sellRecord"]["uid"].push_back(string(token));
				//for hash table
				bucket = hash33(token);
				char *value = (char *)malloc(sizeof(char) * strlen(token) + 1);
				for(int k = 0; k <= strlen(token); ++k)
				  value[k] = token[k];
				struct slot *new_slot = (struct slot *)malloc(sizeof(struct slot));
				new_slot->value = value;
				new_slot->row = row;
				new_slot->next = hash_table["uid"][bucket].head;
				hash_table["uid"][bucket].head = new_slot;
				hash_table["uid"][bucket].num++;
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
				tables["sellRecord"]["no"].push_back(string(token));
				//for hash table
				bucket = hash33(token);
				char *value = (char *)malloc(sizeof(char) * strlen(token) + 1);
				for(int k = 0; k <= strlen(token); ++k)
				  value[k] = token[k];
				struct slot *new_slot = (struct slot *)malloc(sizeof(struct slot));
				new_slot->value = value;
				new_slot->row = row;
				new_slot->next = hash_table["no"][bucket].head;
				hash_table["no"][bucket].head = new_slot;
				hash_table["no"][bucket].num++;
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
				tables["sellRecord"]["isbn_no"].push_back(string(token));
				//for hash table
				bucket = hash33(token);
				char *value = (char *)malloc(sizeof(char) * strlen(token) + 1);
				for(int k = 0; k <= strlen(token); ++k)
				  value[k] = token[k];
				struct slot *new_slot = (struct slot *)malloc(sizeof(struct slot));
				new_slot->value = value;
				new_slot->row = row;
				new_slot->next = hash_table["isbn_no"][bucket].head;
				hash_table["isbn_no"][bucket].head = new_slot;
				hash_table["isbn_no"][bucket].num++;
				j = 0;
				i++;
				break;
			}
			else
				token[j++] = tmp[i];
		}

	}
	table_row_num["sellRecord"] = row;
	
	for(int i = 0; i < 10; ++i)
	{
		//print the isbn hash table
		fprintf(fb1, "Bucket %d\t", i);
		struct slot *ptr = hash_table["isbn"][i].head;
		for(int j = 0; j < hash_table["isbn"][i].num; ++j)
		{
			if(j != hash_table["isbn"][i].num-1)
			  fprintf(fb1, "<%s>, ", ptr->value);
			else
			  fprintf(fb1, "<%s>", ptr->value);
			ptr = ptr->next;
		}
		fprintf(fb1, "\n");

		//print the author hash table
		fprintf(fb2, "Bucket %d\t", i);
		ptr = hash_table["author"][i].head;
		for(int j = 0; j < hash_table["author"][i].num; ++j)
		{
			if(j != hash_table["author"][i].num-1)
			  fprintf(fb2, "<%s>, ", ptr->value);
			else
			  fprintf(fb2, "<%s>", ptr->value);
			ptr = ptr->next;
		}
		fprintf(fb2, "\n");
		
		//print the title hash table
		fprintf(fb3, "Bucket %d\t", i);
		ptr = hash_table["title"][i].head;
		for(int j = 0; j < hash_table["title"][i].num; ++j)
		{
			if(j != hash_table["title"][i].num-1)
			  fprintf(fb3, "<%s>, ", ptr->value);
			else
			  fprintf(fb3, "<%s>", ptr->value);
			ptr = ptr->next;
		}
		fprintf(fb3, "\n");
	
		//print the price hash table
		fprintf(fb4, "Bucket %d\t", i);
		ptr = hash_table["price"][i].head;
		for(int j = 0; j < hash_table["price"][i].num; ++j)
		{
			if(j != hash_table["price"][i].num-1)
			  fprintf(fb4, "<%s>, ", ptr->value);
			else
			  fprintf(fb4, "<%s>", ptr->value);
			ptr = ptr->next;
		}
		fprintf(fb4, "\n");

		//print the subject hash table
		fprintf(fb5, "Bucket %d\t", i);
		ptr = hash_table["subject"][i].head;
		for(int j = 0; j < hash_table["subject"][i].num; ++j)
		{
			if(j != hash_table["subject"][i].num-1)
			  fprintf(fb5, "<%s>, ", ptr->value);
			else
			  fprintf(fb5, "<%s>", ptr->value);
			ptr = ptr->next;
		}
		fprintf(fb5, "\n");
		
		//print the sell_uid hash table
		fprintf(fs1, "Bucket %d\t", i);
		ptr = hash_table["uid"][i].head;
		for(int j = 0; j < hash_table["uid"][i].num; ++j)
		{
			if(j != hash_table["uid"][i].num-1)
			  fprintf(fs1, "<%s>, ", ptr->value);
			else
			  fprintf(fs1, "<%s>", ptr->value);
			ptr = ptr->next;
		}
		fprintf(fs1, "\n");
		
		//print the sell_no hash table
		fprintf(fs2, "Bucket %d\t", i);
		ptr = hash_table["no"][i].head;
		for(int j = 0; j < hash_table["no"][i].num; ++j)
		{
			if(j != hash_table["no"][i].num-1)
			  fprintf(fs2, "<%s>, ", ptr->value);
			else
			  fprintf(fs2, "<%s>", ptr->value);
			ptr = ptr->next;
		}
		fprintf(fs2, "\n");
		
		//print the sell_isbn hash table
		fprintf(fs3, "Bucket %d\t", i);
		ptr = hash_table["isbn_no"][i].head;
		for(int j = 0; j < hash_table["isbn_no"][i].num; ++j)
		{
			if(j != hash_table["isbn_no"][i].num-1)
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
	vector<string> q_attrs;
	vector<string> q_tables;
	vector<int> candidate;
	map<string, vector<int> > potential_can, results;
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
				if(tmp[strlen(tmp)-1] == ',')
				  tmp[strlen(tmp)-1] = '\0';
				q_attrs.push_back(string(tmp));
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
					q_tables.push_back(string(tmp));	
				}
				else if(tmp[strlen(tmp)-1] == ';')	//end of line
				{
					no_con = true;
					tmp[strlen(tmp)-1] = '\0';
					q_tables.push_back(string(tmp));
					break;
				}
				else
				  q_tables.push_back(string(tmp));
			}
			
			//read all the query WHERE condition
			if(!no_con)
			{
				if(q_tables.size() == 1)	//retrieve from one table
				{
					scanf("%s", tmp);	//target attribute
					string target_attr(tmp);
					scanf("%s", tmp);	//exclude out the =
					scanf("%s", tmp);	//target value
					if(tmp[0] == '\'')
					{
						int length = strlen(tmp);
						if(tmp[length - 1] != '\'' && tmp[length-2] != '\'')
						{
							char ch = 'a';
							while(ch != '\'')
							{
								scanf("%c", &ch);
								tmp[length++] = ch;
							}
							scanf("%c", &ch);
							if(ch == ';')
							  tmp[length++] = ch;
							tmp[length] = '\0';
						}
					}
					string tmp_target_val(tmp);
					//clear out the '' around the target value
					int sub_len;
					bool end = false; //check if the where clause have more than one condition
					if(tmp[strlen(tmp)-1] == ';')
					{
						sub_len = strlen(tmp) - 3;
						end = true;
					}
					else
						sub_len = strlen(tmp) - 2;
					string target_val = tmp_target_val.substr(1, sub_len);
					bucket = hash33(target_val.c_str());
					struct slot *ptr = hash_table[target_attr][bucket].head;
					for(int j = 0; j < hash_table[target_attr][bucket].num; ++j)
					{
						if(target_val.compare(ptr->value) == 0)
						  candidate.push_back(ptr->row);
						ptr = ptr->next;
					}

					while(!end)
					{
						scanf("%s", tmp);	//exclude out AND
						scanf("%s", tmp);	//target attribute
						string target_attr(tmp);
						scanf("%s", tmp);	//exclude out the =
						scanf("%s", tmp);	//target value
						if(tmp[0] == '\'')
						{
							int length = strlen(tmp);
							if(tmp[length - 1] != '\'' && tmp[length-2] != '\'')
							{
								char ch = 'a';
								while(ch != '\'')
								{
									scanf("%c", &ch);
									tmp[length++] = ch;
								}
								scanf("%c", &ch);
								if(ch == ';')
								  tmp[length++] = ch;
								tmp[length] = '\0';
							}
						}
						string tmp_target_val(tmp);
						if(tmp[strlen(tmp)-1] == ';')
						{
							sub_len = strlen(tmp) - 3;
							end = true;
						}
						else
							sub_len = strlen(tmp) - 2;
						string target_val = tmp_target_val.substr(1, sub_len);
						bucket = hash33(target_val.c_str());
						bool qualified = false;
						for(int i =  0; i < candidate.size(); ++i)
						{
							struct slot *ptr = hash_table[target_attr][bucket].head;
							for(int j = 0; j < hash_table[target_attr][bucket].num; ++j)
							{
								if(target_val.compare(ptr->value) == 0 && candidate.at(i) == ptr->row)
								{
									qualified = true;
									break;
								}
								ptr = ptr->next;
							}
							if(!qualified)
							{
								candidate.erase(candidate.begin()+i);
								i--;
							}
							qualified = false;
						}
					}
				}
				else	//WHERE clause with joint table
				{
					bool end = false; //check if the where clause have more than one condition
					bool join_start = false;
					for(int i = 0; i < table_row_num[q_tables.at(0)]; ++i)
					  potential_can[q_tables.at(0)].push_back(i);
					for(int i = 0; i < table_row_num[q_tables.at(1)]; ++i)
					  potential_can[q_tables.at(1)].push_back(i);
					while(!end)
					{
						scanf("%s", tmp);	//target attribute
						string target_attr(tmp);
						scanf("%s", tmp);	//exclude out the =
						scanf("%s", tmp);	//target value
						if(tmp[0] == '\'')
						{
							int length = strlen(tmp);
							if(tmp[length - 1] != '\'' && tmp[length-2] != '\'')
							{
								char ch = 'a';
								while(ch != '\'')
								{
									scanf("%c", &ch);
									tmp[length++] = ch;
								}
								scanf("%c", &ch);
								if(ch == ';')
								  tmp[length++] = ch;
								tmp[length] = '\0';
							}
						}
						if(tmp[strlen(tmp)-1] == ';')
						{
							tmp[strlen(tmp)-1] = '\0';
							end = true;
						}
						string target_val(tmp);
						//clear out the '' around the target value (if any)
						if(tmp[0] == '\'')	//simple condition
						{
							target_val = target_val.substr(1, strlen(tmp)-2);
							if(!join_start)
							{
								string t = belong_table(sets, target_attr);
								for(int i = 0; i < potential_can[t].size(); ++i)
								{
									if(target_val.compare(tables[t][target_attr].at(potential_can[t].at(i))) != 0)
									{
										potential_can[t].erase(potential_can[t].begin()+i);
										i--;
									}
								}
							}
							else
							{
								string t = belong_table(sets, target_attr);
								for(int i = 0; i < results[t].size(); ++i)
								{
									if(target_val.compare(tables[t][target_attr].at(results[t].at(i))) != 0)
									{
										results[q_tables.at(0)].erase(results[q_tables.at(0)].begin()+i);
										results[q_tables.at(1)].erase(results[q_tables.at(1)].begin()+i);
										i--;
									}
								}
							}
						}
						else	//join condition
						{
							if(!join_start)
							{
								string t1 = belong_table(sets, target_attr);
								string t2 = belong_table(sets, target_val);
								for(int i = 0; i < potential_can[t1].size(); ++i)
								{
									bucket = hash33(tables[t1][target_attr].at(potential_can[t1].at(i)).c_str());
									struct slot *ptr = hash_table[target_val][bucket].head;
									for(int j = 0; j < hash_table[target_val][bucket].num; ++j)
									{
										if(tables[t1][target_attr].at(potential_can[t1].at(i)).compare(ptr->value) == 0)
										{
											results[t1].push_back(potential_can[t1].at(i));
											results[t2].push_back(ptr->row - 1);
										}
										ptr = ptr->next;
									}
								}
								join_start = true;
							}
							else
							{
								string t1 = belong_table(sets, target_attr);
								string t2 = belong_table(sets, target_val);
								for(int i = 0; i < results[t1].size(); ++i)
								{
									if(tables[t1][target_attr].at(results[t1].at(i)).compare(tables[t2][target_val].at(results[t2].at(i))) != 0)
									{
										results[t1].erase(results[t1].begin()+i);
										results[t2].erase(results[t2].begin()+i);
										i--;
									}
								}
							}
						}
						if(!end)
						  scanf("%s", tmp);		//exclude out AND
					}
				}

			}

		}
		else
		  printf("Invalid command.\n");
		
		//process the query
		if(no_con)	//no WHERE clause
		{
			if(q_attrs.at(0).compare("*") == 0)	//retrieve all attributes
			{
				string target_table(q_tables.at(0));
				//print out the titles
				for(set<string>::iterator it = sets[target_table].begin(); it != sets[target_table].end(); ++it)
				{
					if((*it).compare("title") == 0)
					  printf("%-65s", (*it).c_str());
					else
					  printf("%-25s", (*it).c_str());
				}
				printf("\n");

				for(int i = 0; i < table_row_num[target_table]; ++i)
				{
					for(set<string>::iterator it = sets[target_table].begin(); it != sets[target_table].end(); ++it)
				  	{
						if((*it).compare("title") == 0)
						  printf("%-65s", tables[target_table][*it].at(i).c_str());
						else
						  printf("%-25s", tables[target_table][*it].at(i).c_str());
					}
					printf("\n");
				}
			}
			else	//retrieve part of attributes
			{
				string target_table(q_tables.at(0));
				for(int i = 0; i < q_attrs.size(); ++i)
				{
					if(q_attrs.at(i).compare("title") == 0)
					  printf("%-65s", q_attrs.at(i).c_str());
					else
					  printf("%-25s", q_attrs.at(i).c_str());
				}
				printf("\n");
				if(q_attrs.size() == 1 && distinct)	//if DISTINCT is set
				{
					set<string> used;
					for(int i = 0; i < table_row_num[target_table]; ++i)
					{
						if(used.find(tables[target_table][q_attrs.at(0)].at(i)) == used.end())
						{
							used.insert(tables[target_table][q_attrs.at(0)].at(i));
							if(q_attrs.at(0).compare("title") == 0)
							  printf("%-65s", tables[target_table][q_attrs.at(0)].at(i).c_str());
							else
							  printf("%-25s", tables[target_table][q_attrs.at(0)].at(i).c_str());
							printf("\n");
						}
					}
				}
				else
				{
					for(int i = 0; i < table_row_num[target_table]; ++i)
					{
						for(int j = 0; j < q_attrs.size(); ++j)
					  	{
							if(q_attrs.at(j).compare("title") == 0)
							  printf("%-65s", tables[target_table][q_attrs.at(j)].at(i).c_str());
							else
							  printf("%-25s", tables[target_table][q_attrs.at(j)].at(i).c_str());
						}
						printf("\n");
					}
				}
			}
		}
		else	//with WHERE clause
		{
			if(q_attrs.at(0).compare("*") == 0)	//retrieve all attributes
			{
				q_attrs.pop_back();	//clear the query attribute *
				for(int i = 0; i < q_tables.size(); ++i)
				{
					for(set<string>::iterator it = sets[q_tables.at(i)].begin(); it != sets[q_tables.at(i)].end(); ++it)
					  q_attrs.push_back(*it);
				}
			}
			if(q_tables.size() == 1)
			{
				string target_table(q_tables.at(0));
				for(int i = 0; i < q_attrs.size(); ++i)
				{
					if(q_attrs.at(i).compare("title") == 0)
					  printf("%-65s", q_attrs.at(i).c_str());
					else
					  printf("%-25s", q_attrs.at(i).c_str());
				}
				printf("\n");
				if(q_attrs.size() == 1 && distinct)	//if DISTINCT is set
				{
					set<string> used;
					for(int i = 0; i < candidate.size(); ++i)
					{
						if(used.find(tables[target_table][q_attrs.at(0)].at(candidate.at(i)-1)) == used.end())
						{
							used.insert(tables[target_table][q_attrs.at(0)].at(candidate.at(i)-1));
							if(q_attrs.at(0).compare("title") == 0)
							  printf("%-65s", tables[target_table][q_attrs.at(0)].at(candidate.at(i)-1).c_str());
							else
							  printf("%-25s", tables[target_table][q_attrs.at(0)].at(candidate.at(i)-1).c_str());
							printf("\n");
						}
					}
				}
				else
				{
					for(int i = 0; i < candidate.size(); ++i)
					{
						for(int j = 0; j < q_attrs.size(); ++j)
					  	{
							if(q_attrs.at(j).compare("title") == 0)
							  printf("%-65s", tables[target_table][q_attrs.at(j)].at(candidate.at(i)-1).c_str());
							else
							  printf("%-25s", tables[target_table][q_attrs.at(j)].at(candidate.at(i)-1).c_str());
						}
						printf("\n");
					}
				}
			}
			else
			{
				string target_table(q_tables.at(0));
				for(int i = 0; i < q_attrs.size(); ++i)
				{
					if(q_attrs.at(i).compare("title") == 0)
					  printf("%-65s", q_attrs.at(i).c_str());
					else
					  printf("%-25s", q_attrs.at(i).c_str());
				}
				printf("\n");
				if(q_attrs.size() == 1 && distinct)	//if DISTINCT is set
				{
					set<string> used;
					for(int i = 0; i < results[q_tables.at(0)].size(); ++i)
					{
						string t = belong_table(sets, q_attrs.at(j));
						if(used.find(tables[t][q_attrs.at(0)].at(results[t].at(i))) == used.end())
						{
							used.insert(tables[t][q_attrs.at(0)].at(results[t].at(i)));
							if(q_attrs.at(0).compare("title") == 0)
							  printf("%-65s", tables[t][q_attrs.at(0)].at(results[t].at(i)).c_str());
							else
							  printf("%-25s", tables[t][q_attrs.at(0)].at(results[t].at(i)).c_str());
							printf("\n");
						}
					}
				}
				else
				{
					for(int i = 0; i < results[q_tables.at(0)].size(); ++i)
					{
						for(int j = 0; j < q_attrs.size(); ++j)
					  	{
							string t = belong_table(sets, q_attrs.at(j));
							if(q_attrs.at(j).compare("title") == 0)
							  printf("%-65s", tables[t][q_attrs.at(j)].at(results[t].at(i)).c_str());
							else
							  printf("%-25s", tables[t][q_attrs.at(j)].at(results[t].at(i)).c_str());
						}
						printf("\n");
					}
				}
			}
		}

		//clear the query vectors
		if(q_tables.size() > 1)
		{
			while(!potential_can[q_tables.at(0)].empty())
			  potential_can[q_tables.at(0)].pop_back();
			while(!potential_can[q_tables.at(1)].empty())
			  potential_can[q_tables.at(1)].pop_back();
			while(!results[q_tables.at(0)].empty())
			  results[q_tables.at(0)].pop_back();
			while(!results[q_tables.at(1)].empty())
			  results[q_tables.at(1)].pop_back();
		}
		while(!q_attrs.empty())
		  q_attrs.pop_back();
		while(!q_tables.empty())
		  q_tables.pop_back();
		while(!candidate.empty())
		  candidate.pop_back();
	}
	return 0;
}
