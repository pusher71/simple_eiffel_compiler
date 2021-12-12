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
        f as f6
    end
    I2
    rename
        f as f5,
        f3 as f7
    redefine
        f7
    select
        f7
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
        io.put_string("Hello%N");
    end

    f7(fp0 : A; fp1 : A) : A
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
    redefine
        f3
    end

feature
    f3(fp0 : I1; fp1 : ANY) : A
    do
    end

end
-- EOF

-- b.e
class
    B

feature
    f : ANY
    f2 : B
    f3(fp0, fp1 : ANY) : ANY
    do
    end

end
-- EOF
