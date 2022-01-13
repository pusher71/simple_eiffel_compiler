-- main.e
class
    MAIN

create
    make

feature
    make
    local
        nums : ARRAY[INTEGER]
        chr : CHARACTER
    do
        chr := 'A'
        io.put_boolean(chr < 65)
    end

    bubble_sort(nums : ARRAY[INTEGER])
    local
        i, j : INTEGER
    do
        from
            i := nums.lower + 1
        until
            i > nums.upper
        loop
            from
                j := nums.lower
            until
                j > nums.upper - (i - nums.lower)
            loop

                if (nums @ j > nums @ (j+1))
                then
                    swap_elems_in_nums(nums, j, j+1)
                end

                j := j + 1
            end

            i := i + 1
        end
    end

    print_nums(nums : ARRAY[INTEGER])
    local
        i : INTEGER
    do
        from
            i := nums.lower
        until
            i > nums.upper
        loop
            io.put_integer(nums @ i)
            io.put_string(" ")

            i := i + 1
        end

        io.new_line
    end

    swap_elems_in_nums(nums : ARRAY[INTEGER]; index_1, index_2 : INTEGER)
    local
        buffer : INTEGER
    do
        buffer := nums @ index_1
        nums.set(nums @ index_2, index_1)
        nums.set(buffer, index_2)
    end
end
-- EOF
