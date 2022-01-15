-- main.e
class
    MAIN

create
    make

feature
    field : OBJECT

    make
    do
        field := create {OBJECT}.make
        (create {OBJECT}.make).make
    end
end
-- EOF

-- object.e
class
    OBJECT

create
    make

feature
    make
    do
        io.put_string("OBJECT::make%N")
    end
end
-- EOF
