#include "stdlib.h"

struct buffer {
    char *data;
    int size;
};

/*@

fixpoint list<char> replicate(int n, char c)
    decreases n;
{
    return n <= 0 ? nil : cons(c, replicate(n - 1, c));
}

lemma void replicate_zero_nil(char c)
    requires true;
    ensures replicate(0, c) == nil;
{
}

@*/

/*@

predicate buffer(struct buffer *buf, int size, list<char> content) =
    malloc_block_buffer(buf) &*&
    buffer_data(buf, ?data) &*&
    buffer_size(buf, size) &*&
    malloc_block_chars(data, size) &*&
    chars(data, size, content);

@*/

void send(struct buffer *buf)
    //@ requires buffer(buf, ?size, ?content);
    //@ ensures buffer(buf, size, content);
{
    // No-op
}

void receive(struct buffer *buf)
    //@ requires buffer(buf, ?size, ?content);
    //@ ensures buffer(buf, size, content);
{
    // No-op
}

struct buffer *create_buffer(int size)
    //@ requires 0 <= size;
    //@ ensures buffer(result, size, replicate(size, 0));
{
    struct buffer *buf = malloc(sizeof(struct buffer));
    if (buf == 0) abort();
    buf->size = size;

    char *data = malloc((uintptr_t)size);
    if (data == 0) abort();
    //@ close malloc_block_chars(data, size);

    if (size == 0) {
        //@ replicate_zero_nil(0);
        //@ assert replicate(0, 0) == nil;
        //@ close chars(data, 0, nil);
    } else {
        //@ int i = 0;
        //@ invariant 0 <= i &*& i <= size &*& chars(data, i, replicate(i, 0)) &*& malloc_block_chars(data + i, size - i);
        for (int i = 0; i < size; i++)
            //@ invariant 0 <= i &*& i <= size &*& chars(data, i, replicate(i, 0)) &*& malloc_block_chars(data + i, size - i);
        {
            data[i] = 0;
            //@ open malloc_block_chars(data + i, size - i);
            //@ close chars(data + i, 1, cons(0, nil));
            //@ close chars(data, i + 1, append(replicate(i, 0), cons(0, nil)));
            //@ close malloc_block_chars(data + i + 1, size - i - 1);
        }
        //@ close chars(data, size, replicate(size, 0));
    }

    buf->data = data;
    //@ close buffer(buf, size, replicate(size, 0));
    return buf;
}

void destroy_buffer(struct buffer *buf)
    //@ requires buffer(buf, _, _);
    //@ ensures true;
{
    //@ open buffer(buf, _, _);
    //@ open chars(_, _, _);
    free(buf->data);
    free(buf);
}

int main()
    //@ requires true;
    //@ ensures true;
{
    struct buffer *buf = create_buffer(64);
    send(buf);
    receive(buf);
    destroy_buffer(buf);
    return 0;
}
