-- main.e
class
    MAIN

create
    make
feature
    make
    do
        io.put_string("Input fibonacci elem number: ")
        io.read_integer

        fibonacci(0, 1, io.last_integer)
    end

    fibonacci(a, b : INTEGER; to_elem_index : INTEGER)
    do
        if (to_elem_index > 0)
        then
            io.put_integer(a)
            io.new_line

            fibonacci(b, a+b, to_elem_index-1)
        end
    end
end
-- EOF
