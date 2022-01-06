-- main.e
class
    MAIN

create
    make
feature
    make
    local
        objects : ARRAY[ARRAY[A]]
        int : INTEGER
    do
        -- create objects.make_filled(create {ARRAY[B]}.make_empty, 0, 2)
        objects := create {ARRAY[ARRAY[B]]}.make_filled(create {ARRAY[B]}.make_filled(create {B}.make, 0, 2), 0, 2)

        objects.set(create {ARRAY[B]}.make_filled(create {B}.make, 0, 11), 1)
        objects.set(create {ARRAY[C]}.make_filled(create {C}.make, 0, 11), 2)

        (objects @ 2 @ 0).F;
        -- io.put_integer(int.GET());
    end

    print_int(val : INTEGER; val2 : STRING)
    do
        io.put_integer(val)
        io.put_string(val2)
        io.new_line
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
    some_value : INTEGER

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

