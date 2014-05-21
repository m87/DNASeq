program DNASeq
    use io
    implicit none 
    integer(kind =4) :: n,k,i
    character(len = 1), dimension(:,:), allocatable :: chip
    character(len=1), dimension(:), allocatable:: DNA
    real t1,t2

    read(*,*) n
    read(*,*) k
    allocate(DNA(0:n))
    allocate(chip(0:n-k+1,0:k))

    do,i=0,n+1
    read(*,"(a1)",advance="no") DNA(i)
    end do
    
    call CPU_TIME(t1)
    chip= gen_classic(DNA,n,k)


    call CPU_TIME(t2)

    write(*,*) T2
    
    call pirnt_chip(chip,n,k)



end program 
