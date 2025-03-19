# Feasible - The Pure-Logical Programming Language
Feasible is a programming language purely oriented toward propositional logic.

This language is designed to simplify binary and logical operations, with a syntax suitable for both beginners and experts.

## Examples
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

### Future Features

#### Rules
```feasible
A := true
B:= false
RULE TestRule A AND B ? C := true : C:=false
```
#### Functions
```
fn DoSomething(A) do
   A AND false
end

A := false
X := DoSomething A
PRINT X
```
#### User-defined Operators
```feasible
binop CUSTOM(A, B) do
   NOT A AND NOT A XOR B
end
FACT X := true CUSTOM false
PRINT X // prints "false"
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
* **Variable Names**: Use uppercase for variables and facts and CamelCase for functions (not yet implemented).
* **Comments**: Only if you are adding a **new feature** or idea, document the code by explaining its function.
