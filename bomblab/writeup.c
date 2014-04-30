// ebx == counter
// inner loop

   0x0000000000400f2e <+75>:    movslq %ebx,%rdx
   0x0000000000400f31 <+78>:    mov    0x0(%rbp,%r12,4),%eax
   0x0000000000400f36 <+83>:    cmp    0x30(%rsp,%rdx,4),%eax
   0x0000000000400f3a <+87>:    jne    0x400f41 <phase_6+94>
   0x0000000000400f3c <+89>:    callq  0x40145d <explode_bomb>
   0x0000000000400f41 <+94>:    add    $0x1,%ebx
   0x0000000000400f44 <+97>:    cmp    $0x5,%ebx
   0x0000000000400f47 <+100>:   jle    0x400f2e <phase_6+75>
// pseudo code :

x = 0
while x <= 5
    [some comparison]    

// outer loop
   => 0x0000000000400f09 <+38>: mov    %r13,%r12
      0x0000000000400f0c <+41>: mov    (%r14,%r13,4),%eax
      0x0000000000400f10 <+45>: sub    $0x1,%eax
      0x0000000000400f13 <+48>: cmp    $0x5,%eax
      0x0000000000400f16 <+51>: jbe    0x400f1d <phase_6+58>
      0x0000000000400f18 <+53>: callq  0x40145d <explode_bomb>
      0x0000000000400f1d <+58>: lea    0x1(%r13),%ebx
      0x0000000000400f21 <+62>: cmp    $0x5,%r13
      0x0000000000400f25 <+66>: je     0x400fd5 <phase_6+242>
      0x0000000000400f2b <+72>: mov    %r15,%rbp

          0x0000000000400f2e <+75>: movslq %ebx,%rdx
          0x0000000000400f31 <+78>: mov    0x0(%rbp,%r12,4),%eax
          0x0000000000400f36 <+83>: cmp    0x30(%rsp,%rdx,4),%eax
          0x0000000000400f3a <+87>: jne    0x400f41 <phase_6+94>
          0x0000000000400f3c <+89>: callq  0x40145d <explode_bomb>
          0x0000000000400f41 <+94>: add    $0x1,%ebx
          0x0000000000400f44 <+97>: cmp    $0x5,%ebx
          0x0000000000400f47 <+100>:jle    0x400f2e <phase_6+75>

      0x0000000000400f49 <+102>:    add    $0x1,%r13
      0x0000000000400f4d <+106>:    jmp    0x400f09 <phase_6+38>

// pseudo code



