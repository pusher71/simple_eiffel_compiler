-- main.e
class
    MAIN

create
    make

feature
    i : OBJECT

    make
    do
        create i.make
        current.i.obj.io.put_integer(0xCAFEBABE)
        current.i.obj.f

        Current.print
    end

    print
    do
        Current.io.io.io.io.put_integer(0xFF)
    end
end
-- EOF

-- object.e
class
    OBJECT

create
    make

feature
    obj : SUPER_OBJECT

    make
    do
        create obj
    end

end
-- EOF

-- super_object.e
class
    SUPER_OBJECT

feature
    f
    do
        io.put_string("SUPER_OBJECT::f()%N")
    end

end
-- EOF
