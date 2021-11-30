class MAIN
inherit
    A
        select a, b, c, d
    end;
    B
        rename ID as ID, hello as what
    end;
    C
create ID, A
create D, A
feature
    a, b : INTEGER
feature
    c, d : CHARACTER
end

class BIG_CLASS
inherit
    A
        rename ID as ID, hello as what
        redefine a, b, c
    end;
    B
    C;
feature
    a_, b_ : ARRAY[INTEGER]
    local
        local_0, local_1 : INTEGER; local_2 : ARRAY[STRING]
    do
        if (true) then io.put_string("Hello, World%N"); end
    end

    c_, d_ : STRING
end

class BIG_CLASS
create D
create b
create F
end

class WHAT
inherit
    A
        select hello, a, b, c
    end
feature
    a__, b__ : ARRAY[ARRAY[ID]]
feature
    c__, d__ : ARRAY[ARRAY[ARRAY[STRING]]]
    local
        s_local_0 : CHARACTER s_local_2 : ARRAY[MAIN]
    do
        s_local_2 := create{ID}.make(3, 4);
    end

feature
    e__, f__ : STRING
    do
    end
end

class A_CLASS
inherit
    A;
    B;
    C;
end
