-- main.e
class
    MAIN

create
    make

feature
    make
    local
        l_a : A
    do
        create l_a

        l_a.routine.change(l_a)
        io.put_integer(l_a.val)
    end
end
-- EOF

-- a.e
class
    A

feature
    val : INTEGER

    set(f_val : INTEGER)
    do
        val := f_val
    end

    routine : B
    do
        val := 2
        io.put_integer(val)
        io.new_line

        Result := create {B}
    end
end
-- EOF

-- b.e
class
    B

feature
    change(f_a : A)
    do
        f_a.set(f_a.val * 16)

        io.put_integer(f_a.val)
        io.new_line
    end
end
-- EOF
