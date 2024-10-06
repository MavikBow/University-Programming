! we work with the matrixA, make it tridiagonal before starting.
! (although it manually nullifies the non-tridiagonal elements).
! r is the discrepancy we get after counting x
!
! in the mathematical formulae the indexing starts with 0,
! but since it was a huge pain to do that in Fortran (yes, i tried)
! i have lifted the lower indecies in the formulae from 0 to 1 and from 1 to 2

program gauss
    implicit none

    integer, parameter :: dp = selected_real_kind(15, 307)
    real(kind=dp), dimension(:,:), allocatable :: matrixA
    real(kind=dp), dimension(:), allocatable :: f, x, r, eta, ksi
    real(kind=dp) :: detA
    integer :: inputFile, matrixSize
    integer :: i, j

    inputFile = 1
    detA = 1_dp
    open(unit=inputFile, file='input.txt',status='unknown', action='read')
    read(inputFile, *) matrixSize

    allocate(matrixA(matrixSize,matrixSize))
    allocate(f(matrixSize))
    allocate(x(matrixSize))
    allocate(r(matrixSize))
    allocate(ksi(matrixSize))
    allocate(eta(matrixSize))
   
    read(inputFile, *) (matrixA(i,:), i = 1, matrixSize)
    read(inputFile, *) f

    print '(A)', 'inital matrix A'       
    do i = 1, matrixSize 
        print '(5(F14.5, 1X))', (matrixA(i,j), j = 1, matrixSize)
    end do

    call nullifyNontriagonals(matrixA, matrixSize)

    print *
    print '(A)', 'tridiagonal matrix A'       
    do i = 1, matrixSize 
        print '(5(F14.5, 1X))', (matrixA(i,j), j = 1, matrixSize)
    end do

    call forwardElimination(matrixA, f, ksi, eta, detA, matrixSize)
    call backSubstitution(x, ksi, eta, matrixSize)

    print *
    print '(A)', 'vector x'
    print '(F14.5)', x

    ! r = A * x - f
    r = matmul(matrixA, x) - f
    print *
    print '(A)', 'vector r'
    print '(E14.4)', r


    close(inputFile) 

    deallocate(matrixA)
    deallocate(f)
    deallocate(x)
    deallocate(r)
    deallocate(ksi)
    deallocate(eta)

contains
    
    subroutine nullifyNontriagonals(M, n)
        real(kind=dp), dimension(:,:), intent(inout) :: M
        integer, intent(in) :: n
        integer :: i, j

        do i = 3, n
            do j = 1, i - 2
                M(i,j) = 0_dp
                M(j,i) = 0_dp
            end do
        end do
    end subroutine


    subroutine forwardElimination(M, f, ksi, eta, detA, n)
        real(kind=dp), dimension(:,:), intent(in) :: M
        real(kind=dp), dimension(:), intent(in) :: f
        real(kind=dp), dimension(:), intent(inout) :: ksi, eta
        real(kind=dp), intent(inout) :: detA
        integer, intent(in) :: n
        real(kind=dp) :: detI
        integer :: i

        detA = 1_dp

        ! careful here, the a(2) from the formulae will be at a(1) here, so accessing is done thusly: a(i-1)
        associate(a => [ (-M(i,i-1), i = 2, n) ])
        associate(b => [ (-M(i,i+1), i = 1, n-1) ])
        associate(c => [ (M(i,i), i = 1, n) ] )

        ksi(n) = a(n-1) / c(n)
        eta(n) = f(n) / c(n)

        do i = n - 1, 2, -1
            detI = c(i) - ksi(i+1) * b(i)
            detA = detA * detI

            ksi(i) = a(i-1) / detI ! vector ksi ends at index 2
            eta(i) = (f(i) + b(i) * eta(i+1)) / detI
        end do
            detI = c(1) - ksi(1+1) * b(1)
            detA = detA * detI
            eta(1) = (f(1) + b(1) * eta(1+1)) / detI

        end associate
        end associate
        end associate
    end subroutine

    subroutine backSubstitution(x, ksi, eta, n)
        real(kind=dp), dimension(:), intent(in) :: ksi, eta
        real(kind=dp), dimension(:), intent(inout) :: x
        integer, intent(in) :: n
        integer :: i

        x(1) = eta(1)

        do i = 1, n - 1
            x(i + 1) = ksi(i + 1) * x(i) + eta(i + 1)
        end do
    end subroutine
end program gauss
