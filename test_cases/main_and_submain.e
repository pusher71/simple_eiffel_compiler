-- main.e
class
    MAIN

create
    make
feature
    make
    local
        sm : SUB_MAIN
    do
        create sm.make
    end
end
-- EOF

-- sub_main.e
class
    SUB_MAIN

inherit
    MAIN
    redefine
        make
    end

create
    make

feature
    make
    do
        io.put_string("SUB_MAIN::make()%N")
    end

end
-- EOF
