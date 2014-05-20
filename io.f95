module io
    public::gen_classic,gen_nclassic


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
    
    
    function gen_nclassic(DNA,n, k) result(chip)
        implicit none
        integer(kind = 4)::n,k,i,j
        character(len = 1),dimension(0:n) :: DNA
       
        character(len = 1), dimension(0:n-2*k+1,0:2*k-1) :: chip
        
        do,i=0,n-2*k+1
            do,j=0,k-1
                chip(i,j) = DNA(i+j)
            
            end do
        
            
            do,j=0,k-1
                chip(i,k-1+j) = 'x'
            
            end do

            chip(i,2*k-2) = DNA(i+2*k-2)
        end do


    end function   



    subroutine pirnt_chip(chip,n,a,b)
        integer(kind=4)::n,k,i,j,a,b
        character(len = 1), dimension(0:a,0:b) :: chip

        do,i=0,a
            do,j=0,b
                write(*,"(a1)",advance="no") chip(i,j)
            end do
            write(*,"(a1)",advance="no") " "
        end do
    

    write(*,*) ""
    end subroutine
    
  
 
end module
