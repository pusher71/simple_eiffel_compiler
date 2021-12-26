-- main.e
class
    MAIN

create
    make

feature
    obj : OBJECT_PARENT

    make
    do
        obj := create {OBJECT}
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

inherit
    OBJECT_PARENT
    redefine
        f
    end

feature
    f
    do
        io.put_string("OBJECT::F")
        io.new_line
    end

end
-- EOF

-- object_parent.e
class
    OBJECT_PARENT

feature
    f
    do
        io.put_string("OBJECT_PARENT::F")
        io.new_line
    end

end
-- EOF
