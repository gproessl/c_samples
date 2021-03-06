
#ifndef CONTAINER_C
#define CONTAINER_C
#define S_LINKED
#include "container.c"
#undef CONTAINER_C
#endif

#ifndef LIST_C
#define LIST_C
#include "list.c"
#undef LIST_C
#endif

#ifndef MAP_C
#define MAP_C
#include "map.c"
#undef MAP_C
#endif

#ifndef VECTOR_C
#define VECTOR_C
#include "vector.c"
#undef VECTOR_C
#endif

#ifndef STACK_C
#define STACK_C
#include "stack.c"
#undef STACK_C
#endif

#include "snow.h"

void *v_for_each(int data, void *ref, struct vector_info *info)
{
    if(data == 5)
    {
        return 5;
    }

    return 0;
}

void *m_for_each(int data, void *ref, struct list_info *info)
{
    if(data == 5)
    {
        return 5;
    }
    return 0;
}

void *m_for_each_remove(int data, void *ref, struct list_info *info)
{
    if(data == 3)
    {
        list_remove_at(info->this, 3);
    }
    return 0;
}

void *map_m_for_each(int data, void *ref, struct map_info *info)
{
    if(data == 5)
    {
        return 5;
    }
    return 0;
}

void *map_m_for_each_remove(int data, void *ref, struct map_info *info)
{
    if(data == 3)
    {
        map_remove_at(info->this, 3);
    }
    return 0;
}



describe(container, 
{    

    subdesc(list, 
    {
        it("push_front", 
        {
            struct list mlist;
            list_init(&mlist);
            for(int i = 0; i < 10; i++)
            {
                list_push_front(&mlist, i);
                asserteq(mlist.size, i+1);
                asserteq(list_at(&mlist,0) , i);
            }        
            asserteq(mlist.size, 10);
            list_delete(&mlist);
        });

        it("push_back", 
        {
            struct list mlist;
            list_init(&mlist);
            for(int i = 0; i < 10; i++)
            {
                list_push_back(&mlist, i);
                asserteq(mlist.size, i+1);
                asserteq(list_at(&mlist,9) , i);
            }        
            asserteq(mlist.size, 10);
            list_delete(&mlist);
        });

        it("list_delete", 
        {
            struct list mlist;
            list_init(&mlist);
            for(int i = 0; i < 10; i++)
            {
                list_push_front(&mlist, i);
                asserteq(mlist.size, i+1);
                asserteq(list_at(&mlist,0) , i);
            } 
            list_delete(&mlist);
            assert(!mlist.size);
            assert(!mlist.head);
            assert(!mlist.tail);
            list_delete(&mlist);
        });

        it("pop_back",
        {
            struct list mlist;
            list_init(&mlist);
            for(int i = 0; i < 10; i++)
            {
                list_push_back(&mlist, i);
                asserteq(mlist.size, i+1);
                asserteq(list_at(&mlist,9) , i);
            }
            for(int i = 9; i >= 0; i--)
            {
                asserteq(list_pop_back(&mlist), i);
            }
            assert(!mlist.size);
            assert(!mlist.head);
            assert(!mlist.tail);
            list_delete(&mlist);
        });

        it("pop_front",
        {
            struct list mlist;
            list_init(&mlist);
            for(int i = 0; i < 10; i++)
            {
                list_push_back(&mlist, i);
                asserteq(mlist.size, i+1);
                asserteq(list_at(&mlist,9) , i);
            }
            for(int i = 0; i < 10; i++)
            {
                asserteq(list_pop_front(&mlist), i);
            }
            assert(!mlist.size);
            assert(!mlist.head);
            assert(!mlist.tail);
            list_delete(&mlist);
        });

        it("at",
        {
            struct list mlist;
            list_init(&mlist);
            for(int i = 0; i < 10; i++)
            {
                list_push_back(&mlist, i);
                asserteq(mlist.size, i+1);
                asserteq(list_at(&mlist,9) , i);
            }
            for(int i = 0; i < 10; i++)
            {
                asserteq(list_at(&mlist, i), i);
            }
            asserteq(mlist.size, 10);
            assert(mlist.head);
            assert(mlist.tail);
            list_delete(&mlist);
        });

        it("remove_at",
        {
            struct list mlist;
            list_init(&mlist);
            for(int i = 0; i < 10; i++)
            {
                list_push_back(&mlist, i);
                asserteq(mlist.size, i+1);
                asserteq(list_at(&mlist,9) , i);
            }
            asserteq(list_remove_at(&mlist, 0), 0);
            asserteq(list_remove_at(&mlist, 8), 9);
            asserteq(list_remove_at(&mlist, 3), 4);
            asserteq(list_remove_at(&mlist, 5), 7);
            asserteq(list_remove_at(&mlist, 4), 6);
            asserteq(list_remove_at(&mlist, 4), 8);
            asserteq(list_remove_at(&mlist, 1), 2);
            asserteq(list_remove_at(&mlist, 0), 1);
            asserteq(list_remove_at(&mlist, 1), 5);
            asserteq(list_remove_at(&mlist, 0), 3);

            asserteq(mlist.size, 0);
            assert(!mlist.head);
            assert(!mlist.tail);
            list_delete(&mlist);
        });

        it("remove_node",
        {
            struct list mlist;
            list_init(&mlist);
            struct list_node *node0 = list_push_back(&mlist, 0);
            list_push_back(&mlist, 1);
            list_push_back(&mlist, 2);
            struct list_node *node = list_push_back(&mlist, 3);
            list_push_back(&mlist, 4);
            list_push_back(&mlist, 5);
            list_push_back(&mlist, 6);
            struct list_node *node1 = list_push_back(&mlist, 7);
            asserteq(mlist.size, 8);

            list_remove_node(&mlist, node);
            asserteq(list_at(&mlist, 3), 4);
            asserteq(mlist.size, 7);

            list_remove_node(&mlist, node0);
            list_remove_node(&mlist, node1);

            asserteq(list_at(&mlist, 4), 6);
            asserteq(mlist.size, 5);

            list_delete(&mlist);
        });

        it("for_each",
        {
            struct list mlist;
            list_init(&mlist);
            for(int i = 0; i < 10; i++)
            {
                list_push_back(&mlist, i);
                asserteq(mlist.size, i+1);
                asserteq(list_at(&mlist,9) , i);
            }
            asserteq(list_for_each(&mlist, &m_for_each, 0), 5);
            asserteq(list_for_each(&mlist, &m_for_each_remove, 0), 0);
            asserteq(mlist.size, 9);
            assert(mlist.head);
            assert(mlist.tail);
            list_delete(&mlist);
        });

    });

    subdesc(map, 
    {
        it("push_front", 
        {
            struct map mmap;
            map_init(&mmap);
            char *key = malloc(5);
            strcpy(key, "akey");
            for(int i = 0; i < 10; i++)
            {
                map_push_front(&mmap, key, i);
                asserteq(mmap.size, i+1);
                asserteq(map_at(&mmap,0) , i);
                (*key)++;
            }        
            asserteq(map_get(&mmap, "ckey"), 2);
            asserteq(mmap.size, 10);
            free(key);
        });

        it("push_back", 
        {
            struct map mmap;
            map_init(&mmap);
            char *key = malloc(5);
            strcpy(key, "akey");
            for(int i = 0; i < 10; i++)
            {
                map_push_back(&mmap,key, i);
                asserteq(mmap.size, i+1);
                asserteq(map_at(&mmap,9) , i);
                (*key)++;
            }        
            asserteq(map_get(&mmap, "bkey"), 1);
            asserteq(mmap.size, 10);
            free(key);
        });

        it("map_delete", 
        {
            struct map mmap;
            map_init(&mmap);
            char *key = malloc(5);
            strcpy(key, "akey");
            for(int i = 0; i < 10; i++)
            {
                map_push_front(&mmap, key, i);
                asserteq(mmap.size, i+1);
                asserteq(map_at(&mmap,0) , i);
                (*key)++;
            } 
            asserteq(map_get(&mmap, "dkey"), 3);
            map_delete(&mmap);
            assert(!mmap.size);
            assert(!mmap.head);
            assert(!mmap.tail);
            free(key);
        });

        it("pop_back",
        {
            struct map mmap;
            map_init(&mmap);
            char *key = malloc(5);
            strcpy(key, "akey");
            for(int i = 0; i < 10; i++)
            {
                map_push_back(&mmap, key, i);
                asserteq(mmap.size, i+1);
                asserteq(map_at(&mmap,9) , i);
                (*key)++;
            }
            for(int i = 9; i >= 0; i--)
            {
                asserteq(map_pop_back(&mmap), i);
            }
            asserteq(map_get(&mmap, "akey"), 0);
            assert(!mmap.size);
            assert(!mmap.head);
            assert(!mmap.tail);
            free(key);
        });

        it("pop_front",
        {
            struct map mmap;
            map_init(&mmap);
            char *key = malloc(5);
            strcpy(key, "akey");
            for(int i = 0; i < 10; i++)
            {
                map_push_back(&mmap, key, i);
                asserteq(mmap.size, i+1);
                asserteq(map_at(&mmap,9) , i);
                (*key)++;
            }
            for(int i = 0; i < 10; i++)
            {
                asserteq(map_pop_front(&mmap), i);
            }
            //returns 0 pointer
            asserteq(map_get(&mmap, "ekey"), 0);
            assert(!mmap.size);
            assert(!mmap.head);
            assert(!mmap.tail);
            free(key);
        });

        it("at",
        {
            struct map mmap;
            map_init(&mmap);
            char *key = malloc(5);
            strcpy(key, "akey");
            for(int i = 0; i < 10; i++)
            {
                map_push_back(&mmap, key, i);
                asserteq(mmap.size, i+1);
                asserteq(map_at(&mmap,9) , i);
                (*key)++;
            }
            for(int i = 0; i < 10; i++)
            {
                asserteq(map_at(&mmap, i), i);
            }
            asserteq(map_get(&mmap, "fkey"), 5);
            asserteq(mmap.size, 10);
            assert(mmap.head);
            assert(mmap.tail);
            free(key);
        });

        it("remove_at",
        {
            struct map mmap;
            map_init(&mmap);
            char *key = malloc(5);
            strcpy(key, "akey");
            for(int i = 0; i < 10; i++)
            {
                map_push_back(&mmap, key, i);
                asserteq(mmap.size, i+1);
                asserteq(map_at(&mmap,9) , i);
                (*key)++;
            }
            asserteq(map_get(&mmap, "gkey"), 6);
            asserteq(map_remove_at(&mmap, 0), 0);
            asserteq(map_remove_at(&mmap, 8), 9);
            asserteq(map_remove_at(&mmap, 3), 4);
            asserteq(map_remove_at(&mmap, 5), 7);
            asserteq(map_remove_at(&mmap, 4), 6);
            asserteq(map_remove_at(&mmap, 4), 8);
            asserteq(map_remove_at(&mmap, 1), 2);
            asserteq(map_remove_at(&mmap, 0), 1);
            asserteq(map_remove_at(&mmap, 1), 5);
            asserteq(map_remove_at(&mmap, 0), 3);

            asserteq(mmap.size, 0);
            assert(!mmap.head);
            assert(!mmap.tail);
            free(key);
        });

        it("for_each",
        {
            struct map mmap;
            map_init(&mmap);
            for(int i = 0; i < 10; i++)
            {
                map_push_back(&mmap, "key", i);
                asserteq(mmap.size, i+1);
                asserteq(map_at(&mmap,9) , i);
            }
            asserteq(map_for_each(&mmap, &map_m_for_each, 0), 5);
            asserteq(map_for_each(&mmap, &map_m_for_each_remove, 0), 0);
            asserteq(mmap.size, 9);
            assert(mmap.head);
            assert(mmap.tail);
        });

    });

    subdesc(vector, 
    {
        it("push_front", 
        {
            struct vector mvector;
            vector_init(&mvector, sizeof(int),  10);
            for(int i = 0; i < 15; i++)
            {
                vector_push_front(&mvector, i);
                asserteq(mvector.size, i+1);
                asserteq(vector_at(&mvector,0) , i);
            }        
            asserteq(mvector.size, 15);
            vector_delete(&mvector);
        });

        it("push_back", 
        {
            struct vector mvector;
            vector_init(&mvector, sizeof(int),  10);
            for(int i = 0; i < 15; i++)
            {
                vector_push_back(&mvector, i);
                asserteq(mvector.size, i+1);
                asserteq(vector_at(&mvector,mvector.size-1) , i);
            }        
            asserteq(mvector.size, 15);
            vector_delete(&mvector);
        });

        it("delete", 
        {
            struct vector mvector;
            vector_init(&mvector, sizeof(int),  10);
            for(int i = 0; i < 15; i++)
            {
                vector_push_back(&mvector, i);
                asserteq(mvector.size, i+1);
                asserteq(vector_at(&mvector,mvector.size-1) , i);
            }        
            asserteq(mvector.size, 15);
            vector_delete(&mvector);

            assert(!mvector.size);
        });

        it("pop_back",
        {
            struct vector mvector;
            vector_init(&mvector, sizeof(int),  10);
            for(int i = 0; i < 10; i++)
            {
                vector_push_back(&mvector, i);
                asserteq(mvector.size, i+1);
                asserteq(vector_at(&mvector,mvector.size-1) , i);
            }        

            for(int i = 9; i >= 0; i--)
            {
                asserteq(vector_pop_back(&mvector), i);
            }

            assert(!mvector.size);
            vector_delete(&mvector);
        });

        it("pop_front",
        {
            struct vector mvector;
            vector_init(&mvector, sizeof(int),  10);
            for(int i = 0; i < 10; i++)
            {
                vector_push_back(&mvector, i);
                asserteq(mvector.size, i+1);
                asserteq(vector_at(&mvector,mvector.size-1) , i);
            }        

            for(int i = 0; i < 10; i++)
            {
                asserteq(vector_pop_front(&mvector), i);
            }
            assert(!mvector.size);
            vector_delete(&mvector);
        });

        it("at",
        {
            struct vector mvector;
            vector_init(&mvector, sizeof(int),  10);
            for(int i = 0; i < 10; i++)
            {
                vector_push_back(&mvector, i);
                asserteq(mvector.size, i+1);
                asserteq(vector_at(&mvector,mvector.size-1) , i);
            }        

            for(int i = 0; i < 10; i++)
            {
                asserteq(vector_at(&mvector, i), i);
            }
            asserteq(mvector.size, 10);
            vector_delete(&mvector);
        });

        it("set",
        {
            struct vector mvector;
            vector_init(&mvector, sizeof(int), 5);
            for(int i = 0; i < 10; i++)
            {
                vector_set(&mvector, i, i); 
                asserteq(vector_at(&mvector, i), i);
            }
            asserteq(mvector.size, 10);
            vector_delete(&mvector);
        });

        it("remove_at",
        {
            struct vector mvector;
            vector_init(&mvector, sizeof(int),  10);
            for(int i = 0; i < 10; i++)
            {
                vector_push_back(&mvector, i);
                asserteq(mvector.size, i+1);
                asserteq(vector_at(&mvector,mvector.size-1) , i);
            }        

            asserteq(vector_remove_at(&mvector, 0), 0);
            asserteq(vector_remove_at(&mvector, 8), 9);
            asserteq(vector_remove_at(&mvector, 3), 4);
            asserteq(vector_remove_at(&mvector, 5), 7);
            asserteq(vector_remove_at(&mvector, 4), 6);
            asserteq(vector_remove_at(&mvector, 4), 8);
            asserteq(vector_remove_at(&mvector, 1), 2);
            asserteq(vector_remove_at(&mvector, 0), 1);
            asserteq(vector_remove_at(&mvector, 1), 5);
            asserteq(vector_remove_at(&mvector, 0), 3);

            asserteq(mvector.size, 0);
            vector_delete(&mvector);
        });

        it("for_each",
        {
            struct vector mvector;
            vector_init(&mvector, sizeof(int),  10);
            for(int i = 0; i < 10; i++)
            {
                vector_push_back(&mvector, i);
                asserteq(mvector.size, i+1);
                asserteq(vector_at(&mvector,mvector.size-1) , i);
            }        

            asserteq(vector_for_each(&mvector, &v_for_each, 0), 5);
            asserteq(mvector.size, 10);
            vector_delete(&mvector);
        });


    });

    subdesc(container, 
    {
        it("push_front", 
        {
            struct list mlist;
            list_init(&mlist);
            for(int i = 0; i < 10; i++)
            {
                container_push_front(&mlist, i);
                asserteq(mlist.size, i+1);
                asserteq(container_at(&mlist,0) , i);
            }        
            asserteq(mlist.size, 10);
            container_delete(&mlist);
        });

        it("push_back", 
        {
            struct list mlist;
            list_init(&mlist);
            for(int i = 0; i < 10; i++)
            {
                container_push_back(&mlist, i);
                asserteq(mlist.size, i+1);
                asserteq(container_at(&mlist,9) , i);
            }        
            asserteq(mlist.size, 10);
            container_delete(&mlist);
        });

        it("delete", 
        {
            struct list mlist;
            list_init(&mlist);
            for(int i = 0; i < 10; i++)
            {
                container_push_front(&mlist, i);
                asserteq(mlist.size, i+1);
                asserteq(container_at(&mlist,0) , i);
            } 
            container_delete(&mlist);
            assert(!mlist.size);
            assert(!mlist.head);
            assert(!mlist.tail);
            container_delete(&mlist);
        });

        it("pop_back",
        {
            struct list mlist;
            list_init(&mlist);
            for(int i = 0; i < 10; i++)
            {
                container_push_back(&mlist, i);
                asserteq(mlist.size, i+1);
                asserteq(container_at(&mlist,9) , i);
            }
            for(int i = 9; i >= 0; i--)
            {
                asserteq(container_pop_back(&mlist), i);
            }
            assert(!mlist.size);
            assert(!mlist.head);
            assert(!mlist.tail);
            container_delete(&mlist);
        });

        it("pop_front",
        {
            struct list mlist;
            list_init(&mlist);
            for(int i = 0; i < 10; i++)
            {
                container_push_back(&mlist, i);
                asserteq(mlist.size, i+1);
                asserteq(container_at(&mlist,9) , i);
            }
            for(int i = 0; i < 10; i++)
            {
                asserteq(container_pop_front(&mlist), i);
            }
            assert(!mlist.size);
            assert(!mlist.head);
            assert(!mlist.tail);
            container_delete(&mlist);
        });

        it("at",
        {
            struct list mlist;
            list_init(&mlist);
            for(int i = 0; i < 10; i++)
            {
                container_push_back(&mlist, i);
                asserteq(mlist.size, i+1);
                asserteq(container_at(&mlist,9) , i);
            }
            for(int i = 0; i < 10; i++)
            {
                asserteq(container_at(&mlist, i), i);
            }
            asserteq(mlist.size, 10);
            assert(mlist.head);
            assert(mlist.tail);
            container_delete(&mlist);
        });

        it("remove_at",
        {
            struct list mlist;
            list_init(&mlist);
            for(int i = 0; i < 10; i++)
            {
                container_push_back(&mlist, i);
                asserteq(mlist.size, i+1);
                asserteq(container_at(&mlist,9) , i);
            }
            asserteq(container_remove_at(&mlist, 0), 0);
            asserteq(container_remove_at(&mlist, 8), 9);
            asserteq(container_remove_at(&mlist, 3), 4);
            asserteq(container_remove_at(&mlist, 5), 7);
            asserteq(container_remove_at(&mlist, 4), 6);
            asserteq(container_remove_at(&mlist, 4), 8);
            asserteq(container_remove_at(&mlist, 1), 2);
            asserteq(container_remove_at(&mlist, 0), 1);
            asserteq(container_remove_at(&mlist, 1), 5);
            asserteq(container_remove_at(&mlist, 0), 3);

            asserteq(mlist.size, 0);
            assert(!mlist.head);
            assert(!mlist.tail);
            container_delete(&mlist);
        });

    });

    subdesc(stack, 
    {
        it("push", 
        {
            struct stack mstack;
            stack_init(&mstack);

            for(int i = 0; i < 10; i++)
            {
                stack_push(&mstack, i);
                asserteq(stack_top(&mstack), i);
                asserteq(mstack.size, i + 1);
            }

            stack_delete(&mstack);
        });

        it("pop", 
        {
            struct stack mstack;
            stack_init(&mstack);

            stack_push(&mstack, 0);
            stack_push(&mstack, 1);
            stack_push(&mstack, 2);
            stack_push(&mstack, 3);

            asserteq(stack_pop(&mstack), 3);
            asserteq(mstack.size, 3);
            asserteq(stack_pop(&mstack), 2);
            asserteq(mstack.size, 2);
            asserteq(stack_pop(&mstack), 1);
            asserteq(mstack.size, 1);

            stack_delete(&mstack);
        });

        it("top", 
        {
            struct stack mstack;
            stack_init(&mstack);

            stack_push(&mstack, 0);
            stack_push(&mstack, 1);
            stack_push(&mstack, 2);
            stack_push(&mstack, 3);

            asserteq(stack_top(&mstack), 3);
            asserteq(stack_pop(&mstack), 3);
            asserteq(mstack.size, 3);
            asserteq(stack_top(&mstack), 2);
            asserteq(stack_pop(&mstack), 2);
            asserteq(mstack.size, 2);
            asserteq(stack_top(&mstack), 1);
            asserteq(stack_pop(&mstack), 1);
            asserteq(mstack.size, 1);

            stack_delete(&mstack);
        });

        it("delete", 
        {
            struct stack mstack;
            stack_init(&mstack);

            for(int i = 0; i < 10; i++)
            {
                stack_push(&mstack, i);
                asserteq(stack_top(&mstack), i);
                asserteq(mstack.size, i + 1);
            }

            stack_delete(&mstack);

            asserteq(mstack.size, 0);
        });

        it("delete_all", 
        {
            /*
            struct stack mstack;
            stack_init(&mstack);

            for(int i = 0; i < 10; i++)
            {
                int *sp = malloc(sizeof(int));
                *sp = i;
                stack_push(&mstack, i);
                asserteq(*stack_top(&mstack), i);
                asserteq(mstack.size, i + 1);
            }

            stack_delete_all(&mstack);

            asserteq(mstack.size, 0);
            */
        });

    });


});

snow_main();
