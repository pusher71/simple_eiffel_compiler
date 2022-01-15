-- main.e
class
    MAIN

create
    make

feature
    elem0, elem1 : O_A

    make
    local
        l_a : A
        x : INTEGER
    do
        elem0 := create {O_B}
        elem1 := create {O_D}

        create l_a.make(3, 4, 5)

        x := 3
        (l_a.map @ (x - 3 // 2) @ (45 \\ 4)).values.put(elem0.f, elem1.f)

        if ( (((l_a.map @ 2 @ 1).values @ 3 = 1 ) and (l_a.map @ 2 @ 1).values @ 2 = 0 and (l_a.map @ 2 @ 2).values @ 3 = 0) or print_logic)
        then
            io.put_string("WIN!")
        end
    end

    print_logic : BOOLEAN
    do
        io.put_string("LOGIC!")
    end
end
-- EOF

-- a.e
class
    A

create
    make

feature
    map : ARRAY[ARRAY[B]]

    make(rows, columns, depth : INTEGER)
    local
        i, j : INTEGER
        arr : ARRAY[B]
    do
        create map.make_filled(create {ARRAY[B]}.make_empty, 1, rows)

        from
            i := map.lower
        until
            i >= map.upper
        loop
            create arr.make_filled(create {B}.make(0), 1, columns)

            from
                j := arr.lower
            until
                j >= arr.upper
            loop
                arr.put(create {B}.make(depth), j)
                j := j + 1
            end

            map.put(arr, i)
            i := i + 1
        end
    end
end
-- EOF

-- b.e
class
    B

create
    make

feature
    values : ARRAY[INTEGER]

    make(val_count : INTEGER)
    local
        i : INTEGER
    do
        create values.make_filled(0, 1, val_count)

        from
            i := values.lower
        until
            i >= values.upper
        loop
            values.put(0, i)
            i := i + 1
        end
    end
end
-- EOF

-- o_a.e
class
    O_A

feature
    f : INTEGER
    do
        Result := 0
    end
end
-- EOF

-- o_b.e
class
    O_B

inherit
    O_A
    redefine
        f
    end

feature
    f : INTEGER
    do
        Result := 1
    end
end
-- EOF

-- o_c.e
class
    O_C

inherit
    O_A
    redefine
        f
    end

feature
    f : INTEGER
    do
        Result := 2
    end
end
-- EOF

-- o_d.e
class
    O_D

inherit
    O_B
    rename
        f as f_b
    redefine
        f_b
    select
        f_b
    end
    O_C
    rename
        f as f_c
    redefine
        f_c
    end

feature
    f_b : INTEGER
    do
        Result := 3
    end

    f_c : INTEGER
    do
        Result := 4
    end
end
-- EOF
