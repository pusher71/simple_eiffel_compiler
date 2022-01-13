-- main.e
class
    MAIN

create
    make
feature
    make
    local
        v0, v1, v2, v3, v4 : EXPRESSION
        o0, o1, o2, o3, o4 : EXPRESSION
        val : INTEGER
    do
        v0 := create {NUMBER}.make(3)
        v1 := create {NUMBER}.make(0)
        v2 := create {NUMBER}.make(22)
        v3 := create {NUMBER}.make(17)
        v4 := create {NUMBER}.make(5)

        o0 := create {NEG_OPERATOR}.make(v4)
        o1 := create {DIV_OPERATOR}.make(v3, o0)
        o2 := create {SUB_OPERATOR}.make(v0, v1)
        o3 := create {MUL_OPERATOR}.make(v2, o1)
        o4 := create {SUM_OPERATOR}.make(o2, o3)

        val := o4.eval

        io.put_integer(val)
    end
end
-- EOF

-- expression.e
class
    EXPRESSION

feature
    eval : INTEGER
    do
        io.put_string("<BASE EXPRESSION>%N");
        Result := 0
    end
end
-- EOF

-- number.e
class
    NUMBER

inherit
    EXPRESSION
    redefine
        eval
    end

create
    make

feature
    m_val : INTEGER

    make(val : INTEGER)
    do
        m_val := val
    end

    eval : INTEGER
    do
        Result := m_val
    end
end
-- EOF

-- bin_operator.e
class
    BIN_OPERATOR

inherit
    EXPRESSION

create
    make

feature
    m_left, m_right : EXPRESSION

    make(left, right : EXPRESSION)
    do
        m_left := left
        m_right := right
    end
end
-- EOF

-- un_operator.e
class
    UN_OPERATOR

inherit
    EXPRESSION

create
    make

feature
    m_operand : EXPRESSION

    make(operand : EXPRESSION)
    do
        m_operand := operand
    end
end
-- EOF

-- sum_operator.e
class
    SUM_OPERATOR

inherit
    BIN_OPERATOR
    redefine
        eval
    end

create
    make

feature
    eval : INTEGER
    do
        Result := (m_left.eval + m_right.eval)
    end
end
-- EOF

-- sub_operator.e
class
    SUB_OPERATOR

inherit
    BIN_OPERATOR
    redefine
        eval
    end

create
    make

feature
    eval : INTEGER
    do
        Result := (m_left.eval - m_right.eval)
    end
end
-- EOF

-- mul_operator.e
class
    MUL_OPERATOR

inherit
    BIN_OPERATOR
    redefine
        eval
    end

create
    make

feature
    eval : INTEGER
    do
        Result := (m_left.eval * m_right.eval)
    end
end
-- EOF

-- div_operator.e
class
    DIV_OPERATOR

inherit
    BIN_OPERATOR
    redefine
        eval
    end

create
    make

feature
    eval : INTEGER
    do
        Result := (m_left.eval // m_right.eval)
    end
end
-- EOF

-- neg_operator.e
class
    NEG_OPERATOR

inherit
    UN_OPERATOR
    redefine
        eval
    end

create
    make

feature
    eval : INTEGER
    do
        Result := -m_operand.eval
    end
end
-- EOF
