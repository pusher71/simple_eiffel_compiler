-- main.e
class
    MAIN

create
    make

feature
    so : SUPER_OBJECT

    make
    local
        l_so : SUPER_OBJECT
    do
        create so.make(create {STATE})
        current.self_print(current)

        l_so := create{OBJECT}.make(create {STATE_0})
        l_so.print

        so := create{OBJECT}.make(create {STATE_1})
        current.self_print(current)

        create l_so.make_
        l_so.print

        create so.make_0
        current.self_print(current)

        create l_so.make_1
        l_so.print
    end

    self_print(m : MAIN)
    do
        m.so.print
    end
end
-- EOF

-- object.e
class
    OBJECT

inherit
    SUPER_OBJECT
    redefine
        print
    end

create
    make

feature
    print
    do
        io.put_string("OBJECT::print | ")
        m_state.print
        io.new_line
    end

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
