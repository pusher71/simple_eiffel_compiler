-- main.e
class
    MAIN

create
    make

feature
    make
    local
        objs : ARRAY[A]
        i : INTEGER
    do
        create objs.make_empty
        objs.add_last(create {A})
        objs.add_last(create {B})
        objs.add_last(create {C})
        objs.add_last(create {D})
        objs.add_last(create {E})

        from
            i := objs.lower
        until
            i > objs.upper
        loop
            (objs @ i).f
            io.new_line
            i := i + 1
        end
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

end
-- EOF

-- c.e
class
    C

inherit
    B
    redefine
        f
    end

feature
    f
    do
        Precursor
        io.put_string("C::f%N")
    end
end
-- EOF

-- d.e
class
    D

inherit
    C

end
-- EOF

-- e.e
class
    E

inherit
    D
    redefine
        f
    end

feature
    f
    do
        Precursor
        io.put_string("E::f%N")
    end
end
-- EOF
