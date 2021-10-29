#include "stack.h"

// allocates memory for a stack structure
Stack create_stack()
{
    Stack stack = (Stack)calloc(1, sizeof(TStack));
    if (!stack) return NULL;

    stack->top = NULL;

    return stack;
}

int push(Stack stack, void *info)
{
    // insert elem at the top of the stack, which is the start of the list
    if (push_front(&(stack->top), info))
        return 1;

    return 0;
}

// extracts the element at the top of the stack
void *pop(Stack stack)
{
    void *elem;
    elem = pop_front(&(stack->top));

    return elem;
}

// returns the value of the top element from the stack
void *top(Stack stack)
{
    if (stack->top == NULL) // check if stack is empty
        return NULL;

    return (stack->top->info);
}

// reverses the stack
int reverse_stack(Stack dest, Stack source)
{
    if (source->top == NULL)
        return 1; // source stack is empty

    while (source->top != NULL) {
        void *elem = pop(source);
        push_front(&(dest->top), elem);
    }

    return 0;
}

// returns 1 if stack is empty, 0 otherwise
int is_empty(Stack stack)
{
    if (stack->top == NULL)
        return 1;
    
    return 0;
}

int nr_elem_stack(Stack stack)
{
    int count = 0;
    Stack aux = create_stack();
    if (aux == NULL) return -1; // failed to allocate memory
    
    if (is_empty(stack)) return count;

    while (is_empty(stack) == 0) {
        void *elem = pop(stack);

        if (elem == NULL) return -1; // failed extraction

        push(aux, elem);
        count++;
    }

    reverse_stack(stack, aux);
    free(aux);

    return count;
}

// prints the elements of the stack
void print_stack(Stack stack, TPrint print_elem)
{
    Stack aux = create_stack();
    if (aux == NULL)
        return ;
    
    if (is_empty(stack)) {
        printf("empty stack\n");
        return ;
    }

    while (stack->top != NULL) {
        void *elem = pop(stack);

        if (elem == NULL)
            return ; // extraction failed
        
        if (push(aux, elem))
            return ; // insertion failed
        
        print_elem(elem);
        if (stack->top != NULL)
            printf(", ");
    }

    printf("\n");

    // reconstruct initial stack
    reverse_stack(stack, aux);

    free(aux);
}

// using a compare function, it returns 1 if the searched element
// was found and 0 otherwise
int find_in_stack(Stack stack, void *search, TFCmp fcmp)
{
    int found = 0; // not found;

    Stack aux = create_stack();
    if (stack == NULL)
        return -1;

    while (stack->top != NULL) {
        void *elem = pop(stack);

        if (elem == NULL)
            return -1; // extraction failed
        
        if (push(aux, elem))
            return -1; // insertion failed
        
        if (fcmp(search, elem) == 0)
            found = 1; // searched element was found
    }

    // reconstruct initial stack
    reverse_stack(stack, aux);
    free(aux);
    
    return found;
}

// empties the stack
void reset_s(Stack stack, TFree free_elem)
{
    delete_list(&(stack->top), free_elem);
    stack->top = NULL;
}

// empties the stack, then frees the memory allocated for the stack
void delete_s(Stack *stack, TFree free_elem)
{
    reset_s(*stack, free_elem); // empties the stack
    free(*stack); // frees memory allocated for the stack
    *stack = NULL;
}