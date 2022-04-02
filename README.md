# Knowledge Based Intelligence System
Francisco Romero, William Daniel Hiromoto, Nolan Boner

Input Instructions:


 **general:**
 
 
 **!** == not
 
 
 **a** == and
 
 
 **o** == or
 
 
 **0-9** == variable names
  
  
 **,** == delineates penalties/desirability/quality and propositional logic
  
 
 **Notes and Examples:**
 
 
 **Penalty:** penalty value comes after the comma
 
 
 !2a3o!2,9 == not 2 and 3 or not 2, penalty 9
  
 
 **Possibilistic:** dont add a period infront of the desirability, simply adding a '9' is equivalent to saying .9 desirabily. same syntax as penalty
 
 
 !2a3o!2,9 == not 2 and 3 or not 2, desirability .9


 **Qualitative:** Have > be represented with a new line. Instead of <-, convert to cnf. The two digits after the comma refer to which function that portion belongs to, along with the desirability of that portion
 
 
 1a3a2,11 = 1 and 3 and 2, desirability of 1, belongs to first function


 !1a!3a2,12 = not 1 and not 3 and not 2, desirability of 2, belongs to first function
 
 
 previous two examples provide the syntax for: *1a3a2 > !1a!3a2 <-* 


 !2,33 = not 2, desirability of 3, belongs to third function
