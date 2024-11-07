! we work with the matrixA
! r is the discrepancy we get after counting x

program gauss
    implicit none

    integer, parameter :: dp = selected_real_kind(15, 307)
    real(kind=dp), dimension(:,:), allocatable :: matrixA, matrixE, matrixB
    real(kind=dp), dimension(:), allocatable :: f, x1, x2, b, r 
    real(kind=dp) :: detA
    integer :: inputFile, matrixSize
    integer :: i, j

    inputFile = 1
    detA = 1_dp
    open(unit=inputFile, file='input.txt',status='unknown', action='read')
    read(inputFile, *) matrixSize

    allocate(matrixA(matrixSize,matrixSize))
    allocate(matrixE(matrixSize,matrixSize))
    allocate(matrixB(matrixSize,matrixSize))
    allocate(f(matrixSize))
    allocate(x1(matrixSize))
    allocate(x2(matrixSize))
    allocate(r(matrixSize))
    allocate(b(matrixSize))
   
    read(inputFile, *) (matrixA(i,:), i = 1, matrixSize)
    read(inputFile, *) f

    print '(A)', 'inital matrix A'       
    do i = 1, matrixSize 
        print '(5(F14.5, 1X))', (matrixA(i,j), j = 1, matrixSize)
    end do

    matrixE = 0_dp
    do i = 1, matrixSize
        matrixE(i,i) = 1_dp
    end do

    print '(A)', 'inital matrix E'       
    do i = 1, matrixSize 
        print '(5(F14.5, 1X))', (matrixE(i,j), j = 1, matrixSize)
    end do

    matrixB = matrixE - matrixA
    print '(A)', 'inital matrix B'       
    do i = 1, matrixSize 
        print '(5(F14.5, 1X))', (matrixB(i,j), j = 1, matrixSize)
    end do

    print '(A)', '=============='

    print '(A)', 'cubic norm of matrix B'
    print '(F14.5)', cubic_norm(matrixB)


    close(inputFile) 

    deallocate(matrixA)
    deallocate(matrixE)
    deallocate(matrixB)
    deallocate(f)
    deallocate(x1)
    deallocate(x2)
    deallocate(r)
    deallocate(b)

contains
    function cubic_norm(A) result(max_norm)
    real(kind=dp), dimension(:,:), intent(in) :: A
    real(kind=dp) :: norm, max_norm
    integer :: i, j, n

    max_norm = 0
    n = size(A, 1) ! number of rows

    do i = 1, n
        norm = 0
        do j = 1, n
            norm = norm + abs(A(i,j))
        end do

        if (norm >= max_norm) then
            max_norm = norm
        end if
    end do

    end function
end program gauss
