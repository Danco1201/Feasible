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

Solidity is still under development. Contributions are always welcome!

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
A := false
RULE TestRule NOT A ? C := true : C:=false
```
#### Functions
```
fn DoSomething(A) do
   A AND false
end

A := false
X := DoSomething A
PRINT X
