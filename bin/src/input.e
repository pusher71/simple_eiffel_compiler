-- main.e
class
    MAIN

create
    make
feature
    make
    local
        obj : A
        l_nat : NATURAL
        ent : ENTITY
    do
        l_nat := 0xFFFF_FFFF
        io.put_integer(l_nat)

        obj := create {C}.make
        obj.f

        ent := create {ENTITY}
        ent.f1
        ent := create {SUB_ENTITY}
        ent.f1
    end
end
-- EOF

-- a.e
class
    A

create
    make

feature
    field : STRING

    make
    local
        field2 : STRING
    do
        -- io.put_string("A CREATING")
        -- F
        field := "A::INIT"
        field2 := "WHAT?!?"

        -- io.put_string("A::f%N")
    end

    F
    do
        io.put_string("A::F%N")
    end

end
-- EOF

-- b.e
class
    B

inherit
    A
    rename
        F as F2
    redefine
        F2
    end

create
    make

feature
    F2
    do
        precursor
        io.put_string("B::F2%N")
    end

end
-- EOF

-- c.e
class
    C

inherit
    B
    rename
        field as field2
    redefine
        make, F2
    end

create
    make

feature
    make
    do
        precursor
        -- io.put_string("B::f%N")
        -- io.put_string(field2)
    end

    F2
    do
        precursor{B}
        io.put_string("C::F2%N")
    end
end
-- EOF

-- entity.e
class
    ENTITY

feature
    f1
    do
        io.put_string("ENTITY::f1()%N")
        f2
    end

    f2
    do
        io.put_string("ENTITY::f2()%N")
    end
end
-- EOF

-- sub_entity.e
class
    SUB_ENTITY

inherit
    ENTITY
    redefine
        f2
    end

feature
    f2
    do
        io.put_string("SUB_ENTITY::f2()%N")
    end
end
-- EOF
