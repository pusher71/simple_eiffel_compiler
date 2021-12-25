-- main.e
class
    MAIN

create
    make

feature
    attr0 : INTEGER
    attr1 : STRING
    attr2 : OBJECT

    make
    do
    end

    feat(fp0, fp1 : STRING)
    local
        obj0 : OBJECT
        obj1 : OBJECT2
    do
        create obj0
        create obj1.make
        method0
    end

    method0
    do
    end

    method1
    do
    end

    method2
    do
    end

    method3
    do
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
