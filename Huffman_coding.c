#include <stdio.h>
#include <stdlib.h>
#define MAX_TREE_HT 100

typedef struct node {
    //    �w�q�`�I���c�A�]�tdata, freq�A�����лP�k����
    char data;
    unsigned freq;
    struct node *left, *right;
} node;

typedef struct MinHeap {
    //  �w�qminheap���c�A�]�tsize, capacity�A�P�ΨӦs��m��array
    unsigned size;
    unsigned capacity;
    node** array;
} MinHeap;

node* NewNode(char data, unsigned freq) {
    //    �ΨӲ��ͷs�`�I����ơA�Τ@��temp�x�s���c��Ǧ^
    node* temp = (node*)malloc(sizeof(node));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

MinHeap* CreateMinHeap(unsigned capacity) {
    //  �ΨӲ���minheap����ơA�Τ@��minheap�x�s���c��Ǧ^
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (node**)malloc(minHeap->capacity * sizeof(node*));
    return minHeap;
}

void SwapNode(node** a, node** b) {
    //    �Ψӥ洫���I����ơA�ѩ�n��諸�O���СA�G�ǤJ�����O�O���Ъ�����
    node* t = *a;
    *a = *b;
    *b = t;
}

void MinHeapify(MinHeap* minHeap, int idx) {
    //    ��J�@�Ӹ`�I�A�o�Ө�ƥi�H�T�O�L��L���l���I���٤p(�ϥλ��j�^
    //    ���y�ܻ��A�N�Ocheck minheap structure
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;
    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq) {
        smallest = left;
    }
    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq) {
        smallest = right;
    }
    if (smallest != idx) {
        SwapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        MinHeapify(minHeap, smallest);
    }
}

int IsSizeOne(MinHeap* minHeap) {
    //    �ΨӽT�{miheap��size�O�_����1�����
    return (minHeap->size == 1);
}

node* ExtractMin(MinHeap* minHeap) {
    //    ����root�A�A��̫�@�Ӹɨ�root
    node* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    MinHeapify(minHeap, 0);
    //    �̫�n�ˬdminheap������
    return temp;
}

void InsertMinHeap(MinHeap* minHeap, node* minHeapNode) {
    //  �N�s�`�I���Jminheap�������
    ++minHeap->size;
    int i = minHeap->size - 1;
    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    //    �p�G���`�I��j�A�N��s���`�I�X���J���`�I�]�ί����`�I�^
    minHeap->array[i] = minHeapNode;
}

MinHeap* BuildMinHeap(char data[], int freq[], int size) {
    //    ��J���c���һݭn����ơA�^�ǰ��n��minheap
    MinHeap* minHeap = CreateMinHeap(size);
    minHeap->array[0] = NewNode(data[0], freq[0]);
    for (int i = 1; i < size; i++) {
        minHeap->array[i] = NewNode(data[i], freq[i]);
        //  �ϥΰj��A�C�����ͤ@�Ӹ`�I�A�@�Ӥ@�Ӷ�J
        int div = i;
        while (div != 0) {
            if (minHeap->array[div]->freq >= minHeap->array[(div - 1) / 2]->freq) {
                div = (div - 1) / 2;
                continue;
            }
            SwapNode(&minHeap->array[div], &minHeap->array[(div - 1) / 2]);
            //       �Y���`�I��j�A�մ�����
            div = (div - 1) / 2;
            //       �ϥ�while�j�骽�캡��minheap������
        }
    }
    minHeap->size = size;
    //    ��Jminheap��size
    return minHeap;
}

void PrintMinHeap(MinHeap* minHeap) {
    //    �Nminheap�L�X�����
    int level = 0;
    int temp = minHeap->size;
    while (temp != 1) {
        temp = temp / 2;
        level++;
    }
    //    �ѩ�minheap�Ocomplete tree�A�i�H������o��������
    int exp = 1;
    for (int i = 0; i <= level; i++) {
        for (int j = 0; j < exp; j++) {
            if (exp + j > minHeap->size) {
                continue;
            }
            printf("%d__", minHeap->array[exp + j - 1]->freq);
            //            �̷�freq�L�X
        }
        exp = exp * 2;
        //  �ѩ�minheap�Ocomplete tree�A�C�h�|�O�W�h���⭿�j
        printf("\n");
    }
    printf("Max level: %d\n", level);
    //    �L�Xmax level
}

node* BuildHuffmanTree(MinHeap* minHeap) {
    //    �ɥ�minheap�ӫغcHuffamn tree�����
    node *left, *right, *new;
    //  new��left, right���M

    while (!IsSizeOne(minHeap)) {
        //  �u�nsize of minheap������1�A�N����
        right = ExtractMin(minHeap);
        left = ExtractMin(minHeap);
        //        ���X�̤p����Ӹ`�I�A�ѩ󥪤l�ݸ��j�A�G����X�k�l
        new = NewNode('#', left->freq + right->freq);
        //      ���X�s�`�I�A#���L��data�H�K�᭱�ݭn��{
        new->left = left;
        new->right = right;
        //  �s���`�I���Vleft, right
        InsertMinHeap(minHeap, new);
        //        �Nnew���Jminheap��
    }
    return ExtractMin(minHeap);
    //    �^�ǳ̫�ѤU���]�Y��root)
}

void PrintArr(int arr[], int n) {
    //    ���UHuffman code�L�X�����
    int i;
    for (i = 0; i < n; ++i)
        printf("%d", arr[i]);
    //    �ϥΰj��@�@�L�X
    printf("\n");
}

void PrintCode(node* root, int arr[], int top) {
    //    �NHuffman code����L�X�����
    if (root->left) {
        arr[top] = 1;
        PrintCode(root->left, arr, top + 1);
    }
    //  ���l��1
    // Assign 1 to right edge and recur
    if (root->right) {
        arr[top] = 0;
        PrintCode(root->right, arr, top + 1);
    }
    //  �k�l��0
    if (!(root->left) && !(root->right)) {
        printf("%c: ", root->data);
        //        �Y�����ݸ`�I�A�h�L�X�Ӹ`�I��Huffman
        PrintArr(arr, top);
    }
}

void PrintPreOrder(node* node, int* count) {
    //    �NHuffman tree�̷�pre-order�L�X�����j���
    if (node == NULL) {
        return;
    }
    printf("%d ", node->freq);
    *count = *count + 1;
    //    �Q�Φ����j��ƶ��K��Xnode���ƥ�
    PrintPreOrder(node->left, count);
    PrintPreOrder(node->right, count);
}

void PrintInOrder(node* node) {
    //    �NHuffman tree�̷�in-order�L�X�����j���
    if (node == NULL) {
        return;
    }
    PrintInOrder(node->left);
    printf("%d ", node->freq);
    PrintInOrder(node->right);
}

int MaxLevel(node* node) {
    //  ��Xmax level�����j���
    if (node == NULL) {
        return -1;
    }
    //    ���ݸ`�I��level���s�]-1+1=0)
    int Lleft = MaxLevel(node->left);
    int Lright = MaxLevel(node->right);
    if (Lleft > Lright) {
        return Lleft + 1;
    }
    return Lright + 1;
    //    �C���W���j�@�h�[1
}

void decode(node* root, char* code, int start) {
    //    �ΨӸѽXHuffman code�����
    node* temp = root;
    if (code[start + 1] == '\n' || code[start] == '\n') {
        return;
    }
    //    �p�GŪ��r�ꪺ�̫�A���������
    while (1) {
        if (temp->left == NULL) {
            break;
        }
        if (code[start] == '0') {
            start++;
            temp = temp->right;
        } else {
            start++;
            temp = temp->left;
        }
    }
    //    �_�h�̧ǧ�쥽�ݸ`�I�A�M��L�X�A�M��A���j�@��
    printf("%c", temp->data);
    decode(root, code, start);
}

// �H�U���D�{��
int main() {
    int size, count = 0, level = 0, slen = 1;
    //  �ŧi�ܼ�
    printf("Input a string: ");
    node* string = (node*)malloc(2048 * sizeof(node));
    scanf("%c", &string[0].data);
    //    Ū�J�ϥΪ̿�J���r��
    string[0].freq = 1;
    //    �@�}�l�Ĥ@�Ӫ�freq��1
    char c;
    for (int i = 1; i < 2048; i++) {
        scanf("%c", &c);
        if (c == '\n') {
            break;
        }
        //        �YŪ�J���r��������A�h���X�j��
        int index = 0;
        //        �ΨӬ����r�ꤤ�O�_���ۦP���������
        for (int j = 0; j < slen; j++) {
            if (string[j].data == c) {
                ++string[j].freq;
                //        �Y���ۦP�����A�Ӥ�����freq�[1
                index = -1;
            }
        }
        if (index != -1) {
            //        �Y�L�ۦP�����A�[�J�s�����A�ó]�wfreq��1
            string[slen].data = c;
            string[slen].freq = 1;
            slen++;
        }
    }
    for (int i = 0; i < slen; i++) {
        for (int j = 0; j < slen - 1; j++) {
            if ((int)string[j].data > (int)string[j + 1].data) {
                SwapNode(&string[j], &string[j + 1]);
                //                ��z�ϥΪ̿�J���r�궶��
            }
        }
    }
    size = slen;
    //    slen�Y��size
    int* freq = malloc((size) * sizeof(int));
    //    �ΨӬ����v�����}�C
    char* data = malloc((size) * sizeof(char));
    //    �ΨӬ����r�����}�C
    printf("Your input size[int]: %d\n", size);
    printf("Your input symbol[char]:");
    for (int i = 0; i < slen; i++) {
        printf("%c ", string[i].data);
        data[i] = string[i].data;
        freq[i] = string[i].freq;
    }
    //    ��z�ϥΪ̿�J���r����Xsize, symbol, frequency
    printf("\nYour input frequency[int]:");
    for (int i = 0; i < slen; i++) {
        printf("%d ", string[i].freq);
    }
    printf("\n\n==========================================\n");
    printf("MinHeap Tree:\n");
    MinHeap* minHeap = BuildMinHeap(data, freq, size);
    //    �I�s�i�H���Xminheap�����
    PrintMinHeap(minHeap);
    //    �I�s�i�H�L�Xminheap�����
    node* root = BuildHuffmanTree(minHeap);
    //    �I�s�i�H���XHuffmanTree�����
    printf("\n=========================================\n");
    printf("Huffman Tree:\n");
    printf("Preorder:");
    PrintPreOrder(minHeap->array[0], &count);
    //    �I�s�Hpre-order traversal HuffmanTree�����
    printf("\nInorder:");
    PrintInOrder(minHeap->array[0]);
    //    �I�s�Hin-order traversal HuffmanTree�����
    level = MaxLevel(minHeap->array[0]);
    //    �I�s�i�H�o��Max level of HuffmanTree�����
    printf("\nMax Level: %d", level);
    printf("\nNumber of node: %d\n", count);
    printf("\n=========================================\n");
    printf("Huffman Coding:\n");
    int arr[MAX_TREE_HT], top = 0;
    PrintCode(root, arr, top);
    //    �I�s�i�H�L�B�XHuffman Code�����
    printf("=========================================\n");
    int len = 2;
    char* code = (char*)malloc(len * sizeof(char));
    printf("Input squence for decode: ");
    for (int i = 0; i < len; i++) {
        scanf("%c", &code[i]);
        if (i == len - 1 && code[i] != '\n') {
            len++;
            code = realloc(code, sizeof(char) * len);
        }
    }
    //    �ϥΰʺA�O����t�mŪ�J�ϥΪ̩ҿ�J��01�r��
    printf("Decoded Huffman Data:\n");
    decode(minHeap->array[0], code, 0);
    //    �I�s�ѽX���
    printf("\n");
    return 0;
}
