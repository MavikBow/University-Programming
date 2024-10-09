! basically the matrix we work with is matrixFull
! it looks like this: [A:f:E]
! while we are transforming the A part into E as per Gauss-Jordan method
! the f part turns into the x we search, and the E part becomes A^(-1)
!
! we need the -copy matrices to calculate and analyse the discrepancy afterwards
! r is the discrepancy we get after counting x, and R - after A^(-1)

program gauss
    implicit none

    integer, parameter :: dp = selected_real_kind(15, 307)
    real(kind=dp), dimension(:,:), allocatable :: matrixFull, matrixAcopy, matrixEcopy, matrixR
    real(kind=dp), dimension(:), allocatable :: f, r
    real(kind=dp) :: detA
    integer :: inputFile, matrixSize, swapCounter
    integer :: i, j

    inputFile = 1
    swapCounter = 0
    open(unit=inputFile, file='input.txt',status='unknown', action='read')
    read(inputFile, *) matrixSize

    allocate(matrixFull(matrixSize,2 * matrixSize + 1))
    allocate(matrixAcopy(matrixSize,matrixSize))
    allocate(matrixEcopy(matrixSize,matrixSize))
    allocate(matrixR(matrixSize,matrixSize))
    allocate(f(matrixSize))
    allocate(r(matrixSize))
   
    read(inputFile, *) (matrixAcopy(i,:), i = 1, matrixSize)
    read(inputFile, *) f

    matrixEcopy = 0_dp
    do i = 1, matrixSize
        matrixEcopy(i,i) = 1_dp
    end do
    matrixFull(:,: matrixSize) = matrixAcopy
    matrixFull(:,matrixSize + 1) = f
    matrixFull(:,matrixSize + 2 :) = matrixEcopy


    call swapRowsInOrder(matrixFull, swapCounter)
    call forwardElimination(matrixFull)

    if (mod(swapCounter, 2) == 0) then
        detA = 1_dp
    else
        detA = -1_dp
    end if

    do i = 1, matrixSize
        detA = detA * matrixFull(i,i)
    end do

    call backSubstitution(matrixFull)

    ! r = A * x - f
    r = matmul(matrixAcopy, matrixFull(:,matrixSize + 1)) - f

    ! R = E - A^(-1) * A
    matrixR = matrixEcopy - matmul(matrixFull(:,matrixSize + 2 :), matrixAcopy)


    print '(A, F14.5)', ' detA is ', detA
    print *, 'matrix R'
    do i = 1, size(matrixR, 1)
        print '(5(ES11.4, 1X))', (matrixR(i,j), j = 1, matrixSize)
    end do
    print *, 'vector r'
    print '(ES11.4)', r
    print *, 'matrix A^(-1)'
    do i = 1, size(matrixFull, 1)
        print '(5(F10.5, 1X))', (matrixFull(i,matrixSize + 1 + j), j = 1, matrixSize)
    end do
    print *, 'vector x'
    print '(F14.5)', matrixFull(:,matrixSize + 1)

    close(inputFile) 

    deallocate(matrixFull)
    deallocate(matrixAcopy)
    deallocate(matrixEcopy)
    deallocate(matrixR)
    deallocate(f)
    deallocate(r)

contains

    subroutine swapRowsInOrder(matrixFull, swapCounter)
        real(kind=dp), dimension(:,:), intent(inout) :: matrixFull
        integer, intent(inout) :: swapCounter
        real(kind=dp), dimension(:), allocatable :: tempArr
        integer :: i, j, tempInt(1)

        allocate(tempArr(size(matrixFull,2)))

        do i = 1, size(matrixFull, 1)
            tempInt = maxloc(matrixFull(i:,i))
            j = tempInt(1)
            if (j > i) then
                tempArr = matrixFull(i,:)
                matrixFull(i,:) = matrixFull(j,:)
                matrixFull(j,:) = tempArr

                swapCounter = swapCounter + (j - i)
            end if
        end do

        deallocate(tempArr)
   end subroutine

   subroutine forwardElimination(A)
        real(kind=dp), dimension(:,:), intent(inout) :: A
        integer :: i, j, n

        n = size(A, 1) ! the number of rows

        do i = 1, n
            A(i, i + 1 :) = A(i, i + 1 :) / A(i,i)
            do concurrent (j = i + 1 : n)
                A(j, i:) = A(j, i:) - A(j,i) * A(i, i:)
            end do
        end do
   end subroutine

   subroutine backSubstitution(A)
        real(kind=dp), dimension(:,:), intent(inout) :: A
        integer :: i, j, n

        n = size(A, 1)

        do j = n, 1, -1
            do concurrent (i = 1 : j - 1) 
                A(i, n + 1 :) = A(i, n + 1 :) - A(i,j) * A(j, n + 1 :)
            end do
        end do
   end subroutine

end program gauss
