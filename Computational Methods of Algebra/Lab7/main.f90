! we work with the matrixA
! we transform it into A^T * A, 'cause the task is
! to work with a symmentrical matrix
! we calculate its eigenvectors as columns of matrixX
!
! Note: this one works only if the matrix has n-unique eigenvalues
! pass them as constants lower in the code

program Krylov_Lanczos_method
    implicit none

    integer, parameter :: dp = selected_real_kind(15, 307)
    real(kind=dp), dimension(:,:), allocatable :: matrixA, matrixC, matrixC_safe, matrixBeta, matrixX
    real(kind=dp), dimension(:), allocatable :: lambda_vec
    integer :: inputFile, matrixSize
    integer :: i, j

    inputFile = 1
    open(unit=inputFile, file='input.txt',status='unknown', action='read')
    read(inputFile, *) matrixSize

    allocate(matrixA(matrixSize,matrixSize))
    allocate(matrixC(matrixSize,matrixSize+1))
    allocate(matrixC_safe(matrixSize,matrixSize))
    allocate(matrixBeta(matrixSize,matrixSize))
    allocate(matrixX(matrixSize,matrixSize))
    allocate(lambda_vec(matrixSize))
   
    read(inputFile, *) (matrixA(i,:), i = 1, matrixSize)
    close(inputFile) 

    ! prep work

    matrixA = matmul(matrixA,transpose(matrixA))

    print '(A)', "inital matrix A'A"       
    do i = 1, matrixSize 
        print '(5(F14.8, 1X))', (matrixA(i,j), j = 1, matrixSize)
    end do

    lambda_vec = (/ &
    0.5138612525621694_dp, &
    0.3948379287198427_dp, &
    0.2682915737385599_dp, &
    0.1721659914498502_dp, &
    0.0857293535295782_dp /)

    ! method starts

    matrixC(:,matrixSize) = 0.0_dp
    matrixC(1,matrixSize) = 1.0_dp

    do i = matrixSize - 1, 1, -1
        matrixC(:,i) = matmul(matrixA,matrixC(:,i + 1))
    end do 
    matrixC(:, matrixSize + 1) = matmul(matrixA,matrixC(:,1))
    print '(A)', "initial matrix C"       
    do i = 1, matrixSize 
        print '(6(F14.8, 1X))', (matrixC(i,j), j = 1, matrixSize + 1)
    end do

    matrixC_safe = matrixC(:,:matrixSize)

    call forwardElimination(matrixC)
    call backSubstitution(matrixC)
    print '(A)', "gaussed matrix C"       
    do i = 1, matrixSize 
        print '(6(F14.8, 1X))', (matrixC(i,j), j = 1, matrixSize + 1)
    end do
    
    do concurrent (i = 1:matrixSize)
        matrixBeta(i,1) = 1.0_dp
        do j = 2, matrixSize
            matrixBeta(i,j) = matrixBeta(i,j-1) * lambda_vec(i) - matrixC(j-1,matrixSize + 1)
        end do
    end do
    print '(A)', "matrix of beta vectors (rows)"       
    do i = 1, matrixSize 
        print '(5(F14.8, 1X))', (matrixBeta(i,j), j = 1, matrixSize)
    end do

    matrixX = 0.0_dp
    do concurrent (i = 1:matrixSize)
        do j = 1, matrixSize
            matrixX(:,i) = matrixX(:,i) + matrixBeta(i,j) * matrixC_safe(:,j)
        end do
    end do
    print '(A)', "matrix eigenvectors matrixX (columns)"       
    do i = 1, matrixSize 
        print '(5(F14.8, 1X))', (matrixX(i,j), j = 1, matrixSize)
    end do

    ! method ends

    ! calculating the discrepancy 
    print '(A)', 'discrepancies'       
    do i = 1, matrixSize
         print '(ES11.4)', maxval(abs(matmul(matrixA,matrixX(:,i)) - lambda_vec(i) * matrixX(:,i)))
    end do

    deallocate(matrixA)
    deallocate(matrixC)
    deallocate(matrixC_safe)
    deallocate(matrixBeta)
    deallocate(matrixX)
    deallocate(lambda_vec)

contains

    ! the commented lines are the full gauss method
    ! the working ones only operate with the nessesary elements
    ! which saves time from O(n^3 + n^3) down to O((n^3)/2 + (n/2)^2)

   subroutine forwardElimination(A)
        real(kind=dp), dimension(:,:), intent(inout) :: A
        integer :: i, j, n

        n = size(A, 1) ! the number of rows

        do i = 1, n
            A(i, i + 1 :) = A(i, i + 1 :) / A(i,i)
            !A(i,:) = A(i,:) / A(i,i)
            do concurrent (j = i + 1 : n)
                A(j, i:) = A(j, i:) - A(j,i) * A(i, i:)
            !   A(j, :) = A(j, :) - A(j,i) * A(i, :)
            end do
        end do
   end subroutine

   subroutine backSubstitution(A)
        real(kind=dp), dimension(:,:), intent(inout) :: A
        integer :: j, n

        n = size(A, 1)

        do j = n, 1, -1
            A(1 : j - 1, n + 1) = A(1 : j - 1, n + 1) - A(1 : j - 1, j) * A(j,n + 1)
!           do concurrent (i = 1 : j - 1) 
!               !A(i,:) = A(i,:) - A(i,j) * A(j,:)
!           end do
        end do
   end subroutine
end program Krylov_Lanczos_method
