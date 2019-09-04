#ifndef DICT_H
#define DICT_H

/**
  * struct dict - singly linked list of key-value pairs
  * @key: variable name
  * @value: value of variable
  * @next: pointer to the next node
  */
struct dict
{
	char *key;
	char *value;
	struct dict *next;
};

#endif /* DICT_H */
