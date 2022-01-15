-- main.e
class
    MAIN

create
    make

feature
    make
    do
        -- SPECIAL CASES
        io.put_boolean(False and f)
        io.new_line
        io.put_boolean(True and f)
        io.new_line
        io.put_boolean(True or f)
        io.new_line
        io.put_boolean(False or f)
        io.new_line
        io.new_line

        -- NORMAL CASES
        io.put_boolean(f and f)
        io.new_line
        io.put_boolean(not f or f)
        io.new_line
        io.put_boolean(False or True)
        io.new_line
        io.put_boolean(not True or not False)
        io.new_line
        io.new_line

        -- XOR CASES
        io.put_boolean(f xor f)
        io.new_line
        io.put_boolean(not f xor f)
        io.new_line
        io.put_boolean(False xor True)
        io.new_line
        io.put_boolean(not True xor not False)
        io.new_line
    end

    f : BOOLEAN
    do
        io.put_string("MAIN::F%N")
    end
end
-- EOF
