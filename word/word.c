#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

typedef struct node{
    char letter[25];
    struct node *next;
}node;

typedef struct {
    node *lists[26];
}dict;

void format(char* str);
void initdict(dict* Dict);
void insert(dict* Dict, char* word);
void splitwords(dict* Dict, char* word);
void free_list(node* head);
void free_dict(dict* Dict);

int main(void)
{
    FILE *fin, *fout;
    dict* Dict = (dict*) malloc(sizeof(dict));
    if (Dict == NULL)
    {
        return EXIT_FAILURE;
    }
    char buffer[42];
    printf("Dictionary initialized\n");

    initdict(Dict);

    fin = fopen("in.txt", "r");
    //fin = fopen("D:\\code\\C\\pset5\\in.txt", "r");
    if (!fin)
    {
        perror("Error opening input file");
        return EXIT_FAILURE;
    }

    fout = fopen("words.txt", "w");
    // fout = fopen("D:\\code\\C\\pset5\\words.txt", "w");
    if (!fout)
    {
        perror("Error opening output file");
        fclose(fin);
        return EXIT_FAILURE;
    }

    // 逐个单词写入，但是会写入标点符号，记得清除
    while (fscanf(fin, "%20s", buffer) == 1)
    {
        // 将所有单词转换为小写,并清除标点
        format(buffer);

        // 检测连字符
        int flag = 1; //检测是否有连字符的标志
        for (int i = 0, len = strlen(buffer); i < len; i++)
        {
            // 检测buffer是否为空
            if (strlen(buffer) == 0)
            {
                continue;
            }
            // 检测到连字符
            if (buffer[i] == '-')
            {
                splitwords(Dict, buffer);
                flag = 0;
                break;
            }
        }

        // 在无连字符的情况下插入单词
        if (flag == 1)
        {
            insert(Dict, buffer);
        }
    }

    // 遍历26个字母
    for (int i = 0; i < 26; i++)
    {
        // 遍历该字母的链表
        for (node* ptr = Dict->lists[i]; ptr != NULL; ptr = ptr->next)
        {
            fprintf(fout, "%s\n", ptr->letter);
        }
    }

    fclose(fin);
    fclose(fout);

    free_dict(Dict);
    free(Dict);

    return EXIT_SUCCESS;
}

void initdict(dict* Dict)
{
    for (int i = 0; i < 26; i++)
    {
        Dict->lists[i] = NULL;
    }
}

void format(char* str)
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        str[i] = tolower(str[i]);
    }
    while (!isalpha(str[len - 1]))
    {
        str[len - 1] = '\0';
        len--;
    }
}

void insert(dict* Dict, char* word)
{
     // 插到第几个链表的索引
    int index = word[0] - 'a';
    node *n = (node*) malloc(sizeof(node));

    if (n == NULL)
    {
        printf("Memory allocation failed\n");
        return;
    }

    strcpy(n->letter, word);
    if (strlen(word) == 0)
    {
        return;
    }
    printf("Inserted word: %s\n", n->letter);
    n->next = NULL;

    // 链表为空
    if (Dict->lists[index] == NULL)
    {
        Dict->lists[index] = n;
        return;
    }

    // 该单词属于链表开头
    else if(strcmp(n->letter, Dict->lists[index]->letter) < 0)
    {
        n->next = Dict->lists[index];
        Dict->lists[index] = n;
        return;
    }

    // 该单词与链表开头相同
    else if(strcmp(n->letter, Dict->lists[index]->letter) == 0)
    {
        printf("----Duplicated word: %s\n", n->letter);
        free(n);
        return;
    }

    // 属于链表中间，与开头已经比较完所以从第二个开始
    for (node* ptr = Dict->lists[index]; ptr != NULL; ptr = ptr->next)
    {
        // 如果指向了链表最后一个
        if (ptr->next == NULL)
        {
            // 比最后一个大
            if (strcmp(n->letter, ptr->letter) > 0)
            {
                ptr->next = n;
                return;
            }
            // 和最后一个相等，不存在小的情况
            else
            {
                free(n);
                return;
            }
        }

        // 排除所有情况，现在是完全在中间的情况
        if (strcmp(n->letter, ptr->next->letter) < 0)
        {
            n->next = ptr->next;
            ptr->next = n;
            return;
        }
    }

}

void splitwords(dict* Dict, char* word)
{
    char *token = strtok(word, "-");
    while (token != NULL)
    {
        insert(Dict, token);
        token = strtok(NULL, "-"); // 在上次分割后剩余的单词继续分割
    }
}

// 释放单个链表的内存
void free_list(node* head)
{
    node* current = head;
    while (current != NULL)
    {
        node* temp = current;
        current = current->next;
        free(temp);  // 释放当前节点
    }
}

// 释放整个字典的内存
void free_dict(dict* Dict)
{
    for (int i = 0; i < 26; i++) {
        free_list(Dict->lists[i]);  // 释放每个链表
    }
}
