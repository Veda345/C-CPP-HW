//
// Created by Vedana Voronina on 31.03.17.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

struct contact
{
    int id;
    char *name;
    char *phone;
};

struct dictionary
{
    struct contact *c;
    int size;
};

struct bank
{
    int *gap;
    int size;
};

FILE *file;
const char *file_name;
struct dictionary dict;
int next_id;
struct bank contact_bank;

void read_contacts();

char *read_word(FILE *in);

void rewrite_file();

bool check_char(int c)
{
    return (c != ' ') && (c != '\n') && (c != EOF);
}

bool is_empty(char *line)
{
    return strcmp(line, "") == 0;
}

bool is_phone_number(char *line)
{
    int pos = 0;
    while (line[pos] != '\0')
    {
        if (!(isdigit(line[pos]) || line[pos] == '-' || line[pos] == '(' || line[pos] == ')'))
        {
            return false;
        }
        pos++;
    }
    return true;
}

bool is_number_equals(char *num1, char *num2)
{
    int pos1 = 0, pos2 = 0;
    while (num1[pos1] != '\0' && num2[pos2] != '\0')
    {
        while (num1[pos1] != '\0' && !isdigit(num1[pos1]))
        {
            pos1++;
        }
        while (num2[pos2] != '\0' && !isdigit(num2[pos2]))
        {
            pos2++;
        }
        if (num1[pos1] != num2[pos2])
        {
            return false;
        }
        pos1++;
        pos2++;
    }
    while (num1[pos1] != '\0')
    {
        if (isdigit(num1[pos1]))
        {
            return false;
        }
        pos1++;
    }

    while (num2[pos2] != '\0')
    {
        if (isdigit(num2[pos2]))
        {
            return false;
        }
        pos2++;
    }
    return true;
}

bool is_name_equals(char *name1, char *name2)
{
    char *n1 = malloc(0 * sizeof(char)), *n2 = malloc(0 * sizeof(char));
    strcpy(n1, name1);
    strcpy(n2, name2);

    for (int j = 0; n1[j]; j++)
    {
        n1[j] = (char) tolower(n1[j]);
    }
    for (int i = 0; n2[i]; i++)
    {
        n2[i] = (char) tolower(n2[i]);
    }
    return strstr(n1, n2) != NULL;
}

bool check_input(char *line)
{
    if (is_empty(line))
    {
        printf("Wrong input format.\n");
        return false;
    }

    if (is_phone_number(line))
    {
        return true;
    } else
    {
        int pos = 0;
        while (line[pos] != '\0')
        {
            if (!isalpha(line[pos++]))
            {
                printf("Wrong input format.\n");
                return false;
            }
        }
        return true;
    }
    return false;
}

void find(char *line)
{
    if (!check_input(line))
    {
        return;
    }
    bool found = false;
    if (is_phone_number(line))
    {
        for (int i = 0; i < dict.size; i++)
        {
            if ((dict.c[i].id > 0) && is_number_equals(dict.c[i].phone, line))
            {
                found = true;
                printf("%d %s %s\n", dict.c[i].id, dict.c[i].name, dict.c[i].phone);
            }
        }
    } else
    {
        for (int i = 0; i < dict.size; i++)
        {
            if ((dict.c[i].id > 0) && is_name_equals(dict.c[i].name, line))
            {
                found = true;
                printf("%d %s %s\n", dict.c[i].id, dict.c[i].name, dict.c[i].phone);
            }
        }
    }
    if (!found)
    {
        printf("No contacts found.\n");
    }
    return;
}

void create(char *name, char *phone)
{
    if (!(check_input(name) || !check_input(phone)))
    {
        return;
    }
    if (contact_bank.size > 0)
    {
        contact_bank.size--;
        dict.c[contact_bank.gap[contact_bank.size]].id = next_id;
        dict.c[contact_bank.gap[contact_bank.size]].name = name;
        dict.c[contact_bank.gap[contact_bank.size]].phone = phone;
    } else
    {
        if (dict.size % 32 == 0)
        {
            dict.c = realloc(dict.c, (dict.size + 32) * sizeof(struct contact));
        }
        dict.c[dict.size].id = next_id;
        dict.c[dict.size].name = name;
        dict.c[dict.size].phone = phone;
        dict.size++;
        fprintf(file, "%d %s %s\n", next_id++, name, phone);
        return;
    }
}

void delete(int id)
{
    int match = -1;
    for (int i = 0; i < dict.size; i++)
    {
        if (dict.c[i].id == id)
        {
            match = i;
            break;
        }
    }
    if (match >= 0)
    {
        dict.c[match].id = 0;
        contact_bank.gap[contact_bank.size++] = match;
        if (contact_bank.size % 32 == 0)
        {
            contact_bank.gap = (int *) realloc(contact_bank.gap, (contact_bank.size + 32) * sizeof(int));
        }
        rewrite_file();
        return;
    }
}

void change(int id, char *param, char *line)
{
    if (!check_input(line))
    {
        return;
    }
    int match = -1;
    for (int i = 0; i < dict.size; i++)
    {
        if (dict.c[i].id == id)
        {
            match = i;
            break;
        }
    }
    if (match != -1)
    {
        if (strcmp(param, "name") == 0)
        {
            strcpy(dict.c[match].name, line);
            rewrite_file();
        } else if (strcmp(param, "number") == 0)
        {
            strcpy(dict.c[match].phone, line);
            rewrite_file();
        } else
        {
            printf("Wrong parameter format.\n");
        }
    }
    return;
}

int to_number(char *line)
{
    int num = 0, pos = 0;
    if (strcmp(line, "") == 0)
    {
        return 0;
    }
    char c = line[pos];
    while ((c != '\0') && check_char(c))
    {
        num *= 10;
        num += c - '0';
        c = line[++pos];
    }
    return num;
}

int main(int argc, char *argv[])
{
    file_name = argv[1];
    file = fopen(file_name, "a+");
    if (file == NULL)
    {
        perror("Can't open file.");
        return 0;
    }

    dict.size = 0;
    dict.c = malloc(0 * sizeof(struct contact));

    contact_bank.size = 0;
    contact_bank.gap = malloc(0 * sizeof(int));

    rewind(file);

    read_contacts();

    int max = 0;
    for (int i = 0; i < dict.size; i++)
    {
        max = dict.c[i].id > max ? dict.c[i].id : max;
    }
    next_id = max + 1;

    char *command;
    while (1)
    {
        command = read_word(stdin);
        if (strcmp(command, "find") == 0)
        {
            char *line = read_word(stdin);
            find(line);
            free(line);
        } else if (strcmp(command, "create") == 0)
        {
            char *name = read_word(stdin);
            char *phone = read_word(stdin);
            create(name, phone);
        } else if (strcmp(command, "delete") == 0)
        {
            int id;
            scanf("%d\n", &id);
            delete(id);
        } else if (strcmp(command, "change") == 0)
        {
            int id;
            scanf("%d ", &id);
            char *param = read_word(stdin);
            char *line = read_word(stdin);
            change(id, param, line);
            free(line);
        } else if (strcmp(command, "exit") == 0)
        {
            free(command);
            break;
        } else
        {
            printf("Unknown command.\n");
        }
        free(command);
        fflush(stdout);
    }
    free(dict.c);
    free(contact_bank.gap);
    fclose(file);
}

void read_contacts()
{
    char *id_string = read_word(file);
    int id = to_number(id_string);

    while (id > 0)
    {
        dict.size++;
        dict.c = realloc(dict.c, dict.size * sizeof(struct contact));
        dict.c[dict.size - 1].id = id;
        dict.c[dict.size - 1].name = read_word(file);
        dict.c[dict.size - 1].phone = read_word(file);

        id_string = read_word(file);
        id = to_number(id_string);
    }
}

char *read_word(FILE *in)
{
    char *word = malloc(16 * sizeof(char));
    int c = fgetc(in);
    int pos = 0;
    while (check_char(c))
    {
        word[pos] = (char) c;
        pos++;
        c = fgetc(in);
        if (pos % 16 == 0)
        {
            word = realloc(word, (pos + 16) * sizeof(char));
        }
    }
    word[pos] = '\0';
    return word;
}

void rewrite_file()
{
    freopen(file_name, "w", file);
    for (int i = 0; i < dict.size; i++)
    {
        if (dict.c[i].id > 0)
        {
            fprintf(file, "%d %s %s\n", dict.c[i].id, dict.c[i].name, dict.c[i].phone);
        }
    }
    freopen(file_name, "a+", file);
    return;
}
