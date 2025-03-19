#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_VARS 100
#define MAX_FACTS 100
#define MAX_FILENAME_LENGTH 100

typedef struct {
    char name[20];
    bool value;
} Variable;

typedef struct {
    char name[20];
    bool value;
    bool is_set;
} Fact;

Variable variables[MAX_VARS];
Fact facts[MAX_FACTS];
int var_count = 0;
int fact_count = 0;

bool implies(bool a, bool b) {
    return !a || b;
}

bool xand(bool a, bool b) {
    return !(a && b) || (a && b);
}

bool nand(bool a, bool b) {
    return !(a && b);
}

bool nor(bool a, bool b) {
    return !(a || b);
}

bool xnor(bool a, bool b) {
    return a == b;
}

int findvar(const char *name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int findfact(const char *name) {
    for (int i = 0; i < fact_count; i++) {
        if (strcmp(facts[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

bool get_value(const char *expr) {
    if (strcmp(expr, "true") == 0) return true;
    if (strcmp(expr, "false") == 0) return false;
    
    int index = findvar(expr);
    if (index != -1) return variables[index].value;

    int fact_index = findfact(expr);
    if (fact_index != -1) return facts[fact_index].value;
    
    printf("ERROR: Undefined variable or fact %s\n", expr);
    return false;
}

void set_variable(const char *name, bool value) {
    int index = findvar(name);
    if (index != -1) {
        variables[index].value = value;
    } else {
        strcpy(variables[var_count].name, name);
        variables[var_count].value = value;
        var_count++;
    }
}

void set_fact(const char *name, bool value) {
    int index = findfact(name);
    if (index != -1) {
        if (facts[index].is_set) {
            printf("ERROR: Fact %s cannot be modified once set.\n", name);
        } else {
            facts[index].value = value;
            facts[index].is_set = true;
        }
    } else {
        strcpy(facts[fact_count].name, name);
        facts[fact_count].value = value;
        facts[fact_count].is_set = true;
        fact_count++;
    }
}

bool evaluate(char *expr) {
    char left[20], right[20];
    if (sscanf(expr, "%19s AND %19s", left, right) == 2) return get_value(left) && get_value(right);
    if (sscanf(expr, "%19s OR %19s", left, right) == 2) return get_value(left) || get_value(right);
    if (sscanf(expr, "NOT %19s", left) == 1) return !get_value(left);
    if (sscanf(expr, "%19s IMPLIES %19s", left, right) == 2) return implies(get_value(left), get_value(right));
    if (sscanf(expr, "%19s XOR %19s", left, right) == 2) return get_value(left) != get_value(right);
    if (sscanf(expr, "%19s XAND %19s", left, right) == 2) return xand(get_value(left), get_value(right));
    if (sscanf(expr, "%19s NAND %19s", left, right) == 2) return nand(get_value(left), get_value(right));
    if (sscanf(expr, "%19s NOR %19s", left, right) == 2) return nor(get_value(left), get_value(right));
    if (sscanf(expr, "%19s XNOR %19s", left, right) == 2) return xnor(get_value(left), get_value(right));
    return get_value(expr);
}

void execute_line(char *line) {
    char var[20], expr[50];
    if (strncmp(line, "FACT", 4) == 0) {
        sscanf(line, "FACT %19s := %49[^\n]", var, expr);
        set_fact(var, evaluate(expr));
    } else if (strstr(line, ":=") != NULL) {
        sscanf(line, "%19s := %49[^\n]", var, expr);
        set_variable(var, evaluate(expr));
    } else if (strncmp(line, "PRINT", 5) == 0) {
        printf("%s\n", evaluate(line + 6) ? "true" : "false");
    } else {
        printf("Syntax Error\n");
    }
}

void run_code(const char *code) {
    char buffer[100];
    FILE *stream = fmemopen((void *)code, strlen(code), "r");
    while (fgets(buffer, sizeof(buffer), stream)) {
        buffer[strcspn(buffer, "\n")] = 0;  
        execute_line(buffer);
    }
    fclose(stream);
}

void execute_from_file(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("ERROR: Could not open file %s\n", filename);
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), file)) {
        line[strcspn(line, "\n")] = 0;  
        execute_line(line);
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename.fsl>\n", argv[0]);
        return 1;
    }

    const char *filename = argv[1];
    if (strlen(filename) < 9 || strcmp(filename + strlen(filename) - 8, ".fsl") != 0) {
        printf("ERROR: File must have a .fsl extension\n");
        return 1;
    }

    execute_from_file(filename);
    return 0;
}
