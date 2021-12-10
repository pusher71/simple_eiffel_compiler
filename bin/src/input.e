-- main.e
class MAIN
create make
feature
make
local
obj : A
do
obj := create {O}
obj.f
obj.f4
obj.f5
end
end
-- EOF

-- O.e
class O
  inherit
    I1
    rename
      f5 as f6
    redefine
      f6
    select
      f2,
      f6
    end
    N
    redefine
      f8
    end
    A
    rename
      f as f7
    end
  feature
    f6(fp : ANY) : N
    do
    end

    f8
    do
      io.put_string("O::f8()%N")
    end

    field : INTEGER
end
-- EOF

-- N.e
class N
  inherit
    M1
    M2
    select
      f3
    end
end
-- EOF

-- M1.e
class M1
  inherit
    I2
end
-- EOF

-- M2.e
class M2
  inherit
    I2
    rename
      f as f3
    redefine
      f3
    end
  feature
    f3
    do
      io.put_string("M2::f3()%N")
    end
    f8
    do
      io.put_string("M2::f8()%N")
    end
end
-- EOF

-- I1.e
class I1
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
      io.put_string("I1::f2()%N")
    end
end
-- EOF

-- I2.e
class I2
  inherit
    A
end
-- EOF

-- A.e
class A
  feature
    f
    do
      io.put_string("A::f()%N")
    end
    f4
    do
      io.put_string("A::f4()%N")
    end
    f5(obj : ANY) : N
    do
      io.put_string("A::f5()%N")
    end
end
-- EOF
