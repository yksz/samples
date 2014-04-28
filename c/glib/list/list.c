#include <stdio.h>
#include <glib.h>

static void print_iterator(gpointer item)
{
    printf("[foreach] item: '%s'\n", item);
}

int main()
{
    GList* list = NULL;

    list = g_list_append(list, "first");
    list = g_list_append(list, "second");
    list = g_list_append(list, "third");
    printf("list length: %d\n", g_list_length(list));
    printf("first item: '%s'\n", list->data);
    printf("last item: '%s'\n", g_list_last(list)->data);
    GList* iterator = NULL;
    for (iterator = list; iterator; iterator = iterator->next) {
        printf("[iterator] item: '%s'\n", iterator->data);
    }

    printf("remove item: '%s'\n", "first");
    list = g_list_remove(list, "first");
    printf("list length: %d\n", g_list_length(list));
    g_list_foreach(list, (GFunc) print_iterator, NULL);

    g_list_free(list);
    return 0;
}
