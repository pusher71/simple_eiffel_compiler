-- main.e
class
    MAIN

create
    make

feature
    make
    do
    end
end
-- EOF

-- a.e
class
    A

inherit
    B

end
-- EOF

-- b.e
class
    B

inherit
    C

end
-- EOF

-- c.e
class
    C

inherit
    A

end
-- EOF
