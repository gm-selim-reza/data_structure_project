#include <stdio.h>
#include <stdlib.h>

#define MAX_ORDERS 50

struct OrderDetail
{
    int food_number, quantity;
    char size[20];
};

struct OrderQueue
{
    struct OrderDetail orders[MAX_ORDERS];
    int front;
    int rear;
    int count;
};

int total_order_received = 0;
int total_order_served = 0;

void initialOrderQueue(struct OrderQueue *queue)
{
    queue->front = 0;
    queue->rear = -1;
    queue->count = 0;
}

int isOrderQueueEmpty(struct OrderQueue *queue)
{
    return queue->count == 0;
}

int isOrderQueueExists(struct OrderQueue *queue)
{
    return queue->count > 0 && queue->count <= 50;
}

int isOrderQueueFull(struct OrderQueue *queue)
{
    return queue->count == MAX_ORDERS;
}

// Function to create order
void orderReceive(struct OrderQueue *queue)
{
    if (isOrderQueueFull(queue))
    {
        printf("Order is full. Cannot accept more orders.\n\n");
        return;
    }

    queue->rear = (queue->rear + 1) % MAX_ORDERS;
    struct OrderDetail order;
    printf("Enter Food Number: ");
    scanf("%d", &order.food_number);
    printf("Enter Food Size [S|M|B]: ");
    scanf("%s", order.size);
    printf("Enter Food Qunatity: ");
    scanf("%d", &order.quantity);
    queue->orders[queue->rear] = order;
    queue->count++;
    total_order_received++;

    printf("Order received: Food Number: %d, Size: %s, Quantity: %d\n\n",
           order.food_number, order.size, order.quantity);
}

// Function to serve order
void orderServed(struct OrderQueue *queue)
{
    if (isOrderQueueEmpty(queue))
    {
        printf("No orders waiting to be served.\n");
        return;
    }

    struct OrderDetail order = queue->orders[queue->front];
    queue->front = NULL; // delete order
    queue->front = (queue->front + 1) % MAX_ORDERS;
    queue->count--;
    total_order_served++;

    printf("Order served: Food Number: %d, Size: %s, Quantity: %d\n\n",
           order.food_number, order.size, order.quantity);
}

// Function to display current order status
void displayStatus(struct OrderQueue *queue)
{
    printf("Total orders received: %d\n", queue->count);
    printf("Total orders served: %d\n", total_order_served);
    printf("Total orders waiting: %d\n", total_order_received - total_order_served);

    if (isOrderQueueExists(queue))
    {
        printf("Orders waiting to be served:\n");
        struct OrderQueue *current = queue;
        for (int i = 0; i < queue->count; i++)
        {
            int orderIndex = (queue->front + i) % MAX_ORDERS;
            struct OrderDetail order = queue->orders[orderIndex];
            printf("Food Number: %d, Size: %s, Quantity: %d\n",
                   order.food_number, order.size, order.quantity);
        }
    }
}

int main()
{
    struct OrderQueue *orderQueue = (struct OrderQueue *)malloc(sizeof(struct OrderQueue));
    initialOrderQueue(orderQueue);
    int n;
    while (1)
    {
        printf("Enter 1 for Dispaly order status\n");
        printf("Enter 2 for Add Order\n");
        printf("Enter 3 for Complete Order\n");
        printf("Enter 0 for exit programme\n");
        scanf("%d", &n);
        switch (n)
        {
        case 1:
            displayStatus(orderQueue);
            printf("\n");
            break;
        case 2:
            orderReceive(orderQueue);
            break;
        case 3:
            orderServed(orderQueue);
            break;
        case 0:
            exit(0);
            break;
        }
    }

    return 0;
}