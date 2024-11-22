! we work with the matrixA
! the initial equation is Ax = f
!
! r is the discrepancy we get after counting x

program SOR
    implicit none

    integer, parameter :: dp = selected_real_kind(15, 307)
    real(kind=dp), dimension(:,:), allocatable :: matrixA
    real(kind=dp), dimension(:), allocatable :: f, x1, x2, r
    real(kind=dp), parameter :: Eps = 0.00001_dp
    real(kind=dp) :: Omega, temp
    integer :: inputFile, matrixSize
    integer :: i, j, iteration_count

    inputFile = 1
    open(unit=inputFile, file='input.txt',status='unknown', action='read')
    read(inputFile, *) matrixSize

    allocate(matrixA(matrixSize,matrixSize))
    allocate(f(matrixSize))
    allocate(x1(matrixSize))
    allocate(x2(matrixSize))
    allocate(r(matrixSize))
   
    read(inputFile, *) (matrixA(i,:), i = 1, matrixSize)
    read(inputFile, *) f

    print '(A)', 'inital matrix A'       
    do i = 1, matrixSize 
        print '(5(F14.5, 1X))', (matrixA(i,j), j = 1, matrixSize)
    end do

    ! method starts

    x1 = f
    iteration_count = 0
    Omega = 0.5_dp
    do
        iteration_count = iteration_count + 1

        do i = 1, matrixSize
        temp = 0.0_dp
            do j = 1, i-1 
                temp = temp + matrixA(i,j) * x2(j)
            end do
            do j = i+1, matrixSize
                temp = temp + matrixA(i,j) * x1(j)
            end do
            x2(i) = x1(i) + Omega * ((f(i) - temp)/matrixA(i,i) - x1(i))
        end do

        if (maxval(abs(x1 - x2)) <= Eps) exit
        x1 = x2
    end do

    print '(A)', 'the number of iterations'
    print *, iteration_count 

    ! method ends
    ! calculating the discrepancy 

    print '(A)', 'the approximate x'

    r = matmul(matrixA, x2) - f
    print '(F14.5)', x2

    print '(A)', 'vector r'
    print '(ES11.4)', r


    close(inputFile) 

    deallocate(matrixA)
    deallocate(f)
    deallocate(x1)
    deallocate(x2)
    deallocate(r)

end program SOR
