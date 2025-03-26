#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX 100
#define MAX2 10
#define MAXF 100

typedef struct {
    char name[20];
    bool value;
} Variable;

typedef struct {
    char name[20];
    bool value;
    bool is_set;
} Fact;

typedef struct {
    char name[20];
    char params[20][20];  
    int param_count;
    char body[100];
} Function;

typedef struct {
    char name[20];
    char condition[50];
    char consequence[50];
    char elseblock[50];
} Rule;

Variable variables[MAX];
Fact facts[MAX];
Function functions[MAX2];
Rule rules[MAX2];

int var_count = 0;
int fact_count = 0;
int func_count = 0;
int rule_count = 0;

bool implies(bool a, bool b) {
    return !a || b;
}

bool evaluate(char *expr) {
    if (strcmp(expr, "true") == 0) return true;
    if (strcmp(expr, "false") == 0) return false;
    
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, expr) == 0) {
            return variables[i].value;
        }
    }
    for (int i = 0; i < fact_count; i++) {
        if (strcmp(facts[i].name, expr) == 0) {
            return facts[i].value;
        }
    }
    
    return false; 

void set_variable(const char *name, bool value) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            variables[i].value = value;
            return;
        }
    }
    strcpy(variables[var_count].name, name);
    variables[var_count].value = value;
    var_count++;
}

void set_fact(const char *name, bool value) {
    for (int i = 0; i < fact_count; i++) {
        if (strcmp(facts[i].name, name) == 0) {
            facts[i].value = value;
            return;
        }
    }
    strcpy(facts[fact_count].name, name);
    facts[fact_count].value = value;
    facts[fact_count].is_set = true;
    fact_count++;
}

void set_rule(const char *name, const char *condition, const char *consequence, const char *elseblock) {
    strcpy(rules[rule_count].name, name);
    strcpy(rules[rule_count].condition, condition);
    strcpy(rules[rule_count].consequence, consequence);
    strcpy(rules[rule_count].elseblock, elseblock);
    rule_count++;
}

void set_function(const char *name, const char *params[], int param_count, const char *body) {
    strcpy(functions[func_count].name, name);
    functions[func_count].param_count = param_count;
    for (int i = 0; i < param_count; i++) {
        strcpy(functions[func_count].params[i], params[i]);
    }
    strcpy(functions[func_count].body, body);
    func_count++;
}

bool evaluate_rule(Rule rule) {
    bool condition_value = evaluate(rule.condition);
    if (condition_value) {
        set_fact(rule.name, evaluate(rule.consequence));
    } else {
        set_fact(rule.name, evaluate(rule.elseblock));
    }
    return facts[find_fact(rule.name)].value;
}

void execute_function(const Function *func) {
    bool result = evaluate(func->body);
    printf("%s %s\n", func->name, result ? "true" : "false");
}

int find_fact(const char *name) {
    for (int i = 0; i < fact_count; i++) {
        if (strcmp(facts[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void execute_line(char *line) {
    char var[20], fact1[20], expr[50], condition[50], consequence[50], elseblock[50];
    char params[10][20];
    int param_count;

    if (strncmp(line, "RULE", 4) == 0) {
        sscanf(line, "RULE %19s %49s ? %49s : %49s", var, condition, consequence, elseblock);
        set_rule(var, condition, consequence, elseblock);
    } else if (strncmp(line, "fn", 2) == 0) {
        char name[20];
        char body[100];
        sscanf(line, "fn %19s", name);
        set_function(name, params, param_count, body);
    } else if (strstr(line, ":=") != NULL) {
        sscanf(line, "%19s := %49[^\n]", var, expr);
        set_variable(var, evaluate(expr)); 
        
    } else if (strncmp(line, "PRINT", 5) == 0) {
        char print_expr[50];
        sscanf(line, "PRINT %49s", print_expr);
        printf("%s\n", evaluate(print_expr) ? "true" : "false");
    } else if (strncmp(line, "FACT %19s :=", 4) == 0) {
        sscanf(line, "FACT %19s := %49[^\n]", fact1, expr);
        set_fact(fact1, evaluate(expr));
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
