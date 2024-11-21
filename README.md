## PUSH_SWAP
Push swap is about creating a sorting algorithm for numbers stored in a Stack (stackA) with an auxiliar stack (stackB). A stack is a pile of numbers with a set of instructions (push, swap, rotate, and reverse rotate) to be able to modify it. It must be achived without exceeding some certain amount of instructions for doing it. 
 
If you want to see it in action you can run the following commands in your terminal:
```
make deps
make
export nums="5 6 3 2 8 10"; ./push_swap$numbers | ./graphics $numbers 
```

The frist two lines prepare the project and only have to be executed the first time. While the last one is the one that executes it and can be run with numbers diferent thant "5 6 3 2 8 10"

## STACK BASICS
A stack is a plie of numbers with a set of instructions to modifiy it. The instructions are:
- ### SWAP
  It changes the first to numbers of a given stack. So if a stack has the numbers 2 1 3 4 5 and we swap it it will become 1 2 3 4 5

- ### ROTATE and REVERSE_ROTATE
    Rotate sends the top number from the stack to it bottom. So the stack 1 2 3 4 5 wolud becom 2 3 4 5 1.
    Reverse_rotate does the oposit, sends the bottom number to the top. So the stack 1 2 3 4 5 would become 5 1 2 3 4.
- ### PUSH
    Push sends the top number of one stack to the top of another stack so if we push from a stackA="1 2 3 4" to a stackB="5 6 7 8" the result would be:
    stackA="2 3 4" stackB="1 5 6 7 8"

## PROJECT STRUCTURE
This project creates 3 executables push_swap checker graphics. All thre executables expect as parameters a set of numbers representing the intital state of the stackA. 
- ### pus_swap
    It is used to get a set of instructios that would sort a stack.
    Will print on the console thorugh the standard_output all the instructions needed to sort the numbers recived as parameters.
- ### checker 
    It is used tho check the result given by bush_swap.
    Will check if the instructions recived through the standar_input will sort the numbers recived as as parameters.
- ### graphics
    It is used to see how the stacks are modified by the instructions.
    Will show all the status of the stacks after executing each instruction recived throught the standard_input.

## INSTRUCTIONS NOMENCLATURE
- **ra:** Rotates stackA
- **rb:** Rotates stackB
- **rr:** Rotates stackA and stackB
- **rra:** Reverserotates stackA
- **rrb:** Reverserotates stackB
- **rrr:** Reverserotates stackA and stackB
- **sa:** Swaps stackA
- **sb:** Swaps stackB
- **ss:** Swaps stackA, and stackB
- **pa:** Pushes from stackB to stackA, if stackA is not empty
- **pb:** Pushes from stackA to stackB, if stackB is not empty  

\* The isntructions `rr, rrr, ss` only count as only one instruction instead the two. 