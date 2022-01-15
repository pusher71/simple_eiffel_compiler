-- main.e
class
    MAIN

create
    make

feature
    make
    local
        nums : ARRAY[INTEGER]
        i : INTEGER
        elems_count : INTEGER
    do
        io.put_string("input integers count: ")
        io.read_integer

        create nums.make_filled(0, 1, io.last_integer)

        from
            i := nums.lower
        until
            i > nums.upper
        loop
            io.put_string("input natural value: ")
            io.read_integer

            nums.put(io.last_integer, i)

            i := i + 1
        end

        print_nums(nums)
        bubble_sort(nums)
        print_nums(nums)
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
        nums.put(nums @ index_2, index_1)
        nums.put(buffer, index_2)
    end
end
-- EOF
