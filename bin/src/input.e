-- main.e
class
    MAIN

create
    make

feature
    make
    local
        calc_stack : ARRAY[CALC_ELEM]
        calc_result : INTEGER
    do
        create calc_stack.make_empty
        calc_stack.add_last(create {CALC_ELEM}.make_val(2))
        calc_stack.add_last(create {CALC_ELEM}.make_val(3))
        calc_stack.add_last(create {CALC_ELEM}.make_op_sum)
        calc_stack.add_last(create {CALC_ELEM}.make_val(3))
        calc_stack.add_last(create {CALC_ELEM}.make_val(7))
        calc_stack.add_last(create {CALC_ELEM}.make_op_sub)
        calc_stack.add_last(create {CALC_ELEM}.make_op_mul)
        calc_stack.add_last(create {CALC_ELEM}.make_val(5))
        calc_stack.add_last(create {CALC_ELEM}.make_op_div)
        calc_stack.add_last(create {CALC_ELEM}.make_op_neg)

        calc_result := eval_calc_stack(calc_stack)
        io.put_integer(calc_result)
    end

    eval_calc_stack(calc_stack : ARRAY[CALC_ELEM]) : INTEGER
    local
        val_stack : ARRAY[INTEGER]
        cursor : INTEGER

        buffer0, buffer1, buffer2 : INTEGER
    do
        -- Evaluate calc stack
        create val_stack.make_empty

        from
            cursor := calc_stack.lower
        until
            cursor > calc_stack.upper
        loop
            if ((calc_stack @ cursor).type = 'n')
            then
                val_stack.add_last((calc_stack @ cursor).val)
            else
                if (val_stack.capacity >= (calc_stack @ cursor).operands_count)
                then
                    buffer1 := val_stack @ (val_stack.upper)
                    val_stack.remove_last

                    if ((calc_stack @ cursor).operands_count > 1)
                    then
                        buffer0 := val_stack @ (val_stack.upper)
                        val_stack.remove_last
                    end

                    if ((calc_stack @ cursor).type = '+')
                    then
                        val_stack.add_last(buffer0 + buffer1)
                    end

                    if ((calc_stack @ cursor).type = '-')
                    then
                        val_stack.add_last(buffer0 - buffer1)
                    end

                    if ((calc_stack @ cursor).type = '*')
                    then
                        val_stack.add_last(buffer0 * buffer1)
                    end

                    if ((calc_stack @ cursor).type = '/')
                    then
                        val_stack.add_last(buffer0 // buffer1)
                    end

                    if ((calc_stack @ cursor).type = '~')
                    then
                        val_stack.add_last(-buffer1)
                    end
                else
                    io.put_string("ERROR :: OPERATOR REQUIRES ")
                    io.put_integer((calc_stack @ cursor).operands_count)
                    io.put_string(" OPERANDS BUT HAS ONLY ")
                    io.put_integer(val_stack.capacity)
                    io.new_line
                end
            end


            cursor := cursor + 1
        end

        -- Check that value stack has only one number value
        if (val_stack.capacity /= 1)
        then
            io.put_string("ERROR :: NOT ONE VALUE IN VALUE STACK - count: ")
            io.put_integer(val_stack.capacity)
            io.new_line
        else
            Result := val_stack @ val_stack.upper
        end
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
    operands_count : INTEGER

    make_val(f_val : INTEGER)
    do
        type := 'n'
        val := f_val

        operands_count := -1
    end

    make_op_sum
    do
        type := '+'
        operands_count := 2
    end

    make_op_sub
    do
        type := '-'
        operands_count := 2
    end

    make_op_mul
    do
        type := '*'
        operands_count := 2
    end

    make_op_div
    do
        type := '/'
        operands_count := 2
    end

    make_op_neg
    do
        type := '~'
        operands_count := 1
    end
end
-- EOF
