-- main.e
class
    MAIN

create
    make

feature
    make
    do
        print_two_integers(3, 4)
    end

    print_two_integers(a, b : INTEGER)
    do
        io.put_string("Values: ")
        io.put_integer(2)
        io.put_string(", ")
        io.put_integer(3)
        io.new_line
    end
end
-- EOF
