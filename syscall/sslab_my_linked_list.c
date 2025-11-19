/* 2025 Fall COSE341 Operating System */
/* Project 1 */
/* 이동현 */
#include <linux/syscalls.h>
#include <linux/kernel.h>
#include <linux/linkage.h>
#include <linux/slab.h>
#define MAX_LIST_OUTPUT_SIZE PAGE_SIZE

typedef struct myLinkedListNode {
    int value;
    struct myLinkedListNode *next;
} Node;

static Node *head = NULL;

static void print_list(void)
{
    Node *cur = head;
    char *buf;
    int len = 0;
    
    buf = kmalloc(MAX_LIST_OUTPUT_SIZE, GFP_KERNEL);
    if (!buf) {
        printk(KERN_ERR "Failed to allocate printk buffer.\n");
        return;
    }

    len += snprintf(buf + len, MAX_LIST_OUTPUT_SIZE - len, "List Head -> ");

    while (cur && len < MAX_LIST_OUTPUT_SIZE) {
        len += snprintf(buf + len, MAX_LIST_OUTPUT_SIZE - len, "[%d] -> ", cur->value);
        cur = cur->next;
    }

    snprintf(buf + len, MAX_LIST_OUTPUT_SIZE - len, "NULL\n");

    printk("%s", buf);

    kfree(buf);
}

SYSCALL_DEFINE1(os2025_add, int, val)
{
    Node *newNode = kmalloc(sizeof(Node), GFP_KERNEL);
    if (!newNode)
        return -ENOMEM;

    newNode->value = val;
    newNode->next = NULL;

    printk("[Sys_call] os2025_add();\n");

    if (head == NULL) {
        head = newNode;
    } else {
        Node *oldHead = head;
        head = newNode;
        newNode->next = oldHead;
    }

    print_list();
    return 0;
}

SYSCALL_DEFINE2(os2025_insert, int, tar_val, int, val)
{
    Node *cur = head;
    printk("[Sys_call] os2025_insert();\n");

    while (cur && cur->value != tar_val) {
        cur = cur->next;
    }

    if (cur == NULL) {
        printk("Invalid Target Value: %d\n", tar_val);
        return -EINVAL;
    }

    Node *newNode = kmalloc(sizeof(Node), GFP_KERNEL);
    if (!newNode)
        return -ENOMEM;

    newNode->value = val;
    newNode->next = cur->next;
    cur->next = newNode;

    print_list();
    return 0;
}

SYSCALL_DEFINE1(os2025_remove, int, val)
{
    Node *cur = head, *prev = NULL;
    printk("[Sys_call] os2025_remove();\n");

    while (cur && cur->value != val) {
        prev = cur;
        cur = cur->next;
    }

    if (!cur) {
        printk("Invalid Target Value: %d\n", val);
        return -EINVAL;
    }

    if (prev == NULL)
        head = cur->next;
    else
        prev->next = cur->next;

    kfree(cur);

    print_list();
    return 0;
}
