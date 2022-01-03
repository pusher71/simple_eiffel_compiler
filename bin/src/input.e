-- main.e
class
    MAIN

create
    make

feature
    obj : NATURAL

    make
    do
        obj := 0xFFFF_FFFF
        obj := -0x1

        io.put_integer(obj)
    end
end
-- EOF
