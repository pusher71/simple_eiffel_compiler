-- main.e
class MAIN
create make
feature
make
local
obj : A
do
obj := create {A}
obj.f
obj := create {B}
obj.f
obj := create {C}
obj.f
obj := create {D}
obj.f
obj := create {E}
obj.f
end
end
-- EOF

-- E.e
class E
  inherit
    D
    A
    rename
      f as f3
    redefine
      f3
    select
      f3
    end
  feature
    f3
    do
      io.put_string("E::f3()%N")
    end
end
-- EOF

-- D.e
class D
  inherit
    B
    select
      f2
    end
    C
end
-- EOF

-- C.e
class C
  inherit
    A
    redefine
      f
    end
  feature
    f
    do
      io.put_string("C::f()%N")
    end
end
-- EOF

-- B.e
class B
  inherit
    A
    rename
      f as f2
    redefine
      f2
    end
  feature
    f2
    do
      io.put_string("B::f2()%N")
    end
end
-- EOF

-- A.e
class A
  feature
    f
    do
      io.put_string("A::f()%N")
    end
end
-- EOF

