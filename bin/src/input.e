-- main.e
class
    MAIN

create
    make

feature
    make
    local
        obj_main : MAIN
    do
        create obj_main.make
    end
end
-- EOF

-- object.e
class
    OBJECT

feature
    f
    do
        io.put_string("A::f()%N")
    end

end
-- EOF

-- object2.e
class
    OBJECT2

create
    make

feature
    make
    do
        io.put_string("HELLO")
    end

end
-- EOF
