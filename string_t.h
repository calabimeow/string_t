#ifndef STRING_T_H
#define STRING_T_H

#ifndef STRING_MALLOC
    #define STRING_MALLOC(size) string_malloc(size)
#endif

#ifndef STRING_FREE
    #define STRING_FREE(ptr) string_free(ptr)
#endif

#ifndef STRING_SIZE_T
    #define STRING_SIZE_T unsigned long
#endif

typedef STRING_SIZE_T string_size_t;

typedef struct
{
    char *data;
    string_size_t size;
}string_t;

string_t string_new(const char *s);
string_t string_from(const char *s, string_size_t n);
string_t string_substr(string_t s, string_size_t start, string_size_t n);
string_t string_copy(string_t s);
void string_free(string_t *s);
int string_find(string_t s, string_t needle);
int string_cmp(string_t s1, string_t s2);
int string_eq(string_t s1, string_t s2);
string_t string_reverse(string_t s);
string_t string_concat(string_t s1, string_t s2);
char string_at(string_t s, string_size_t i);
char string_first(string_t s);
char string_last(string_t s);
string_t string_to_upper(string_t s);
string_t string_to_lower(string_t s);

#ifdef STRING_T_IMPLEMENTATION

string_t string_new(const char *s)
{
    string_size_t i = 0;

    if (!s)
    {
        string_t string;
        string.data = 0;
        string.size = 0;
        return string;
    }

    while (s[i] != '\0')
        i++;

    return string_from(s, i);
}

string_t string_from(const char *s, string_size_t n)
{
    string_t string;
    string_size_t i;

    if (!s || !n)
    {
        string.data = 0;
        string.size = 0;
        return string;
    }

    string.data = STRING_MALLOC(n + 1);

    if (!string.data)
    {
        string.size = 0;
        return string;
    }

    for (i = 0; i < n; i++)
        string.data[i] = s[i];

    string.data[i] = '\0';
    string.size = i;

    return string;
}

string_t string_substr(string_t s, string_size_t start, string_size_t n)
{
    string_t string;

    if (!s.data || start > s.size)
    {
        string.data = 0;
        string.size = 0;
        return string;
    }

    if (n > s.size - start)
        n = s.size - start;

    return string_from(s.data + start, n);
}

string_t string_copy(string_t s)
{
    return string_from(s.data, s.size);
}

void string_free(string_t *s)
{
    if (!s)
        return;

    if (s->data)
        STRING_FREE(s->data);

    s->data = 0;
    s->size = 0;
}

int string_find(string_t s, string_t needle)
{
    string_size_t i;
    string_size_t j;

    if (!s.data || !needle.data)
        return -1;

    if (needle.size == 0)
        return 0;

    if (needle.size > s.size)
        return -1;

    for (i = 0; i + needle.size <= s.size; i++)
    {
        for (j = 0; j < needle.size; j++)
        {
            if (s.data[i + j] != needle.data[j])
                break;
        }

        if (j == needle.size)
            return i;
    }

    return -1;
}

int string_cmp(string_t a, string_t b)
{
    string_size_t i;
    string_size_t n = a.size < b.size ? a.size : b.size;

    if (!a.data && !b.data)
        return 0;

    if (!a.data)
        return -1;

    if (!b.data)
        return  1;

    for (i = 0; i < n; i++)
    {
        unsigned char ca = a.data[i];
        unsigned char cb = b.data[i];

        if (ca != cb)
            return ca - cb;
    }

    if (a.size < b.size)
        return -1;

    if (a.size > b.size)
        return  1;

    return 0;
}

int string_eq(string_t s1, string_t s2)
{
    return string_cmp(s1, s2) == 0;
}

string_t string_reverse(string_t s)
{
    string_t string;
    string_size_t i;

    if (!s.data)
    {
        string.data = 0;
        string.size = 0;
        return string;
    }

    string = string_copy(s);

    for (i = 0; i < s.size; i++)
        string.data[i] = s.data[s.size - 1 - i];

    string.data[s.size] = '\0';
    return string;
}

string_t string_concat(string_t s1, string_t s2)
{
    string_t string;
    string_size_t i;
    string_size_t j;

    if (!s1.data)
        return string_copy(s2);

    if (!s2.data)
        return string_copy(s1);

    string.data = STRING_MALLOC(s1.size + s2.size + 1);

    if (!string.data)
    {
        string.size = 0;
        return string;
    }

    string.size = s1.size + s2.size;

    for (i = 0; i < s1.size; i++)
        string.data[i] = s1.data[i];

    for (j = 0; j < s2.size; j++)
        string.data[i + j] = s2.data[j];

    string.data[i + j] = '\0';
    return string;
}

char string_at(string_t s, string_size_t i)
{
    if (i > s.size)
        return s.data[s.size - 1];

    return s.data[i];
}

char string_first(string_t s)
{
    return *s.data;
}

char string_last(string_t s)
{
    return s.data[s.size - 1];
}

string_t string_to_upper(string_t s)
{
    string_t string = string_copy(s);
    string_size_t i;

    for (i = 0; i < s.size; i++)
    {
        if (string.data[i] >= 'a' && string.data[i] <= 'z')
            string.data[i] -= 32;
    }

    return string;
}

string_t string_to_lower(string_t s)
{
    string_t string = string_copy(s);
    string_size_t i;

    for (i = 0; i < s.size; i++)
    {
        if (string.data[i] >= 'A' && string.data[i] <= 'Z')
            string.data[i] += 32;
    }

    return string;
}

#endif /* STRING_T_IMPLEMENTATION */
#endif /* STRING_T_H */
