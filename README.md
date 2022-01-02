# rcfunge with ffi
 Implemented a fingerprint to call C library functions (CFFI). More esolangs need to have FFIs IMO. Or at least be able to link with wrappers.

 This implementation depends on libffi, install it using your distro's package manager.

### Instructions for CFFI
CFFI uses an extra pointer stack to push pointers to due to many architectures requiring 64-bit pointers while the funge stack is only 32 bits.

(f) - funge stack  
(p) - pointer stack


B - pop(f) index, pop(p) C char * pointer then push(f) the char at that location.

C -
pop(f) return type (0 for integer, 1 for pointer, 2 for void)  
pop(f) len  
pop(f) argument type bitmask (LSB to MSB, 0 for integer, 1 for pointer).    
pop len arguments from the appropriate stack.   
pop(p) C function pointer.  
call the C function with the arguments.  
Push the return value to the appropriate stack.  

D - duplicate pointer on pointer stack.   
F - pop(p) C pointer and free it.   
G - pop(p) then push(f) its 2 words. (32 bit architectures will push 0 then the pointer)  
I - pop(p).   
L - pop(p) as char * then load a dynamic library with that filename and push(p) its pointer, reflect on error. (dlopen)  
M - pop(f) len then create an array and then push(p) its C pointer. (malloc)  
O - Display the contents of the pointer stack (without popping)  
P - pop(f) twice then push(p) a pointer generated from the two words. (32 bit architectures should push 0 first)  
S - pop(f) a null terminated string and create a C String out of it then push(p) its pointer. (like M but different)  
T - pop(p) char * , then pop(p) dynamic library pointer, then push(p) a symbol from the library, reflect on error. (dlsym)  
U - pop(p) dynamic library pointer and close it, reflect on error. (dlclose)  
W - pop(f) index, then pop(p) C array pointer then push(f) the word in the array at that index.   
Y - swap two pointers on pointer stack.  
