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
        (l_a.map @ (x - 3 // 2) @ (45 \\ 4)).values.set(elem0.f, elem1.f)

        if ((l_a.map @ 2 @ 1).values @ 3 = 1 or print_logic)
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
        create map.make_empty

        from
            i := map.lower
        until
            i >= map.lower + rows
        loop
            create arr.make_empty

            from
                j := arr.lower
            until
                j >= arr.lower + columns
            loop
                arr.add_last(create {B}.make(depth))
                j := j + 1
            end

            map.add_last(arr)
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
        create values.make_empty

        from
            i := values.lower
        until
            i >= values.lower + val_count
        loop
            values.add_last(0)
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
