-- main.e
class
    MAIN

create
    make

feature
    x, y, s : INTEGER
    r: BOOLEAN

    make
    do
        x := 5 * 20 - 35 // 3
        y := -2 * -x
        s := -(((x) + (y))) * ((((2))))
        r := x < y and y * s <= x

        io.put_integer(x)
        io.new_line
        io.put_integer(y)
        io.new_line
        io.put_integer(s)
        io.new_line
        io.put_boolean(r)
        io.new_line
    end
end
-- EOF
