! we work with the matrixA
! the initial equation is Ax = f
! but the method is iterational for the equation of x = Bx + b
! so we make into this format by doing b = f and B = (I - A)
! I name the "I" matrix as "E" for consistency with my own notes
! Note that the resulting B has to have a cubic norm of less than 1 for the method to work
!
! n is the number of iterations

program SoLE
    implicit none

    integer, parameter :: dp = selected_real_kind(15, 307)
    real(kind=dp), dimension(3,3) :: matrixA, matrixE, matrixB
    real(kind=dp), dimension(3) :: f, x0, x1, y 
    real(kind=dp) :: alpha, n_calculated
    real(kind=dp), parameter :: Eps = 0.0001_dp
    integer, parameter :: matrixSize = 3
    integer :: i, n_approximated, n_actual 

    ! initiating the variables
    matrixA = transpose(reshape([ &
        0.9_dp, 0.1_dp, 0.1_dp, & 
        0.2_dp, 1.1_dp, 0.2_dp, & 
        0.1_dp, 0.2_dp, 1.2_dp], shape(matrixA)))

    f = [1_dp, 1_dp, 0_dp]

    matrixE = 0_dp
    do i = 1, matrixSize
        matrixE(i,i) = 1_dp
    end do

    ! the algorithm starts

    matrixB = matrixE - matrixA
    y = f

    alpha = cubic_norm(matrixB)

    print '(A)', 'cubic norm of matrix B'       
    print '(F14.5)', alpha 

    x0 = 0_dp
    x1 = matmul(matrixB,x0) + y

    n_calculated = log(((1_dp - alpha) * Eps)/sum(abs(x0 -x1))) / log(alpha)
    print '(A)', 'the calculated number of iterations'       
    print '(F14.5)', n_calculated

    n_approximated = int(n_calculated) + 1
    print '(A)', 'the approximate number of iterations' 
    print *, n_approximated

    n_actual = 0
    do 
        x1 = matmul(matrixB,x0) + y
        n_actual = n_actual + 1
        if (sum(abs(x0-x1)) < Eps) exit
        x0 = x1
    end do

    print '(A)', 'the actual number of iterations'
    print *, n_actual

    print '(A)', 'the last iteration'
    print '(F14.5)', x1

contains
    function cubic_norm(A) result(max_norm)
    real(kind=dp), dimension(:,:), intent(in) :: A
    real(kind=dp) :: norm, max_norm
    integer :: i, n

    max_norm = 0_dp
    n = size(A, 1) ! number of rows

    do i = 1, n
        norm = sum(abs(A(i,:)))
        if (norm >= max_norm) then
            max_norm = norm
        end if
    end do
    end function
end program SoLE
