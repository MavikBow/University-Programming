! we work with the matrixA
! the initial equation is Ax = f
! but the Seidel method is iterational for the equation of x = Bx + b
! so we make into this format by doing b = f and B = (I - A)
! I name the "I" matrix as "E" for consistency with my own notes
! Note that the resulting B has to have a cubic norm of less than 1 for the method to work
!
! r is the discrepancy we get after counting x

program seidel
    implicit none

    integer, parameter :: dp = selected_real_kind(15, 307)
    real(kind=dp), dimension(:,:), allocatable :: matrixA, matrixE, matrixB
    real(kind=dp), dimension(:), allocatable :: f, x1, x2, b, r 
    real(kind=dp) :: detA
    real(kind=dp), parameter :: Eps = 0.00001_dp
    integer :: inputFile, matrixSize
    integer :: i, j, iteration_count

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

    ! method starts
    b = f
    x1 = b
    iteration_count = 0
    do
        iteration_count = iteration_count + 1
        call iteration(x1, x2, matrixB, b)
        if (maxval(abs(x1 - x2)) <= Eps) exit
        
        iteration_count = iteration_count + 1
        call iteration(x2, x1, matrixB, b)
        if (maxval(abs(x1 - x2)) <= Eps) exit
    end do

    print '(A)', 'the number of iterations'
    print *, iteration_count 

    ! method ends
    ! calculating the discrepancy 

    print '(A)', 'the approximate x'

    if (MOD(iteration_count, 2) == 1) then ! x2 is the last value
        r = matmul(matrixA, x2) - f
        print '(F14.5)', x2
    else ! x1 is the last value
        r = matmul(matrixA, x1) - f
        print '(F14.5)', x1
    end if

    print '(A)', 'vector r'
    print '(ES11.4)', r


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
    integer :: i, n

    max_norm = 0
    n = size(A, 1) ! number of rows

    do i = 1, n
        norm = sum(abs(A(i,:)))
        if (norm >= max_norm) then
            max_norm = norm
        end if
    end do
    end function

    subroutine iteration(x1, x2, mB, b)
    real(kind=dp), dimension(:,:), intent(in) :: mB
    real(kind=dp), dimension(:), intent(inout) :: x1, x2
    real(kind=dp), dimension(:), intent(in) :: b
    integer :: i, n

    n = size(mB,1)

    x2(1) = dot_product(mB(1,:),x1) + b(1)
    do i = 2, n
        x2(i) = dot_product(mB(i,:i-1), x2(:i-1)) + dot_product(mB(i,i:), x1(i:)) + b(i)
    end do
    end subroutine

end program seidel
