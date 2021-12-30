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
    C

end
-- EOF

-- b.e
class
    B

inherit
    E
    D

end
-- EOF

-- c.e
class
    C

inherit
    F

end
-- EOF

-- d.e
class
    D

inherit
    F

end
-- EOF

-- e.e
class
    E

inherit
    G

end
-- EOF

-- f.e
class
    F

inherit
    B

end
-- EOF

-- g.e
class
    G

inherit
    A
    C

end
-- EOF
