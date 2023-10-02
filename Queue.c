#include <stdio.h>
#include <stdlib.h>
//    �ޤJ�禡�w
typedef struct Queue {
    //    �w�q��C���c�A�䤤�]�t�e�q�B�}�C�Bfront & rear
    int front, rear, capacity;
    int* array;
} Queue;

Queue* CreateQueue(int capacity) {                 // ��l�ơA�]�N�O�ھڨϥΪ̩ҿ�J��capacity�A�h��queue���X��
    Queue* queue = (Queue*)malloc(sizeof(Queue));  //    ���t�O���鵹queue(struct)
                                                   //    ���Ф@�ӫ��A��queue�� Queue�A�Ψ��x�s���c�����ơA�̫�return���X�h
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = 0;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    //  ��Jqueue�����U���Ѽ�
    return queue;  //    �^�Ǧ�Cqueue
};

int IsFull(Queue* queue) {                        // �T�{queue�O�_�w�������
    return (queue->rear + 1 == queue->capacity);  // ��rear+1 ���� capacity�ɡA��C�w��
}
int IsEmpty(Queue* queue) {                // �T�{queue�O�_���Ū����
    return (queue->front == queue->rear);  // ��front����rear�ɡA��C����
}

void Insert(Queue* queue, int value) {  // �[�J���������
    if (IsFull(queue)) {
        // �Y��Ƥw���A��XQueue is full!!�A�M�ᵲ��
        printf("\nQueue is full!!");
        return;
    }
    //    �Ϥ��A�hrear�V��B�s�Jvalue
    queue->rear = queue->rear + 1;
    queue->array[queue->rear] = value;
}

void Delete(Queue* queue) {  //  �R�����������
    if (IsEmpty(queue)) {
        //        �Y��Ƭ��šA��XQueue is empty!!�A�M�ᵲ��
        printf("\nQueue is empty!!");
        return;
    }
    //    �Ϥ��Afront�V��]���ݧR���^
    queue->front = queue->front + 1;
}

void ShowQueue(Queue* queue) {  // ���queue�����
    printf("\nLinear Queue : ");
    for (int i = 0; i < queue->capacity; i++) {
        if (i <= queue->front | i > queue->rear) {
            //            ��i���bfront&rear�����ɡA�N�Ӧ�m���]��0
            printf("[] ");
        }
        //      �L�X�C�Ӥ�������
        else {
            printf("[%d] ", queue->array[i]);
        }
    }
    printf("\nFront = %d, Rear = %d\n", queue->front, queue->rear);
    //    �L�Xfront&rear
}
//------------------------------�H�W�Ĥ@�D------------------------------------

//--------------------------------�ĤG�D-------------------------------------
typedef struct Queue2 {
    //    �w�q��C���c�A�䤤�]�t�e�q�B�}�C�Bfront & rear
    int front, rear, capacity;
    int* array;
} Queue2;

Queue2* CreateQueue2(int capacity) {                  // ��l�ơA�]�N�O�ھڨϥΪ̩ҿ�J��capacity�A�h��queue���X��
    Queue2* queue = (Queue2*)malloc(sizeof(Queue2));  // ���t�O���鵹queue(struct)
    queue->capacity = capacity;
    queue->front = 0;
    queue->rear = 0;
    queue->array = (int*)malloc(queue->capacity * sizeof(int));
    //  ��Jqueue�����U���Ѽ�
    return queue;
    //    �^�Ǧ�Cqueue(struct)
};

int IsFull2(Queue2* queue) {  // �T�{queue�O�_�w�������
    return ((queue->rear - queue->front + queue->capacity) % queue->capacity == queue->capacity - 1);
    // �� rear-front+capacity �i�H�Qcapacity�㰣�ɡA��C�w��
}
int IsEmpty2(Queue2* queue) {              // �T�{queue�O�_���Ū����
    return (queue->front == queue->rear);  // ��front ���� rear�ɡA��C����
}

void Insert2(Queue2* queue, int value) {  // �[�J���������
    if (IsFull2(queue)) {
        // �Y��Ƥw���A��XQueue is full!!�A�M�ᵲ��
        printf("\nQueue is full!!");
        return;
    }
    //    �Ϥ��A�hrear�V��B�s�Jvalue
    queue->rear = (queue->rear + 1) % queue->capacity;
    queue->array[queue->rear] = value;
}

void Delete2(Queue2* queue) {  //  �R�����������
    if (IsEmpty2(queue)) {
        //        �Y��Ƭ��šA��XQueue is empty!!�A�M�ᵲ��
        printf("\nQueue is empty!!");
        return;
    }
    //    �Ϥ��Afront�V��]���ݧR���^
    queue->front = (queue->front + 1) % queue->capacity;
}

void ShowQueue2(Queue2* queue) {
    printf("\nCircular Queue : ");
    for (int i = 0; i < queue->capacity; i++) {
        //        �L�X�C�@����
        if (i > queue->front & i <= queue->rear & queue->front < queue->rear) {
            printf("[%d] ", queue->array[i]);
        } else if ((i > queue->front | i <= queue->rear) & (queue->front > queue->rear)) {
            printf("[%d] ", queue->array[i]);
        } else {
            printf("[] ");
        }
    }
    printf("\nFront = %d, Rear = %d\n", queue->front, queue->rear);  // �L�Xfront&Rear
}
//------------------------------�H�W�ĤG�D------------------------------------

//--------------------------------�ĤT�D-------------------------------------
typedef struct node {
    //    �w�q�`�I���c�A�䤤�]�tdata�P�U�Ӹ`�I����}
    int data;
    struct node* next;
} node;

typedef struct queue {
    //    �w�q��C���c�A�䤤�]�t�e�q�B�_�lhead�]���M������A�@�_�|�ñ��^�Bfront & rear
    int capacity;
    node *head, *front, *rear;
} queue;

queue* createQueue(int capacity) {
    //    ��l�ơA�]�N�O�ھڨϥΪ̩ҿ�J��capacity�A�h��linked list���X��

    queue* LinkedQueue = (queue*)malloc(sizeof(queue));  // ���t�O���鵹queue(struct)
    //    ���Ф@�ӫ��A��queue�� LinkedQueue�A�Ψ��x�s���c�����ơA�̫�return���X�h

    node* head = (node*)malloc(sizeof(node));
    head->next = NULL;
    head->data = 0;
    //    ���t�O���鵹�m������head�A�H�K���@�U�j�鱵�򧹦����

    for (int i = 0; i < capacity - 1; i++) {
        node* temp = head;
        //        �ϥ�while����P�_�A��temp�ɥi��Ჾ
        while (temp->next != NULL) {
            temp = temp->next;
        }

        //        �j�餺�Q��new�A�ꦨ����A�B�Ȭҹw�]��0�ҫ��VNULL
        node* new = NULL;
        new = (node*)malloc(sizeof(node));
        new->data = 0;
        new->next = NULL;
        temp->next = new;
    }
    node* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    //        �ϥ�while����P�_�A��temp�ɥi��Ჾ
    temp->next = head;
    //    ������̫�@�Ӥ������V��head

    //    �̫᧹���]�w��������U���Ѽ�
    LinkedQueue->head = head;
    LinkedQueue->front = head;
    LinkedQueue->rear = head;
    LinkedQueue->capacity = capacity;
    return LinkedQueue;
};

int isFull(queue* Queue) {
    return (Queue->rear->next == Queue->front);
    //    �p�Grear���U�@�ӬOfront�A���ɦ�C�w��
}
int isEmpty(queue* Queue) {
    return (Queue->front == Queue->rear);
    //    �p�Grear����front�A���ɦ�C����
}

void insert(queue* Queue, int value) {
    //    �ŧiinsert�����^�ǭȪ���ơA�ݭn��J����H�α��[�J����
    if (isFull(Queue)) {
        printf("\nQueue is full!!");
        return;
    }
    //    �p�G��C�w���A�h��X"Queue is full!!"�A�B�����o��function
    Queue->rear->next->data = value;
    Queue->rear = Queue->rear->next;
    //    �_�h�A�[�J���[�J���ơA�M��Nrear���Ჾ
};

void delete(queue* Queue) {
    //    �ŧidelete�����^�ǭȪ���ơA�u�ݿ�J���
    if (isEmpty(Queue)) {
        printf("\nQueue is empty!!");
        return;
    }
    //    �p�G��C���šA�h��X"Queue is empty!!"�A�B�����o��function
    Queue->front->next->data = 0;
    Queue->front = Queue->front->next;
    //    �_�h�A�R���̫e�����ơA�M��Nfront���Ჾ
};

void showQueue(queue* Queue) {
    //    �Ψ���ܦ�C����ơA�ҥH���ݦ^�ǭ�
    printf("\nLinked Queue : ");
    int Front, Rear;
    //    �ŧiFront, Rear�A�����i�H�����x�s�n�L�X����
    node* temp = (node*)malloc(sizeof(node));
    temp = Queue->head;
    //    ��temp���@���Ӳ��ʪ�����
    for (int i = 0; i < Queue->capacity; i++) {
        //        �L�X�C�@�Ӥ����A�p�Gtemp����front or rear���ܡA�⥦�x�s�_��
        if (temp == Queue->front) {
            Front = i;
        }
        if (temp == Queue->rear) {
            Rear = i;
        }
        temp = temp->next;
        //        ����temp�ܤU�@��
    }
    temp = Queue->head;
    for (int i = 0; i < Queue->capacity; i++) {
        //        �L�X�C�@�Ӥ���
        if (i > Front & i <= Rear & Rear > Front) {
            printf("[%d] ", temp->data);
        } else if ((i > Front | i <= Rear) & (Rear < Front)) {
            printf("[%d] ", temp->data);
        } else {
            printf("[] ");
        }
        temp = temp->next;
        //        ����temp�ܤU�@��
    }
    printf("\nFront = %d, Rear = %d\n", Front, Rear);
    //    �L�XFront��Rear
};

//------------------------------�H�W�ĤT�D------------------------------------

int main(int argc, const char* argv[]) {
    int type, choice, value, capacity;  // �ŧitype, choice, value, capacity
    printf("1. Linear queue\n");
    printf("2. Circular queue\n");
    printf("3. Linked list\n");
    printf("Select your choice:");
    scanf("%d", &type);  // ��J�n�ĴX�D��queue
    printf("Enter the size of queue:");
    scanf("%d", &capacity);  // ��Jqueue���e�q
    if (type == 1) {
        //        �Ĥ@�D�G��array��linear queue
        Queue* queue = CreateQueue(capacity);  // �I�sCreateQueue���
        while (1) {                            // �ϥεL�a�j��
            printf("1. Insertion\n");
            printf("2. Deletion\n");
            printf("3. Exit\n");
            printf("Enter your choice :");
            scanf("%d", &choice);  // ��J�n���檺�ʧ@
            switch (choice) {      // �ϥ�switch������P�_
                case 1:
                    printf("Enter an element:");
                    scanf("%d", &value);   // ��J�n�[�J����
                    Insert(queue, value);  // �I�sInsert���
                    ShowQueue(queue);      // �I�sShowQueue���
                    printf("\n");
                    break;
                case 2:
                    Delete(queue);     // �I�sDelete���
                    ShowQueue(queue);  // �I�sShowQueue���
                    printf("\n");
                    break;
                case 3:
                    return 0;
                default:
                    printf("Error!\n");
                    break;
            }
        }
    } else if (type == 2) {
        //        �ĤG�D�G��array��circular queue
        Queue2* queue = CreateQueue2(capacity);  // �I�sCreateQueue2���
        while (1) {                              // �ϥεL�a�j��
            printf("1. Insertion\n");
            printf("2. Deletion\n");
            printf("3. Exit\n");
            printf("Enter your choice :");
            scanf("%d", &choice);  // ��J�n���檺�ʧ@
            switch (choice) {      // �ϥ�switch������P�_
                case 1:
                    printf("Enter an element:");
                    scanf("%d", &value);    // ��J�n�[�J����
                    Insert2(queue, value);  // �I�sInsert2���
                    ShowQueue2(queue);      // �I�sShowQueue2���
                    printf("\n");
                    break;
                case 2:
                    Delete2(queue);     // �I�sDelete2���
                    ShowQueue2(queue);  // �I�sShowQueue2���
                    printf("\n");
                    break;
                case 3:
                    return 0;
                default:
                    printf("Error!\n");
                    break;
            }
        }

    } else if (type == 3) {
        queue* Queue = createQueue(capacity);  // �I�screateQueue2���
        while (1) {
            printf("1. Insertion\n");
            printf("2. Deletion\n");
            printf("3. Exit\n");
            printf("Enter your choice :");
            scanf("%d", &choice);  // ��J�n���檺�ʧ@
            switch (choice) {      // �ϥ�switch������P�_
                case 1:
                    printf("Enter an element:");
                    scanf("%d", &value);   // ��J�n�[�J����
                    insert(Queue, value);  // �I�sinsert���
                    showQueue(Queue);      // �I�sshowQueue���
                    printf("\n");
                    break;
                case 2:
                    delete (Queue);    // �I�sdelete���
                    showQueue(Queue);  // �I�sshowQueue���
                    printf("\n");
                    break;
                case 3:
                    return 0;
                default:
                    printf("Error!\n");
                    break;
            }
        }
    } else {
        printf("Error!\n");
    }
    return 0;
}
