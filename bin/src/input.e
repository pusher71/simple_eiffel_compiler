-- main.e
class
    MAIN

create
    make

feature
    make
    local
        obj : OBJECT
    do
        create obj

        obj.f
        print_two_integers
    end

    print_two_integers
    do
        io.put_string("Values: ")
        io.put_integer(2)
        io.put_string(", ")
        io.put_integer(3)
        io.new_line
    end
end
-- EOF

-- object.e
class
    OBJECT

feature
    f
    do
        io.put_string("OBJECT::F")
        io.new_line
    end

end
-- EOF
