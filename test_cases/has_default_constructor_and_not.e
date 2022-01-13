-- main.e
class
    MAIN

create
    make

feature
    make
    local
        obj : OBJECT2
    do

    end
end
-- EOF

-- object.e
class
    OBJECT

create
    make

feature
    val : ANY

    make
    do
        create val
    end
end
-- EOF

-- object2.e
class
    OBJECT2

inherit
    OBJECT
    redefine
        val
    end

create
    make

feature
    val : OBJECT
end
-- EOF
