-- main.e
class
    MAIN

create
    make

feature
    x, y, s : INTEGER
    r: BOOLEAN

    make
    local
        what0, what1, what2, what3 : INTEGER
    do
        x := 5 * 20 - 35 // 3;
        y := -2 * -x;;;
        s := -(((x) + (y))) * ((((2))));
        r := x < y and y * s <= x

        what0 := - -3
        what1 := (2 + - (- ((- -3))) * 3)
        what2 := - -24 // - - (- -3) * 5
        what3 := - -3 - - - 4

        io.put_integer(x)
        io.new_line
        io.put_integer(y)
        io.new_line;;
        io.put_integer(s)
        io.new_line
        io.put_boolean(r)
        io.new_line;

        io.put_integer(what0)
        io.new_line
        io.put_integer(what1)
        io.new_line;;
        io.put_integer(what2)
        io.new_line
        io.put_integer(what3)
        io.new_line;
    end
end
-- EOF
