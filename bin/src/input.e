-- main.e
class
    MAIN

create
    make

feature
    make
    do
        obj := void
        obj.f
        obj.f4
        obj.f5
    end
end
-- EOF

-- a.e
class
    A

feature
    f
    do
        io.put_string("A::f()%N")
    end

end
-- EOF

-- b.e
class
    B

inherit
    A

end
-- EOF
