-- main.e
class
    MAIN

create
    make

feature
    make
    do
        obj := create {O}
        obj.f
        obj.f4
        obj.f5
    end
end
-- EOF

-- a.e
class
    A

inherit
    I1
    rename
        f as f2
    end
    I2
    rename
        f as f3
    end
    B
    rename
        f as f4
    select
        f4
    end

feature
    f
    do
    end

end
-- EOF

-- i1.e
class
    I1

inherit
    B

end
-- EOF

-- i2.e
class
    I2

inherit
    B

end
-- EOF

-- b.e
class
    B

feature
    f : NATURAL

end
-- EOF
