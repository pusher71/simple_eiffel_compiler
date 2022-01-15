-- main.e
class
    MAIN

create
    make

feature
    matrix : ARRAY[ARRAY[INTEGER]]

    make
    do
        -- Create matrix
        create matrix.make_filled(create {ARRAY[INTEGER]}.make_empty, 1, 7)
        matrix.put(create {ARRAY[INTEGER]}.make_filled(0, 1, 8), 1)
        matrix.put(create {ARRAY[INTEGER]}.make_filled(0, 1, 8), 2)
        matrix.put(create {ARRAY[INTEGER]}.make_filled(0, 1, 8), 3)
        matrix.put(create {ARRAY[INTEGER]}.make_filled(0, 1, 8), 4)
        matrix.put(create {ARRAY[INTEGER]}.make_filled(0, 1, 8), 5)
        matrix.put(create {ARRAY[INTEGER]}.make_filled(0, 1, 8), 6)
        matrix.put(create {ARRAY[INTEGER]}.make_filled(0, 1, 8), 7)

        -- Initialize matrix
        (matrix @ 4).put(1, 3)
        (matrix @ 4).put(1, 4);;
        (matrix @ 4).put(1, 5)
        (matrix @ 4).put(1, 6)
        (matrix @ 4).put(1, 7);;;;

        (matrix @ 7).put(1, 3)
        (matrix @ 7).put(1, 4);;
        (matrix @ 7).put(1, 5)
        (matrix @ 7).put(1, 6)
        (matrix @ 7).put(1, 7);;;;

        (matrix @ 4).put(1, 3)
        (matrix @ 5).put(1, 3);;
        (matrix @ 6).put(1, 3)
        (matrix @ 7).put(1, 3)

        (matrix @ 4).put(1, 7)
        (matrix @ 5).put(1, 7);;
        (matrix @ 6).put(1, 7)
        (matrix @ 7).put(1, 7)

        -- Print matrix
        print_matrix(matrix)

        -- Fill matrix beginning with given position
        fill_matrix(matrix, 2, 3)

        -- Print matrix
        io.new_line
        print_matrix(matrix)
    end

    print_matrix(f_matrix : ARRAY[ARRAY[INTEGER]])
    local
        i, j : INTEGER
    do
        from
            i := f_matrix.lower
        until
            i > f_matrix.upper
        loop
            from
                j := (f_matrix @ f_matrix.lower).lower
            until
                j > (f_matrix @ f_matrix.lower).upper
            loop
                io.put_integer(f_matrix @ i @ j);
                io.put_character(' ')

                j := j + 1;
            end

            io.new_line

            i := i + 1
        end
    end

    fill_matrix(f_matrix : ARRAY[ARRAY[INTEGER]]; row, column : INTEGER)
    do
        if (f_matrix.capacity /= 0 and (f_matrix @ f_matrix.lower).capacity /= 0 and f_matrix @ row @ column = 0)
        then
            (f_matrix @ row).put(1, column)

            if (row - 1 >= f_matrix.lower)
            then
                fill_matrix(f_matrix, row - 1, column)
            end

            if (row + 1 <= f_matrix.upper)
            then
                fill_matrix(f_matrix, row + 1, column)
            end

            if (column - 1 >= (f_matrix @ f_matrix.lower).lower)
            then
                fill_matrix(f_matrix, row, column - 1)
            end

            if (column + 1 <= (f_matrix @ f_matrix.lower).upper)
            then
                fill_matrix(f_matrix, row, column + 1)
            end
        end
    end
end
-- EOF
