-- main.e
class
    MAIN

create
    make
feature
    make
    do
        fibonacci(0, 1)
    end

    fibonacci(a, b : INTEGER)
    do
        if (a < 1_000_000)
        then
            io.put_integer(a)
            io.new_line

            fibonacci(b, a+b)
        end
    end
end
-- EOF
