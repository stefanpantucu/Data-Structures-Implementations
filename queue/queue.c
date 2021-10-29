#include "queue.h"

// allocates memory for a queue structure
Queue create_queue()
{
    Queue queue = (Queue)calloc(1, sizeof(TQueue));
    if (queue == NULL)
        return NULL;

    queue->front = queue->rear = NULL;

    return queue;
}

// inserts elem in the queue
int insert_q(Queue queue, void *elem)
{
    // if the queue is empty
    if (queue->front == NULL && queue->rear == NULL) {
        push_front(&(queue->front), elem);
        queue->rear = queue->front;
        return 0;
    }

    // if the queue is not empty
    if(push_back(&(queue->rear), elem))
        return 1; // failure
    queue->rear = queue->rear->next;

    return 0;
}

// extracts an element from the queue
void *extract_q(Queue queue)
{
    // if queue is empty there is nothing to extract
    if (queue->front == NULL && queue->rear == NULL)
        return NULL;

    void *elem = pop_front(&(queue->front));

    // test if the queue had only one element -> queue becomes empty
    if (queue->front == NULL)
        queue->rear = NULL;

    return elem;
}

// determines if a queue is empty or not (1 - empty, 0 - otherwise)
int empty_queue(Queue queue)
{
    if (queue->front == NULL && queue->rear == NULL)
        return 1; // queue is empty
    
    return 0; // queue is not empty
}

// prints the elements of a queue
void print_q(Queue queue,  TPrint print_elem)
{
    Queue aux = create_queue();
    if (aux == NULL)
        return ;

    if (empty_queue(queue)) {
        printf("empty queue\n");
        return ;
    }

    while (queue->front != NULL && queue->rear != NULL) {
        void *elem = NULL;
        elem = extract_q(queue);

        if (elem == NULL)
            return ; // the extraction failed

        //add the elements in aux to reconstruct initial queue
        if (insert_q(aux, elem))
            return ; // insertion failed 
        
        print_elem(elem);
        if (queue->front != NULL && queue->rear != NULL)
            printf(", ");
    }

    printf("\n");

    // reconstruct initial queue
    while (aux->front != NULL && aux->rear != NULL) {
        void *elem = NULL;
        elem = extract_q(aux);

        if (elem == NULL)
            return ; // extraction failed

        if (insert_q(queue, elem))
            return ; // insertion failed
    }

    free(aux);
}

// returns the number of elements in the queue
int nr_elem_q(Queue queue)
{
    int count = 0;

    Queue aux = create_queue();
    if (aux == NULL)
        return -1;

    while (queue->front != NULL && queue->rear != NULL) {
        void *elem = NULL;
        elem = extract_q(queue);

        if (elem == NULL)
            return -1; // the extraction failed

        //add the elements in aux to reconstruct initial queue
        if (insert_q(aux, elem))
            return -1; // insertion failed 
        
        count++;
    }

    // reconstruct initial queue
    while (aux->front != NULL && aux->rear != NULL) {
        void *elem = NULL;
        elem = extract_q(aux);

        if (elem == NULL)
            return -1; // extraction failed

        if (insert_q(queue, elem))
            return -1; // insertion failed
    }

    free(aux);

    return count;
}

// using a compare function, it returns 1 if the searched element
// was found and 0 otherwise
int find_in_q(Queue queue, void *search, TFCmp fcmp)
{
    int found = 0; // not found

    Queue aux = create_queue();
    if (aux == NULL)
        return -1;

    while (queue->front != NULL && queue->rear != NULL) {
        void *elem = NULL;
        elem = extract_q(queue);

        if (elem == NULL)
            return -1; // the extraction failed

        //add the elements in aux to reconstruct initial queue
        if (insert_q(aux, elem))
            return -1; // insertion failed 
        
        if (fcmp(search, elem) == 0)
            found = 1; // searched element was found
    }

    // reconstruct initial queue
    while (aux->front != NULL && aux->rear != NULL) {
        void *elem = NULL;
        elem = extract_q(aux);

        if (elem == NULL)
            return -1; // extraction failed

        if (insert_q(queue, elem))
            return -1; // insertion failed
    }

    free(aux);

    return found;
}

// empties the queue
void reset_q(Queue queue, TFree free_elem)
{   
    delete_list(&(queue->front), free_elem);
    queue->front = queue->rear = NULL;
}

// empties the queue, then frees the memory allocated for the queue
void delete_q(Queue *queue, TFree free_elem)
{
    reset_q(*queue, free_elem); // empties the queue
    free(*queue); // frees memory allocated for the queue
    *queue = NULL;
}

void invert(Queue *queue)
{
    List aux = NULL;

    while (empty_queue(*queue) == 0) {
        void *elem = extract_q(*queue);
        if (elem == NULL) return ; // extraction failed
        
        if (push_front(&aux, elem)) return ; // insertion failed
    }

    while (aux) {
        void *elem = pop_front(&aux);

        if (insert_q(*queue, elem)) return ; // insertion failed
    }
}

/*
    TODO: -invert queue
*/