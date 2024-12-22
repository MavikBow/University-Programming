! we work with the matrixA
! we transform it into A^T * A, 'cause the task is
! to work with a symmentrical matrix
! we calculate its minimal eigenvalue and its eigenvector
!
! Note: this one works only if the matrix symmetrical

program Power_iteration
    implicit none

    integer, parameter :: dp = selected_real_kind(15, 307)
    real(kind=dp), dimension(:,:), allocatable :: matrixA, matrixA_safe
    real(kind=dp), dimension(:), allocatable :: y_1, y_2
    real(kind=dp), parameter :: Eps = 1.0E-05_dp
    real(kind=dp) :: lambda_1, lambda_2
    integer :: inputFile, matrixSize, iteration_counter
    integer :: i, j

    inputFile = 1
    open(unit=inputFile, file='input.txt',status='unknown', action='read')
    read(inputFile, *) matrixSize

    allocate(matrixA(matrixSize,matrixSize * 2))
    allocate(matrixA_safe(matrixSize,matrixSize))
    allocate(y_1(matrixSize))
    allocate(y_2(matrixSize))
   
    read(inputFile, *) (matrixA(i,:matrixSize), i = 1, matrixSize)
    close(inputFile) 

    ! prep work

    matrixA(:,:matrixSize) = matmul(matrixA(:,:matrixSize),transpose(matrixA(:,:matrixSize)))
    matrixA_safe = matrixA(:,:matrixSize)
    matrixA(:,matrixSize+1:) = 0.0_dp
    do i = 1, matrixSize
        matrixA(i, matrixSize + i) = 1.0_dp
    end do

    print '(A)', "inital matrix A'A"       
    do i = 1, matrixSize 
        print '(10(F10.7, 1X))', (matrixA(i,j), j = 1, matrixSize * 2)
    end do

    ! method starts

    call forwardElimination(matrixA)
    call backSubstitution(matrixA)
    print '(A)', "gaussed matrix A'A"       
    do i = 1, matrixSize 
        print '(10(F10.7, 1X))', (matrixA(i,j), j = 1, matrixSize * 2)
    end do

    ! now matrix A^(-1) is at matrixA(:,matrixSize +1:)

    y_1 = 0.0_dp
    y_1(1) = 1.0_dp
    iteration_counter = 0
    lambda_1 = 1.0E+300_dp

    do
        iteration_counter = iteration_counter + 1
        y_2 = matmul(matrixA(:,matrixSize + 1 :), y_1)

        lambda_2 = dot_product(y_2, y_1) / dot_product(y_1, y_1)

        y_2 = y_2 / maxval(abs(y_2))

        if (abs(lambda_2 - lambda_1) <= Eps) exit

        y_1 = y_2
        lambda_1 = lambda_2

    end do
    print '(A)', "number of iterations"       
    print *, iteration_counter

    ! method ends

    lambda_1 = 1.0_dp / lambda_1

    print '(A)', 'the lambda'
    print '(F20.14)', lambda_1
    print '(A)', 'the eigenvector'
    print '(F20.14)', y_1

    ! calculating the discrepancy 

    print '(A)', 'discrepancy'       
    print '(ES11.4)', matmul(matrixA_safe,y_1) - lambda_1 * y_1

    deallocate(matrixA)
    deallocate(matrixA_safe)
    deallocate(y_1)
    deallocate(y_2)

contains

   subroutine forwardElimination(A)
        real(kind=dp), dimension(:,:), intent(inout) :: A
        integer :: i, j, n

        n = size(A, 1) ! the number of rows

        do i = 1, n
            A(i,:) = A(i,:) / A(i,i)
            do concurrent (j = i + 1 : n)
                A(j, :) = A(j, :) - A(j,i) * A(i, :)
            end do
        end do
   end subroutine

   subroutine backSubstitution(A)
        real(kind=dp), dimension(:,:), intent(inout) :: A
        integer :: j, n

        n = size(A, 1)

        do j = n, 1, -1
            do concurrent (i = 1 : j - 1) 
                 A(i,:) = A(i,:) - A(i,j) * A(j,:)
            end do
        end do
   end subroutine
end program Power_iteration
