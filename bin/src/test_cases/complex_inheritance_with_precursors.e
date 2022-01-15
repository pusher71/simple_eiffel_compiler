-- main.e
class MAIN
create make
feature
make
local
objA : A1
objR : R1
objL : L1
objO : O1
objN : N
do
-- Check A objects ...
io.put_string(" == CHECK A ====================%N%N")
-- ... Assign A objects
io.put_string("... Assign A%N")
objA := create {A1}
objA.f
objA := create {A2}
objA.f
objA := create {A3}
objA.f
objA := create {A4}
objA.f
io.new_line
-- ... Assign R objects
io.put_string("... Assign R%N")
objA := create {R1}
objA.f
objA := create {R2}
objA.f
objA := create {R3}
objA.f
objA := create {R4}
objA.f
io.new_line
-- ... Assign L objects
io.put_string("... Assign L%N")
objA := create {L1}
objA.f
objA := create {L2}
objA.f
objA := create {L3}
objA.f
objA := create {L4}
objA.f
io.new_line
-- ... Assign O objects
io.put_string("... Assign O%N")
objA := create {O1}
objA.f
objA := create {O2}
objA.f
objA := create {O3}
objA.f
objA := create {O4}
objA.f
io.new_line
-- ... Assign N object
io.put_string("... Assign N%N")
objA := create {N}
objA.f
io.new_line
-- Check R objects
io.put_string(" == CHECK R ====================%N%N")
-- ... Assign R objects
io.put_string("... Assign R%N")
objR := create {R1}
objR.f2
objR := create {R2}
objR.f2
objR := create {R3}
objR.f2
objR := create {R4}
objR.f2
io.new_line
-- ... Assign O objects
io.put_string("... Assign O%N")
objR := create {O1}
objR.f2
objR := create {O2}
objR.f2
objR := create {O3}
objR.f2
objR := create {O4}
objR.f2
io.new_line
-- ... Assign N object
io.put_string("... Assign N%N")
objR := create {N}
objR.f2
io.new_line
-- Check L objects
io.put_string(" == CHECK L ====================%N%N")
-- ... Assign L objects
io.put_string("... Assign L%N")
objL := create {L1}
objL.f
objL := create {L2}
objL.f
objL := create {L3}
objL.f
objL := create {L4}
objL.f
io.new_line
-- ... Assign O objects
io.put_string("... Assign O%N")
objL := create {O1}
objL.f
objL := create {O2}
objL.f
objL := create {O3}
objL.f
objL := create {O4}
objL.f
io.new_line
-- ... Assign N object
io.put_string("... Assign N%N")
objL := create {N}
objL.f
io.new_line
-- Check O objects
io.put_string(" == CHECK O ====================%N%N")
-- ... Assign O objects
io.put_string("... Assign O%N")
objO := create {O1}
objO.f
objO.f2
objO.f3
objO.f4
objO.f5
objO := create {O2}
objO.f
objO.f2
objO.f3
objO.f4
objO.f5
objO := create {O3}
objO.f
objO.f2
objO.f3
objO.f4
objO.f5
objO := create {O4}
objO.f
objO.f2
objO.f3
objO.f4
objO.f5
io.new_line
-- ... Assign N object
io.put_string("... Assign N%N")
objO := create {N}
objO.f
objO.f2
objO.f3
objO.f4
objO.f5
io.new_line
-- Check N objects
io.put_string(" == CHECK N ====================%N%N")
-- ... Assign N object
io.put_string("... Assign N%N")
objN := create {N}
objN.f
objN.f2
objN.f3
objN.f4
objN.f_4
objN.f5
io.new_line
end
end
-- EOF

-- N.e
class N
  inherit
    O4
    redefine
      f_4
    end
  feature
    f_4
    do
      precursor
      io.put_string("N::f_4()%N")
    end
end
-- EOF

-- O4.e
class O4
  inherit
    A1
    rename
      f as f6
    redefine
      f6
    end
    O2
    O3
    select
      f_4
    end
  feature
    f6
    do
      io.put_string("O4::f6()%N")
    end
end
-- EOF

-- O3.e
class O3
  inherit
    O1
    rename
      f4 as f_4
    redefine
      f_4
    end
  feature
    f_4
    do
      precursor
      io.put_string("O3::f_4()%N")
    end
end
-- EOF

-- O2.e
class O2
  inherit
    O1
end
-- EOF

-- O1.e
class O1
  inherit
    A4
    rename
      f2 as f5
    end
    R4
    redefine
      f4
    select
      f4
    end
    L4
    rename
      f as f3
    end
  feature
    f4
    do
      precursor{A4}
      io.put_string("O1::f4()%N")
    end
end
-- EOF

-- L4.e
class L4
  inherit
    L2
    L3
end
-- EOF

-- L3.e
class L3
  inherit
    L1
end
-- EOF

-- L2.e
class L2
  inherit
    L1
end
-- EOF

-- L1.e
class L1
  inherit
    A2
end
-- EOF

-- R4.e
class R4
  inherit
    R2
    redefine
      f4
    select
      f4
    end
    R3
  feature
    f4
    do
      precursor{R3}
      io.put_string("R4::f4()%N")
    end
end
-- EOF

-- R3.e
class R3
  inherit
    R1
end
-- EOF

-- R2.e
class R2
  inherit
    R1
    rename
      f2 as f4
    end
end
-- EOF

-- R1.e
class R1
  inherit
    A3
    redefine
      f2
    end
  feature
    f2
    do
      precursor
      io.put_string("R1::f2()%N")
    end
end
-- EOF

-- A4.e
class A4
  inherit
    A2
    A3
    select
      f2
    end
end
-- EOF

-- A3.e
class A3
  inherit
    A1
    rename
      f as f2
    redefine
      f2
    end
  feature
    f2
    do
      precursor
      io.put_string("A3::f2()%N")
    end
end
-- EOF

-- A2.e
class A2
  inherit
    A1
    redefine
      f
    end
  feature
    f
    do
      precursor
      io.put_string("A2::f()%N")
    end
end
-- EOF

-- A1.e
class A1
  feature
    f
    do
      io.put_string("A1::f()%N")
    end
end
-- EOF

