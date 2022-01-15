-- main.e
class
    MAIN

create
    make

feature
    make
    local
        objA : A
        objB : B
        objC : C
        objD : D
        objE : E
    do
        -- A OBJECTS
        objA := create {A}
        objA.f
        objA := create {B}
        objA.f
        objA := create {C}
        objA.f
        objA := create {D}
        objA.f
        objA := create {E}
        objA.f

        io.new_line

        -- B OBJECTS
        objB := create {B}
        objB.f2
        objB := create {D}
        objB.f2
        objB := create {E}
        objB.f2

        io.new_line

        -- C OBJECTS
        objC := create {C}
        objC.f
        objC := create {D}
        objC.f
        objC := create {E}
        objC.f

        io.new_line

        -- D OBJECTS
        objD := create {D}
        objD.f
        objD.f2
        objD := create {E}
        objD.f
        objD.f2

        io.new_line

        -- E OBJECTS
        objE := create {E}
        objE.f
        objE.f2
        objE.f3

        io.new_line

    end
end
-- EOF

-- a.e
class
    A

feature
    f
    do
        io.put_string("A::f%N")
    end
end
-- EOF

-- b.e
class
    B

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
        precursor
        io.put_string("B::f2%N")
    end
end
-- EOF

-- c.e
class
    C

inherit
    A
    redefine
        f
    end

feature
    f
    do
        precursor
        io.put_string("C::f%N")
    end
end
-- EOF

-- d.e
class
    D

inherit
    B
    redefine
        f2
    select
        f2
    end
    C

feature
    f2
    do
        precursor{C}
        io.put_string("D::f2%N");
    end
end
-- EOF

-- e.e
class
    E

inherit
    A
    rename
        f as f3
    redefine
        f3
    select
        f3
    end
    D

feature
    f3
    do
        io.put_string("E::f3%N")
    end
end
-- EOF
