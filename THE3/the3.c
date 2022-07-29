#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "the3.h"
#define MAX_SIZE 10
QueryNode* query_table[MAX_SIZE];
CountNode* head = NULL;

CountNode* createNewCountNode(int count)
{
    CountNode* temp = (CountNode*) malloc(sizeof(CountNode));
    temp->count = count;
    temp->next = NULL;
    temp->prev = NULL;
    temp->querylist = NULL;
    return temp;
}
QueryNode* createNewQueryNode()
{
    QueryNode* temp = (QueryNode*) malloc(sizeof(QueryNode));
    temp->query = (char*) calloc(6, sizeof(char));
    temp->next = NULL;
    temp->prev = NULL;
    return temp;
}
void addCountNode(int count)
{
    if (head == NULL) head = createNewCountNode(count);
    else
    {
        CountNode* newCountNode = createNewCountNode(count);
        CountNode* iterator = head;
        if (head->count > count) /* beginning */
        {
            head->prev = newCountNode;
            newCountNode->next = head;
            head = newCountNode;
        }
        else
        {
            while (iterator->next != NULL && iterator->count < count)
            {
                iterator = iterator->next;
            }
            if (count > iterator->count) /* end */
            {
                iterator->next = newCountNode;
                newCountNode->prev = iterator;
            }
            else if (count < iterator->count) /* middle */
            {
                if (iterator->prev != NULL) 
                {
                    iterator->prev->next = newCountNode;
                    newCountNode->prev = iterator->prev;
                    newCountNode->next = iterator;
                    iterator->prev = newCountNode;
                }
            }
        }
    }
}
void addQueryNode(int count, QueryNode* table_element) /* alphabetically sorted */
{
    CountNode* temp = head;
    while(temp->next != NULL && temp->count != count)
    {
        temp = temp->next;
    }
    if (temp->querylist == NULL)
    {
        temp->querylist = (QueryNode**) malloc(sizeof(QueryNode*));
        *(temp->querylist) = table_element;
    }
    else
    {
        QueryNode* iterator = *(temp->querylist);
        if (strcmp(iterator->query, table_element->query) > 0) /* beginning */
        {
            iterator->prev = table_element;
            table_element->next = iterator;
            *(temp->querylist) = table_element;
        }
        else
        {
            while (iterator->next != NULL && strcmp(iterator->query, table_element->query) < 0)
            {
                iterator = iterator->next;
            }
            if (strcmp(iterator->query, table_element->query) < 0) /* end */
            {
                iterator->next = table_element;
                table_element->prev = iterator;
            }
            else if (strcmp(iterator->query, table_element->query) > 0) /* middle */
            {
                iterator->prev->next = table_element;
                table_element->prev = iterator->prev;
                table_element->next = iterator;
                iterator->prev = table_element;
            }
        }
    }
}
void printTheResult()
{
    CountNode* outerPointer = head;
    while (outerPointer != NULL)
    {
        QueryNode* innerPointer = *(outerPointer->querylist);
        printf("%d", outerPointer->count);
        while (innerPointer != NULL)
        {
            printf(" %s", innerPointer->query);
            innerPointer = innerPointer->next;
        }
        printf("\n");
        outerPointer = outerPointer->next;
    }
}
void removeCountNode(int wantedCount)
{
    CountNode* outerPointer = head;
    if (outerPointer == NULL) return;  
    while (outerPointer->count != wantedCount)
    {
        outerPointer = outerPointer->next;
    }
    if (outerPointer->querylist == NULL)
    {
        if (outerPointer == head) /* beginning */
        {
            if (outerPointer->next != NULL)
            {
                outerPointer->next->prev = NULL;
                head = outerPointer->next;
                free(outerPointer);
            }
            else
            {
                free(outerPointer);
                head = NULL;
            }
        }
        else if (outerPointer->next == NULL)/* end */
        {
            if (outerPointer->prev != NULL)
            {
                outerPointer->prev->next = NULL;
                free(outerPointer);
            }
        }
        else /* middle */
        {
            if (outerPointer->next != NULL)
            {
                outerPointer->next->prev = outerPointer->prev;
            }
            if (outerPointer->prev != NULL)
            {
                outerPointer->prev->next = outerPointer->next;
                free(outerPointer);
            }
        }
    }
}
void removeQueryNode(int wantedCount, QueryNode* table_element)
{
    CountNode* outerPointer = head;
    QueryNode* innerPointer = NULL;
    if (outerPointer == NULL) return;
    while (outerPointer->count != wantedCount && outerPointer != NULL)
    {
        outerPointer = outerPointer->next;
    }
    if (outerPointer->querylist != NULL)
    {
        innerPointer = *(outerPointer->querylist);
    }
    if (innerPointer == NULL) return ;

    else if (innerPointer->prev == NULL && innerPointer->next == NULL) /* only one element */
    {
        *(outerPointer->querylist) = NULL;
        outerPointer->querylist = NULL;
        return ;
    }
    else if (!strcmp(innerPointer->query, table_element->query))
    {
        if (innerPointer->next != NULL)/* head */
        {
            innerPointer->next->prev = NULL;
            *(outerPointer->querylist) = innerPointer->next;
            innerPointer->next = NULL;
            return ;
        }
    }
    while (innerPointer != NULL)
    {
        if (!strcmp(innerPointer->query, table_element->query))
        {
            if (innerPointer->next == NULL) /* end */
            {
                if (innerPointer->prev != NULL)
                {
                    innerPointer->prev->next = NULL;
                    innerPointer->prev = NULL;
                    break;
                }
            }
            else /* middle */
            {
                if(innerPointer->prev != NULL) innerPointer->prev->next = innerPointer->next;
                if(innerPointer->next != NULL) innerPointer->next->prev = innerPointer->prev;
                if(innerPointer->next != NULL) innerPointer->next = NULL;
                if(innerPointer->prev != NULL) innerPointer->prev = NULL;
                break;
            }
        }
        innerPointer = innerPointer->next;
    }
}
int main() 
{
    int query_number, i, j, count, newInputCount, tableIsEmpty = 0, inTheTable = 0;
    int indexInQueryTable = 0, wantedCount = 0, removedIndex, minCount;
    char* removedQuery = (char*) calloc(6, sizeof(char));
    char* tempString = (char*) calloc(6, sizeof(char)); 
    scanf("%d", &query_number);
    for (i = 0; i < query_number; i++)
    {
        query_table[i] = createNewQueryNode();
        scanf(" %s",query_table[i]->query);
        scanf("%d", &count);
        addCountNode(count);
        addQueryNode(count, query_table[i]);
    }
    scanf("%d", &newInputCount);
    
    for (i = 0; i < newInputCount; i++)
    {
        scanf(" %s", tempString);
        for (j = 0; j < MAX_SIZE; j++)
        {
            if (query_table[j] == NULL)
            {   
                tableIsEmpty = 1;
                break;
            }
            else tableIsEmpty = 0;
        }
        for (j = 0; j < MAX_SIZE; j++)
        {
            if (query_table[j] == NULL) continue;
            else if (!(strcmp(query_table[j]->query, tempString)))
            {   
                inTheTable = 1;
                indexInQueryTable = j;
                break;
            }
            else inTheTable = 0;
        }
        if (!inTheTable && tableIsEmpty) 
        {
            for (j = 0; j < MAX_SIZE; j++)
            {   
                if (query_table[j] == NULL)
                {
                    query_table[j] = createNewQueryNode();
                    strcpy(query_table[j]->query, tempString);
                    addCountNode(1);
                    addQueryNode(1, query_table[j]);
                    break;
                }
            }
        }

        else if (inTheTable)
        {
            CountNode* outerPointer = head;
            while (outerPointer != NULL)
            {
                QueryNode* innerPointer = *(outerPointer->querylist);
                while (innerPointer != NULL)
                {
                    if (!strcmp(innerPointer->query, tempString))
                    {
                        wantedCount = outerPointer->count;
                    }
                    innerPointer = innerPointer->next;
                }
                outerPointer = outerPointer->next;
            }
            removeQueryNode(wantedCount, query_table[indexInQueryTable]);
            removeCountNode(wantedCount);
            addCountNode(wantedCount+1);
            addQueryNode(wantedCount+1, query_table[indexInQueryTable]);
        }

        else if(!inTheTable && !tableIsEmpty)
        {
            CountNode* outerPointer = head;
            QueryNode* innerPointer = *(outerPointer->querylist);
            minCount = head->count;
            strcpy(removedQuery, innerPointer->query);
            for (j = 0; j < MAX_SIZE; j++)
            {
                if (!strcmp(query_table[j]->query, removedQuery))
                {
                    removedIndex = j;
                }
            }
            removeQueryNode(minCount, query_table[removedIndex]);
            removeCountNode(minCount);
            query_table[removedIndex] = createNewQueryNode();
            strcpy(query_table[removedIndex]->query, tempString);
            addCountNode(1);
            addQueryNode(1, query_table[removedIndex]);
        }
    }
    printTheResult();
    return 0;
}
