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

class
    A

feature
    f
    local
        arr : ARRAY[INTEGER]
    do
        arr := create {ARRAY[INTEGER]}
    end

end

class
    B

inherit
    A
    rename
        f as f2
    redefine
        f2
    select
        f2
    end
    A

feature
    f2
    do
    end

end
