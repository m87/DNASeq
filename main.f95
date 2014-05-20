program DNASeq
    use io
    implicit none 
    integer(kind =4) :: n,k,i
    character(len=32) :: file
    character(len = 1), dimension(:,:), allocatable :: chip
    character(len = 1), dimension(:,:), allocatable :: chipn
    character(len=1), dimension(:), allocatable:: DNA
    real t1,t2

    call getarg(1,file)

    open(unit=99,file=file ,status="old", action ="read")
    read(99,*) n
    
    read(99,*) k
    
    allocate(DNA(0:n))
    allocate(chip(0:n-k+1,0:k))
    allocate(chipn(0:n-2*k+1,0:2*k-1))

    do,i=0,n+1
    read(99,"(a1)",advance="no") DNA(i)
    end do

   
    write(*,*) "--------------"
    

    call CPU_TIME(t1)
    chip= gen_classic(DNA,n,k)
    chipn= gen_nclassic(DNA,n,k)

    call CPU_TIME(t2)

    
    call pirnt_chip(chip,n,n-k,k-1)
    call pirnt_chip(chipn,n,n-2*k+1,2*k-1)
    
    write(*,*) "--------------"
    write(*,"(F6.4, a1)") t2-t1,"s"
    
    deallocate(DNA)
    deallocate(chip)
    deallocate(chipn)

end program 
