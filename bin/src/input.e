-- main.e
class
    MAIN
create
    make

feature
    make
    local
        othe : ARRAY[ARRAY[B]]
        othe_2 : OTHER
    do
        io.put_string("Example%N")

        a := create{A};

        a.func(create {OTHER})
    end

    to_instruction(o : OTHER)
    do
    end
end
-- EOF

-- a.e
class
    A

inherit
    B
    redefine
        func
    end

feature
    func(a_var : OTHER)
    do
        io.put_string("A::func(a : OTHER);%N");
        io.put_integer(a.val);
        io.put_integer(a.var);
        io.put_character('%N');
    end

end
-- EOF

-- b.e
class
    B

feature
    func(o : OTHER_2)
    do
        io.put_string("B::func(o : ANY);%N");
    end

end
-- EOF

-- other.e
class
    OTHER

inherit
    OTHER_2
    rename
        var as val
    redefine
        val
    end

feature
    var : INTEGER

    val : INTEGER
    do
        io.put_string("OTHER::var()%N");
    end

end
-- EOF

-- other_2.e
class
    OTHER_2

feature
    var : INteGeR
    do
        io.put_string("OTHER_2::var()%N");
    end

end
-- EOF

-- wow.e
class
    WOW

feature
    wow(wow_0, wow_1 : ARRAY[WOW2]; wow_2, wow_3, wow_4 : INTEGER) : WOW
    local
        wow_0 : INTEGER
        wow_1, wow_2 : CHARACTER
    do
    end

end
-- EOF
