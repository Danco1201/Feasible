# Feasible - The Pure-Logical Programming Language
Feasible is a programming language purely oriented toward propositional logic.

This language is designed to simplify binary and logical operations, with a syntax suitable for both beginners and experts.

## Examples
### Hello World
Strings may not be printable, so there is no "Hello, World!", but here is a simple program written in Feasible:
```feasible
A := true
B := false
C := A IMPLIES B 
D := C NXOR A
FACT X := A OR D
PRINT D
PRINT X
```
### P implies Q
``` feasible
// First option
P := true
RULE PImpliesQ P ? Q := true : false
// Second option
P := true
Q := false
FACT PIMPQ := P IMPLIES Q
```
## Development

Feasible is still under development. Contributions are always welcome! If you want to contribute, please read [Contributing](#contributing)

## Instalation
### Requirements
* Feasible is written in C, so a compiler like the GNU Collection Compiler (GCC) is required.
* Compatible with operating systems like Linux, macOS, and Windows (with MinGW or Cygwin)
### Installation Steps
**Step 1: Clone the repository**:
```bash
git clone https://github.com/Danco1201/Feasible.git
cd Feasible
```
**Step 2: Compile the code**
```makefile
make
```
**Step 3: Create a file**:
*For example, test.fsl:*
```feasible
A := true
B :=  false IMPLIES NOT A
FACT X := A NXOR B
PRINT X
```
**Step 3: Run the CLI**
*On Linux and macOS:*
```cli
./feasible test.fsl
```
*On Windows:*
```cli
feasible.exe test.fsl
```

## Basic Syntax
### Assignment
In Feasible, variables are dynamic and are declared with the ":=" operator and the following syntax:
```feasible
<name> := <boolean>
```
An example would be:
```feasible
X := true
```
Here we declare a variable X with the value true.

It is conventional that variables are capitalized, although it is not mandatory.

### Logical Operators
Feasible supports many propositional logic operators, for example:
```feasible
A:=true
B:=false
C:=A and B // true and false
D:=C IMPLIES B // false implies false
E:=A XOR B //true xor false
F:=C NAND E //false nand true
G:= NOT F // not true
H:= G NXOR E // false nxor true
PRINT H
```
In this example, two variables called "A" and "B" are declared at the beginning with the values ​​true and false respectively. The rest of the operations experiment with these operations, maintaining in most cases the syntax `<var1> <binop> <var2>` with the exception of the NOT operator, which has the syntax `NOT <var>`.

### Facts
Constants (or, as we call them here, facts) are a type of immutable variable, meaning they cannot be modified under any circumstances; if so, they will throw an error. They are the equivalent of `const` in JavaScript.
They are declared with the following syntax:
```feasible
FACT <name> := <boolean>
```
Where "name" is the name of the fact and "boolean" is its value. Here's an example of how it works:
```feasible
FACT X := true
FACT X := false // this will throw an error
PRINT X
```
### Rules
**Rules** in Feasible are logical statements that establish relationships between Boolean elements. Simply put, a rule is a fact (or constant) that can store a Boolean condition (true or false). If condition X is met, consequence Y will occur; otherwise, consequence Z will occur. It is the equivalent of the ternary operator in C.
Syntax:

``` feasible
RULE <RuleName> <cond X> ? <consq Y> : <consq Z>
```

Example:
```feasible
A := true
B:= false
RULE TestRule A AND B ? C := true : C:=false
```
### Functions
Functions in Feasible are a type of code block that allows you to reuse and organize code more efficiently. They are defined with the following syntax:
``` feasible
fn <name> <[params]>
   <body>
```
Where name is the name of the function, params are the parameters (separated by a space), and body is the body.

Here's an example:
```
fn doSomething a b
a AND NOT b
```
To run this function, you can do it in three ways:
Print it simply:
PRINT doSomething true false
Variables:
A := true
B := false
FACT X := doSomething A B
PRINT X
and recreate it manually:
PRINT true and NOT false
### Future Features


#### User-defined Operators
```feasible
binop CUSTOM(A, B) do
   NOT A AND NOT A XOR B
end
FACT X := true CUSTOM false
PRINT X // prints "false"
```

### Compile to C
```bash
feasible.exe --compile my_program.fsl -o output.c
gcc output.c -o my_program
my_program.exe
```

## Contributing

Thank you for your interest in contributing to **Feasible**! If you're interested in helping develop the language, here are some steps to get started:

**How ​​to contribute?**

1. **Report an issue:** If you find a bug or have an idea for a new feature, open an issue in the repository. Be sure to provide as much detail as possible so we can replicate the problem or understand the improvement proposal.

**How ​​to open an issue**
* Go to the ***Issues*** tab in the repository.
* Click "New Issue".
* Use a template if available, or describe the issue or feature you want to propose.
2. **Submit a pull request:** : If you have changes you'd like to share with the project, you can create a pull request. Be sure to follow these steps:

**Steps for a Pull Request:**
* Fork the repository and clone your fork to your local machine.
* Create a new branch (with a descriptive name) for the changes you're going to make.
* Make your code changes.
* Add tests to ensure your changes don't break anything (if possible).
* Make sure your code complies with the project's style guidelines.
* Make a clear and descriptive commit of your changes.
* Push your changes to your fork and open a pull request in the original repository.

3. **Testing**: If you want to test the language locally before submitting your changes, follow the steps in [Installation Steps](#installation-steps).

4. **Code Sytle**: Please follow the following style rules when contributing:

**Conventions:**
* **Variable Names**: Use uppercase for variables and facts, camelCase for functions and DromedaryCase for rules.
* **Comments**: Only if you are adding a **new feature** or idea, document the code by explaining its function.
