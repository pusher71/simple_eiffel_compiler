-- main.e
class
    MAIN

create
    make

feature
    stack : INT_STACK

    make
    do
        create stack.make
        stack.push(0)
        stack.push(1)
        stack.push(2)
        stack.push(3)

        from
        until
            stack.isEmpty
        loop
            io.put_integer(stack.pop)
            io.new_line
        end
    end
end
-- EOF

-- int_stack.e
class
    INT_STACK

create
    make

feature
    elems : ARRAY[INTEGER]

    make
    do
        create elems.make_empty
    end

    push(f_elem : INTEGER)
    do
        elems.add_last(f_elem)
    end

    pop : INTEGER
    do
        if (Current.elems.capacity > 0)
        then
            Result := elems @ elems.upper
            elems.remove_last
        else
            io.put_string("ERROR :: pop operation is performed on empty integer stack.")
        end
    end

    top : INTEGER
    do
        if (Current.elems.capacity > 0)
        then
            Result := elems @ elems.upper
            elems.remove_last
        else
            io.put_string("ERROR :: pop operation is performed on empty integer stack.")
        end
    end

    count : INTEGER
    do
        Result := elems.capacity
    end

    isEmpty : BOOLEAN
    do
        Result := (count = 0)
    end
end
-- EOF
