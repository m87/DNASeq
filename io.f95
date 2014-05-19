module io
    public::gen_chip


contains

    function gen_classic(DNA,n, k) result(chip)
        implicit none
        integer(kind = 4)::n,k,i,j
        character(len = 1),dimension(0:n) :: DNA
        character(len = 1), dimension(0:n-k,0:k-1) :: chip
            
        


        
        do,i=0,n-k
            do,j=0,k-1
                chip(i,j) = DNA(i+j)            
            end do
        end do


    end function
    

    subroutine pirnt_chip(chip,n,k)
        integer(kind=4)::n,k,i,j
        character(len = 1), dimension(0:n-k,0:k) :: chip

        do,i=0,n-k
            do,j=0,k-1
                write(*,"(a1)",advance="no") chip(i,j)
            end do
            write(*,"(a1)",advance="no") " "
        end do
    

    end subroutine
    

end module
