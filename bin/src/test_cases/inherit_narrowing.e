-- main.e
class
    MAIN

create
    make

feature
    make
    local
        elems : ARRAY[A]
        i : INTEGER
    do
        create elems.make_filled(create {A}, 1, 3)
        elems.put(create {A}, 1)
        elems.put(create {B}, 2)
        elems.put(create {C}.make(100), 3)

        from
            i := elems.lower
        until
            i > elems.upper
        loop
            io.put_integer( (elems @ i).elem.val )
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
    elem : BASE_VALUE
    do
        Result := create {BASE_VALUE}.make(1 + 2 * 3)
    end
end
-- EOF

-- b.e
class
    B

inherit
    A
    redefine
        elem
    end

feature
    elem : MIDDLE_VALUE
    do
        Result := create {MIDDLE_VALUE}.make(14 // 3)
    end
end
-- EOF

-- c.e
class
    C

inherit
    B
    redefine
        elem
    end

create
    make

feature
    elem : CHILD_VALUE

    make(f_val : INTEGER)
    do
        elem := create {CHILD_VALUE}.make(f_val)
    end
end
-- EOF

-- base_value.e
class
    BASE_VALUE

create
    make

feature
    val : INTEGER

    make(f_val : INTEGER)
    do
        val := f_val
    end
end
-- EOF

-- middle_value.e
class
    MIDDLE_VALUE

inherit
    BASE_VALUE

create
    make
end
-- EOF

-- child_value.e
class
    CHILD_VALUE

inherit
    MIDDLE_VALUE

create
    make
end
-- EOF
