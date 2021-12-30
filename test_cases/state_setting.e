-- main.e
class
    MAIN

create
    make

feature
    make
    local
        so : SUPER_OBJECT
    do
        create so.make(create {STATE})
        so.print

        create so.make(create {STATE_0})
        so.print

        create so.make(create {STATE_1})
        so.print

        create so.make_
        so.print

        create so.make_0
        so.print

        create so.make_1
        so.print
    end
end
-- EOF

-- object.e
class
    OBJECT

inherit
    SUPER_OBJECT

create
    make

end
-- EOF

-- super_object.e
class
    SUPER_OBJECT

create
    make, make_, make_0, make_1

feature
    m_state : STATE

    make(in_state : STATE)
    do
        m_state := in_state
    end

    make_
    do
        create m_state
    end

    make_0
    do
        m_state := create {STATE_0}
    end

    make_1
    do
        m_state := create {STATE_1}
    end

    print
    do
        io.put_string("SUPER_OBJECT::print | ")
        m_state.print
        io.new_line
    end

end
-- EOF

-- state.e
class
    STATE

inherit
    ANY
    rename
        io as io_state
    end
    ANY
    select
        io
    end

feature
    print
    do
        Current.io_state.put_string("STATE")
    end

end
-- EOF

-- state_0.e
class
    STATE_0

inherit
    STATE
    redefine
        print
    end

feature
    print
    do
        io_state.put_string("STATE_0")
    end

end
-- EOF

-- state_1.e
class
    STATE_1

inherit
    STATE
    redefine
        print
    end

feature
    print
    do
        io_state.put_string("STATE_1")
    end

end
-- EOF
