-- main.e
class
    MAIN

create
    make

feature
    i : OBJECT
    si : SUPER_OBJECT

    what : ANY

    make
    do
        i := create {OBJECT}.make(create {SUPER_OBJECT});
        create i.make(create {SUPER_OBJECT})
        create i.make2
        i := create {OBJECT}.make2;

        what := create {OBJECT}.make(create {SUPER_OBJECT});

        (create {OBJECT}.make(create {SUPER_OBJECT})).make(create {SUPER_OBJECT});

        ((current.i).obj).io.put_integer(0xCAFE)
        ((current.i).obj).io.io.new_line;
        (current.i.obj).io.put_integer(0xBABE)
        (current.i.obj).io.new_line
        i.io.io.put_string("HELLO%N")
        create si

        io.put_string("================%N")
        io.put_string("----------------%N")
        return_obj.obj.f
        io.put_string("----------------%N")
        io.put_string("================%N")

        Current.print_obj(return_obj)
    end

    return_obj : OBJECT
    local
        myResult : OBJECT
        param : SUPER_OBJECT
    do
        Current.io.io.io.io.io.put_string("WHATHHATHL%N");
        create param
        create myResult.make(param)

        Result := myResult
        Current.io.io.io.io.io.put_string(" ??? WHATHHATHL ??? %N");

        result := create {SUPER_OBJECT}
    end

    print_obj(obj2 : OBJECT)
    do
        io.put_string(" == PRINT OBJECT INFO ================%N")
        obj2.obj.f
        io.put_string(" == END OF PRINTING   ================%N")
    end
end
-- EOF

-- object.e
class
    OBJECT

create
    make, make2

feature
    obj : SUPER_OBJECT

    make(in_obj : SUPER_OBJECT)
    do
        io.put_string("CREATING OBJECT%N")
        obj := in_obj
    end

    make2
    do
        io.put_string("CREATING OBJECT [2]%N")
        obj := create {SUPER_OBJECT}
    end

    f
    do
        io.put_string("routine OBJECT::f%N")
    end
end
-- EOF

-- super_object.e
class
    SUPER_OBJECT

feature
    f
    do
        io.put_string("<SUPER_OBJECT::f()>%N")
    end

end
-- EOF
