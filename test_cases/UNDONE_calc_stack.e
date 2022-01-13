-- main.e
class
    MAIN

create
    make
feature
    make
    local
        calc_stack : ARRAY[CALC_ELEM]
    do
        create calc_stack.make_empty
        calc_stack.add_first(create {CALC_ELEM}.make_val(2))
    end

    eval_calc_stack(calc_stack : ARRAY[CALC_ELEM])
    do
    end
end
-- EOF

-- calc_elem.e
class
    CALC_ELEM

create
    make_val,
    make_op_sum,
    make_op_sub,
    make_op_mul,
    make_op_div,
    make_op_neg

feature
    type : CHARACTER
    val : INTEGER

    make_val(f_val : INTEGER)
    do
        type := 'n'
        val := f_val
    end

    make_op_sum
    do
        type := '+'
    end

    make_op_sub
    do
        type := '-'
    end

    make_op_mul
    do
        type := '*'
    end

    make_op_div
    do
        type := '/'
    end

    make_op_neg
    do
        type := '~'
    end
end
-- EOF
