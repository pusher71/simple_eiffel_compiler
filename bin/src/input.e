class
    MAIN
inherit parent; file;
create
    make, a, b, c, d
create
    make, a, b, c, d
create
    make, a, b, c, d
feature
    make
    do
        ID := 3 - 4 + 5;
    end
feature
    make : NATURAL_16
    do
        io.put_string("[ Hello, }  ]")
        ID := 4 + "HELLO" + call('%N', What(3, 4, 5))
        d := a.b@c.d - a + 3
    end

    a : INTEGER_32
    b : INTEGER_32
    do
    end
feature
    make
    local
        a, b, d : INTEGER_32 hello : CHARACTER
    do
        ID := 4;

        io.put_string("[ Hello, }  ]")
        ID := 4 + "HELLO" + call('%N', What(3, 4, 5))
        (a.b@c).d = a.b@c.d - a + 3
        (2+3).hello(3, 4).ID.io.hello('W')@4
    end
end
