-- main.e
class
    MAIN

create
    make

feature
    make
    do
        io.put_string("Input value: ")
        io.read_integer()

        io.put_string("Input value: ")
        io.put_integer(io.last_integer)
        io.new_line
    end
end
-- EOF
