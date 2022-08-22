# Build an executable using the following:
#
# clang barebones.s -o barebones  # clang is another compiler like gcc
#
.text
_barebones:

.data
	
.globl main

main:
				# (1) What are we setting up here?
				# Ans:
	pushq %rbp		# push the main function to the satck
	movq  %rsp, %rbp	# decrement stack pointer, store source at top of the stack

				# (2) What is going on here
				# Ans:
	movq $1, %rax		# system call of the write function 
	movq $1, %rdi		# write to stdout
	leaq .hello.str,%rsi	# set the string register address to be written as output


			# (3) What is syscall? We did not talk about this
			# in class.
			# Ans:
			# call OS to write
	syscall			# Which syscall is being run?
				# Ans: write(1, "Hello World!\n", 13), which will write "Hello World!\n" to the terminal

				# (4) What would another option be instead of 
				# using a syscall to achieve this?
				# Ans: call printf("Hello World!\n") instead

	movq	$60, %rax	# (5) We are again setting up another syscall
	movq	$0, %rdi	# What command is it?
				# Ans:	exit(0); It will exit the program
	syscall

	popq %rbp		# (Note we do not really need
			 	# this command here after the syscall)

.hello.str:
	.string "Hello World!\n"
	.size	.hello.str,13		# (6) Why is there a 13 here?
					# Ans: the size of the string "Hello World!\n" is 13.
