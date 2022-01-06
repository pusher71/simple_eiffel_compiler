-- main.e
class
    MAIN

create
    make
feature
    a1 : INTEGER
    a2 : NATURAL
    a3 : STRING
    a4 : CHARACTER
    a5 : BOOLEAN
    a6 : ARRAY[ARRAY[BOOLEAN]]
    a7 : ANY

    make
    do
        -- a6 := create {ARRAY[INTEGER]}.make_filled(2, -2, 2)
        create a6.make_filled(create {ARRAY[BOOLEAN]}.make_filled(False, 2, 4), 2, 4)
        a6.set(create {ARRAY[BOOLEAN]}.make_filled(False, 2, 4), 2)
        a6.set(create {ARRAY[BOOLEAN]}.make_filled(True, 2, 5), 3)
        a6.set(create {ARRAY[BOOLEAN]}.make_filled(False, 2, 7), 4)
        (a6 @ 2).set(True, 2)

        if (True)
        then
            io.put_string("BRANCH TRUE START%N")
            io.put_string("TRUE%N")
            io.put_string("BRANCH TRUE FINISH%N")
        else
        end

        if (True)
        then
        else
            io.put_string("BRANCH FALSE START%N")
            io.put_string("FALSE%N")
            io.put_string("BRANCH FALSE FINISH%N")
        end

        if (True)
        then
        else
        end


        if (True)
        then
        end

        if (True)
        then
            io.put_string("BRANCH TRUE START%N")
            io.put_string("TRUE%N")
            io.put_string("BRANCH TRUE FINISH%N")
        end

        a5 := True

        if (a5)
        then
            io.put_string("BRANCH TRUE START%N")
            io.put_string("TRUE%N")
            io.put_string("BRANCH TRUE FINISH%N")
        else
            io.put_string("BRANCH FALSE START%N")
            io.put_string("FALSE%N")
            io.put_string("BRANCH FALSE FINISH%N")
        end

        from
            a5 := False
        until
            False
        loop
            io.put_string("LOOP START%N")
            io.put_string("INCREMENT%N")
            io.put_string("LOOP FINISH%N")

            a5 := True
        end
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

