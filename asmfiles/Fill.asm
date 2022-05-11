(loop)
   @KBD
   D = M

   @BLACK
   D;JGT

   @WHITE
   D;JEQ


(BLACK)
   @SCREEN
   D = A
   @addr
   M = D
   (BLOOP)
      @addr
      A = M
      M = -1

      @addr
      M = M + 1
      @24576
      D = A
      
      @addr
      D = D - M

      @BLOOP
      D;JGT
   @loop
   0;JMP

(WHITE)
   @SCREEN
   D = A
   @addr
   M = D

   (WLOOP)
      @addr
      A = M
      M = 0

      @addr
      M = M + 1
      @24576
      D = A
      
      @addr
      D = D - M

      @WLOOP
      D;JGT
   @loop
   0;JMP
