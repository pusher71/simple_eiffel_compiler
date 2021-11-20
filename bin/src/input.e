class
    MAIN
inherit parent
    rename
        a as b
    redefine
        a, b
    select
        a, b
    end

    file
    rename
        a as b
    select
        a, b
    end

create
    make, a, b, c, d
create
    make, a, b, c, d
create
    make, a, b, c, d
feature
    make
    do;;;
        ID := 3 - 4 + 5;
        precursor.ID
        var_1 := precursor{BOSS_CLASS}.ID(3, 4, 5);;;;
        var_2 := precursor{BOSS_CLASS}(3, 4, 5).ID(3, 4, 5);;;;
        ID := create {BIG_CLASS}.make(3, create{ARRAY}.make(3, 2));
    end
feature
    make : NATURAL_16
    do
        io.put_string("[ Hello, }  ]")
        ID := 4 + "HELLO" + call('%N', What(3, 4, 5))
        d := a.b@c.d - a + 3;

        ID := void

        a := -b + c;
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
