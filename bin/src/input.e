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
    end

    print_two_integers
    do
        io.put_string("Values: ")
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
