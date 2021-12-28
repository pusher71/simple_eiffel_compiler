-- main.e
class
    MAIN

create
    make

feature
    si : SUPER_INVOKER

    make
    do
        io.put_string("HELLO")
        io.new_line

        si := create {INVOKER}
        si.print_object(create {SUPER_OBJECT})
    end
end
-- EOF

-- invoker.e
class
    INVOKER

inherit
    SUPER_INVOKER
    redefine
        print_object
    end

feature
    print_object(o : OBJECT)
    do
        io.put_string("INVOKER ||| ")
        o.print_self
        -- o.simple_print
    end
end
-- EOF

-- super_invoker.e
class
    SUPER_INVOKER

feature
    print_object(o : SUPER_OBJECT)
    do
        io.put_string("SUPER-INVOKER ||| ")
        o.print_self
    end
end
-- EOF

-- object.e
class
    OBJECT

inherit
    SUPER_OBJECT
    redefine
        print_self
    end

feature
    print_self
    do
        io.put_string("OBJECT::print_self%N")
    end

    simple_print
    do
        io.put_string("<<<< OBJECT || print_self >>>>%N")
    end

end
-- EOF

-- super_object.e
class
    SUPER_OBJECT

feature
    print_self
    do
        io.put_string("SUPER_OBJECT::print_self%N")
    end

end
-- EOF
