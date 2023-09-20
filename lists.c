#include "shell.h"

/**
 * add_node - Adds a new node to the beginning of the linked list.
 *
 * @head: Address of the pointer to the head of the list.
 * @str: String data for the new node.
 * @num: Node index used by history.
 *
 * Return: Pointer to the newly added node or NULL on failure.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
    list_t *new_node;/*New node to be added.*/ 

    if (!head)
        return (NULL);

/*Allocate memory for the new node.*/ 
    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return (NULL);

/*Initialize the new node.*/ 
    _memset((void *)new_node, 0, sizeof(list_t));
    new_node->num = num;

    if (str)
    {
        new_node->str = _strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return (NULL);
        }
    }


   
    new_node->next = *head;
    *head = new_node;

    return (new_node);
}

/**
 * add_node_end - Adds a new node to the end of the linked list.
 *
 * @head: Address of the pointer to the head of the list.
 * @str: String data for the new node.
 * @num: Node index used by history.
 *
 * Return: Pointer to the newly added node or NULL on failure.
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
    list_t *new_node, *current_node; /* New node to be added and current node for traversal.*/

    if (!head)
        return (NULL);

    current_node = *head;
/* Allocate memory for the new node.*/
    new_node = malloc(sizeof(list_t));
    if (!new_node)
        return (NULL);

/*Initialize the new node.*/ 
    _memset((void *)new_node, 0, sizeof(list_t));
    new_node->num = num;

    if (str)
    {
        new_node->str = _strdup(str);
        if (!new_node->str)
        {
            free(new_node);
            return (NULL);
        }
    }

    if (current_node)
    {
/*Traverse to the end of the list and insert the new node.*/ 
        while (current_node->next)
            current_node = current_node->next;
        current_node->next = new_node;
    }
    else
    {
/*If the list is empty, set the new node as the head.*/ 
        *head = new_node;
    }

    return (new_node);
}

/**
 * print_list_str - Prints only the 'str' element of a list_t linked list.
 *
 * @h: Pointer to the first node.
 *
 * Return: Size of the list.
 */
size_t print_list_str(const list_t *h)
{
/*Counter for the number of nodes printed.*/ 
    size_t count = 0;

    while (h)
    {
/*Print the 'str' or "(nil)" if it's NULL.*/ 
        _puts(h->str ? h->str : "(nil)");
        _puts("\n");
        h = h->next;
        count++;
    }

    return (count);
}

/**
 * delete_node_at_index - Deletes a node at the specified index.
 *
 * @head: Address of the pointer to the first node.
 * @index: Index of the node to delete.
 *
 * Return: 1 on success, 0 on failure.
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
/*Current node and its previous node for traversal.*/ 
    list_t *current_node, *previous_node; 
    unsigned int i = 0; /*Counter for the current node index*/ 

    if (!head || !*head)
        return (0);

    if (!index)
    {
/* If index is 0, delete the head node.*/
        current_node = *head;
        *head = (*head)->next;
        free(current_node->str);
        free(current_node);
        return (1);
    }

    current_node = *head;
    while (current_node)
    {
        if (i == index)
        {
/**Node found at the specified index, delete it.*/ 
            previous_node->next = current_node->next;
            free(current_node->str);
            free(current_node);
            return (1);
        }
        i++;
        previous_node = current_node;
        current_node = current_node->next;
    }

    return (0); 
}

/**
 * free_list - Frees all nodes of a list.
 *
 * @head_ptr: Address of the pointer to the head node.
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
    list_t *current_node, *next_node, *head; 

    if (!head_ptr || !*head_ptr)
        return;

    head = *head_ptr;
    current_node = head;
    while (current_node)
    {
        next_node = current_node->next;
        free(current_node->str);
        free(current_node);
        current_node = next_node;
    }

    *head_ptr = NULL;
}
